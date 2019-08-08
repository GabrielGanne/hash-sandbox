#include <stdint.h>

#include "hash-functions.h"

uint32_t bernstein_hash(const void * data, int len)
{
    int i;
    uint_fast32_t h;
    const unsigned char* d = data;

    h = 5381;
    for (i = 0 ; i < len ; i++)
        h = h * 33 + d[i];

    return h;
}
