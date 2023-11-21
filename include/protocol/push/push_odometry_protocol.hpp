/// @file
/// @author Jongkuk Lim <limjk@jmarple.ai>
/// @copyright 2023 J.Marple
/// @brief Base protocol for communication

#ifndef FLEXXLAM_SDK_INCLUDE_PROTOCOL_PUSH_PUSH_ODOMETRY_PROTOCOL_HPP_
#define FLEXXLAM_SDK_INCLUDE_PROTOCOL_PUSH_PUSH_ODOMETRY_PROTOCOL_HPP_

#include <array>
#include <memory>
#include <vector>

#include "communication/flexxlam_parser.hpp"
#include "flexxlam_msgs/Odometry.hpp"
#include "protocol/base_protocol.hpp"
#include "utils/to_bytes.hpp"

namespace flexxlam {

/// @brief Get odometry protocol
class PushOdometryProtocol : public BaseProtocol {
 public:
  /// @brief Get odometry protocol constructor
  /// @param odom odometry
  /// @details This constructor initialize `mode` and `payload` from `odom`
  explicit PushOdometryProtocol(const flexxlam_msgs::Odometry &odom)
      : BaseProtocol(protocol::kModePushOdometry) {
    this->odom = odom;
    this->payload_ = flexxlam_msgs::serialize(odom);
  }

  /// @brief Get odometry protocol constructor
  /// @param bytes byte array of whole protocol (from header to checksum) or
  /// payload
  /// @param payload_only if true, then payload is not decapsulated
  /// @details This constructor decapsulates byte array and then initialize
  /// `payload` and `odom`
  explicit PushOdometryProtocol(const vector<uint8_t> &bytes,
                                bool payload_only = false)
      : BaseProtocol(bytes, protocol::kModePushOdometry, payload_only) {
    PushOdometryProtocol::init_from_payload_();
  }

  /// @copydoc BaseProtocol::handle_callback
  void handle_callback(
      const vector<ParsedMessageInterface *> &callbacks) override {
    for (auto callback : callbacks) {
      callback->on_get_odometry(this->odom);
    }
  }

  /// @brief Get odometry
  /// @return odometry
  flexxlam_msgs::Odometry get_odometry() { return this->odom; }

 protected:
  /// @brief Initialize `odom` from `payload`
  void init_from_payload_() override {
    if (!this->is_valid()) {
      return;
    }

    this->odom = flexxlam_msgs::Odometry(this->payload_);
  }

 private:
  /// @brief odometry
  flexxlam_msgs::Odometry odom;
};

}  // namespace flexxlam

#endif  // FLEXXLAM_SDK_INCLUDE_PROTOCOL_PUSH_PUSH_ODOMETRY_PROTOCOL_HPP_
