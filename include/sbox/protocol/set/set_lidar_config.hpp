/// @file
/// @author Jongkuk Lim <limjk@jmarple.ai>
/// @copyright 2023 J.Marple
/// @brief Set lidar config protocol

#ifndef SLAMBOX_SDK_INCLUDE_SBOX_PROTOCOL_SET_SET_LIDAR_CONFIG_HPP_
#define SLAMBOX_SDK_INCLUDE_SBOX_PROTOCOL_SET_SET_LIDAR_CONFIG_HPP_

#include <string>
#include <vector>

#include "sbox/protocol/base_protocol.hpp"
#include "sbox/utils/to_bytes.hpp"

namespace sbox {

/// @brief Set lidar config protocol
class SetLidarConfigProtocol : public BaseProtocol {
 public:
  /// @brief Set lidar config protocol constructor
  /// @param lidar_type LiDAR type defined in `protocol::kLidarCodeToType`
  explicit SetLidarConfigProtocol(uint8_t lidar_type)
      : BaseProtocol(protocol::kModeSetLidarConfig), lidar_type_(lidar_type) {
    this->payload_.clear();
    this->payload_.push_back(lidar_type);
  }

  /// @brief Set lidar config protocol constructor
  /// @param lidar_type LiDAR type defined in `protocol::kLidarTypeToCode`
  explicit SetLidarConfigProtocol(std::string lidar_type)
      : BaseProtocol(protocol::kModeSetLidarConfig) {
    if (protocol::kLidarTypeToCode.find(lidar_type) ==
        protocol::kLidarTypeToCode.end()) {
      this->lidar_type_ = protocol::kLidarUnknown;
    } else {
      this->lidar_type_ = protocol::kLidarTypeToCode.at(lidar_type);
    }

    this->payload_.clear();
    this->payload_.push_back(this->lidar_type_);
  }

  /// @brief Set lidar config protocol constructor
  /// @param bytes byte array of whole protocol or payload only
  /// @param payload_only if true, then `bytes` is not decapsulated
  explicit SetLidarConfigProtocol(const vector<uint8_t> &bytes,
                                  bool payload_only = false)
      : BaseProtocol(bytes, protocol::kModeSetLidarConfig, payload_only) {
    this->init_from_payload_();
  }

  /// @copydoc BaseProtocol::handle_callback
  void handle_callback(
      const vector<ParsedMessageInterface *> &callbacks) override {
    for (auto callback : callbacks) {
      callback->on_set_lidar_config(this->lidar_type_);
    }
  }

  /// @brief Get lidar type defined in `protocol::kLidarCodeToType`
  /// @return lidar type defined in `protocol::kLidarCodeToType`
  uint8_t get_lidar_type() const { return lidar_type_; }

 protected:
  /// @brief Initialize `lidar_type` from `payload`
  void init_from_payload_() override { this->lidar_type_ = this->payload_[0]; }

 private:
  /// @brief enabled or not
  uint8_t lidar_type_;
};
}  // namespace sbox

#endif  // SLAMBOX_SDK_INCLUDE_SBOX_PROTOCOL_SET_SET_LIDAR_CONFIG_HPP_
