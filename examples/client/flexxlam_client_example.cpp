/// @file
/// @author Jongkuk Lim <limjk@jmarple.ai>
/// @copyright 2023 J.Marple
/// @brief FlexXlam ROS Driver Client

#include "include/flexxlam_client_example.hpp"

#include <glog/logging.h>
#include <memory>

#include <sbox/protocol/push/push_pointcloud_protocol.hpp>

FlexXlamClientExample::FlexXlamClientExample()
    : udp_parser_(131070), udp_ip_("127.0.0.1"), udp_port_(21580) {
  udp_communication_ =
      std::make_unique<sbox::UDPCommunication>(false, udp_ip_, udp_port_);
  udp_parser_.add_parsed_message_callback(this);
  udp_communication_->set_callback(&sbox::SBoxParser::parse, &udp_parser_);
  udp_communication_->run();
  udp_communication_->write({0x01, 0x02, 0x03, 0x04, 0x05});
}

FlexXlamClientExample::~FlexXlamClientExample() {}

void FlexXlamClientExample::on_push_odometry(const sbox_msgs::Odometry &odom) {
  LOG(INFO) << "[odom] x: " << odom.pose.position.x
            << ", y: " << odom.pose.position.y
            << ", z: " << odom.pose.position.z;
}

void FlexXlamClientExample::on_push_pointcloud(
    const sbox_msgs::PointCloud2 &pointcloud) {
  LOG(INFO) << "pointcloud: " << pointcloud.data.size();
  sbox::PushPointCloudProtocol protocol(pointcloud,
                                        /*compress_payload=*/true);
  std::vector<uint8_t> bytes = protocol.encapsulate();
  LOG(INFO) << "bytes: " << bytes.size();
}
