#include <stdint.h>

#include "hash-functions.h"

uint32_t flat_hash(void const * data, int len)
{
    (void) data;
    (void) len;
    return 42;
}
