/// @file
/// @author Jongkuk Lim <limjk@jmarple.ai>
/// @copyright 2023 J.Marple
/// @brief Request mavlink communication config protocol

#ifndef FLEXXLAM_SDK_INCLUDE_PROTOCOL_REQUEST_REQUEST_ETHERNET_COMMUNICATION_CONFIG_HPP_
#define FLEXXLAM_SDK_INCLUDE_PROTOCOL_REQUEST_REQUEST_ETHERNET_COMMUNICATION_CONFIG_HPP_

#include <vector>

#include "sbox/protocol/base_protocol.hpp"

namespace flexxlam {

/// @brief Request ethernet communication config protocol
class RequestEthernetCommunicationConfigProtocol : public BaseProtocol {
 public:
  /// @brief Request ethernet communication config protocol constructor
  RequestEthernetCommunicationConfigProtocol()
      : BaseProtocol(protocol::kModeReqEthernetCommConfig) {}

  /// @brief Request ethernet communication config protocol constructor
  /// @param bytes byte array of whole protocol or payload
  /// @param payload_only if true, then bytes parameter contains only payload
  /// and `bytes` is empty vector since it has no payload.
  /// @details This constructor decapsulates byte array and then initialize
  explicit RequestEthernetCommunicationConfigProtocol(
      const std::vector<uint8_t> &bytes, bool payload_only = false)
      : BaseProtocol(bytes, protocol::kModeReqEthernetCommConfig,
                     payload_only) {}

  /// @copydoc BaseProtocol::handle_callback
  void handle_callback(
      const vector<ParsedMessageInterface *> &callbacks) override {
    for (auto callback : callbacks) {
      callback->on_request_ethernet_communication_config();
    }
  }

 protected:
  void init_from_payload_() override {}
};

}  // namespace flexxlam

#endif  // FLEXXLAM_SDK_INCLUDE_PROTOCOL_REQUEST_REQUEST_ETHERNET_COMMUNICATION_CONFIG_HPP_
