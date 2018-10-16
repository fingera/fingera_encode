#include <fingera/encode/base32.h>

#include <stdint.h>
#include <stdio.h>
#include <string>

#include <fingera/encode/hex.h>
#include <gtest/gtest.h>

#define EXPECT_ZERO(x) EXPECT_EQ((x), 0)

std::vector<uint8_t> as_vector(const std::string &str) {
  return std::vector<uint8_t>(str.begin(), str.end());
}

std::string as_string(const std::vector<uint8_t> &buf) {
  return std::string(buf.begin(), buf.end());
}

TEST(base32, custom) {
  static const std::string vstrIn[] = {
      "", "f", "fo", "foo", "foob", "fooba", "foobar", "abcdefghijklmn"};
  static const std::string vstrOut[] = {
      "",         "my======", "mzxq====",         "mzxw6===",
      "mzxw6yq=", "mzxw6ytb", "mzxw6ytboi======", "mfrggzdfmztwq2lknnwg23q="};

  char out_char[256];
  size_t out_size;
  for (unsigned int i = 0; i < sizeof(vstrIn) / sizeof(vstrIn[0]); i++) {
    EXPECT_EQ(base32_encode(as_vector(vstrIn[i])), vstrOut[i]);
    EXPECT_EQ(as_string(base32_decode(vstrOut[i])), vstrIn[i]);
    EXPECT_EQ(
        as_string(base32raw_decode(base32raw_encode(as_vector(vstrIn[i])))),
        vstrIn[i]);

    memset(out_char, 0, sizeof(out_char));
    base32_encode(vstrIn[i].c_str(), vstrIn[i].size(), out_char);
    EXPECT_EQ(vstrOut[i], out_char);
    EXPECT_EQ(base32_encode_len(vstrIn[i].size()), vstrOut[i].size());
    EXPECT_GE(base32_decode_max_len(vstrOut[i].size()), vstrIn[i].size());
    memset(out_char, 0, sizeof(out_char));
    EXPECT_EQ(base32_decode(vstrOut[i].c_str(), vstrOut[i].size(), out_char),
              vstrIn[i].size());
    EXPECT_EQ(vstrIn[i], out_char);

    memset(out_char, 0, sizeof(out_char));

    EXPECT_GE(base32raw_encode_max_len(vstrIn[i].size()), vstrOut[i].size());
    EXPECT_GE(base32raw_decode_max_len(vstrOut[i].size()), vstrIn[i].size());

    out_size = base32raw_encode(vstrIn[i].c_str(), vstrIn[i].size(), out_char);
    char values[256];
    size_t size_of_values = base32raw_decode(out_char, out_size, values);
    EXPECT_EQ(size_of_values, vstrIn[i].size());
    values[size_of_values] = '\0';
    EXPECT_EQ(vstrIn[i], values);
  }

  EXPECT_EQ(base32_decode("mzxw6ytb#mzxw6ytb", 17, out_char), 5);
}