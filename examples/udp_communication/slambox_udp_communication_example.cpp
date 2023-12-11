/// @file
/// @author Jongkuk Lim <limjk@jmarple.ai>
/// @copyright 2023 J.Marple
/// @brief SLAMBOX UDP Communication example

#include <glog/logging.h>

#include <sbox/communication/sbox_parser.hpp>
#include <sbox/communication/udp_communication.hpp>
#include <sbox/protocol/acknowledge/ping_protocol.hpp>

#include <sbox/sbox_msgs/Odometry.hpp>
#include <sbox/sbox_msgs/PointCloud2.hpp>

class SBoxUdpClient : public sbox::ParsedMessageInterface {
 public:
  SBoxUdpClient(const std::string &udp_addr, const int &udp_port) {
    this->udp_communication_ =
        std::make_shared<sbox::UDPCommunication>(false, udp_addr, udp_port);
    this->udp_communication_->set_callback(&sbox::SBoxParser::parse,
                                           &this->sbox_parser_);
    this->sbox_parser_.add_parsed_message_callback(this);

    this->udp_communication_->run();

    // This should be sent to let the SLAMBOX know that the client is connected.
    // Otherwise, the SLAMBOX will not send any data.
    this->udp_communication_->write(sbox::PingProtocol().encapsulate());
  }

  void on_push_odometry(const sbox_msgs::Odometry &odometry) override {
    this->odom = odometry;

    LOG(INFO) << "[odom] x: " << this->odom.pose.position.x
              << ", y: " << this->odom.pose.position.y
              << ", z: " << this->odom.pose.position.z;
  }

  void on_push_pointcloud(const sbox_msgs::PointCloud2 &pointcloud2) override {
    this->pointcloud = pointcloud2;

    LOG(INFO) << "[pointcloud] timestamp: "
              << this->pointcloud.timestamp_sec +
                     this->pointcloud.timestamp_nsec * 1e-9
              << ", size: " << this->pointcloud.data.size();
  }

  sbox_msgs::Odometry odom;
  sbox_msgs::PointCloud2 pointcloud;

 private:
  std::shared_ptr<sbox::UDPCommunication> udp_communication_;
  sbox::SBoxParser sbox_parser_;
};

/// @brief Main function for SLAMBOX Serial Communication
/// @param argc Number of arguments
/// @param argv arguments
///
/// @return 0
int main(int argc, char **argv) {
  FLAGS_stderrthreshold = google::INFO;
  FLAGS_colorlogtostderr = true;
  google::InitGoogleLogging(argv[0]);

  std::string udp_addr = "192.168.101.101";
  int udp_port = 21580;

  if (argc > 1) {
    udp_addr = argv[1];
  }
  if (argc > 2) {
    udp_port = std::stoi(argv[2]);
  }

  SBoxUdpClient sbox_udp_client(udp_addr, udp_port);

  while (true) {
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }
}
