/// @file
/// @author Jongkuk Lim <limjk@jmarple.ai>
/// @copyright 2023 J.Marple
/// @brief UDP communication

#include "communication/udp_communication.hpp"

#include <glog/logging.h>
#include <sys/socket.h>

namespace flexxlam {
UDPCommunication::UDPCommunication(bool is_server, const std::string &ip,
                                   uint16_t port)
    : is_server_(is_server), ip_(ip), port_(port) {
  if (is_server_) {
    listen_addr_ = &client_addr_;
  } else {
    listen_addr_ = &server_addr_;
  }
}

bool UDPCommunication::open_() {
  this->socket_fd_ = socket(AF_INET, SOCK_DGRAM, 0);
  if (this->socket_fd_ < 0) {
    LOG(ERROR) << "Failed to create socket";
    return false;
  }

  struct timeval socket_opt = {0, 100};
  int socket_opt_len = sizeof(socket_opt);
  setsockopt(this->socket_fd_, SOL_SOCKET, SO_RCVTIMEO, &socket_opt,
             socket_opt_len);

  memset(&server_addr_, 0, sizeof(server_addr_));
  memset(&client_addr_, 0, sizeof(client_addr_));

  server_addr_.sin_family = AF_INET;
  server_addr_.sin_port = htons(port_);
  server_addr_.sin_addr.s_addr =
      is_server_ ? INADDR_ANY : inet_addr(ip_.c_str());

  if (is_server_) {
    if (bind(this->socket_fd_, (const sockaddr *)&server_addr_,
             sizeof(server_addr_)) < 0) {
      LOG(ERROR) << "Failed to bind socket";
      return false;
    }
  }

  return true;
}

bool UDPCommunication::close_() {
  if (this->socket_fd_ >= 0) {
    close(this->socket_fd_);
    this->socket_fd_ = -1;
  }
  return true;
}

void UDPCommunication::run_() {
  uint8_t buffer[UDPCommunication::kMaxBufferSize];
  socklen_t len = sizeof(*listen_addr_);  // len is value/result

  while (this->is_running_ && listen_addr_ != nullptr) {
    int n =
        recvfrom(this->socket_fd_, buffer, UDPCommunication::kMaxBufferSize,
                 MSG_WAITALL, reinterpret_cast<sockaddr *>(listen_addr_), &len);
    if (n < 0) {
      // TODO(jeikeilim): Add heartbeat protocol to detect connection loss
      std::this_thread::sleep_for(std::chrono::milliseconds(1));
      continue;
    }

    if (this->callback_ != nullptr) {
      std::vector<uint8_t> data(buffer, buffer + n);
      this->callback_(data);
    }
  }
}

void UDPCommunication::run() {
  if (!this->open_()) {
    LOG(ERROR) << "Failed to open socket";
    return;
  }

  this->is_running_ = true;
  this->run_thread_ = std::thread(&UDPCommunication::run_, this);
}

void UDPCommunication::stop() {
  this->is_running_ = false;
  if (this->run_thread_.joinable()) {
    this->run_thread_.join();
  }
  this->close_();
}

void UDPCommunication::write(std::vector<uint8_t> data) {
  if (this->socket_fd_ < 0) {
    LOG(ERROR) << "Socket is not opened";
    return;
  }

  sendto(this->socket_fd_, data.data(), data.size(), MSG_CONFIRM,
         (const sockaddr *)listen_addr_, sizeof(*listen_addr_));
}

}  // namespace flexxlam
