/// @file
/// @author Jongkuk Lim <limjk@jmarple.ai>
/// @copyright 2023 J.Marple
/// @brief FlexXlam ROS Driver Client

#ifndef FLEXXLAM_SDK_EXAMPLES_CLIENT_INCLUDE_FLEXXLAM_CLIENT_EXAMPLE_HPP_
#define FLEXXLAM_SDK_EXAMPLES_CLIENT_INCLUDE_FLEXXLAM_CLIENT_EXAMPLE_HPP_

#include <memory>
#include <string>
#include <vector>

#include <sbox/communication/flexxlam_parser.hpp>
#include <sbox/communication/udp_communication.hpp>
#include <sbox/flexxlam_msgs/Odometry.hpp>
#include <sbox/flexxlam_msgs/PointCloud2.hpp>

namespace flexxlam {

/// @brief FlexXlam Driver Client
class FlexXlamClientExample : public ParsedMessageInterface {
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
  void on_push_odometry(const flexxlam_msgs::Odometry &odom) override;

  /// @brief Callback function for pointcloud message
  /// @param pointcloud Pointcloud message
  /// @details This function is called when pointcloud message is received.
  void on_push_pointcloud(
      const flexxlam_msgs::PointCloud2 &pointcloud) override;

  /// @brief UDP port number
  int udp_port_;

  /// @brief UDP IP address
  std::string udp_ip_;

  /// @brief Parser for UDP communication
  flexxlam::FlexXlamParser udp_parser_;

  /// @brief UDP communication
  std::unique_ptr<UDPCommunication> udp_communication_ = nullptr;
};

}  // namespace flexxlam

#endif  // FLEXXLAM_SDK_EXAMPLES_CLIENT_INCLUDE_FLEXXLAM_CLIENT_EXAMPLE_HPP_
