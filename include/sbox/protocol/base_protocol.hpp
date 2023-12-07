/// @file
/// @author Jongkuk Lim <limjk@jmarple.ai>
/// @copyright 2023 J.Marple
/// @brief Base protocol for communication

#ifndef SLAMBOX_SDK_INCLUDE_SBOX_PROTOCOL_BASE_PROTOCOL_HPP_
#define SLAMBOX_SDK_INCLUDE_SBOX_PROTOCOL_BASE_PROTOCOL_HPP_

#include <array>
#include <cstring>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "sbox/communication/flexxlam_parser.hpp"

using std::vector;

/// @brief Protocol constants namespace
namespace flexxlam::protocol {
/// @brief Header of protocol
constexpr std::array<uint8_t, 2> kHeader = {0xFA, 0x5A};

/// @{
/// Modes of protocol
constexpr std::array<uint8_t, 2> kModeAck = {0xA0, 0x00};
constexpr std::array<uint8_t, 2> kModeAckPing = {0xA0, 0x01};

constexpr std::array<uint8_t, 2> kModeCmdRestartLIO = {0x30, 0x01};
constexpr std::array<uint8_t, 2> kModeCmdSavePCD = {0x30, 0x02};

constexpr std::array<uint8_t, 2> kModePushOdometry = {0x01, 0x01};
constexpr std::array<uint8_t, 2> kModePushPointcloud = {0x01, 0x02};

constexpr std::array<uint8_t, 2> kModeReqMavlinkCommConfig = {0x10, 0x01};
constexpr std::array<uint8_t, 2> kModeReqSerialCommConfig = {0x10, 0x02};
constexpr std::array<uint8_t, 2> kModeReqEthernetCommConfig = {0x10, 0x03};
constexpr std::array<uint8_t, 2> kModeReqLidarConfig = {0x10, 0x10};

constexpr std::array<uint8_t, 2> kModeResMavlinkCommConfig = {0x11, 0x01};
constexpr std::array<uint8_t, 2> kModeResSerialCommConfig = {0x11, 0x02};
constexpr std::array<uint8_t, 2> kModeResEthernetCommConfig = {0x11, 0x03};
constexpr std::array<uint8_t, 2> kModeResLidarConfig = {0x11, 0x10};

constexpr std::array<uint8_t, 2> kModeSetMavlinkCommConfig = {0x20, 0x01};
constexpr std::array<uint8_t, 2> kModeSetSerialCommConfig = {0x20, 0x02};
constexpr std::array<uint8_t, 2> kModeSetEthernetCommConfig = {0x20, 0x03};
constexpr std::array<uint8_t, 2> kModeSetLidarConfig = {0x20, 0x10};
/// @}

/// @{
/// Types of LiDAR
constexpr uint8_t kLidarFlexx2 = 0x10;
constexpr uint8_t kLidarOusterOS1 = 0x20;
constexpr uint8_t kLidarLivoxMID360 = 0x30;
constexpr uint8_t kLidarUnknown = 0xFF;
/// @}

/// @{
/// Status of protocol
constexpr uint8_t kStatusAckSuccess = 0x00;
constexpr uint8_t kStatusAckFailed = 0x01;
/// @}

/// Lidar type string to code
const std::map<std::string, uint8_t> kLidarTypeToCode = {
    {"Flexx2", kLidarFlexx2},
    {"Ouster_os1", kLidarOusterOS1},
    {"Livox_MID360", kLidarLivoxMID360},
};

/// Reverse map of `kLidarTypeToCode`
const std::map<uint8_t, std::string> kLidarCodeToType = {
    {kLidarFlexx2, "Flexx2"},
    {kLidarOusterOS1, "Ouster_os1"},
    {kLidarLivoxMID360, "Livox_MID360"},
};

/// Payload length of protocol (in bytes) where length is equal to
/// `payload_length` in protocol.
const std::map<std::array<uint8_t, 2>, uint16_t> kModeToPayloadLengthEq = {
    {kModeAck, 3},
    {kModeAckPing, 0},
    {kModeCmdRestartLIO, 0},
    {kModeCmdSavePCD, 2},
    {kModePushOdometry, 348},
    {kModeReqMavlinkCommConfig, 0},
    {kModeReqSerialCommConfig, 0},
    {kModeReqEthernetCommConfig, 0},
    {kModeReqLidarConfig, 0},
    {kModeResMavlinkCommConfig, 5},
    {kModeResSerialCommConfig, 5},
    {kModeResEthernetCommConfig, 5},
    {kModeResLidarConfig, 1},
    {kModeSetMavlinkCommConfig, 5},
    {kModeSetSerialCommConfig, 5},
    {kModeSetEthernetCommConfig, 5},
    {kModeSetLidarConfig, 1},
};

/// Payload length of protocol (in bytes) where length is greater than
/// `payload_length` in protocol.
const std::map<std::array<uint8_t, 2>, uint16_t> kModeToPayloadLengthGt = {
    {kModePushPointcloud, 300},
};

}  // namespace flexxlam::protocol

namespace flexxlam {
/// @brief Base protocol for communication
class BaseProtocol {
 public:
  /// @brief Base protocol constructor
  /// @param mode mode of protocol (2 bytes)
  /// @details This constructor initialize mode and payload length.
  explicit BaseProtocol(const std::array<uint8_t, 2> mode) : mode_(mode) {
    this->is_valid_ = true;
  }

  /// @brief Base protocol constructor
  /// @param bytes byte array
  /// @param mode mode of protocol (2 bytes)
  /// @param payload_only if true, then payload is not decapsulated
  /// @details This constructor decapsulates byte array and then initialize
  /// payload.
  explicit BaseProtocol(const vector<uint8_t> &bytes,
                        std::array<uint8_t, 2> mode, bool payload_only = false)
      : BaseProtocol(mode) {
    if (payload_only) {
      this->payload_ = bytes;
    } else {
      this->payload_ = decapsulate_(bytes);
    }
  }

  /// @brief Base protocol destructor
  /// @details This destructor deletes payload.
  ~BaseProtocol() {}

  /// @brief Get payload only
  /// @return payload
  vector<uint8_t> get_payload() { return this->payload_; }

  /// @brief Get the validity of the protocol.
  /// @return true if the protocol is valid, otherwise false
  bool is_valid() { return this->is_valid_; }

  /// @brief Encapsulate payload into the protocol.
  /// @return byte array of whole protocol (from header to checksum)
  /// @details The protocol is as follows:
  ///
  /// | header |  mode  | length | payload | checksum |
  /// |--------|--------|--------|---------|----------|
  /// | 2 byte | 2 byte | 2 byte | length  | 1 byte   |
  virtual vector<uint8_t> encapsulate() { return encapsulate_(this->payload_); }

  /// @brief Call callback functions from parsed message interface
  /// @param callbacks parsed message interfaces
  /// @details This function is called from `FlexXlamParser::parse`.
  virtual void handle_callback(
      const vector<ParsedMessageInterface *> &callbacks) = 0;

  /// @brief Get checksum of protocol
  /// @param mode mode of protocol (2 bytes)
  /// @param length length of payload
  /// @param payload payload
  /// @return checksum
  /// @details The checksum is calculated as follows:
  /// checksum = mode[0] ^ mode[1] ^ length[0] ^ length[1] ^ payload[0] ^
  /// payload[1] ^ ... ^ payload[length - 1]
  static std::array<uint8_t, 2> get_checksum(vector<uint8_t> mode,
                                             vector<uint8_t> length,
                                             vector<uint8_t> payload) {
    uint8_t checksum_a = mode[0];
    uint8_t checksum_b = checksum_a;

    checksum_a += mode[1];
    checksum_b += checksum_a;

    checksum_a += length[0];
    checksum_b += checksum_a;

    checksum_a += length[1];
    checksum_b += checksum_a;

    int len = length[0] * 256 + length[1];

    for (int i = 0; i < len; i++) {
      checksum_a += payload[i];
      checksum_b += checksum_a;
    }

    return {checksum_a, checksum_b};
  }

 protected:
  /// @brief mode of protocol (2 bytes)
  std::array<uint8_t, 2> mode_;

  /// @brief is valid protocol
  bool is_valid_ = false;

  /// @brief payload
  // vector<uint8_t> payload = nullptr;
  vector<uint8_t> payload_;

  /// @brief Create whole protocol message from payload
  /// @param payload payload
  /// @return byte array
  vector<uint8_t> encapsulate_(vector<uint8_t> payload);

  /// @brief Decapsulate payload from protocol
  /// @param bytes byte array
  /// @return payload if checksum and header are valid, otherwise nullptr
  vector<uint8_t> decapsulate_(vector<uint8_t> bytes);

  /// @brief Initialize members of the derived class from payload
  virtual void init_from_payload_() = 0;
};
}  // namespace flexxlam

#endif  // SLAMBOX_SDK_INCLUDE_SBOX_PROTOCOL_BASE_PROTOCOL_HPP_
