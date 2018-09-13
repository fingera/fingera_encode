/**
 * @brief 整数的常用压缩算法
 *
 * @file compress.h
 * @author liuyujun@fingera.cn
 * @date 2018-09-12
 */
#ifndef _FINGERA_ENCODE_COMPRESS_H_
#define _FINGERA_ENCODE_COMPRESS_H_

#include <stddef.h>

#include <fingera/header.h>

FINGERA_EXTERN_C_BEGIN

size_t varint_encode(uint64_t value, void *buf10);
size_t varint_decode(const void *buf, size_t size, uint64_t *out);

size_t zigzag_encode(int64_t value, void *buf10);
size_t zigzag_decode(const void *buf, size_t size, int64_t *out);

size_t compactsize_encode(uint64_t value, void *buf9);
size_t compactsize_decode(const void *buf, size_t size, uint64_t *out);

FINGERA_EXTERN_C_END

#endif  // _FINGERA_ENCODE_COMPRESS_H_