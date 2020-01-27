#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "check.h"
#include "hash-functions.h"
#include "primes.h"

#define ABS(a) ((a) > 0 ? (a) : (-(a)))

struct hash_fn_test_entry {
    uint32_t (* hash_fn) (const void*, int);
    char const * name;
};

static struct hash_fn_test_entry hash_fn_test_list[] = {
    {.hash_fn = bernstein_hash, .name = "bernstein_hash"},
    {.hash_fn = oat_hash, .name = "oat_hash"},
    {.hash_fn = fibonacci_32_hash, .name = "fibonacci_32_hash"},
};

/* return the dffering bits between the two hashes */
static
uint32_t strict_avalanche_criterion(uint32_t (* hash_fn)(const void*, int),
        void const * data, size_t len)
{
    /* copy input and flip a single random bit in the copy */
    uint8_t copy[len];
    memcpy(copy, data, len);
    int r = rand();
    copy[r % len] ^= (1 << (r % 8));

    uint32_t data_hash = hash_fn(data, len);
    uint32_t copy_hash = hash_fn(copy, len);

    return ~(data_hash ^ copy_hash);
}

static int
test_hash_strict_avalanche_primes(uint32_t (* hash_fn)(const void*, int),
        char const * hash_fn_name)
{
    size_t i, j;
    uint32_t rv;

    /* flipped is a vector of how many times the n-th bit has been flipped */
    int flipped[8 * sizeof(uint32_t)] = {0};

    for (i = 0 ; i < primes_len ; i++) {
        rv = strict_avalanche_criterion(hash_fn, &primes[i], sizeof(primes[i]));
        for (j = 0 ; j < arraylen(flipped) ; j++)
            flipped[j] += (rv & (1 << j)) != 0;
    }

    /* if a bit has been randomly flipped each time, flipped should contain
     * numbers ~ primes_len / 2.
     * Arbitrarily decide that
     *  - number > 60%(primes_len) => error
     *  - number > 51%(primes_len) => warning
     */
    ssize_t num = (ssize_t) primes_len;
    for (i = 0 ; i < arraylen(flipped) ; i++) {
        float score = 100. * ABS(flipped[i] - (num / 2)) / num;

        if (score > 1.) {
            fprintf(stderr, "[%s] FAILED %s: score=%f\n",
                    hash_fn_name, __func__, 50. + score);
            return (score > 60.) ? -1 : 0;
        }
    }

    fprintf(stderr, "[%s] PASSES %s (50 <= score <= 51)\n",
            hash_fn_name, __func__);

    return 0;
}

static int
test_hash_strict_avalanche_random(uint32_t (* hash_fn)(const void*, int),
        char const * hash_fn_name)
{
    size_t i, j;
    uint32_t rv;
    int data[100]; /* test on pseudo-random vectors of size 100 */

    /* flipped is a vector of how many times the n-th bit has been flipped */
    int flipped[8 * sizeof(uint32_t)] = {0};

    for (i = 0 ; i < primes_len ; i++) {
        for (j = 0 ; j < arraylen(data) ; j++)
            data[j] = rand();

        rv = strict_avalanche_criterion(hash_fn, data, arraylen(data));
        for (j = 0 ; j < 8 * sizeof(primes[i]) ; j++)
            flipped[j] += (rv & (1 << j)) != 0;
    }

    /* if a bit has been randomly flipped each time, flipped should contain
     * numbers ~ primes_len / 2.
     * Arbitrarily decide that
     *  - number > 60%(primes_len) => error
     *  - number > 51%(primes_len) => warning
     */
    ssize_t num = (ssize_t) primes_len;
    for (i = 0 ; i < sizeof(primes[0]) ; i++) {
        float score = 100. * ABS(flipped[i] - (num / 2)) / num;

        if (score > 1.) {
            fprintf(stderr, "[%s] FAILED %s: score=%f\n",
                    hash_fn_name, __func__, 50. + score);
            return (score > 60.) ? -1 : 0;
        }
    }

    fprintf(stderr, "[%s] PASSES %s (50 <= score <= 51)\n",
            hash_fn_name, __func__);
    return 0;
}

int main(void)
{
    size_t i;
    struct hash_fn_test_entry * test;

    srand(0);

    for (i = 0 ; i < arraylen(hash_fn_test_list) ; i++) {
        test = &hash_fn_test_list[i];
        test_hash_strict_avalanche_primes(test->hash_fn, test->name);
        test_hash_strict_avalanche_random(test->hash_fn, test->name);
    }

    return 0;
}
