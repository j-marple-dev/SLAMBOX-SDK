/// @file
/// @author Jongkuk Lim <limjk@jmarple.ai>
/// @copyright 2023 J.Marple
/// @brief Converting data into byte array

#ifndef SLAMBOX_SDK_INCLUDE_SBOX_UTILS_TO_BYTES_HPP_
#define SLAMBOX_SDK_INCLUDE_SBOX_UTILS_TO_BYTES_HPP_

#include <cstdint>
#include <string>
#include <vector>

using std::vector;

/// @brief Convert data into byte array
namespace flexxlam::to_bytes {

/// @brief Convert string to byte array
/// @param str string to convert
/// @return byte array
/// The length of the byte array is 1 + length of the string.
/// The first byte is the length of the string.
/// The maximum length of the string is 255.
/// If the length of the string is greater than 255, then only first 255
/// characters will be sent.
vector<uint8_t> from_string(std::string str);

/// @brief Convert double to 4 bytes
/// This function converts double to float and then convert it to 4
/// bytes.
///
/// @param x double value
/// @return 4 bytes
vector<uint8_t> four(double x);

/// @brief Convert float to 4 bytes
/// @param x float value
/// @return 4 bytes
vector<uint8_t> four(float x);

/// @brief Convert double array to byte array
/// This function converts double array to float array and then convert
/// it to byte array.
///
/// @param x double array
/// @return byte array
/// The length of the byte array is 4 * length.
vector<uint8_t> four(vector<double> x);

/// @brief Convert float array to byte array
/// @param x float array
/// @return byte array
/// The length of the byte array is 4 * length.
vector<uint8_t> four(vector<float> x);

/// @brief Convert uint32_t to 4 bytes with little endian
/// @param x uint32_t value
/// @return 4 bytes
vector<uint8_t> four(uint32_t x);

/// @brief Convert int to 2 bytes with little endian
/// @param x int value (This assume that x is less than 65536)
/// @return 2 bytes
vector<uint8_t> two(uint32_t x);

}  // namespace flexxlam::to_bytes

/// @brief Convert byte array into data
namespace flexxlam::from_bytes {

/// @brief Convert 4 bytes to float
/// @param bytes bytes to convert
/// @param offset offset to start converting
/// @return float value
float to_float(vector<uint8_t> bytes, int offset = 0);

/// @brief Convert 1~4 bytes to int
/// @param bytes bytes to convert
/// @return int value
uint32_t to_int(vector<uint8_t> bytes);

/// @brief Convert byte array to string
/// @param bytes bytes to convert
/// @param offset offset index to start converting
/// @return string
std::string to_string(vector<uint8_t> bytes, size_t offset = 0);
}  // namespace flexxlam::from_bytes

#endif  // SLAMBOX_SDK_INCLUDE_SBOX_UTILS_TO_BYTES_HPP_
