/// @file
/// @author Jongkuk Lim <limjk@jmarple.ai>
/// @copyright 2023 J.Marple
/// @brief Test for converting data into byte array

#include <gtest/gtest.h>

#include <random>
#include <vector>

#include "sbox/utils/compress_bytes.hpp"

TEST(CompressBytes, CompressDecompressWithZeros) {
  std::random_device rd;
  std::mt19937 gen(rd());

  std::uniform_int_distribution<uint8_t> dis_uint8(0, 255);
  std::uniform_int_distribution<uint16_t> dis_uint16(1000, 65535);
  std::uniform_int_distribution<uint8_t> dis_bool(0, 1);

  for (int i = 0; i < 100; i++) {
    std::vector<uint8_t> bytes(dis_uint16(gen));
    for (int j = 0; j < bytes.size(); j++) {
      bytes[j] = dis_bool(gen) ? dis_uint8(gen) : 0;
    }

    std::vector<uint8_t> compressed_bytes = sbox::compress_bytes(bytes);

    std::vector<uint8_t> decompressed_bytes = sbox::decompress_bytes(
        compressed_bytes, /*original_size=*/bytes.size());

    EXPECT_LT(compressed_bytes.size(), bytes.size());
    EXPECT_EQ(bytes.size(), decompressed_bytes.size());
    for (int j = 0; j < bytes.size(); j++) {
      EXPECT_EQ(bytes[j], decompressed_bytes[j]);
    }
  }
}

TEST(CompressBytes, CompressDecompress) {
  std::random_device rd;
  std::mt19937 gen(rd());

  std::uniform_int_distribution<uint8_t> dis_uint8(0, 255);
  std::uniform_int_distribution<uint16_t> dis_uint16(0, 65535);

  for (int i = 0; i < 300; i++) {
    std::vector<uint8_t> bytes(dis_uint16(gen));
    for (int j = 0; j < bytes.size(); j++) {
      bytes[j] = dis_uint8(gen);
    }

    std::vector<uint8_t> compressed_bytes = sbox::compress_bytes(bytes);
    std::vector<uint8_t> decompressed_bytes =
        sbox::decompress_bytes(compressed_bytes);

    EXPECT_EQ(bytes.size(), decompressed_bytes.size());
    for (int j = 0; j < bytes.size(); j++) {
      EXPECT_EQ(bytes[j], decompressed_bytes[j]);
    }
  }
}
