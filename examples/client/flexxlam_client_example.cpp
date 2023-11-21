/// @file
/// @author Jongkuk Lim <limjk@jmarple.ai>
/// @copyright 2023 J.Marple
/// @brief FlexXlam ROS Driver Client

#include "include/flexxlam_client_example.hpp"

#include <memory>

#include <communication/serial_communication.hpp>
#include <protocol/base_protocol.hpp>
#include <protocol/command/command_save_pcd_protocol.hpp>
#include <protocol/push/push_pointcloud_protocol.hpp>
#include <protocol/request/request_ethernet_communication_config.hpp>
#include <protocol/request/request_mavlink_communication_config.hpp>
#include <protocol/request/request_serial_communication_config.hpp>

namespace flexxlam {

FlexXlamClientExample::FlexXlamClientExample()
    : udp_parser_(131070), udp_ip_("127.0.0.1"), udp_port_(21580) {
  udp_communication_ =
      std::make_unique<UDPCommunication>(false, udp_ip_, udp_port_);
  udp_parser_.add_parsed_message_callback(this);
  udp_communication_->set_callback(&FlexXlamParser::parse, &udp_parser_);
  udp_communication_->run();
  udp_communication_->write({0x01, 0x02, 0x03, 0x04, 0x05});
}

FlexXlamClientExample::~FlexXlamClientExample() {}

void FlexXlamClientExample::on_get_odometry(
    const flexxlam_msgs::Odometry &odom) {
  LOG(INFO) << "[odom] x: " << odom.pose.position.x
            << ", y: " << odom.pose.position.y
            << ", z: " << odom.pose.position.z;
}

void FlexXlamClientExample::on_get_pointcloud(
    const flexxlam_msgs::PointCloud2 &pointcloud) {
  LOG(INFO) << "pointcloud: " << pointcloud.data.size();
  flexxlam::PushPointCloudProtocol protocol(pointcloud,
                                            /*compress_payload=*/true);
  std::vector<uint8_t> bytes = protocol.encapsulate();
  LOG(INFO) << "bytes: " << bytes.size();
}

}  // namespace flexxlam
