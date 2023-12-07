/// @file
/// @author Jongkuk Lim <limjk@jmarple.ai>
/// @copyright 2023 J.Marple
/// @brief FlexXlam ROS Driver client node

#include <glog/logging.h>

#include "include/flexxlam_client_example.hpp"

/// @brief Main node for FlexXlam Driver Server
/// @param argc Number of arguments
/// @param argv arguments
///
/// @return 0
int main(int argc, char **argv) {
  FLAGS_stderrthreshold = google::INFO;
  FLAGS_colorlogtostderr = true;
  google::InitGoogleLogging(argv[0]);

  FlexXlamClientExample driver_client;

  LOG(INFO) << "FlexXlam client node is running.";

  while (true) {
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }

  return 0;
}
