/// @file
/// @author Jongkuk Lim <limjk@jmarple.ai>
/// @copyright 2023 J.Marple
/// @brief Serial communication

#include "sbox/communication/serial_communication.hpp"

#include <libserial/SerialPortConstants.h>
#include <exception>

namespace sbox {

bool SerialCommunication::open_() {
  LibSerial::BaudRate baud_rate_libserial = LibSerial::BaudRate::BAUD_115200;

  if (SerialCommunication::kBaudRateMap.find(this->baud_rate_) !=
      SerialCommunication::kBaudRateMap.end()) {
    baud_rate_libserial =
        SerialCommunication::kBaudRateMap.at(this->baud_rate_);
  } else {
    LOG(ERROR) << "Invalid baud rate: " << this->baud_rate_;
    return false;
  }

  try {
    if (this->serial_port_.IsOpen() &&
        this->serial_port_.GetBaudRate() == baud_rate_libserial) {
      LOG(INFO) << "Serial port is already opened";
      return true;
    }

    if (!this->serial_port_.IsOpen()) {
      this->serial_port_.Open(this->port_name_);
    }

    this->serial_port_.SetBaudRate(baud_rate_libserial);
    this->serial_port_.SetCharacterSize(LibSerial::CharacterSize::CHAR_SIZE_8);
    this->serial_port_.SetFlowControl(
        LibSerial::FlowControl::FLOW_CONTROL_NONE);
    this->serial_port_.SetParity(LibSerial::Parity::PARITY_NONE);
    this->serial_port_.SetStopBits(LibSerial::StopBits::STOP_BITS_1);
  } catch (const LibSerial::OpenFailed &) {
    LOG(ERROR) << "Serial port " << this->port_name_ << " with baudrate "
               << this->baud_rate_ << " failed to open";
    return false;
  }

  return true;
}

bool SerialCommunication::set_baudrate(int baud_rate) {
  if (SerialCommunication::kBaudRateMap.find(baud_rate) ==
      SerialCommunication::kBaudRateMap.end()) {
    LOG(ERROR) << "Invalid baud rate: " << baud_rate;
    return false;
  }

  if (!this->serial_port_.IsOpen()) {
    LOG(ERROR) << "Serial port is not opened";
    return false;
  }

  try {
    this->serial_port_.SetBaudRate(
        SerialCommunication::kBaudRateMap.at(baud_rate));
    this->baud_rate_ = baud_rate;
  } catch (std::exception &e) {
    LOG(ERROR) << "Setting baudrate failed " << baud_rate << " with exception "
               << e.what();
    return false;
  }

  return true;
}

void SerialCommunication::write(std::vector<uint8_t> bytes) {
  if (!this->serial_port_.IsOpen()) {
    LOG(ERROR) << "Serial port is not opened";
    return;
  }

  this->serial_port_.Write(bytes);
  this->serial_port_.DrainWriteBuffer();
}

void SerialCommunication::run() {
  if (!this->open_()) {
    LOG(ERROR) << "Serial port " << this->port_name_ << " with baudrate "
               << this->baud_rate_ << " failed to open";
    return;
  }

  this->is_running_ = true;
  this->run_thread_ = std::thread(&SerialCommunication::run_, this);
}

void SerialCommunication::stop() {
  this->is_running_ = false;
  if (this->run_thread_.joinable()) {
    this->run_thread_.join();
  }

  if (this->serial_port_.IsOpen()) {
    this->serial_port_.DrainWriteBuffer();
    this->serial_port_.Close();
  }
}

void SerialCommunication::run_() {
  while (this->is_running_) {
    std::vector<uint8_t> data;

    try {
      this->serial_port_.Read(data, 0, 2);
    } catch (const LibSerial::ReadTimeout &) {
    }

    if (data.size() == 0) {
      std::this_thread::sleep_for(std::chrono::milliseconds(1));
      continue;
    }

    if (this->callback_ != nullptr) {
      this->callback_(data);
    }
  }
}

const std::map<int, LibSerial::BaudRate> SerialCommunication::kBaudRateMap = {
    {9600, LibSerial::BaudRate::BAUD_9600},
    {19200, LibSerial::BaudRate::BAUD_19200},
    {38400, LibSerial::BaudRate::BAUD_57600},
    {115200, LibSerial::BaudRate::BAUD_115200},
    {230400, LibSerial::BaudRate::BAUD_230400},
    {460800, LibSerial::BaudRate::BAUD_460800},
    {921600, LibSerial::BaudRate::BAUD_921600},
    {1000000, LibSerial::BaudRate::BAUD_1000000},
    {1152000, LibSerial::BaudRate::BAUD_1152000},
    {1500000, LibSerial::BaudRate::BAUD_1500000},
    {2000000, LibSerial::BaudRate::BAUD_2000000},
    {2500000, LibSerial::BaudRate::BAUD_2500000},
    {3000000, LibSerial::BaudRate::BAUD_3000000},
    {3500000, LibSerial::BaudRate::BAUD_3500000},
    {4000000, LibSerial::BaudRate::BAUD_4000000},
};

}  // namespace sbox
