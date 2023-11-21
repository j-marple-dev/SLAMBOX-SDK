/// @file
/// @author Jongkuk Lim <limjk@jmarple.ai>
/// @copyright 2023 J.Marple
/// @brief Test for converting data into byte array

#include <gtest/gtest.h>

#include <random>
#include <vector>

#include "flexxlam_msgs/Odometry.hpp"
#include "protocol/push/push_odometry_protocol.hpp"

using std::vector;

bool is_odometry_same(flexxlam_msgs::Odometry a, flexxlam_msgs::Odometry b) {
  EXPECT_EQ(a.timestamp_sec, b.timestamp_sec);
  EXPECT_EQ(a.timestamp_nsec, b.timestamp_nsec);

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

TEST(PushOdometryProtocol, ConstructorTest) {
  std::random_device rd;
  std::mt19937 gen(rd());

  std::uniform_real_distribution<double> dis(-1000.0, 1000.0);
  std::uniform_int_distribution<uint32_t> dis_uint32(0, 4294967295);

  for (int i = 0; i < 1000; i++) {
    flexxlam_msgs::Odometry odom;

    odom.timestamp_sec = dis_uint32(gen);
    odom.timestamp_nsec = dis_uint32(gen);
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

    // Odom to protocol
    flexxlam::PushOdometryProtocol protocol1(odom);
    vector<uint8_t> bytes = protocol1.encapsulate();

    // Encapsulated bytes to protocol
    flexxlam::PushOdometryProtocol protocol2(bytes, /*payload_only=*/false);

    // Decapsulated bytes to protocol
    flexxlam::PushOdometryProtocol protocol3(protocol1.get_payload(),
                                             /*payload_only=*/true);

    flexxlam_msgs::Odometry odom1 = protocol1.get_odometry();
    flexxlam_msgs::Odometry odom2 = protocol2.get_odometry();
    flexxlam_msgs::Odometry odom3 = protocol3.get_odometry();

    is_odometry_same(odom, odom1);
    is_odometry_same(odom, odom2);
    is_odometry_same(odom, odom3);
  }
}
