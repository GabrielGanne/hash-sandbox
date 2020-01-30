#include <stdint.h>
#include <xxhash.h>

#include "hash-functions.h"

#define SEED 0

uint32_t xxh_hash(void const * data, int len)
{
    return XXH32(data, len, SEED);
}

uint32_t xxh3_hash(void const * data, int len)
{
    /* only keep the first 32 bits */
    return (XXH64(data, len, SEED) >> 32);
}
