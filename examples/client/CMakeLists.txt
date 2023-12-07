cmake_minimum_required(VERSION 3.0.2)
project(flexxlam_client_example)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")

find_package(glog 0.6.0 REQUIRED)

add_executable(flexxlam_client_example flexxlam_client_example_app.cpp flexxlam_client_example.cpp)

if (NOT DEFINED slambox_sdk_LIBRARIES)
  find_package(slambox_sdk 0.0.1 REQUIRED)
else()
  set(slambox_sdk_LIBRARIES ${slambox_sdk_LIBRARIES};slambox_sdk_static)
endif()

target_link_libraries(flexxlam_client_example
  glog::glog
  ${slambox_sdk_LIBRARIES}
  )

