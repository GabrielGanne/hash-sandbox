#include <stdint.h>

#include "hash-functions.h"

#define PRIME 4294967029

uint32_t modulo_hash(const void* data, int len)
{
    const uint_fast8_t* d8 = data;
    const uint_fast32_t* d32 = data;
    uint_fast32_t g, h = 0;
    int i = 0;

    for ( ; i < len / 4 ; i++)
        h += d32[i];

    if (i * 4 < len) {
        g = 0;
        for (i *= 4 ; i < len ; i++)
            g += d8[i] << 8 * (len - 1 - i);

        h += g;
    }

    return h % PRIME;
}
