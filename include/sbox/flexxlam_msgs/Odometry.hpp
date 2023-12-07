/// @file
/// @author Jongkuk Lim <limjk@jmarple.ai>
/// @copyright 2023 J.Marple
/// @brief Equivalent message of nav_msgs/Odometry in ROS

#ifndef SLAMBOX_SDK_INCLUDE_SBOX_FLEXXLAM_MSGS_ODOMETRY_HPP_
#define SLAMBOX_SDK_INCLUDE_SBOX_FLEXXLAM_MSGS_ODOMETRY_HPP_

#include <array>
#include <cstdint>
#include <vector>

/// @brief FlexXlam Messages
namespace sbox_msgs {

/// @brief Odometry message that is equivalent to nav_msgs/Odometry in ROS
struct Odometry {
  /// @brief Odometry default empty constructor
  Odometry() {}

  /// @brief Odometry constructor from payload bytes.
  /// @param bytes byte array of payload
  explicit Odometry(const std::vector<uint8_t> &bytes);

  /// Timestamp in seconds
  uint32_t timestamp_sec;
  /// Timestamp in nanoseconds
  uint32_t timestamp_nsec;

  /// Pose of odometry
  struct Pose {
    /// Position of odometry
    struct Position {
      /// Position x
      float x;
      /// Position y
      float y;
      /// Position z
      float z;
    }
    /// Position of odometry
    position;

    /// Orientation of odometry
    struct Orientation {
      /// Quaternion x
      float x;
      /// Quaternion y
      float y;
      /// Quaternion z
      float z;
      /// Quaternion w
      float w;
    }
    /// Orientation of odometry
    orientation;

    /// Covariance of pose
    std::array<float, 36> covariance;
  }
  /// Pose of odometry
  pose;

  /// Twist of odometry
  struct Twist {
    /// Linear velocity of odometry
    struct Linear {
      /// Linear velocity x
      float x;
      /// Linear velocity y
      float y;
      /// Linear velocity z
      float z;
    }
    /// Linear velocity of odometry
    linear;

    /// Angular velocity of odometry
    struct Angular {
      /// Angular velocity x
      float x;
      /// Angular velocity y
      float y;
      /// Angular velocity z
      float z;
    }
    /// Angular velocity of odometry
    angular;

    /// Covariance of twist
    std::array<float, 36> covariance;
  }
  /// Twist of odometry
  twist;
};

/// @brief Serialize Odometry message
/// @param odom Odometry message
/// @return serialized bytes
std::vector<uint8_t> serialize(const Odometry &odom);

}  // namespace sbox_msgs

#endif  // SLAMBOX_SDK_INCLUDE_SBOX_FLEXXLAM_MSGS_ODOMETRY_HPP_
