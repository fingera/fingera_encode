/**
 * @brief base58
 *
 * @file base58.h
 * @author liuyujun@fingera.cn
 * @date 2018-09-12
 */
#ifndef _FINGERA_ENCODE_BASE58_H_
#define _FINGERA_ENCODE_BASE58_H_

#include <stddef.h>

#include <fingera/header.h>

FINGERA_EXTERN_C_BEGIN

size_t base58_encode_max_len(size_t buf_size);
size_t base58_encode(const void *buf, size_t buf_size, char *str);

size_t base58_decode_max_len(size_t str_len);
size_t base58_decode(const char *str, size_t str_len, void *buf);

FINGERA_EXTERN_C_END

///////////////////////////////////cplusplus///////////////////////////////////
#if defined(__cplusplus)

#include <string>
#include <utility>
#include <vector>

static inline std::string base58_encode(const std::vector<uint8_t> &buf) {
  std::string ret;
  ret.resize(base58_encode_max_len(buf.size()));
  ret.resize(
      base58_encode(buf.data(), buf.size(), const_cast<char *>(ret.c_str())));
  return std::move(ret);
}

static inline std::vector<uint8_t> base58_decode(const std::string &str) {
  std::vector<uint8_t> buf;
  buf.resize(base58_decode_max_len(str.size()));
  buf.resize(base58_decode(str.c_str(), str.size(), buf.data()));
  return std::move(buf);
}

#endif  // __cplusplus

#endif  // _FINGERA_ENCODE_BASE58_H_