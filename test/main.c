#include <stdio.h>
#include "gold_sequence.h"

int main(void)
{
    uint32_t cinit = 12345;
    size_t   Mpn   = 50;
    uint8_t  seq[50];

    if (gold_seq(cinit, Mpn, seq) != 0) {
        printf("Error: gold_seq failed\n");
        return 1;
    }

    printf("Gold sequence (cinit=%u, N=%zu):\n", cinit, Mpn);
    for (size_t i = 0; i < Mpn; i++) {
        printf("%u", seq[i]);
        if ((i + 1) % 10 == 0)
            printf("\n");
        else
            printf(" ");
    }
    printf("\n");

    return 0;
}
