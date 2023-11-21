/// @file
/// @author Jongkuk Lim <limjk@jmarple.ai>
/// @copyright 2023 J.Marple
/// @brief Base protocol for communication

#include "protocol/base_protocol.hpp"

#include <cstring>
#include <vector>

#include "utils/to_bytes.hpp"

namespace flexxlam {

vector<uint8_t> BaseProtocol::encapsulate_(vector<uint8_t> payload) {
  int length = payload.size();

  std::vector<uint8_t> length_bytes = to_bytes::two(length);
  std::array<uint8_t, 2> checksum = BaseProtocol::get_checksum(
      std::vector<uint8_t>(this->mode_.begin(), this->mode_.end()),
      length_bytes, payload);

  vector<uint8_t> bytes(length + 8, 0);

  bytes[0] = protocol::kHeader[0];
  bytes[1] = protocol::kHeader[1];

  bytes[2] = this->mode_[0];
  bytes[3] = this->mode_[1];

  bytes[4] = length_bytes[0];
  bytes[5] = length_bytes[1];

  memcpy(bytes.data() + 6, payload.data(), length);

  bytes[length + 6] = checksum[0];
  bytes[length + 7] = checksum[1];

  return bytes;
}

vector<uint8_t> BaseProtocol::decapsulate_(vector<uint8_t> bytes) {
  uint8_t header[2] = {bytes[0], bytes[1]};
  if (memcmp(header, protocol::kHeader.begin(), 2) != 0) {
    this->is_valid_ = false;
    return vector<uint8_t>();
  }

  vector<uint8_t> mode = {bytes[2], bytes[3]};
  vector<uint8_t> length = {bytes[4], bytes[5]};
  int len = length[0] * 256 + length[1];

  vector<uint8_t> payload(len, 0);
  memcpy(payload.data(), bytes.data() + 6, len);

  std::array<uint8_t, 2> checksum_in_msg = {bytes[6 + len], bytes[7 + len]};
  std::array<uint8_t, 2> checksum =
      BaseProtocol::get_checksum(mode, length, payload);

  if (memcmp(checksum_in_msg.data(), checksum.data(), 2) != 0) {
    this->is_valid_ = false;
    return vector<uint8_t>();
  }

  return payload;
}

}  // namespace flexxlam
