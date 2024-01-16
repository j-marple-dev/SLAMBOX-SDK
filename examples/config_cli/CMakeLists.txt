cmake_minimum_required(VERSION 3.0.2)
project(slambox_serial_config_cli_example)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")

find_package(glog 0.6.0 REQUIRED)

add_executable(slambox_serial_config_cli_example config_cli.cpp config_cli_app.cpp)

if (NOT DEFINED slambox_sdk_LIBRARIES)
  find_package(slambox_sdk 0.2.0 REQUIRED)
else()
  set(slambox_sdk_LIBRARIES ${slambox_sdk_LIBRARIES};slambox_sdk_static)
endif()

target_link_libraries(slambox_serial_config_cli_example
  glog::glog
  cli::cli
  ${slambox_sdk_LIBRARIES}
  )

add_subdirectory("libs/cli")

