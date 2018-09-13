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

#endif  // _FINGERA_ENCODE_BASE58_H_