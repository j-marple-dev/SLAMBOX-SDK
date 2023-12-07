/// @file
/// @author Jongkuk Lim <limjk@jmarple.ai>
/// @copyright 2023 J.Marple
/// @brief Equivalent message of nav_msgs/Odometry in ROS

#include "sbox/sbox_msgs/Odometry.hpp"

#include <cstring>

#include "sbox/utils/to_bytes.hpp"

namespace sbox_msgs {

using sbox::from_bytes::to_float;
using sbox::from_bytes::to_int;

using sbox::to_bytes::four;

Odometry::Odometry(const std::vector<uint8_t> &bytes) {
  this->timestamp_sec =
      to_int(vector<uint8_t>(bytes.begin() + 0, bytes.begin() + 4));
  this->timestamp_nsec =
      to_int(vector<uint8_t>(bytes.begin() + 4, bytes.begin() + 8));

  this->pose.position.x = to_float(bytes, 8);
  this->pose.position.y = to_float(bytes, 12);
  this->pose.position.z = to_float(bytes, 16);
  this->pose.orientation.x = to_float(bytes, 20);
  this->pose.orientation.y = to_float(bytes, 24);
  this->pose.orientation.z = to_float(bytes, 28);
  this->pose.orientation.w = to_float(bytes, 32);

  for (int i = 0; i < 36; i++) {
    this->pose.covariance[i] = to_float(bytes, 36 + i * 4);
  }
  this->twist.linear.x = to_float(bytes, 180);
  this->twist.linear.y = to_float(bytes, 184);
  this->twist.linear.z = to_float(bytes, 188);
  this->twist.angular.x = to_float(bytes, 192);
  this->twist.angular.y = to_float(bytes, 196);
  this->twist.angular.z = to_float(bytes, 200);
  for (int i = 0; i < 36; i++) {
    this->twist.covariance[i] = to_float(bytes, 204 + i * 4);
  }
}

std::vector<uint8_t> serialize(const Odometry &odom) {
  std::vector<float> msgs_to_bytes(85);
  msgs_to_bytes[0] = odom.pose.position.x;
  msgs_to_bytes[1] = odom.pose.position.y;
  msgs_to_bytes[2] = odom.pose.position.z;
  msgs_to_bytes[3] = odom.pose.orientation.x;
  msgs_to_bytes[4] = odom.pose.orientation.y;
  msgs_to_bytes[5] = odom.pose.orientation.z;
  msgs_to_bytes[6] = odom.pose.orientation.w;
  std::memcpy(msgs_to_bytes.data() + 7, odom.pose.covariance.cbegin(),
              36 * sizeof(float));
  msgs_to_bytes[43] = odom.twist.linear.x;
  msgs_to_bytes[44] = odom.twist.linear.y;
  msgs_to_bytes[45] = odom.twist.linear.z;
  msgs_to_bytes[46] = odom.twist.angular.x;
  msgs_to_bytes[47] = odom.twist.angular.y;
  msgs_to_bytes[48] = odom.twist.angular.z;
  std::memcpy(msgs_to_bytes.data() + 49, odom.twist.covariance.cbegin(),
              36 * sizeof(float));

  std::vector<uint8_t> bytes = four(msgs_to_bytes);

  vector<uint8_t> secs = four(odom.timestamp_sec);
  vector<uint8_t> nsecs = four(odom.timestamp_nsec);

  bytes.insert(bytes.begin(), nsecs.begin(), nsecs.end());
  bytes.insert(bytes.begin(), secs.begin(), secs.end());

  return bytes;
}

}  // namespace sbox_msgs
