/// @file
/// @author Jongkuk Lim <limjk@jmarple.ai>
/// @copyright 2023 J.Marple
/// @brief Get pointcloud protocol

#ifndef SLAMBOX_SDK_INCLUDE_SBOX_PROTOCOL_PUSH_PUSH_POINTCLOUD_PROTOCOL_HPP_
#define SLAMBOX_SDK_INCLUDE_SBOX_PROTOCOL_PUSH_PUSH_POINTCLOUD_PROTOCOL_HPP_

#include <vector>

#include "sbox/protocol/base_protocol.hpp"
#include "sbox/sbox_msgs/PointCloud2.hpp"

namespace sbox {

/// @brief Get pointcloud protocol
class PushPointCloudProtocol : public BaseProtocol {
 public:
  /// @brief PushPointCloudProtocol constructor
  /// @param pointcloud Pointcloud
  /// @param compress_payload if true, then payload is compressed
  explicit PushPointCloudProtocol(const sbox_msgs::PointCloud2 &pointcloud,
                                  bool compress_payload = false)
      : BaseProtocol(protocol::kModePushPointcloud) {
    this->pointcloud_ = pointcloud;
    this->payload_ =
        sbox_msgs::serialize(pointcloud, /*compress=*/compress_payload);
  }

  /// @brief PushPointCloudProtocol constructor
  /// @param bytes byte array of whole protocol (from header to checksum) or
  /// payload
  /// @param payload_only if true, then payload is not decapsulated
  /// @details This constructor decapsulates byte array and then initialize
  /// `payload` and `pointcloud`
  explicit PushPointCloudProtocol(const vector<uint8_t> &bytes,
                                  bool payload_only = false)
      : BaseProtocol(bytes, protocol::kModePushPointcloud, payload_only) {
    this->init_from_payload_();
  }

  /// @copydoc BaseProtocol::handle_callback
  void handle_callback(
      const vector<ParsedMessageInterface *> &callbacks) override {
    for (auto callback : callbacks) {
      callback->on_push_pointcloud(this->pointcloud_);
    }
  }

  /// @brief Get pointcloud
  /// @return pointcloud
  sbox_msgs::PointCloud2 get_pointcloud() { return this->pointcloud_; }

 protected:
  /// @brief Initialize `pointcloud` from `payload`
  void init_from_payload_() override {
    if (!this->is_valid()) {
      return;
    }

    this->pointcloud_ = sbox_msgs::PointCloud2(this->payload_);
  }

 private:
  /// @brief Pointcloud
  sbox_msgs::PointCloud2 pointcloud_;
};

}  // namespace sbox

#endif  // SLAMBOX_SDK_INCLUDE_SBOX_PROTOCOL_PUSH_PUSH_POINTCLOUD_PROTOCOL_HPP_
