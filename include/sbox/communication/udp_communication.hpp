/// @file
/// @author Jongkuk Lim <limjk@jmarple.ai>
/// @copyright 2023 J.Marple
/// @brief UDP communication

#ifndef SLAMBOX_SDK_INCLUDE_SBOX_COMMUNICATION_UDP_COMMUNICATION_HPP_
#define SLAMBOX_SDK_INCLUDE_SBOX_COMMUNICATION_UDP_COMMUNICATION_HPP_

#include <arpa/inet.h>

#include <functional>
#include <string>
#include <thread>  // NOLINT
#include <vector>

namespace flexxlam {

/// @brief UDP communication
class UDPCommunication {
  /// @brief Maximum buffer size for UDP communication
  static constexpr size_t kMaxBufferSize = 102400;

 public:
  /// @brief UDP communication constructor
  /// @param is_server server flag
  /// @param ip IP address
  /// @param port port number
  UDPCommunication(bool is_server, const std::string &ip, uint16_t port);

  /// @brief Set callback function for UDP Communication
  /// @param callback callback function
  /// @details This function sets callback function for UDP communication.
  /// Once data is received from UDP, callback function is called.
  /// @note Callback function should be set before calling `run()`.
  void set_callback(std::function<void(std::vector<uint8_t>)> callback) {
    this->callback_ = callback;
  }

  /// @brief Set callback function for UDP Communication
  /// @param fp callback function
  /// @param obj object of callback function
  /// @details This function sets callback function for UDP communication.
  /// Once data is received from UDP, callback function is called.
  /// @note Callback function should be set before calling `run()`.
  template <class M, class T>
  void set_callback(void (T::*fp)(M), T *obj) {
    this->callback_ = std::bind(fp, obj, std::placeholders::_1);
  }

  /// @brief Start UDP communication thread
  /// Once this function is called, UDP communication thread is started in
  /// the background and listens to the UDP port.
  void run();

  /// @brief Stop UDP communication thread
  void stop();

  /// @brief Write bytes to UDP
  /// @param bytes bytes to write
  void write(std::vector<uint8_t> bytes);

  /// @brief Check if UDP socket is open
  /// @return true if UDP socket is open
  bool is_socket_open() { return this->socket_fd_ >= 0; }

  /// @brief Check if UDP communication thread is running
  /// @return true if UDP communication thread is running
  bool is_running() { return this->is_running_; }

 private:
  /// @brief Open serial port
  /// @return true if serial port is opened successfully
  bool open_();

  /// @brief Close serial port
  /// @return true if serial port is closed successfully
  bool close_();

  /// @brief Serial communication thread
  void run_();

  /// @brief Server flag
  /// @details If this flag is true, UDP communication is server mode.
  bool is_server_;

  /// @brief IP address of server
  std::string ip_;

  /// @brief Port number
  uint16_t port_;

  /// @brief Server address structure for socket communication
  sockaddr_in server_addr_;

  /// @brief Client address structure for socket communication
  sockaddr_in client_addr_;

  /// @brief Pointer of listening address structure for socket communication
  /// @details It's either server_addr_ or client_addr_.
  sockaddr_in *listen_addr_ = nullptr;

  /// @brief Socket file descriptor used for socket communication
  int socket_fd_ = -1;

  /// @brief Serial communication thread running state
  bool is_running_ = false;

  /// @brief Serial communication thread
  std::thread run_thread_;

  /// @brief Callback function for serial communication
  std::function<void(std::vector<uint8_t>)> callback_ = nullptr;
};
}  // namespace flexxlam

#endif  // SLAMBOX_SDK_INCLUDE_SBOX_COMMUNICATION_UDP_COMMUNICATION_HPP_
