/// @file
/// @author Jongkuk Lim <limjk@jmarple.ai>
/// @copyright 2023 J.Marple
/// @brief Equivalent message of sensor_msgs/PointCloud2 in ROS

#include "sbox/sbox_msgs/PointCloud2.hpp"

#include <memory>

#include "sbox/utils/compress_bytes.hpp"
#include "sbox/utils/to_bytes.hpp"

namespace sbox_msgs {

using sbox::from_bytes::to_int;
using sbox::from_bytes::to_string;

using sbox::to_bytes::four;
using sbox::to_bytes::from_string;

using sbox::compress_bytes;
using sbox::decompress_bytes;

using std::vector;

PointCloud2::PointCloud2(const std::vector<uint8_t> &bytes) {
  std::shared_ptr<vector<uint8_t>> bytes_ptr;
  bool compression_flag = bytes[0] == 0x01;
  uint32_t idx = 1;

  if (compression_flag) {
    uint32_t original_length =
        to_int(vector<uint8_t>(bytes.begin() + 1, bytes.begin() + 5));
    bytes_ptr = std::make_shared<vector<uint8_t>>(
        decompress_bytes(vector<uint8_t>(bytes.begin() + 5, bytes.end()),
                         /*original_size=*/original_length));
    idx = 0;
  } else {
    bytes_ptr = std::make_shared<vector<uint8_t>>(bytes);
  }

  const vector<uint8_t> &bytes_ = *bytes_ptr;

  this->timestamp_sec =
      to_int(vector<uint8_t>(bytes_.begin() + idx, bytes_.begin() + idx + 4));
  this->timestamp_nsec = to_int(
      vector<uint8_t>(bytes_.begin() + idx + 4, bytes_.begin() + idx + 8));
  idx += 8;

  this->frame_id = to_string(bytes_, idx);
  idx += this->frame_id.length() + 1;

  this->height =
      to_int(vector<uint8_t>(bytes_.begin() + idx, bytes_.begin() + idx + 4));
  this->width = to_int(
      vector<uint8_t>(bytes_.begin() + idx + 4, bytes_.begin() + idx + 8));
  idx += 8;

  uint8_t n_fields = bytes_[idx++];
  this->fields.resize(n_fields);
  for (uint8_t i = 0; i < n_fields; i++) {
    this->fields[i].name = to_string(bytes_, idx);
    idx += this->fields[i].name.length() + 1;
    this->fields[i].offset =
        to_int(vector<uint8_t>(bytes_.begin() + idx, bytes_.begin() + idx + 4));
    idx += 4;
    this->fields[i].datatype = bytes_[idx++];
    this->fields[i].count =
        to_int(vector<uint8_t>(bytes_.begin() + idx, bytes_.begin() + idx + 4));
    idx += 4;
  }
  this->is_bigendian = bytes_[idx++];
  this->point_step =
      to_int(vector<uint8_t>(bytes_.begin() + idx, bytes_.begin() + idx + 4));
  this->row_step = to_int(
      vector<uint8_t>(bytes_.begin() + idx + 4, bytes_.begin() + idx + 8));
  idx += 8;

  uint32_t n_data =
      to_int(vector<uint8_t>(bytes_.begin() + idx, bytes_.begin() + idx + 4));
  idx += 4;
  this->data =
      vector<uint8_t>(bytes_.begin() + idx, bytes_.begin() + idx + n_data);
  idx += n_data;
  this->is_dense = bytes_[idx++];
}

std::vector<uint8_t> serialize(const PointCloud2 &pointcloud, bool compress) {
  vector<uint8_t> bytes;
  bytes.reserve(pointcloud.data.size() + 128);

  vector<uint8_t> secs = four(pointcloud.timestamp_sec);
  vector<uint8_t> nsecs = four(pointcloud.timestamp_nsec);
  vector<uint8_t> frame_id = from_string(pointcloud.frame_id);

  vector<uint8_t> height = four(pointcloud.height);
  vector<uint8_t> width = four(pointcloud.width);
  uint8_t n_fields = pointcloud.fields.size();

  bytes.insert(bytes.end(), secs.begin(), secs.end());
  bytes.insert(bytes.end(), nsecs.begin(), nsecs.end());
  bytes.insert(bytes.end(), frame_id.begin(), frame_id.end());
  bytes.insert(bytes.end(), height.begin(), height.end());
  bytes.insert(bytes.end(), width.begin(), width.end());
  bytes.insert(bytes.end(), n_fields);
  for (uint8_t i = 0; i < n_fields; i++) {
    vector<uint8_t> name = from_string(pointcloud.fields[i].name);
    vector<uint8_t> offset = four(pointcloud.fields[i].offset);
    uint8_t datatype = pointcloud.fields[i].datatype;
    vector<uint8_t> count = four(pointcloud.fields[i].count);

    bytes.insert(bytes.end(), name.begin(), name.end());
    bytes.insert(bytes.end(), offset.begin(), offset.end());
    bytes.insert(bytes.end(), datatype);
    bytes.insert(bytes.end(), count.begin(), count.end());
  }
  vector<uint8_t> point_step = four(pointcloud.point_step);
  vector<uint8_t> row_step = four(pointcloud.row_step);
  bytes.insert(bytes.end(), pointcloud.is_bigendian);
  bytes.insert(bytes.end(), point_step.begin(), point_step.end());
  bytes.insert(bytes.end(), row_step.begin(), row_step.end());

  uint32_t n_data_ = pointcloud.data.size();
  vector<uint8_t> n_data = four(n_data_);
  bytes.insert(bytes.end(), n_data.begin(), n_data.end());
  bytes.insert(bytes.end(), pointcloud.data.begin(), pointcloud.data.end());
  bytes.insert(bytes.end(), pointcloud.is_dense);

  if (compress) {
    vector<uint8_t> compressed_bytes = compress_bytes(bytes);
    vector<uint8_t> original_length = four(static_cast<uint32_t>(bytes.size()));
    compressed_bytes.insert(compressed_bytes.begin(), original_length.begin(),
                            original_length.end());
    compressed_bytes.insert(compressed_bytes.begin(), 0x01);

    return compressed_bytes;
  } else {
    bytes.insert(bytes.begin(), 0x00);

    return bytes;
  }
}

}  // namespace sbox_msgs
