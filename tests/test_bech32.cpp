#include <fingera/encode/bech32.h>

#include <stdint.h>
#include <string>

#include <vector>

#include <gtest/gtest.h>

#define EXPECT_ZERO(x) EXPECT_EQ((x), 0)

TEST(bech32, custom) {
  static const std::string CASES[] = {
      "A12UEL5L",
      "a12uel5l",
      "an83characterlonghumanreadablepartthatcontainsthenumber1andtheexcludedch"
      "aractersbio1tt5tgs",
      "abcdef1qpzry9x8gf2tvdw0s3jn54khce6mua7lmqqqxw",
      "11qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq"
      "qqqqqqqqqqqqc8247j",
      "split1checkupstagehandshakeupstreamerranterredcaperred2y9e3w",
      "?1ezyfcl",
  };
  static const std::string PREFIXES[] = {
      "a",
      "a",
      "an83characterlonghumanreadablepartthatcontainsthenumber1andtheexcludedch"
      "aractersbio",
      "abcdef",
      "1",
      "split",
      "?",
  };
  static const uint8_t data4[] = {
      0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a,
      0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15,
      0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f,
  };
  static const uint8_t data6[] = {
      0x18, 0x17, 0x19, 0x18, 0x16, 0x1c, 0x01, 0x10, 0x0b, 0x1d, 0x08, 0x19,
      0x17, 0x1d, 0x13, 0x0d, 0x10, 0x17, 0x1d, 0x16, 0x19, 0x1c, 0x01, 0x10,
      0x0b, 0x03, 0x19, 0x1d, 0x1b, 0x19, 0x03, 0x03, 0x1d, 0x13, 0x0b, 0x19,
      0x03, 0x03, 0x19, 0x0d, 0x18, 0x1d, 0x01, 0x19, 0x03, 0x03, 0x19, 0x0d,
  };
  const std::vector<uint8_t> DATAS[] = {
      std::vector<uint8_t>(),
      std::vector<uint8_t>(),
      std::vector<uint8_t>(),
      std::vector<uint8_t>(data4, data4 + sizeof(data4)),
      std::vector<uint8_t>(82, 0),
      std::vector<uint8_t>(data6, data6 + sizeof(data6)),
      std::vector<uint8_t>(),
  };
  char buffer[256];
  char hrp[256];

  assert(_countof_(CASES) == _countof_(PREFIXES));
  assert(_countof_(CASES) == _countof_(DATAS));

  for (size_t i = 0; i < _countof_(CASES); i++) {
    memset(buffer, 0, sizeof(buffer));
    memset(hrp, 0, sizeof(hrp));
    size_t hrp_size = sizeof(hrp);
    size_t buf_size = sizeof(buffer);

    std::string str = CASES[i];
    std::string first = PREFIXES[i];
    std::vector<uint8_t> second = DATAS[i];
    EXPECT_EQ(bech32_encode_len(first.size(), second.size()), str.size());

    bech32_encode(first.c_str(), first.size(), second.data(), second.size(),
                  buffer);
    EXPECT_STRCASEEQ(str.c_str(), buffer);

    EXPECT_TRUE(bech32_decode(str.c_str(), str.size(), hrp, &hrp_size, buffer,
                              &buf_size));
    EXPECT_EQ(hrp_size, first.size());
    hrp[hrp_size] = '\0';
    EXPECT_STRCASEEQ(first.c_str(), hrp);
    EXPECT_EQ(buf_size, second.size());
    if (second.data()) {
      EXPECT_ZERO(memcmp(buffer, second.data(), buf_size));
    }
  }
}

TEST(bech32, bip173_testvectors_invalid) {
  static const std::string CASES[] = {
      " 1nwldj5",
      "\x7f"
      "1axkwrx",
      "\x80"
      "1eym55h",
      "an84characterslonghumanreadablepartthatcontainstheencode1andtheexcludedc"
      "haractersbio1569pvx",
      "pzry9x0s0muk",
      "1pzry9x0s0muk",
      "x1b4n0q5v",
      "li1dgmt3",
      "de1lg7wt\xff",
      "A1G7SGD8",
      "10a06t8",
      "1qzzfhee",
      "a12UEL5L",
      "A12uEL5L",
  };
  char hrp[256];
  char buf[256];
  for (size_t i = 0; i < _countof_(CASES); i++) {
    std::string str = CASES[i];
    size_t hrp_size = sizeof(hrp_size);
    size_t buf_size = sizeof(buf);
    EXPECT_FALSE(
        bech32_decode(str.c_str(), str.size(), hrp, &hrp_size, buf, &buf_size));
  }
}
