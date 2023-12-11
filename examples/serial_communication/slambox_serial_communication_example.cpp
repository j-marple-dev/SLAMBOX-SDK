/// @file
/// @author Jongkuk Lim <limjk@jmarple.ai>
/// @copyright 2023 J.Marple
/// @brief SLAMBOX Serial Communication example

#include <glog/logging.h>

#include <sbox/communication/sbox_parser.hpp>
#include <sbox/communication/serial_communication.hpp>
#include <sbox/protocol/acknowledge/ping_protocol.hpp>

#include <sbox/sbox_msgs/Odometry.hpp>
#include <sbox/sbox_msgs/PointCloud2.hpp>

struct ParsedInterface : public sbox::ParsedMessageInterface {
  void on_push_odometry(const sbox_msgs::Odometry &odometry) override {
    this->odom = odometry;
  }

  void on_push_pointcloud(const sbox_msgs::PointCloud2 &pointcloud2) override {
    this->pointcloud = pointcloud2;
  }

  sbox_msgs::Odometry odom;
  sbox_msgs::PointCloud2 pointcloud;
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

  std::string port_name = "/dev/ttyUSB1";
  int baudrate = 921600;

  if (argc > 1) {
    port_name = argv[1];
  }
  if (argc > 2) {
    baudrate = std::stoi(argv[2]);
  }

  sbox::SerialCommunication serial_communication(port_name, baudrate);
  sbox::SBoxParser sbox_parser;
  ParsedInterface parsed_interface;

  sbox_parser.add_parsed_message_callback(&parsed_interface);
  serial_communication.set_callback(&sbox::SBoxParser::parse, &sbox_parser);

  serial_communication.run();

  // This should be sent to let the SLAMBOX know that the client is connected.
  // Otherwise, the SLAMBOX will not send any data.
  serial_communication.set_baudrate(115200);
  serial_communication.write(sbox::PingProtocol().encapsulate());
  serial_communication.set_baudrate(baudrate);

  while (true) {
    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    LOG(INFO) << "[odom] x: " << parsed_interface.odom.pose.position.x
              << ", y: " << parsed_interface.odom.pose.position.y
              << ", z: " << parsed_interface.odom.pose.position.z
              << " // [pointcloud] timestamp: "
              << parsed_interface.pointcloud.timestamp_sec +
                     parsed_interface.pointcloud.timestamp_nsec * 1e-9
              << ", size: " << parsed_interface.pointcloud.data.size();
  }

  return 0;
}
