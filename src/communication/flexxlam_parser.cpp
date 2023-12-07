/// @file
/// @author Jongkuk Lim <limjk@jmarple.ai>
/// @copyright 2023 J.Marple
/// @brief Base parser for FlexXlam Driver

#include "sbox/communication/flexxlam_parser.hpp"

#include <glog/logging.h>

#include "sbox/protocol/acknowledge/acknowledge_protocol.hpp"
#include "sbox/protocol/acknowledge/ping_protocol.hpp"
#include "sbox/protocol/base_protocol.hpp"
#include "sbox/protocol/command/command_save_pcd_protocol.hpp"
#include "sbox/protocol/push/push_odometry_protocol.hpp"
#include "sbox/protocol/push/push_pointcloud_protocol.hpp"
#include "sbox/protocol/request/request_ethernet_communication_config.hpp"
#include "sbox/protocol/request/request_lidar_config.hpp"
#include "sbox/protocol/request/request_mavlink_communication_config.hpp"
#include "sbox/protocol/request/request_serial_communication_config.hpp"
#include "sbox/protocol/response/response_ethernet_communication_config.hpp"
#include "sbox/protocol/response/response_lidar_config.hpp"
#include "sbox/protocol/response/response_mavlink_communication_config.hpp"
#include "sbox/protocol/response/response_serial_communication_config.hpp"
#include "sbox/protocol/set/set_ethernet_communication_config.hpp"
#include "sbox/protocol/set/set_lidar_config.hpp"
#include "sbox/protocol/set/set_mavlink_communication_config.hpp"
#include "sbox/protocol/set/set_serial_communication_config.hpp"
#include "sbox/utils/to_bytes.hpp"

namespace flexxlam {

void FlexXlamParser::parse(vector<uint8_t> data) {
  // 1. Add data to buffer
  this->buffer_.insert(this->buffer_.end(), data.begin(), data.end());

  // 2. Remove data if buffer size is larger than buffer size
  if (this->buffer_.size() > this->buffer_size_) {
    this->buffer_.erase(
        this->buffer_.begin(),
        this->buffer_.begin() + this->buffer_.size() - this->buffer_size_);
  }

  while (this->buffer_.size() > 7) {
    // 3. Find header
    if (!this->find_header_()) {
      return;
    }

    // 4. Check length
    std::array<uint8_t, 2> mode = {this->buffer_[2], this->buffer_[3]};
    vector<uint8_t> length_bytes(this->buffer_.begin() + 4,
                                 this->buffer_.begin() + 6);
    uint32_t length = from_bytes::to_int(length_bytes);

    if (!this->is_length_valid_({mode[0], mode[1]}, length)) {
      this->buffer_.erase(this->buffer_.begin(), this->buffer_.begin() + 2);
      continue;
    }

    if (this->buffer_.size() < length + 8) {
      return;
    }

    // 5. Check checksum
    vector<uint8_t> payload(this->buffer_.begin() + 6,
                            this->buffer_.begin() + 6 + length);
    std::array<uint8_t, 2> computed_checksum =
        BaseProtocol::get_checksum({mode[0], mode[1]}, length_bytes, payload);
    std::array<uint8_t, 2> checksum = {this->buffer_[6 + length],
                                       this->buffer_[7 + length]};

    // if (computed_checksum != checksum) {
    if (memcmp(computed_checksum.data(), checksum.data(), 2) != 0) {
      this->buffer_.erase(this->buffer_.begin(), this->buffer_.begin() + 2);
      continue;
    }

    // 6. Decapsulate payload
    this->decapsulate_payload_(mode, payload);

    // 7. Remove data from buffer
    this->buffer_.erase(this->buffer_.begin(),
                        this->buffer_.begin() + 6 + length);
  }
}

bool FlexXlamParser::find_header_() {
  bool is_header_found = false;
  while (this->buffer_.size() > 7) {
    std::vector<uint8_t> header_candidate(this->buffer_.begin(),
                                          this->buffer_.begin() + 2);
    if (memcmp(header_candidate.data(), protocol::kHeader.data(), 2) == 0) {
      is_header_found = true;
      break;
    }
    this->buffer_.erase(this->buffer_.begin());
  }

  return is_header_found;
}

void FlexXlamParser::decapsulate_payload_(const std::array<uint8_t, 2> &mode,
                                          const vector<uint8_t> &payload) {
  /// TODO(jeikeilim): Refactor this function
  if (mode == protocol::kModePushOdometry) {
    PushOdometryProtocol(payload, /*payload_only=*/true)
        .handle_callback(this->parsed_message_interfaces_);
  } else if (mode == protocol::kModePushPointcloud) {
    PushPointCloudProtocol(payload, /*payload_only=*/true)
        .handle_callback(this->parsed_message_interfaces_);
  } else if (mode == protocol::kModeReqMavlinkCommConfig) {
    RequestMavlinkCommunicationConfigProtocol(payload, /*payload_only=*/true)
        .handle_callback(this->parsed_message_interfaces_);
  } else if (mode == protocol::kModeReqSerialCommConfig) {
    RequestSerialCommunicationConfigProtocol(payload, /*payload_only=*/true)
        .handle_callback(this->parsed_message_interfaces_);
  } else if (mode == protocol::kModeReqEthernetCommConfig) {
    RequestEthernetCommunicationConfigProtocol(payload, /*payload_only=*/true)
        .handle_callback(this->parsed_message_interfaces_);
  } else if (mode == protocol::kModeReqLidarConfig) {
    RequestLidarConfigProtocol(payload, /*payload_only=*/true)
        .handle_callback(this->parsed_message_interfaces_);
  } else if (mode == protocol::kModeResMavlinkCommConfig) {
    ResponseMavlinkCommunicationConfig(payload, /*payload_only=*/true)
        .handle_callback(this->parsed_message_interfaces_);
  } else if (mode == protocol::kModeResSerialCommConfig) {
    ResponseSerialCommunicationConfig(payload, /*payload_only=*/true)
        .handle_callback(this->parsed_message_interfaces_);
  } else if (mode == protocol::kModeResEthernetCommConfig) {
    ResponseEthernetCommunicationConfig(payload, /*payload_only=*/true)
        .handle_callback(this->parsed_message_interfaces_);
  } else if (mode == protocol::kModeResLidarConfig) {
    ResponseLidarConfig(payload, /*payload_only=*/true)
        .handle_callback(this->parsed_message_interfaces_);
  } else if (mode == protocol::kModeCmdSavePCD) {
    CommandSavePCDProtocol(payload, /*payload_only=*/true)
        .handle_callback(this->parsed_message_interfaces_);
  } else if (mode == protocol::kModeAck) {
    AcknowledgeProtocol(payload, /*payload_only=*/true)
        .handle_callback(this->parsed_message_interfaces_);
  } else if (mode == protocol::kModeAckPing) {
    PingProtocol(payload, /*payload_only=*/true)
        .handle_callback(this->parsed_message_interfaces_);
  } else if (mode == protocol::kModeSetMavlinkCommConfig) {
    SetMavlinkCommunicationConfigProtocol(payload, /*payload_only=*/true)
        .handle_callback(this->parsed_message_interfaces_);
  } else if (mode == protocol::kModeSetSerialCommConfig) {
    SetSerialCommunicationConfigProtocol(payload, /*payload_only=*/true)
        .handle_callback(this->parsed_message_interfaces_);
  } else if (mode == protocol::kModeSetEthernetCommConfig) {
    SetEthernetCommunicationConfigProtocol(payload, /*payload_only=*/true)
        .handle_callback(this->parsed_message_interfaces_);
  } else if (mode == protocol::kModeSetLidarConfig) {
    SetLidarConfigProtocol(payload, /*payload_only=*/true)
        .handle_callback(this->parsed_message_interfaces_);
  } else {
    LOG(ERROR) << "Unknown mode: " << std::hex << mode[0] << mode[1];
  }
}

bool FlexXlamParser::is_length_valid_(std::array<uint8_t, 2> mode,
                                      uint16_t length) {
  if (protocol::kModeToPayloadLengthEq.find(mode) !=
      protocol::kModeToPayloadLengthEq.end()) {
    return length == protocol::kModeToPayloadLengthEq.at(mode);
  } else if (protocol::kModeToPayloadLengthGt.find(mode) !=
             protocol::kModeToPayloadLengthGt.end()) {
    return length > protocol::kModeToPayloadLengthGt.at(mode);
  }

  return false;
}

void FlexXlamParser::add_parsed_message_callback(
    ParsedMessageInterface *parsed_message_interface) {
  this->parsed_message_interfaces_.push_back(parsed_message_interface);
}

}  // namespace flexxlam
