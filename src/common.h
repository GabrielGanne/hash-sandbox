#ifndef COMMON_H
#define COMMON_H

/* config values */
#define CACHELINE_SIZE 64

/* common macros */
#define arraylen(x) (sizeof(x) / sizeof(*(x)))

#define MIN(x, y) ((x) < (y) ? (x) : (y))
#define MAX(x, y) ((x) > (y) ? (x) : (y))

#define likely(expr)   __builtin_expect(!!(expr), 1)
#define unlikely(expr) __builtin_expect(!!(expr), 0)

#define ALWAYS_INLINE inline __attribute__((always_inline))
#define NOINLINE __attribute__((noinline))
#define PACKED __attribute__((packed))
#define CACHE_ALIGNED __attribute__((aligned(CACHELINE_SIZE)))

#endif /* COMMON_H */
