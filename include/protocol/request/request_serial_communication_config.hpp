/// @file
/// @author Jongkuk Lim <limjk@jmarple.ai>
/// @copyright 2023 J.Marple
/// @brief Request mavlink communication config protocol

#ifndef FLEXXLAM_SDK_INCLUDE_PROTOCOL_REQUEST_REQUEST_SERIAL_COMMUNICATION_CONFIG_HPP_
#define FLEXXLAM_SDK_INCLUDE_PROTOCOL_REQUEST_REQUEST_SERIAL_COMMUNICATION_CONFIG_HPP_

#include <vector>

#include "protocol/base_protocol.hpp"

namespace flexxlam {

/// @brief Request serial communication config protocol
class RequestSerialCommunicationConfigProtocol : public BaseProtocol {
 public:
  /// @brief Request serial communication config protocol constructor
  RequestSerialCommunicationConfigProtocol()
      : BaseProtocol(protocol::kModeReqSerialCommConfig) {}

  /// @brief Request serial communication config protocol constructor
  /// @param bytes byte array of whole protocol or payload
  /// @param payload_only if true, then bytes parameter contains only payload
  /// and `bytes` is empty vector since it has no payload.
  /// @details This constructor decapsulates byte array and then initialize
  explicit RequestSerialCommunicationConfigProtocol(
      const std::vector<uint8_t> &bytes, bool payload_only = false)
      : BaseProtocol(bytes, protocol::kModeReqSerialCommConfig, payload_only) {}

  /// @copydoc BaseProtocol::handle_callback
  void handle_callback(
      const vector<ParsedMessageInterface *> &callbacks) override {
    for (auto callback : callbacks) {
      callback->on_request_serial_communication_config();
    }
  }

 protected:
  void init_from_payload_() override {}
};

}  // namespace flexxlam

#endif  // FLEXXLAM_SDK_INCLUDE_PROTOCOL_REQUEST_REQUEST_SERIAL_COMMUNICATION_CONFIG_HPP_
