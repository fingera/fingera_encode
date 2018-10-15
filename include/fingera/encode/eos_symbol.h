/**
 * @brief EOS token符号编码解码
 *
 * @file eos_symbol.h
 * @author liuyujun@fingera.cn
 * @date 2018-10-15
 */
#ifndef _FINGERA_ENCODE_EOS_SYMBOL_H_
#define _FINGERA_ENCODE_EOS_SYMBOL_H_

#include <stddef.h>

#include <fingera/header.h>

FINGERA_EXTERN_C_BEGIN

// symbol: precision0 char1 char2 char3 char4 char5 char6 char7
bool eos_symbol_is_valid_precision(uint8_t precision);
bool eos_symbol_is_valid_char(const char *str, size_t str_len);

uint64_t eos_symbol_encode(uint8_t precision, const char *str, size_t str_len);

uint8_t eos_symbol_decode_precision(uint64_t symbol);

size_t eos_symbol_decode_char(uint64_t symbol, char *str7);

FINGERA_EXTERN_C_END

#endif  // _FINGERA_ENCODE_EOS_SYMBOL_H_