/// @file
/// @author Jongkuk Lim <limjk@jmarple.ai>
/// @copyright 2023 J.Marple
/// @brief SLAMBOX Client example

#include <glog/logging.h>

#include "include/slambox_client_example.hpp"

/// @brief Main node for SlamBox Driver Server
/// @param argc Number of arguments
/// @param argv arguments
///
/// @return 0
int main(int argc, char **argv) {
  FLAGS_stderrthreshold = google::INFO;
  FLAGS_colorlogtostderr = true;
  google::InitGoogleLogging(argv[0]);

  SlamBoxClientExample driver_client;

  LOG(INFO) << "SlamBox client node is running.";

  while (true) {
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }

  return 0;
}
