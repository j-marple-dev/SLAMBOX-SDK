/// @file
/// @author Jongkuk Lim <limjk@jmarple.ai>
/// @copyright 2023 J.Marple
/// @brief Compress bytes

#ifndef SLAMBOX_SDK_INCLUDE_SBOX_UTILS_COMPRESS_BYTES_HPP_
#define SLAMBOX_SDK_INCLUDE_SBOX_UTILS_COMPRESS_BYTES_HPP_

#include <zlib.h>

#include <cstdint>
#include <vector>

using std::vector;

namespace flexxlam {
/// @brief Compress bytes
/// @param bytes bytes to compress
/// @return compressed bytes
/// @details This function compresses bytes using zlib.
/// If compression is failed, it returns empty vector.
vector<uint8_t> compress_bytes(const vector<uint8_t> &bytes);

/// @brief Decompress bytes
/// @param bytes bytes to decompress
/// @param original_size original size of bytes
/// @details If original_size is 0, it will be calculated from bytes.
/// @return decompressed bytes
/// @details This function decompresses bytes using zlib.
/// If decompression is failed, it returns empty vector.
vector<uint8_t> decompress_bytes(const vector<uint8_t> &bytes,
                                 uint32_t original_size = 0);
}  // namespace flexxlam

#endif  // SLAMBOX_SDK_INCLUDE_SBOX_UTILS_COMPRESS_BYTES_HPP_
