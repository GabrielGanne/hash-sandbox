#include <stdint.h>

#include "hash-functions.h"

uint32_t oat_hash(const void * data, int len)
{
    const uint8_t * p = data;
    uint32_t h = 0;
    int i;

    for (i = 0 ; i < len ; i++) {
        h += p[i];
        h += (h << 10);
        h ^= (h >> 6);
    }

    h += (h << 3);
    h ^= (h >> 11);
    h += (h << 15);

    return h;
}
