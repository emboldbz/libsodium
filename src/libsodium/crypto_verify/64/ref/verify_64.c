
#include <stddef.h>
#include <stdint.h>

#include "crypto_verify_64.h"

int
crypto_verify_64(const unsigned char *x, const unsigned char *y)
{
#ifdef CPU_UNALIGNED_ACCESS
    uint_fast64_t d = 0U;
    int           i;

    for (i = 0; i < 64; i += 4) {
        d |= *((const uint32_t *) (const void *) &x[i]) ^
             *((const uint32_t *) (const void *) &y[i]);
    }
    return (1 & ((d - 1) >> 32)) - 1;
#else
    uint_fast16_t d = 0U;
    int           i;

    for (i = 0; i < 64; i++) {
        d |= x[i] ^ y[i];
    }
    return (1 & ((d - 1) >> 8)) - 1;
#endif
}
