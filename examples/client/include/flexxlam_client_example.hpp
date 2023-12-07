/// @file
/// @author Jongkuk Lim <limjk@jmarple.ai>
/// @copyright 2023 J.Marple
/// @brief FlexXlam ROS Driver Client

#ifndef SLAMBOX_SDK_EXAMPLES_CLIENT_INCLUDE_FLEXXLAM_CLIENT_EXAMPLE_HPP_
#define SLAMBOX_SDK_EXAMPLES_CLIENT_INCLUDE_FLEXXLAM_CLIENT_EXAMPLE_HPP_

#include <memory>
#include <string>
#include <vector>

#include <sbox/communication/flexxlam_parser.hpp>
#include <sbox/communication/udp_communication.hpp>
#include <sbox/flexxlam_msgs/Odometry.hpp>
#include <sbox/flexxlam_msgs/PointCloud2.hpp>

/// @brief FlexXlam Driver Client
class FlexXlamClientExample : public sbox::ParsedMessageInterface {
 public:
  /// @brief Constructor
  /// @param nh ROS NodeHandle
  /// @param pnh ROS Private NodeHandle
  FlexXlamClientExample();

  /// @brief Destructor
  ~FlexXlamClientExample();

 private:
  /// @brief Callback function for odometry message
  /// @param odom Odometry message
  ///
  /// This function is called when odometry message is received.
  void on_push_odometry(const sbox_msgs::Odometry &odom) override;

  /// @brief Callback function for pointcloud message
  /// @param pointcloud Pointcloud message
  /// @details This function is called when pointcloud message is received.
  void on_push_pointcloud(const sbox_msgs::PointCloud2 &pointcloud) override;

  /// @brief UDP port number
  int udp_port_;

  /// @brief UDP IP address
  std::string udp_ip_;

  /// @brief Parser for UDP communication
  sbox::FlexXlamParser udp_parser_;

  /// @brief UDP communication
  std::unique_ptr<sbox::UDPCommunication> udp_communication_ = nullptr;
};

#endif  // SLAMBOX_SDK_EXAMPLES_CLIENT_INCLUDE_FLEXXLAM_CLIENT_EXAMPLE_HPP_
