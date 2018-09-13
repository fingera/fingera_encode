#include <fingera/encode/bech32.h>

#include <stdint.h>
#include <string>

#include <vector>

#include <gtest/gtest.h>

#define EXPECT_ZERO(x) EXPECT_EQ((x), 0)

namespace bech32 {

typedef std::vector<uint8_t> data;
/** Encode a Bech32 string. */
std::string Encode(const std::string& hrp, const data& values);
/** Decode a Bech32 string. */
std::pair<std::string, data> Decode(const std::string& str);
}  // namespace bech32

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
  char buffer[256];
  char hrp[256];
  for (const std::string& str : CASES) {
    memset(buffer, 0, sizeof(buffer));
    memset(hrp, 0, sizeof(hrp));
    size_t hrp_size = sizeof(hrp);
    size_t buf_size = sizeof(buffer);

    auto ret = bech32::Decode(str);
    EXPECT_EQ(bech32_encode_len(ret.first.size(), ret.second.size()),
              str.size());

    bech32_encode(ret.first.c_str(), ret.first.size(), ret.second.data(),
                  ret.second.size(), buffer);
    EXPECT_STRCASEEQ(str.c_str(), buffer);

    EXPECT_TRUE(bech32_decode(str.c_str(), str.size(), hrp, &hrp_size, buffer,
                              &buf_size));
    EXPECT_EQ(hrp_size, ret.first.size());
    hrp[hrp_size] = '\0';
    EXPECT_STRCASEEQ(ret.first.c_str(), hrp);
    EXPECT_EQ(buf_size, ret.second.size());
    if (ret.second.data()) {
      EXPECT_ZERO(memcmp(buffer, ret.second.data(), buf_size));
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
  for (const std::string& str : CASES) {
    size_t hrp_size = sizeof(hrp_size);
    size_t buf_size = sizeof(buf);
    EXPECT_FALSE(
        bech32_decode(str.c_str(), str.size(), hrp, &hrp_size, buf, &buf_size));
  }
}
