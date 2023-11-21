/// @file
/// @author Jongkuk Lim <limjk@jmarple.ai>
/// @copyright 2023 J.Marple
/// @brief Test for converting data into byte array

#include <gtest/gtest.h>

#include <random>
#include <vector>

#include "utils/to_bytes.hpp"

using std::vector;

TEST(ToBytes, ByteConversionFloat) {
  std::random_device rd;
  std::mt19937 gen(rd());

  std::uniform_real_distribution<float> dis(-1000.0, 1000.0);

  for (int i = 0; i < 1000; i++) {
    float x = dis(gen);
    vector<uint8_t> bytes = flexxlam::to_bytes::four(x);
    float y = flexxlam::from_bytes::to_float(bytes);

    EXPECT_FLOAT_EQ(x, y);
  }
}

TEST(ToBytes, ByteConversionDouble) {
  std::random_device rd;
  std::mt19937 gen(rd());

  std::uniform_real_distribution<double> dis(-1000.0, 1000.0);

  for (int i = 0; i < 1000; i++) {
    double x = dis(gen);
    vector<uint8_t> bytes = flexxlam::to_bytes::four(x);
    float y = flexxlam::from_bytes::to_float(bytes);

    EXPECT_FLOAT_EQ(x, y);
  }
}

TEST(ToBytes, ByteConversionFloatArray) {
  std::random_device rd;
  std::mt19937 gen(rd());

  std::uniform_real_distribution<float> dis(-1000.0, 1000.0);
  std::uniform_int_distribution<int> dis_length(1, 1000);

  for (int i = 0; i < 1000; i++) {
    int length = dis_length(gen);
    vector<float> x(length);
    for (int j = 0; j < length; j++) {
      x[j] = dis(gen);
    }

    vector<uint8_t> bytes = flexxlam::to_bytes::four(x);
    vector<float> y(length);
    for (int j = 0; j < length; j++) {
      y[j] = flexxlam::from_bytes::to_float(bytes, j * 4);
    }

    for (int j = 0; j < length; j++) {
      EXPECT_FLOAT_EQ(x[j], y[j]);
    }
  }
}

TEST(ToBytes, ByteConversionFloatOffset) {
  std::random_device rd;
  std::mt19937 gen(rd());

  std::uniform_real_distribution<float> dis(-1000.0, 1000.0);
  std::uniform_int_distribution<int> dis_offset(0, 995);

  vector<uint8_t> bytes(1000, 0);
  for (int i = 0; i < 1000; i++) {
    float x = dis(gen);
    int offset = dis_offset(gen);

    vector<uint8_t> data = flexxlam::to_bytes::four(x);

    for (int j = 0; j < 4; j++) {
      bytes[j + offset] = data[j];
    }

    float y = flexxlam::from_bytes::to_float(bytes, offset);

    EXPECT_FLOAT_EQ(x, y);
  }
}

TEST(ToBytes, ToInt) {
  std::random_device rd;
  std::mt19937 gen(rd());

  std::uniform_int_distribution<uint32_t> dis_4bytes(0, 4294967295);
  std::uniform_int_distribution<uint32_t> dis_2bytes(0, 65535);

  for (int i = 0; i < 1000; i++) {
    uint32_t x2 = dis_2bytes(gen);
    vector<uint8_t> bytes2 = flexxlam::to_bytes::two(x2);
    uint32_t y2 = flexxlam::from_bytes::to_int(bytes2);

    EXPECT_EQ(bytes2.size(), 2);
    EXPECT_EQ(x2, y2);

    uint32_t x4 = dis_4bytes(gen);
    vector<uint8_t> bytes4 = flexxlam::to_bytes::four(x4);
    uint32_t y4 = flexxlam::from_bytes::to_int(bytes4);

    EXPECT_EQ(bytes4.size(), 4);
    EXPECT_EQ(x4, y4);
  }
}

TEST(ToBytes, ToString) {
  std::random_device rd;
  std::mt19937 gen(rd());

  std::uniform_int_distribution<uint8_t> dis_length(1, 255);
  std::uniform_int_distribution<uint8_t> dis_char(0, 26);
  std::uniform_int_distribution<uint8_t> dis_bool(0, 1);

  for (int i = 0; i < 1000; i++) {
    uint8_t length = dis_length(gen);
    std::string str(length, 'a');

    for (int j = 0; j < length; j++) {
      if (dis_bool(gen)) {
        str[j] = 'A' + dis_char(gen);
      } else {
        str[j] = 'a' + dis_char(gen);
      }
    }

    vector<uint8_t> bytes = flexxlam::to_bytes::from_string(str);
    std::string str2 = flexxlam::from_bytes::to_string(bytes);

    EXPECT_EQ(str, str2);
  }

  // Test for offset conversion
  for (int i = 0; i < 1000; i++) {
    uint8_t append_length = dis_length(gen);
    vector<uint8_t> bytes;
    vector<std::string> answers;

    for (int j = 0; j < append_length; j++) {
      uint8_t length = dis_length(gen);
      std::string str(length, 'a');
      if (dis_bool(gen)) {
        str[0] = 'A' + dis_char(gen);
      } else {
        str[0] = 'a' + dis_char(gen);
      }

      vector<uint8_t> append_bytes = flexxlam::to_bytes::from_string(str);
      bytes.insert(bytes.end(), append_bytes.begin(), append_bytes.end());
      answers.push_back(str);
    }

    size_t offset = 0;
    for (int j = 0; j < append_length; j++) {
      std::string str = flexxlam::from_bytes::to_string(bytes, offset);
      EXPECT_EQ(str, answers[j]);
      offset += str.size() + 1;
    }
  }
}
