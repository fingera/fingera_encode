/**
 * @brief 标准BASE64 和 URL安全BASE64
 *
 * @file base64.h
 * @author liuyujun@fingera.cn
 * @date 2018-09-12
 */
#ifndef _FINGERA_ENCODE_BASE64_H_
#define _FINGERA_ENCODE_BASE64_H_

#include <fingera/header.h>

FINGERA_EXTERN_C_BEGIN

////////////////////////////////////////////////////////////////////////////////
size_t base64_encode_len(size_t buf_size);
void base64_encode(const void *buf, size_t buf_size, char *str);

size_t base64_decode_max_len(size_t str_len);
size_t base64_decode(const char *str, size_t str_len, void *buf);

////////////////////////////////////////////////////////////////////////////////
size_t base64url_encode_len(size_t buf_size);
void base64url_encode(const void *buf, size_t buf_size, char *str);

size_t base64url_decode_max_len(size_t str_len);
size_t base64url_decode(const char *str, size_t str_len, void *buf);

FINGERA_EXTERN_C_END

#endif  // _FINGERA_ENCODE_BASE64_H_