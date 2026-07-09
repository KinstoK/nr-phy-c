#include "gold_sequence.h"
#include <stdio.h>
#include <string.h>

#define NC 1600

int gold_seq(uint32_t cinit, size_t Mpn, uint8_t *out)
{
    VALIDATE(cinit <= 0x7FFFFFFF, "cinit must be a 31-bit value (<= 0x7FFFFFFF)");
    VALIDATE(Mpn > 0,             "Mpn must be positive");
    VALIDATE(out != NULL,         "out pointer must not be NULL");

    size_t len = NC + Mpn;
    uint8_t x1[len];
    uint8_t x2[len];

    /* Initialise x1: x1(0) = 1, x1(1..30) = 0 */
    memset(x1, 0, len);
    x1[0] = 1;

    /* Initialise x2: first 31 bits from cinit */
    memset(x2, 0, len);
    for (int i = 0; i < 31; i++)
        x2[i] = (cinit >> i) & 1;

    /* Generate remaining bits via LFSR */
    for (size_t i = 31; i < len; i++) {
        x1[i] = x1[i - 28] ^ x1[i - 31];                              /* x^31 + x^28 + 1 */
        x2[i] = (x2[i - 28] + x2[i - 29] + x2[i - 30] + x2[i - 31]) & 1;  /* x^31 + x^29 + x^30 + x^28 + 1 */
    }

    /* Gold sequence: c(n) = x1(n+Nc) XOR x2(n+Nc) */
    for (size_t n = 0; n < Mpn; n++)
        out[n] = x1[NC + n] ^ x2[NC + n];

    return 0;
}
