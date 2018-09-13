#include <fingera/encode/compress.h>

size_t varint_encode(uint64_t value, void *buf) {
  uint8_t tmp[10];
  uint8_t *out = (uint8_t *)buf;
  int len = 0;

  for (;;) {
    tmp[len] = (value & 0x7F) | (len ? 0x80 : 0x00);
    if (value <= 0x7F) break;
    value = (value >> 7) - 1;
    len++;
  }

  do {
    *out++ = tmp[len];
  } while (len--);

  return out - (uint8_t *)buf;
}

size_t varint_decode(const void *buf, size_t size, uint64_t *out) {
  *out = 0;
  const uint8_t *in = (const uint8_t *)buf;
  if (size > 10) size = 10;
  for (size_t i = 0; i < size; i++) {
    uint8_t byte = *in++;
    *out = (*out << 7) | (byte & 0x7F);
    if (byte & 0x80) {
      (*out)++;
    } else {
      return in - (uint8_t *)buf;
    }
  }
  return 0;
}

size_t zigzag_encode(int64_t value, void *buf) {
  uint64_t uvalue, sign;
  if (value < 0) {
    uvalue = (uint64_t)-value;
    sign = 1;
  } else {
    uvalue = (uint64_t)value;
    sign = 0;
  }
  uvalue <<= 1;
  uvalue |= sign;
  return varint_encode(uvalue, buf);
}

size_t zigzag_decode(const void *buf, size_t size, int64_t *out) {
  uint64_t uvalue;
  uint64_t sign;
  size_t len = varint_decode(buf, size, &uvalue);
  if (len > 0) {
    sign = uvalue & 1;
    uvalue >>= 1;
    if (sign) {
      *out = -(int64_t)uvalue;
    } else {
      *out = (int64_t)uvalue;
    }
  }
  return len;
}

size_t compactsize_encode(uint64_t value, void *buf9) {
  uint8_t *buf = (uint8_t *)buf9;
  size_t r;
  if (value < 253) {
    buf[0] = (uint8_t)value;
    r = 1;
  } else if (value <= 0xFFFF) {
    buf[0] = 253;
    writele16(buf + 1, (uint16_t)value);
    r = 3;
  } else if (value <= 0xFFFFFFFFul) {
    buf[0] = 254;
    writele32(buf + 1, (uint32_t)value);
    r = 5;
  } else {
    buf[0] = 255;
    writele64(buf + 1, (uint64_t)value);
    r = 9;
  }
  return r;
}

size_t compactsize_decode(const void *buf_in, size_t size, uint64_t *out) {
  const uint8_t *buf = (const uint8_t *)buf_in;
  size_t r;
  switch (buf[0]) {
    case 253:
      *out = (uint64_t)readle16(buf + 1);
      if (*out < 253) return 0;  // bad compact size
      r = 3;
      break;
    case 254:
      *out = (uint64_t)readle32(buf + 1);
      if (*out < 0x10000) return 0;  // bad compact size
      r = 5;
      break;
    case 255:
      *out = (uint64_t)readle64(buf + 1);
      if (*out < 0x100000000ull) return 0;  // bad compact size
      r = 9;
      break;
    default:
      *out = (uint64_t)buf[0];
      r = 1;
      break;
  }
  return r;
}
