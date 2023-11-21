/// @file
/// @author Jongkuk Lim <limjk@jmarple.ai>
/// @copyright 2023 J.Marple
/// @brief Acknowledge protocol for communication

#ifndef FLEXXLAM_SDK_INCLUDE_PROTOCOL_ACKNOWLEDGE_PING_PROTOCOL_HPP_
#define FLEXXLAM_SDK_INCLUDE_PROTOCOL_ACKNOWLEDGE_PING_PROTOCOL_HPP_

#include <vector>

#include "protocol/base_protocol.hpp"

namespace flexxlam {

/// @brief Ping protocol
class PingProtocol : public BaseProtocol {
 public:
  /// @brief Ping protocol constructor
  PingProtocol() : BaseProtocol(protocol::kModeAckPing) {}

  /// @brief Request lidar config protocol constructor
  /// @param bytes byte array of whole protocol or payload
  /// @param payload_only if true, then bytes parameter contains only payload
  /// and `bytes` is empty vector since it has no payload.
  /// @details This constructor decapsulates byte array and then initialize
  explicit PingProtocol(const std::vector<uint8_t> &bytes,
                        bool payload_only = false)
      : BaseProtocol(bytes, protocol::kModeAckPing, payload_only) {}

  /// @copydoc BaseProtocol::handle_callback
  void handle_callback(
      const vector<ParsedMessageInterface *> &callbacks) override {
    for (auto callback : callbacks) {
      callback->on_ping();
    }
  }

 protected:
  /// @brief It does nothing because there is no payload.
  void init_from_payload_() override {}
};

}  // namespace flexxlam

#endif  // FLEXXLAM_SDK_INCLUDE_PROTOCOL_ACKNOWLEDGE_PING_PROTOCOL_HPP_
