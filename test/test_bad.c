#include "gold_sequence.h"

int main(void) {
    uint8_t out[10];
    gold_seq(0xFFFFFFFF, 10, out);   // cinit too large
    gold_seq(0, 0, out);             // Mpn = 0
    gold_seq(0, 10, NULL);           // null pointer
    return 0;
}
