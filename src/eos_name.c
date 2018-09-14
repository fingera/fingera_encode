#include <assert.h>

#include <fingera/encode/eos_name.h>

static const char *EOS_BASE32_ENCODE = ".12345abcdefghijklmnopqrstuvwxyz";

static inline char decode_char(char c) {
  if (c >= 'a' && c <= 'z') return (c - 'a') + 6;
  if (c >= '1' && c <= '5') return (c - '1') + 1;
  return 0;
}

uint64_t eos_name_encode(const char *str, size_t len) {
  uint64_t value = 0;

  size_t loop = len > 12 ? 12 : len;
  for (size_t i = 0; i < loop; ++i) {
    uint64_t c = (uint64_t)decode_char(str[i]);
    assert(c <= 0x1F);
    c <<= 64 - 5 * (i + 1);
    value |= c;
  }

  if (len >= 13) {
    value |= (uint64_t)decode_char(str[12]) & 0xF;
  }

  return value;
}

size_t eos_name_decode(uint64_t name, char *str13) {
  str13[12] = EOS_BASE32_ENCODE[name & 0xf];
  name >>= 4;

  for (size_t i = 1; i < 13; i++) {
    str13[12 - i] = EOS_BASE32_ENCODE[name & 0x1F];
    name >>= 5;
  }

  size_t r = 13;
  while (r != 0 && str13[r - 1] == '.') r--;
  if (r == 0) r = 13;
  return r;
}
