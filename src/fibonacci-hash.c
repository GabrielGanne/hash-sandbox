#include <stdint.h>

#include "hash-functions.h"

#define FIBO_NUM 2654435769ull
#define FIBO_HASH(N) (((N * FIBO_NUM)*4294967295ull) >> 32)

uint32_t fibonacci_32_hash(const void* data, int len)
{
	const uint8_t* d8 = data;
	const uint32_t* d32 = data;
	uint32_t g, h = 0;
	int i = 0;

	for (; i < len/4; i++)
		h += FIBO_HASH(d32[i]);

	if (i*4 < len) {
		g = 0;
		for (i*=4 ; i < len; i++)
			g += d8[i] << 8*(len-1-i);

		h += FIBO_HASH(g);
	}

	return h;
}
