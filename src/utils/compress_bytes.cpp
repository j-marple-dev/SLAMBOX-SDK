/// @file
/// @author Jongkuk Lim <limjk@jmarple.ai>
/// @copyright 2023 J.Marple
/// @brief Compress bytes

#include "sbox/utils/compress_bytes.hpp"

#include <glog/logging.h>

namespace flexxlam {

vector<uint8_t> compress_bytes(const vector<uint8_t>& bytes) {
  uint8_t* bytes_ptr = const_cast<uint8_t*>(bytes.data());
  size_t data_size = bytes.size();
  size_t compressed_size = compressBound(data_size);

  vector<uint8_t> compressed_bytes(compressed_size);
  int result =
      compress(compressed_bytes.data(), &compressed_size, bytes_ptr, data_size);

  if (result == Z_OK) {
    compressed_bytes.resize(compressed_size);

    return compressed_bytes;
  }

  // TODO(jeikeilim): Handle error case better than now
  LOG(ERROR) << "Failed to compress bytes";
  return vector<uint8_t>();
}

vector<uint8_t> decompress_bytes(const vector<uint8_t>& bytes,
                                 uint32_t original_size) {
  uint8_t* bytes_ptr = const_cast<uint8_t*>(bytes.data());
  size_t data_size = bytes.size();
  size_t decompressed_size = original_size == 0 ? data_size * 5 : original_size;

  vector<uint8_t> decompressed_bytes(decompressed_size);
  int result = uncompress(decompressed_bytes.data(), &decompressed_size,
                          bytes_ptr, data_size);

  if (result == Z_OK) {
    decompressed_bytes.resize(decompressed_size);

    return decompressed_bytes;
  }

  // TODO(jeikeilim): Handle error case better than now
  LOG(ERROR) << "Failed to decompress bytes";
  return vector<uint8_t>();
}

}  // namespace flexxlam
