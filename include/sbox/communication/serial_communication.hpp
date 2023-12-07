/// @file
/// @author Jongkuk Lim <limjk@jmarple.ai>
/// @copyright 2023 J.Marple
/// @brief Serial communication

#ifndef SLAMBOX_SDK_INCLUDE_SBOX_COMMUNICATION_SERIAL_COMMUNICATION_HPP_
#define SLAMBOX_SDK_INCLUDE_SBOX_COMMUNICATION_SERIAL_COMMUNICATION_HPP_

#include <glog/logging.h>
#include <libserial/SerialPort.h>

#include <functional>
#include <map>
#include <string>
#include <thread>  // NOLINT
#include <vector>

using LibSerial::SerialPort;

namespace sbox {

/// @brief Serial communication
class SerialCommunication {
 public:
  /// @brief Serial communication constructor
  /// @param port_name port name to open
  /// @param baud_rate baud rate
  /// @details This constructor initialize `port_name` and `baud_rate`.
  SerialCommunication(const std::string &port_name, int baud_rate)
      : port_name_(port_name), baud_rate_(baud_rate) {}

  /// @brief Serial communication destructor
  /// @details This destructor closes serial port and stops thread.
  ~SerialCommunication() {
    if (this->serial_port_.IsOpen()) {
      this->serial_port_.Close();
    }
    this->stop();
  }

  /// @brief Start serial communication thread
  /// Once this function is called, serial communication thread is started in
  /// the background and listens to the serial port.
  void run();

  /// @brief Stop serial communication thread
  void stop();

  /// @brief Check if serial communication thread is running
  /// @return true if serial communication thread is running
  bool is_running() { return this->is_running_; }

  /// @brief Write bytes to serial port
  /// @param bytes bytes to write
  void write(std::vector<uint8_t> bytes);

  /// @brief Set callback function for serial Serial Communication
  /// @param callback callback function
  /// @details This function sets callback function for serial communication.
  /// Once data is received from serial port, callback function is called.
  /// @note Callback function should be set before calling `run()`.
  void set_callback(std::function<void(std::vector<uint8_t>)> callback) {
    this->callback_ = callback;
  }

  /// @brief Set baud rate
  /// @param baudrate baud rate
  /// @return true if baud rate is set successfully
  bool set_baudrate(int baudrate);

  /// @brief Get baud rate
  /// @return baud rate
  int get_baudrate() { return this->baud_rate_; }

  /// @brief Set callback function for serial Serial Communication
  /// @param fp callback function
  /// @param obj object of callback function
  /// @details This function sets callback function for serial communication.
  /// Once data is received from serial port, callback function is called.
  /// @note Callback function should be set before calling `run()`.
  template <class M, class T>
  void set_callback(void (T::*fp)(M), T *obj) {
    this->callback_ = std::bind(fp, obj, std::placeholders::_1);
  }

  /// @brief Baud rate map from int to `LibSerial::BaudRate`
  static const std::map<int, LibSerial::BaudRate> kBaudRateMap;

 private:
  /// @brief Open serial port
  /// @return true if serial port is opened successfully
  bool open_();

  /// @brief Close serial port
  /// @return true if serial port is closed successfully
  bool close_();

  /// @brief Serial communication thread
  void run_();

  /// @brief Port name
  std::string port_name_;

  /// @brief Baud rate
  int baud_rate_;

  /// @brief Serial port
  SerialPort serial_port_;

  /// @brief Serial communication thread running state
  bool is_running_ = false;

  /// @brief Serial communication thread
  std::thread run_thread_;

  /// @brief Callback function for serial communication
  std::function<void(std::vector<uint8_t>)> callback_ = nullptr;
};

}  // namespace sbox

#endif  // SLAMBOX_SDK_INCLUDE_SBOX_COMMUNICATION_SERIAL_COMMUNICATION_HPP_
