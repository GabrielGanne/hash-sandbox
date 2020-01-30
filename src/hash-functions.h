#ifndef HASH_FUNCTIONS_H
#define HASH_FUNCTIONS_H

#include <stdint.h>

/* "one-at-a-time" generic hash function used by jenkins */
uint32_t oat_hash(const void * data, int len);

/* string-optimized hash function created by Dan Bernstein */
uint32_t bernstein_hash(const void * data, int len);

/* dummy function. only here to test the tests */
uint32_t flat_hash(void const * data, int len);

/**
 * https://probablydance.com/2018/06/16/fibonacci-hashing-the-optimization-that-the-world-forgot-or-a-better-alternative-to-integer-modulo/
 */
uint32_t fibonacci_32_hash(const void* data, int len);

uint32_t modulo_hash(const void* data, int len);

uint32_t fiboat_hash(const void* data, int len);

#endif /* HASH_FUNCTIONS_H */
