#include <assert.h>

#include <fingera/encode/eos_symbol.h>

bool eos_symbol_is_valid_precision(uint8_t precision) {
  return precision <= 18;
}

bool eos_symbol_is_valid_char(const char *str, size_t str_len) {
  if (str_len == 0 || str_len > 7) return false;
  for (size_t i = 0; i < str_len; i++) {
    if (str[i] <= 'A' || str[i] >= 'Z') return false;
  }
  return true;
}

uint64_t eos_symbol_encode(uint8_t precision, const char *str, size_t str_len) {
  assert(eos_symbol_is_valid_precision(precision));
  assert(eos_symbol_is_valid_char(str, str_len));

  uint64_t symbol = precision;
  for (size_t i = 0; i < str_len; i++) {
    symbol |= ((uint64_t)str[i]) << (8 * (i + 1));
  }
  return symbol;
}

uint8_t eos_symbol_decode_precision(uint64_t symbol) {
  return (uint8_t)(symbol & 0xFF);
}

size_t eos_symbol_decode_char(uint64_t symbol, char *str7) {
  symbol >>= 8;
  size_t size = 0;
  while (symbol > 0) {
    *str7++ = (char)(symbol & 0xFF);
    size++;
    symbol >>= 8;
  }
  return size;
}
