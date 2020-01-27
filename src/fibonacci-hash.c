#include <stdint.h>

#include "hash-functions.h"

/**
 * https://probablydance.com/2018/06/16/fibonacci-hashing-the-optimization-that-the-world-forgot-or-a-better-alternative-to-integer-modulo/
 */
uint32_t fibonacci_32_hash(const void* data, int len)
{
	const uint_fast8_t* d8 = data;
	const uint_fast32_t* d32 = data;
	uint_fast32_t h = 0;
	int i = 0;

	for (; i < len/4; i++)
		h += (d32[i] * 2654435915) >> 32;
	for (i*=4 ; i < len; i++)
		h += (d8[i] * 2654435915) >> 32;

	return h;
}
