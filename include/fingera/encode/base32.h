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

#endif  // _FINGERA_ENCODE_BASE32_H_