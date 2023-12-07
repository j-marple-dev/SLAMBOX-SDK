/// @file
/// @author Jongkuk Lim <limjk@jmarple.ai>
/// @copyright 2023 J.Marple
/// @brief Converting data into byte array

#include "sbox/utils/to_bytes.hpp"

#include <glog/logging.h>

#include <cstring>

namespace flexxlam::to_bytes {

vector<uint8_t> from_string(std::string str) {
  int size = str.size();
  if (str.size() > 255) {
    LOG(WARNING) << "String size is too big. Only first 255 characters will be "
                    "sent.";
    size = 255;
  }
  vector<uint8_t> bytes;
  bytes.push_back(static_cast<uint8_t>(size));
  bytes.insert(bytes.end(), str.begin(), str.begin() + size);

  return bytes;
}

vector<uint8_t> four(double x) { return four(static_cast<float>(x)); }

vector<uint8_t> four(float x) {
  uint8_t const *p = reinterpret_cast<uint8_t const *>(&x);
  vector<uint8_t> bytes(p, p + 4);

  return bytes;
}

vector<uint8_t> four(vector<double> x) {
  vector<float> floats(x.size());

  for (int i = 0; i < x.size(); i++) {
    floats[i] = static_cast<float>(x[i]);
  }

  vector<uint8_t> bytes = four(floats);

  return bytes;
}

vector<uint8_t> four(vector<float> x) {
  vector<uint8_t> bytes;

  for (int i = 0; i < x.size(); i++) {
    vector<uint8_t> element = four(x[i]);
    bytes.insert(bytes.end(), element.begin(), element.end());
  }

  return bytes;
}

vector<uint8_t> four(uint32_t x) {
  vector<uint8_t> bytes;
  bytes.push_back((x >> 24) & 0xFF);
  bytes.push_back((x >> 16) & 0xFF);
  bytes.push_back((x >> 8) & 0xFF);
  bytes.push_back(x & 0xFF);

  return bytes;
}

vector<uint8_t> two(uint32_t x) {
  vector<uint8_t> bytes;
  bytes.push_back((x >> 8) & 0xFF);
  bytes.push_back(x & 0xFF);

  return bytes;
}

}  // namespace flexxlam::to_bytes

namespace flexxlam::from_bytes {

float to_float(vector<uint8_t> bytes, int offset) {
  float x;
  memcpy(&x, bytes.data() + offset, 4);

  return x;
}

uint32_t to_int(vector<uint8_t> bytes) {
  uint32_t x = 0;

  int size = bytes.size();

  if (size > 4) {
    LOG(WARNING) << "The size of the byte array is larger than 4. "
                    "Only the first 4 bytes are used.";
    size = 4;
  }

  for (int i = 0; i < size; i++) {
    x += bytes[i] << (8 * (size - i - 1));
  }

  return x;
}

std::string to_string(vector<uint8_t> bytes, size_t offset) {
  if (bytes.size() < offset + 1) {
    LOG(WARNING) << "The size of the byte array is smaller than the offset. "
                    "Empty string is returned.";
    return "";
  }

  int size = bytes[offset];

  if ((bytes.size() - offset) < size + 1) {
    LOG(WARNING) << "The size of the byte array is smaller than the string "
                    "size. Only the first "
                 << bytes.size() - 1 << " bytes are used. The string size is "
                 << size << ".";
    size = bytes.size() - offset - 1;
  }

  std::string str(bytes.begin() + offset + 1,
                  bytes.begin() + offset + 1 + size);

  return str;
}

}  // namespace flexxlam::from_bytes
