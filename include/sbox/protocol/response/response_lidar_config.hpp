/// @file
/// @author Jongkuk Lim <limjk@jmarple.ai>
/// @copyright 2023 J.Marple
/// @brief Response data status protocol for communication

#ifndef FLEXXLAM_SDK_INCLUDE_PROTOCOL_RESPONSE_RESPONSE_LIDAR_CONFIG_HPP_
#define FLEXXLAM_SDK_INCLUDE_PROTOCOL_RESPONSE_RESPONSE_LIDAR_CONFIG_HPP_

#include <vector>

#include "sbox/protocol/base_protocol.hpp"
#include "sbox/utils/to_bytes.hpp"

namespace flexxlam {

/// @brief Response lidar config protocol
class ResponseLidarConfig : public BaseProtocol {
 public:
  /// @brief Response lidar config protocol constructor
  /// @param lidar_type LiDAR type defined in `protocol::kLidar*`
  explicit ResponseLidarConfig(uint8_t lidar_type)
      : BaseProtocol(protocol::kModeResLidarConfig), lidar_type_(lidar_type) {
    this->payload_.clear();
    this->payload_.push_back(lidar_type);
  }

  /// @brief Response data status protocol constructor
  /// @param bytes byte array of whole protocol or payload only
  /// @param payload_only if true, then `bytes` is not decapsulated
  explicit ResponseLidarConfig(const vector<uint8_t> &bytes,
                               bool payload_only = false)
      : BaseProtocol(bytes, protocol::kModeResLidarConfig, payload_only) {
    this->init_from_payload_();
  }

  /// @copydoc BaseProtocol::handle_callback
  void handle_callback(
      const vector<ParsedMessageInterface *> &callbacks) override {
    for (auto callback : callbacks) {
      callback->on_response_lidar_config(this->lidar_type_);
    }
  }

  /// @brief Get type of lidar
  /// @return type of lidar defined in `protocol::kLidar*`
  uint8_t get_lidar_type() const { return lidar_type_; }

 protected:
  /// @brief Initialize `enabled_` and `baudrate_` from `payload`
  void init_from_payload_() override { this->lidar_type_ = this->payload_[0]; }

 private:
  /// @brief LiDAR type defined in `protocol::kLidar*`
  uint8_t lidar_type_;
};
}  // namespace flexxlam

#endif  // FLEXXLAM_SDK_INCLUDE_PROTOCOL_RESPONSE_RESPONSE_LIDAR_CONFIG_HPP_
