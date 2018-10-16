/**
 * @brief 标准BASE32 和不转换为显示字符串的BASE32
 *
 * @file base32.h
 * @author liuyujun@fingera.cn
 * @date 2018-09-12
 */
#ifndef _FINGERA_ENCODE_BASE32_H_
#define _FINGERA_ENCODE_BASE32_H_

#include <stddef.h>

#include <fingera/header.h>

FINGERA_EXTERN_C_BEGIN

////////////////////////////////////////////////////////////////////////////////
size_t base32_encode_len(size_t buf_size);
void base32_encode(const void *buf, size_t buf_size, char *str);

size_t base32_decode_max_len(size_t str_len);
size_t base32_decode(const char *str, size_t str_len, void *buf);

////////////////////////////////////////////////////////////////////////////////
size_t base32raw_encode_max_len(size_t buf_size);
size_t base32raw_encode(const void *buf, size_t buf_size, void *str);

size_t base32raw_decode_max_len(size_t str_len);
size_t base32raw_decode(const void *str, size_t str_len, void *buf);

FINGERA_EXTERN_C_END

///////////////////////////////////cplusplus///////////////////////////////////
#if defined(__cplusplus)

#include <string>
#include <utility>
#include <vector>

static inline std::string base32_encode(const std::vector<uint8_t> &buf) {
  std::string ret;
  ret.resize(base32_encode_len(buf.size()));
  base32_encode(buf.data(), buf.size(), const_cast<char *>(ret.c_str()));
  return std::move(ret);
}

static inline std::vector<uint8_t> base32_decode(const std::string &str) {
  std::vector<uint8_t> buf;
  buf.resize(base32_decode_max_len(str.size()));
  buf.resize(base32_decode(str.c_str(), str.size(), buf.data()));
  return std::move(buf);
}

static inline std::string base32raw_encode(const std::vector<uint8_t> &buf) {
  std::string ret;
  ret.resize(base32raw_encode_max_len(buf.size()));
  ret.resize(base32raw_encode(buf.data(), buf.size(),
                              const_cast<char *>(ret.c_str())));
  return std::move(ret);
}

static inline std::vector<uint8_t> base32raw_decode(const std::string &str) {
  std::vector<uint8_t> buf;
  buf.resize(base32raw_decode_max_len(str.size()));
  buf.resize(base32raw_decode(str.c_str(), str.size(), buf.data()));
  return std::move(buf);
}

#endif  // __cplusplus

#endif  // _FINGERA_ENCODE_BASE32_H_