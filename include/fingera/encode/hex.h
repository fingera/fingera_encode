/**
 * @brief HEX的编码和解码
 *
 * @file hex.h
 * @author liuyujun@fingera.cn
 * @date 2018-08-17
 */
#ifndef _FINGERA_ENCODE_HEX_H_
#define _FINGERA_ENCODE_HEX_H_

#include <stddef.h>

#include <fingera/header.h>

FINGERA_EXTERN_C_BEGIN

size_t hex_encode_len(size_t buf_size);
void hex_encode(const void *buf, size_t buf_size, char *str, int upper);
void hex_reverse_encode(const void *buf, size_t buf_size, char *str, int upper);

size_t hex_decode_max_len(size_t str_len);
size_t hex_decode(const char *str, size_t str_len, void *buf);
size_t hex_reverse_decode(const char *str, size_t str_len, void *buf);

void hex_dump(const void *buf, size_t buf_size);

FINGERA_EXTERN_C_END

#endif  // _FINGERA_ENCODE_HEX_H_