/// @file
/// @author Jongkuk Lim <limjk@jmarple.ai>
/// @copyright 2023 J.Marple
/// @brief Equivalent message of sensor_msgs/PointCloud2 in ROS

#ifndef SLAMBOX_SDK_INCLUDE_SBOX_SBOX_MSGS_POINTCLOUD2_HPP_
#define SLAMBOX_SDK_INCLUDE_SBOX_SBOX_MSGS_POINTCLOUD2_HPP_

#include <cstdint>
#include <string>
#include <vector>

namespace sbox_msgs {

/// @brief Point field description
/// Please refer to
/// https://docs.ros.org/en/melodic/api/sensor_msgs/html/msg/PointField.html
struct PointField {
  /// Name of the field
  std::string name;
  /// Offset value
  uint32_t offset;
  /// Datatype
  uint8_t datatype;
  /// Number of elements
  uint32_t count;
};

/// @brief PointCloud2 message that is equivalent to sensor_msgs/PointCloud2 in
/// ROS Please refer to
/// https://docs.ros.org/en/melodic/api/sensor_msgs/html/msg/PointCloud2.html
struct PointCloud2 {
  /// @brief PointCloud2 default empty constructor
  PointCloud2() {}

  /// @brief PointCloud2 constructor from payload bytes.
  /// @param bytes byte array of payload
  explicit PointCloud2(const std::vector<uint8_t> &bytes);

  /// Timestamp in seconds
  uint32_t timestamp_sec;

  /// Timestamp in nano seconds
  uint32_t timestamp_nsec;

  /// Frame id
  std::string frame_id;

  /// Height of pointcloud
  uint32_t height;

  /// Width of pointcloud
  uint32_t width;

  /// Description of fields
  std::vector<PointField> fields;

  /// Is big endian
  bool is_bigendian;

  /// Length of point in bytes
  uint32_t point_step;

  /// Length of row in bytes
  uint32_t row_step;

  /// Point data, its size is `row_step * height`
  std::vector<uint8_t> data;

  /// True if there are no invalid points
  bool is_dense;
};

/// @brief Serialize PointCloud2 message
/// @param pointcloud PointCloud2 message
/// @param compress if true, then compress payload
/// @return serialized byte array
std::vector<uint8_t> serialize(const PointCloud2 &pointcloud,
                               bool compress = false);

}  // namespace sbox_msgs

#endif  // SLAMBOX_SDK_INCLUDE_SBOX_SBOX_MSGS_POINTCLOUD2_HPP_
