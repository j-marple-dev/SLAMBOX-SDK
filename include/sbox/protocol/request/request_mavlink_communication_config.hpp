/// @file
/// @author Jongkuk Lim <limjk@jmarple.ai>
/// @copyright 2023 J.Marple
/// @brief Request mavlink communication config protocol

#ifndef SLAMBOX_SDK_INCLUDE_SBOX_PROTOCOL_REQUEST_REQUEST_MAVLINK_COMMUNICATION_CONFIG_HPP_
#define SLAMBOX_SDK_INCLUDE_SBOX_PROTOCOL_REQUEST_REQUEST_MAVLINK_COMMUNICATION_CONFIG_HPP_

#include <vector>

#include "sbox/protocol/base_protocol.hpp"

namespace flexxlam {

/// @brief Request mavlink communication config protocol
class RequestMavlinkCommunicationConfigProtocol : public BaseProtocol {
 public:
  /// @brief Request mavlink communication config protocol constructor
  RequestMavlinkCommunicationConfigProtocol()
      : BaseProtocol(protocol::kModeReqMavlinkCommConfig) {}

  /// @brief Request mavlink communication config protocol constructor
  /// @param bytes byte array of whole protocol or payload
  /// @param payload_only if true, then bytes parameter contains only payload
  /// and `bytes` is empty vector since it has no payload.
  /// @details This constructor decapsulates byte array and then initialize
  explicit RequestMavlinkCommunicationConfigProtocol(
      const std::vector<uint8_t> &bytes, bool payload_only = false)
      : BaseProtocol(bytes, protocol::kModeReqMavlinkCommConfig, payload_only) {
  }

  /// @copydoc BaseProtocol::handle_callback
  void handle_callback(
      const vector<ParsedMessageInterface *> &callbacks) override {
    for (auto callback : callbacks) {
      callback->on_request_mavlink_communication_config();
    }
  }

 protected:
  void init_from_payload_() override {}
};

}  // namespace flexxlam

#endif  // SLAMBOX_SDK_INCLUDE_SBOX_PROTOCOL_REQUEST_REQUEST_MAVLINK_COMMUNICATION_CONFIG_HPP_
