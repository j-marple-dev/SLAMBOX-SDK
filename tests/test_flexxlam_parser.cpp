/// @file
/// @author Jongkuk Lim <limjk@jmarple.ai>
/// @copyright 2023 J.Marple
/// @brief Test for FlexXlam Parse

#include <gtest/gtest.h>

#include <random>
#include <vector>

#include "sbox/communication/flexxlam_parser.hpp"
#include "sbox/flexxlam_msgs/Odometry.hpp"
#include "sbox/protocol/push/push_odometry_protocol.hpp"

using std::vector;

bool is_odometry_same(flexxlam_msgs::Odometry a, flexxlam_msgs::Odometry b) {
  EXPECT_FLOAT_EQ(a.pose.position.x, b.pose.position.x);
  EXPECT_FLOAT_EQ(a.pose.position.y, b.pose.position.y);
  EXPECT_FLOAT_EQ(a.pose.position.z, b.pose.position.z);
  EXPECT_FLOAT_EQ(a.pose.orientation.x, b.pose.orientation.x);
  EXPECT_FLOAT_EQ(a.pose.orientation.y, b.pose.orientation.y);
  EXPECT_FLOAT_EQ(a.pose.orientation.z, b.pose.orientation.z);
  EXPECT_FLOAT_EQ(a.pose.orientation.w, b.pose.orientation.w);
  for (int j = 0; j < 36; j++) {
    EXPECT_FLOAT_EQ(a.pose.covariance[j], b.pose.covariance[j]);
  }
  EXPECT_FLOAT_EQ(a.twist.linear.x, b.twist.linear.x);
  EXPECT_FLOAT_EQ(a.twist.linear.y, b.twist.linear.y);
  EXPECT_FLOAT_EQ(a.twist.linear.z, b.twist.linear.z);
  EXPECT_FLOAT_EQ(a.twist.angular.x, b.twist.angular.x);
  EXPECT_FLOAT_EQ(a.twist.angular.y, b.twist.angular.y);
  EXPECT_FLOAT_EQ(a.twist.angular.z, b.twist.angular.z);
  for (int j = 0; j < 36; j++) {
    EXPECT_FLOAT_EQ(a.twist.covariance[j], b.twist.covariance[j]);
  }

  return true;
}

TEST(FlexXlamParser, PushOdometryProtocolParse) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<double> dis(-1000, 1000);
  std::uniform_int_distribution<int> dis_int(0, 100);
  std::uniform_int_distribution<uint8_t> dis_uint8(0, 255);

  flexxlam::FlexXlamParser parser;
  struct TestParsedMessageInterface : public flexxlam::ParsedMessageInterface {
    void on_push_odometry(const flexxlam_msgs::Odometry &odom) override {
      is_odometry_same(expected_odom, odom);
    }
    flexxlam_msgs::Odometry expected_odom;
  } test_parsed_message_interface;
  parser.add_parsed_message_callback(&test_parsed_message_interface);

  for (int i = 0; i < 100; i++) {
    flexxlam_msgs::Odometry odom;
    odom.pose.position.x = dis(gen);
    odom.pose.position.y = dis(gen);
    odom.pose.position.z = dis(gen);
    odom.pose.orientation.x = dis(gen);
    odom.pose.orientation.y = dis(gen);
    odom.pose.orientation.z = dis(gen);
    odom.pose.orientation.w = dis(gen);
    for (int j = 0; j < 36; j++) {
      odom.pose.covariance[j] = dis(gen);
    }
    odom.twist.linear.x = dis(gen);
    odom.twist.linear.y = dis(gen);
    odom.twist.linear.z = dis(gen);
    odom.twist.angular.x = dis(gen);
    odom.twist.angular.y = dis(gen);
    odom.twist.angular.z = dis(gen);
    for (int j = 0; j < 36; j++) {
      odom.twist.covariance[j] = dis(gen);
    }
    test_parsed_message_interface.expected_odom = odom;

    flexxlam::PushOdometryProtocol protocol(odom);
    vector<uint8_t> pre_random_bytes;
    vector<uint8_t> post_random_bytes;
    for (int j = 0; j < dis_int(gen); j++) {
      pre_random_bytes.push_back(dis_uint8(gen));
    }
    for (int j = 0; j < dis_int(gen); j++) {
      post_random_bytes.push_back(dis_uint8(gen));
    }
    vector<uint8_t> bytes = protocol.encapsulate();
    bytes.insert(bytes.begin(), pre_random_bytes.begin(),
                 pre_random_bytes.end());
    bytes.insert(bytes.end(), post_random_bytes.begin(),
                 post_random_bytes.end());
    parser.parse(bytes);
  }
}

TEST(FlexXlamParser, PushOdometryProtocolParseBatch) {
  std::random_device rd;
  std::mt19937 gen(rd());

  std::uniform_real_distribution<double> dis(-1000, 1000);
  std::uniform_int_distribution<int> dis_int(1, 100);
  std::uniform_int_distribution<uint8_t> dis_uint8(0, 255);

  flexxlam::FlexXlamParser parser(102400);
  struct TestParsedMessageInterface : public flexxlam::ParsedMessageInterface {
    void on_push_odometry(const flexxlam_msgs::Odometry &odom) override {
      is_odometry_same(expected_odoms[odom_idx++], odom);
    }
    vector<flexxlam_msgs::Odometry> expected_odoms;
    int odom_idx = 0;
  } test_parsed_message_interface;
  parser.add_parsed_message_callback(&test_parsed_message_interface);

  for (int i = 0; i < 100; i++) {
    int batch_size = dis_int(gen);
    vector<uint8_t> bytes;
    vector<flexxlam_msgs::Odometry> odoms(batch_size);

    for (int j = 0; j < batch_size; j++) {
      flexxlam_msgs::Odometry odom;
      odom.pose.position.x = dis(gen);
      odom.pose.position.y = dis(gen);
      odom.pose.position.z = dis(gen);
      odom.pose.orientation.x = dis(gen);
      odom.pose.orientation.y = dis(gen);
      odom.pose.orientation.z = dis(gen);
      odom.pose.orientation.w = dis(gen);
      for (int k = 0; k < 36; k++) {
        odom.pose.covariance[k] = dis(gen);
      }
      odom.twist.linear.x = dis(gen);
      odom.twist.linear.y = dis(gen);
      odom.twist.linear.z = dis(gen);
      odom.twist.angular.x = dis(gen);
      odom.twist.angular.y = dis(gen);
      odom.twist.angular.z = dis(gen);
      for (int k = 0; k < 36; k++) {
        odom.twist.covariance[k] = dis(gen);
      }
      odoms[j] = odom;
      flexxlam::PushOdometryProtocol protocol(odom);

      vector<uint8_t> pre_random_bytes(dis_int(gen));
      for (int k = 0; k < pre_random_bytes.size(); k++) {
        pre_random_bytes[k] = dis_uint8(gen);
      }
      vector<uint8_t> post_random_bytes(dis_int(gen));
      for (int k = 0; k < post_random_bytes.size(); k++) {
        post_random_bytes[k] = dis_uint8(gen);
      }

      vector<uint8_t> bytes_ = protocol.encapsulate();
      bytes_.insert(bytes_.begin(), pre_random_bytes.begin(),
                    pre_random_bytes.end());
      bytes_.insert(bytes_.end(), post_random_bytes.begin(),
                    post_random_bytes.end());

      bytes.insert(bytes.end(), bytes_.begin(), bytes_.end());
    }
    test_parsed_message_interface.expected_odoms = odoms;
    test_parsed_message_interface.odom_idx = 0;

    parser.parse(bytes);

    EXPECT_EQ(test_parsed_message_interface.odom_idx, batch_size);
  }
}
