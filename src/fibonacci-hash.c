#include <stdint.h>

#include "hash-functions.h"

/**
 * https://probablydance.com/2018/06/16/fibonacci-hashing-the-optimization-that-the-world-forgot-or-a-better-alternative-to-integer-modulo/
 */
uint32_t fibonacci_32_hash_v1(const void* data, int len)
{
    const unsigned char* d = data;
    uint_fast32_t h = 0;
    int i;

    for (i = 0 ; i < len ; i++)
        h = h * 33 + d[i];

    return h * 2654435915;
}

uint32_t fibonacci_32_hash_v2(const void* data, int len)
{
    const unsigned char* d = data;
    uint_fast32_t h = 0;
    uint64_t tmp;
    int i;

    for (i = 0 ; i < len ; i++) {
        tmp = d[i] * 2654435915;
        h += tmp >> 32;
    }

    return h;
}
