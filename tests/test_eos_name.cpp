#include <fingera/encode/eos_name.h>

#include <stdint.h>
#include <stdio.h>
#include <string>

#include <fingera/encode/hex.h>
#include <gtest/gtest.h>

/**
 *  Converts a base32 symbol into its binary representation, used by
 * string_to_name()
 *
 *  @brief Converts a base32 symbol into its binary representation, used by
 * string_to_name()
 *  @param c - Character to be converted
 *  @return constexpr char - Converted character
 *  @ingroup types
 */
static char char_to_symbol(char c) {
  if (c >= 'a' && c <= 'z') return (c - 'a') + 6;
  if (c >= '1' && c <= '5') return (c - '1') + 1;
  return 0;
}

/**
 *  Converts a base32 string to a uint64_t. This is a constexpr so that
 *  this method can be used in template arguments as well.
 *
 *  @brief Converts a base32 string to a uint64_t.
 *  @param str - String representation of the name
 *  @return constexpr uint64_t - 64-bit unsigned integer representation of the
 * name
 *  @ingroup types
 */
static uint64_t N(const char* str) {
  uint32_t len = 0;
  while (str[len]) ++len;

  uint64_t value = 0;

  for (uint32_t i = 0; i <= 12; ++i) {
    uint64_t c = 0;
    if (i < len && i <= 12) c = uint64_t(char_to_symbol(str[i]));

    if (i < 12) {
      c &= 0x1f;
      c <<= 64 - 5 * (i + 1);
    } else {
      c &= 0x0f;
    }

    value |= c;
  }

  return value;
}

std::string to_string(uint64_t value) {
  static const char* charmap = ".12345abcdefghijklmnopqrstuvwxyz";

  std::string str(13, '.');

  for (uint32_t i = 0; i <= 12; ++i) {
    char c = charmap[value & (i == 0 ? 0x0f : 0x1f)];
    str[12 - i] = c;
    value >>= (i == 0 ? 4 : 5);
  }
  size_t last = str.find_last_not_of('.');
  if (last != std::string::npos) str = str.substr(0, last + 1);
  return str;
}

TEST(eos_name, custom) {
  const std::string test_list[] = {
      "a",
      "ba",
      "cba",
      "dcba",
      "edcba",
      "fedcba",
      "gfedcba",
      "hgfedcba",
      "ihgfedcba",
      "jihgfedcba",
      "kjihgfedcba",
      "lkjihgfedcba",
      "mlkjihgfedcba",
      "mlkjihgfedcba1",
      "mlkjihgfedcba55",
      "azAA34",
      "AZaz12Bc34",
      "AAAAAAAAAAAAAAA",
      "AA11",
      "11AA",
      "AABBCC",
      "22BBCCXXAA",
      "AAAbbcccdd",
      "11bbcccdd",
  };
  for (size_t i = 0; i < _countof_(test_list); i++) {
    const std::string& str = test_list[i];
    uint64_t id = eos_name_encode(str.c_str(), str.size());
    EXPECT_EQ(id, N(str.c_str()));
    char buf[13];
    size_t size = eos_name_decode(id, buf);
    EXPECT_EQ(to_string(id), std::string(buf, buf + size));
  }
}