/// @file
/// @author Jongkuk Lim <limjk@jmarple.ai>
/// @copyright 2023 J.Marple
/// @brief Acknowledge protocol for communication

#ifndef FLEXXLAM_SDK_INCLUDE_PROTOCOL_ACKNOWLEDGE_ACKNOWLEDGE_PROTOCOL_HPP_
#define FLEXXLAM_SDK_INCLUDE_PROTOCOL_ACKNOWLEDGE_ACKNOWLEDGE_PROTOCOL_HPP_

#include <array>
#include <vector>

#include "protocol/base_protocol.hpp"

using std::vector;

namespace flexxlam {

/// @brief Acknowledge protocol
class AcknowledgeProtocol : public BaseProtocol {
 public:
  /// @brief Acknowledge protocol constructor
  /// @param requested_mode requested mode to acknowledge
  /// @param status status of requested mode
  AcknowledgeProtocol(std::array<uint8_t, 2> requested_mode, uint8_t status)
      : BaseProtocol(protocol::kModeAck),
        requested_mode_(requested_mode),
        status_(status) {
    this->payload_.clear();
    this->payload_.push_back(this->requested_mode_[0]);
    this->payload_.push_back(this->requested_mode_[1]);
    this->payload_.push_back(this->status_);
  }

  /// @brief Acknowledge protocol constructor
  /// @param bytes byte array of whole protocol or payload only
  /// @param payload_only if true, then `bytes` is not decapsulated
  /// @details This constructor decapsulates byte array and then initialize
  explicit AcknowledgeProtocol(const vector<uint8_t> &bytes,
                               bool payload_only = false)
      : BaseProtocol(bytes, protocol::kModeAck, payload_only) {
    this->init_from_payload_();
  }

  /// @copydoc BaseProtocol::handle_callback
  void handle_callback(
      const vector<ParsedMessageInterface *> &callbacks) override {
    for (auto callback : callbacks) {
      callback->on_acknowledge(this->requested_mode_, this->status_);
    }
  }

 protected:
  /// @brief Initialize `requested_mode_` and `status_` from `payload`
  /// @details This function is called from constructor
  void init_from_payload_() override {
    this->requested_mode_[0] = this->payload_[0];
    this->requested_mode_[1] = this->payload_[1];
    this->status_ = this->payload_[2];
  }

 private:
  /// @brief Requested mode to acknowledge
  std::array<uint8_t, 2> requested_mode_;

  /// @brief Status of requested mode
  uint8_t status_;
};

}  // namespace flexxlam

#endif  // FLEXXLAM_SDK_INCLUDE_PROTOCOL_ACKNOWLEDGE_ACKNOWLEDGE_PROTOCOL_HPP_
