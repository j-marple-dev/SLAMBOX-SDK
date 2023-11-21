/// @file
/// @author Haneol Kim <hekim@jmarple.ai>
/// @copyright 2023 J.Marple
/// @brief Save PCD protocol for communication

#ifndef FLEXXLAM_SDK_INCLUDE_PROTOCOL_COMMAND_COMMAND_SAVE_PCD_PROTOCOL_HPP_
#define FLEXXLAM_SDK_INCLUDE_PROTOCOL_COMMAND_COMMAND_SAVE_PCD_PROTOCOL_HPP_

#include <glog/logging.h>

#include <vector>

#include "protocol/base_protocol.hpp"
#include "utils/to_bytes.hpp"

namespace flexxlam {

/// @brief Save PCD protocol
class CommandSavePCDProtocol : public BaseProtocol {
 public:
  /// @brief Command save PCD protocoll constructor
  /// @param save save pcd or not
  /// @param reset reset the pointcloud from buffer or not
  explicit CommandSavePCDProtocol(bool save, bool reset)
      : BaseProtocol(protocol::kModeCmdSavePCD), save_(save), reset_(reset) {
    this->payload_.push_back(save_);
    this->payload_.push_back(reset_);
  }

  /// @brief Command save PCD protocoll constructor
  /// @param bytes byte array of whole protocol or payload
  /// @param payload_only if trure, then bytes parameter contains only payload
  explicit CommandSavePCDProtocol(const std::vector<uint8_t> &bytes,
                                  bool payload_only = false)
      : BaseProtocol(bytes, protocol::kModeCmdSavePCD, payload_only) {
    this->init_from_payload_();
  }

  /// @copydoc BaseProtocol::handle_callback
  void handle_callback(
      const vector<ParsedMessageInterface *> &callbacks) override {
    for (auto callback : callbacks) {
      callback->on_command_save_pcd(this->save_, this->reset_);
    }
  }

  /// @brief Get save(save or not)
  /// @return save flag
  bool get_save() { return this->save_; }

  /// @brief Get reset(reset or not)
  /// @return reset flag
  bool get_reset() { return this->reset_; }

 protected:
  /// @brief initialize save_ and reset_ from payload
  void init_from_payload_() override {
    if (!this->is_valid()) {
      return;
    }
    this->save_ = (this->payload_[0] == 1);
    this->reset_ = (this->payload_[1] == 1);
  }

 private:
  /// @brief a flag used for saving the pcd map data
  bool save_;
  /// @brief a flag used for reset the pointcloud buffer of odometry algorithm
  bool reset_;
};
}  // namespace flexxlam

#endif  // FLEXXLAM_SDK_INCLUDE_PROTOCOL_COMMAND_COMMAND_SAVE_PCD_PROTOCOL_HPP_
