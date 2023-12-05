cmake_minimum_required(VERSION 3.0.2)
project(flexxlam_sdk
  VERSION 0.0.3
  LANGUAGES CXX
  )

include(CMakePackageConfigHelpers)

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

option(test "Build unit tests." OFF)

set(INSTALL_STATIC "Install static library" ON)
set(INSTALL_SHARED "Install shared library" ON)
set(BUILD_EXAMPLES "Build examples" ON)

set (CPACK_PACKAGE_NAME ${PROJECT_NAME})
set (CPACK_PACKAGE_DESCRIPTION_SUMMARY "FlexXlam SDK")
set (CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set (CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set (CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
set (CPACK_PACKAGE_VERSION ${PROJECT_VERSION})

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")

include (CPack)

## Compile as C++17, supported in ROS Kinetic and newer
add_compile_options(-std=c++17 -O3)

find_package(ZLIB REQUIRED)
find_package(Threads REQUIRED)

include_directories(
  include
)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

set(${PROJECT_NAME}_LIBRARIES
  ZLIB::ZLIB
  Threads::Threads
  serial)

add_library(${PROJECT_NAME}_static STATIC "")
set_target_properties(${PROJECT_NAME}_static PROPERTIES OUTPUT_NAME ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}_static PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_sources(${PROJECT_NAME}_static PUBLIC
    ${SOURCES}
)
target_link_libraries(${PROJECT_NAME}_static
  PRIVATE
  ${${PROJECT_NAME}_LIBRARIES}
)

configure_package_config_file(
    "${CMAKE_CURRENT_LIST_DIR}/${PROJECT_NAME}Config.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
    INSTALL_DESTINATION lib/cmake/${PROJECT_NAME}
)

install(DIRECTORY include/
    DESTINATION include ${CMAKE_INSTALL_INCLUDEDIR}
)
install(
    FILES
      "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
      "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
    DESTINATION lib/cmake/${PROJECT_NAME}
)

if (INSTALL_STATIC)
  install(TARGETS ${PROJECT_NAME}_static
      EXPORT ${PROJECT_NAME}Config
      ARCHIVE DESTINATION lib
      LIBRARY DESTINATION lib
      RUNTIME DESTINATION bin
      )
endif()

if (INSTALL_SHARED)
  add_library(${PROJECT_NAME}_shared SHARED "")
  set_target_properties(${PROJECT_NAME}_shared PROPERTIES OUTPUT_NAME ${PROJECT_NAME})

  target_include_directories(${PROJECT_NAME}_shared PUBLIC
      ${CMAKE_CURRENT_SOURCE_DIR}/include
  )
  target_sources(${PROJECT_NAME}_shared PUBLIC
      ${SOURCES}
  )
  target_link_libraries(${PROJECT_NAME}_shared
    PRIVATE
  ${${PROJECT_NAME}_LIBRARIES}
  )

  install(TARGETS ${PROJECT_NAME}_shared
      ARCHIVE DESTINATION lib
      LIBRARY DESTINATION lib
      RUNTIME DESTINATION bin
      )
endif()

# Examples
if (BUILD_EXAMPLES)
  add_subdirectory(examples/client)
endif()

# Unit test
if (test)
    set(TEST_NAME_BASE test-${PROJECT_NAME})

    find_package(glog 0.6.0 REQUIRED)
    enable_testing()

    include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

    # Auto adding unit test files starting with test_*.cpp
    FILE(GLOB UNITTEST_LIST CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/tests/test_*.cpp")
    FOREACH(unittest_path ${UNITTEST_LIST})
        get_filename_component(unittest_name ${unittest_path} NAME_WLE)
        string(REPLACE "test_" "" unittest_name ${unittest_name})
        set(TEST_NAME ${TEST_NAME_BASE}-${unittest_name})

        message("Build Unit Test for ${unittest_path} with name of ${TEST_NAME}")

        add_executable(${TEST_NAME} ${unittest_path} ${SOURCES})

        target_link_libraries(${TEST_NAME}
            gtest
            gtest_main
            glog::glog
            ${PROJECT_NAME}_static
        )

        add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
    ENDFOREACH()
endif()
