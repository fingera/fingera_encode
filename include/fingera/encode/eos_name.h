/**
 * @brief EOS名字编码解码
 *
 * @file eos_name.h
 * @author liuyujun@fingera.cn
 * @date 2018-09-13
 */
#ifndef _FINGERA_ENCODE_EOS_NAME_H_
#define _FINGERA_ENCODE_EOS_NAME_H_

#include <stddef.h>

#include <fingera/header.h>

FINGERA_EXTERN_C_BEGIN

uint64_t eos_name_encode(const char *str, size_t str_len);

size_t eos_name_decode(uint64_t name, char *str13);

FINGERA_EXTERN_C_END

#endif  // _FINGERA_ENCODE_EOS_NAME_H_