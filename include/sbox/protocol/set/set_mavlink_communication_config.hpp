/// @file
/// @author Jongkuk Lim <limjk@jmarple.ai>
/// @copyright 2023 J.Marple
/// @brief Set mavlink communication config protocol

#ifndef FLEXXLAM_SDK_INCLUDE_PROTOCOL_SET_SET_MAVLINK_COMMUNICATION_CONFIG_HPP_
#define FLEXXLAM_SDK_INCLUDE_PROTOCOL_SET_SET_MAVLINK_COMMUNICATION_CONFIG_HPP_

#include <vector>

#include "sbox/protocol/base_protocol.hpp"
#include "sbox/utils/to_bytes.hpp"

namespace flexxlam {

/// @brief Set mavlink communication config protocol
class SetMavlinkCommunicationConfigProtocol : public BaseProtocol {
 public:
  /// @brief Set mavlink communication config protocol constructor
  /// @param enabled enabled or not
  /// @param baudrate baudrate of mavlink communication
  SetMavlinkCommunicationConfigProtocol(bool enabled, uint32_t baudrate)
      : BaseProtocol(protocol::kModeSetMavlinkCommConfig),
        enabled_(enabled),
        baudrate_(baudrate) {
    vector<uint8_t> baudrate_bytes = to_bytes::four(baudrate);
    this->payload_.clear();
    this->payload_.push_back(enabled);
    this->payload_.insert(this->payload_.end(), baudrate_bytes.begin(),
                          baudrate_bytes.end());
  }

  /// @brief Set mavlink communication config protocol constructor
  /// @param bytes byte array of whole protocol or payload only
  /// @param payload_only if true, then `bytes` is not decapsulated
  explicit SetMavlinkCommunicationConfigProtocol(const vector<uint8_t> &bytes,
                                                 bool payload_only = false)
      : BaseProtocol(bytes, protocol::kModeSetMavlinkCommConfig, payload_only) {
    this->init_from_payload_();
  }

  /// @copydoc BaseProtocol::handle_callback
  void handle_callback(
      const vector<ParsedMessageInterface *> &callbacks) override {
    for (auto callback : callbacks) {
      callback->on_set_mavlink_communication_config(this->enabled_,
                                                    this->baudrate_);
    }
  }

  /// @brief Get enabled or not
  /// @return enabled or not
  bool get_enabled() const { return enabled_; }

  /// @brief Get baudrate of mavlink communication
  /// @return baudrate of mavlink communication
  uint32_t get_baudrate() const { return baudrate_; }

 protected:
  /// @brief Initialize `enabled_` and `baudrate_` from `payload`
  void init_from_payload_() override {
    this->enabled_ = this->payload_[0];
    this->baudrate_ = from_bytes::to_int(
        vector<uint8_t>(this->payload_.begin() + 1, this->payload_.end()));
  }

 private:
  /// @brief enabled or not
  bool enabled_;

  /// @brief baudrate of mavlink communication
  uint32_t baudrate_;
};
}  // namespace flexxlam

#endif  // FLEXXLAM_SDK_INCLUDE_PROTOCOL_SET_SET_MAVLINK_COMMUNICATION_CONFIG_HPP_
