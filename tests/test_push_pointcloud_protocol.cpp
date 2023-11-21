/// @file
/// @author Jongkuk Lim <limjk@jmarple.ai>
/// @copyright 2023 J.Marple
/// @brief Test for converting data into byte array

#include <gtest/gtest.h>

#include <random>
#include <vector>

#include "flexxlam_msgs/PointCloud2.hpp"
#include "protocol/push/push_pointcloud_protocol.hpp"

using std::vector;

bool is_pointcloud_same(const flexxlam_msgs::PointCloud2 &a,
                        const flexxlam_msgs::PointCloud2 &b) {
  EXPECT_EQ(a.timestamp_sec, b.timestamp_sec);
  EXPECT_EQ(a.timestamp_nsec, b.timestamp_nsec);

  EXPECT_EQ(a.frame_id, b.frame_id);

  EXPECT_EQ(a.height, b.height);
  EXPECT_EQ(a.width, b.width);
  EXPECT_EQ(a.fields.size(), b.fields.size());
  for (int i = 0; i < a.fields.size(); i++) {
    if (i >= b.fields.size()) {
      return false;
    }

    EXPECT_EQ(a.fields[i].name, b.fields[i].name);
    EXPECT_EQ(a.fields[i].offset, b.fields[i].offset);
    EXPECT_EQ(a.fields[i].datatype, b.fields[i].datatype);
    EXPECT_EQ(a.fields[i].count, b.fields[i].count);
  }
  EXPECT_EQ(a.is_bigendian, b.is_bigendian);
  EXPECT_EQ(a.point_step, b.point_step);
  EXPECT_EQ(a.row_step, b.row_step);
  EXPECT_EQ(a.data.size(), b.data.size());
  for (int i = 0; i < a.data.size(); i++) {
    if (i >= b.data.size()) {
      return false;
    }

    EXPECT_EQ(a.data[i], b.data[i]);
  }
  EXPECT_EQ(a.is_dense, b.is_dense);

  return true;
}

TEST(PushPointCloudProtocol, ConstructorTest) {
  std::random_device rd;
  std::mt19937 gen(rd());

  std::uniform_int_distribution<uint32_t> dis_uint32(0, 4294967295);
  std::uniform_int_distribution<uint16_t> dis_uint16(0, 65200);
  std::uniform_int_distribution<uint8_t> dis_uint8(0, 255);

  std::uniform_int_distribution<uint8_t> dis_length(1, 16);
  std::uniform_int_distribution<uint8_t> dis_bool(0, 1);

  std::uniform_int_distribution<uint8_t> dis_char(33, 126);

  for (int i = 0; i < 100; i++) {
    flexxlam_msgs::PointCloud2 pointcloud;

    pointcloud.timestamp_sec = dis_uint32(gen);
    pointcloud.timestamp_nsec = dis_uint32(gen);
    pointcloud.height = dis_uint32(gen);
    std::string frame_id = "";
    for (int j = 0; j < dis_length(gen); j++) {
      frame_id += dis_char(gen);
    }
    pointcloud.frame_id = frame_id;

    pointcloud.width = dis_uint32(gen);
    pointcloud.fields.resize(dis_length(gen));
    for (int j = 0; j < pointcloud.fields.size(); j++) {
      std::string field_name = "";
      for (int k = 0; k < dis_length(gen); k++) {
        field_name += dis_char(gen);
      }

      pointcloud.fields[j].name = field_name;
      pointcloud.fields[j].offset = dis_uint32(gen);
      pointcloud.fields[j].datatype = dis_uint8(gen);
      pointcloud.fields[j].count = dis_uint32(gen);
    }
    pointcloud.is_bigendian = dis_bool(gen);
    pointcloud.point_step = dis_uint32(gen);
    pointcloud.row_step = dis_uint32(gen);
    pointcloud.data.resize(dis_uint16(gen));
    for (int j = 0; j < pointcloud.data.size(); j++) {
      pointcloud.data[j] = dis_uint8(gen);
    }
    pointcloud.is_dense = dis_bool(gen);

    // PointCloud2 to Protocol
    flexxlam::PushPointCloudProtocol protocol1(pointcloud);
    // Protocol to bytes
    vector<uint8_t> bytes = protocol1.encapsulate();
    // Bytes to Protocol
    flexxlam::PushPointCloudProtocol protocol2(bytes, /*payload_only=*/false);
    // Decapsulated bytes to Protocol
    flexxlam::PushPointCloudProtocol protocol3(protocol2.get_payload(),
                                               /*payload_only=*/true);

    EXPECT_TRUE(protocol1.is_valid());
    EXPECT_TRUE(protocol2.is_valid());
    EXPECT_TRUE(protocol3.is_valid());

    flexxlam_msgs::PointCloud2 pointcloud1 = protocol1.get_pointcloud();
    flexxlam_msgs::PointCloud2 pointcloud2 = protocol2.get_pointcloud();
    flexxlam_msgs::PointCloud2 pointcloud3 = protocol3.get_pointcloud();

    is_pointcloud_same(pointcloud, pointcloud1);
    is_pointcloud_same(pointcloud, pointcloud2);
    is_pointcloud_same(pointcloud, pointcloud3);
  }
}
