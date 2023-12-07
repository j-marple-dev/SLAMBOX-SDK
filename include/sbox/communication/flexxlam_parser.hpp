/// @file
/// @author Jongkuk Lim <limjk@jmarple.ai>
/// @copyright 2023 J.Marple
/// @brief Base parser for FlexXlam Driver

#ifndef SLAMBOX_SDK_INCLUDE_SBOX_COMMUNICATION_FLEXXLAM_PARSER_HPP_
#define SLAMBOX_SDK_INCLUDE_SBOX_COMMUNICATION_FLEXXLAM_PARSER_HPP_

#include <cstdint>
#include <vector>

#include "sbox/flexxlam_msgs/Odometry.hpp"
#include "sbox/flexxlam_msgs/PointCloud2.hpp"

using std::vector;

/// @brief FlexXlam Driver namespace
namespace sbox {

/// @brief Parsed message interface
struct ParsedMessageInterface {
  /// @brief Get odometry callback
  /// @param odom odometry
  /// @details This function is called when odometry is parsed.
  virtual void on_push_odometry(const sbox_msgs::Odometry &odom) {}

  /// @brief Get pointcloud callback
  /// @param pointcloud pointcloud
  /// @details This function is called when pointcloud is parsed.
  virtual void on_push_pointcloud(
      const sbox_msgs::PointCloud2 &pointcloud) {}

  /// @brief Request communication config callback
  /// @param type communication type. Please refer to `protocol::kCommType*`
  /// @details This function is called when request communication config is
  /// parsed.
  virtual void on_request_communication_config(uint8_t type) {}

  /// @{
  /// @brief Request config value from server callback
  virtual void on_request_mavlink_communication_config() {}
  virtual void on_request_serial_communication_config() {}
  virtual void on_request_ethernet_communication_config() {}
  virtual void on_request_lidar_config() {}
  /// @}

  /// @brief Response mavlink communication config callback
  /// @param enabled enabled or not
  /// @param baudrate baudrate of mavlink communication
  virtual void on_response_mavlink_communication_config(bool enabled,
                                                        uint32_t baudrate) {}

  /// @brief Response serial communication config callback
  /// @param enabled enabled or not
  /// @param baudrate baudrate of serial communication
  virtual void on_response_serial_communication_config(bool enabled,
                                                       uint32_t baudrate) {}

  /// @brief Response ethernet communication config callback
  /// @param enabled enabled or not
  /// @param port port number of ethernet communication
  virtual void on_response_ethernet_communication_config(bool enabled,
                                                         uint32_t port) {}

  /// @brief Response lidar config callback
  /// @param lidar_type lidar type defined in `protocol::kLidar*`
  virtual void on_response_lidar_config(uint8_t lidar_type) {}

  /// @brief Set mavlink communication config callback
  /// @param enabled enabled or not
  /// @param baudrate baudrate of mavlink communication
  virtual void on_set_mavlink_communication_config(bool enabled,
                                                   uint32_t baudrate) {}

  /// @brief Set serial communication config callback
  /// @param enabled enabled or not
  /// @param baudrate baudrate of serial communication
  virtual void on_set_serial_communication_config(bool enabled,
                                                  uint32_t baudrate) {}

  /// @brief Set ethernet communication config callback
  /// @param enabled enabled or not
  /// @param port port number of ethernet communication
  virtual void on_set_ethernet_communication_config(bool enabled,
                                                    uint32_t port) {}

  /// @brief Set lidar config callback
  /// @param lidar_type lidar type defined in `protocol::kLidar*`
  virtual void on_set_lidar_config(uint8_t lidar_type) {}

  /// @brief Save PCD command data callback
  /// @param save save to PCD or not
  /// @param reset reset the map pointcloud buffer or not
  /// @details This fuction is called when save command is parsed.
  virtual void on_command_save_pcd(bool save, bool reset) {}

  /// @brief Restart LIO command callback
  /// @details This function is called when restart LIO command is parsed.
  virtual void on_command_restart_lio() {}

  /// @brief Ping callback
  /// @details This function is called when ping is parsed.
  virtual void on_ping() {}

  /// @brief Acknowledge callback
  /// @param requested_mode requested mode
  /// @param status status
  /// @details This function is called when acknowledge is parsed.
  virtual void on_acknowledge(std::array<uint8_t, 2> requested_mode,
                              uint8_t status) {}
};

/// @brief Protocol parser for FlexXlam Driver
class FlexXlamParser {
 public:
  /// @brief Protocol parser constructor
  /// @param buffer_size size of buffer
  explicit FlexXlamParser(size_t buffer_size = 1024)
      : buffer_size_(buffer_size) {
    buffer_.reserve(buffer_size_ * 2);
  }

  /// @brief Parse byte array
  /// @param data byte array
  /// @details This function parses byte array and then call
  /// parsed_message_callback.
  void parse(vector<uint8_t> data);

  /// @brief Add parsed message callback
  /// @param parsed_message_interface parsed message interface
  void add_parsed_message_callback(
      ParsedMessageInterface *parsed_message_interface);

 private:
  /// @brief Find header in `buffer_`
  /// @return true if header is found
  /// @details This function finds header in `buffer_` while erasing data
  /// before header.
  bool find_header_();

  /// @brief Decapsulate payload and call parsed message callback
  /// @param mode mode
  /// @param payload payload
  /// @details This function decapsulates payload and then call registered
  /// callbacks.
  void decapsulate_payload_(const std::array<uint8_t, 2> &mode,
                            const vector<uint8_t> &payload);

  /// @brief Check if length is valid by comparing with mode
  /// @param mode mode
  /// @param length length
  /// @return true if length is valid
  bool is_length_valid_(std::array<uint8_t, 2> mode, uint16_t length);

  /// @brief Byte array for decapsulation
  vector<uint8_t> buffer_;

  /// @brief Size of buffer
  size_t buffer_size_;

  /// @brief Parsed message interface callbacks
  vector<ParsedMessageInterface *> parsed_message_interfaces_;
};

}  // namespace sbox

#endif  // SLAMBOX_SDK_INCLUDE_SBOX_COMMUNICATION_FLEXXLAM_PARSER_HPP_
