/**
 * @brief 标准BECH32 和不转换为显示字符串的BECH32
 *
 * @file bech32.h
 * @author liuyujun@fingera.cn
 * @date 2018-09-12
 */
#ifndef _FINGERA_ENCODE_BECH32_H_
#define _FINGERA_ENCODE_BECH32_H_

#include <stddef.h>

#include <fingera/header.h>

FINGERA_EXTERN_C_BEGIN

size_t bech32_encode_len(size_t hrp_len, size_t b32_size);
void bech32_encode(const char *hrp, size_t hrp_len, const uint8_t *b32,
                   size_t b32_size, char *result);

bool bech32_decode(const char *str, size_t str_len, char *hrp, size_t *hrp_size,
                   void *b32, size_t *b32_size);

FINGERA_EXTERN_C_END

#endif  // _FINGERA_ENCODE_BECH32_H_