#ifndef GOLD_SEQ_H
#define GOLD_SEQ_H

#include<stdio.h>
#include<string.h>
#include<stdint.h>
#include<stdbool.h>
#include<stdlib.h>

/**
 * Generate gold (pseudo-random) sequence according to TS38.211 5.2.1
 * 
 * @param c_init 31-bit initialization value
 * @param Mpn size of gold sequence
 * @param out gold sequence array (byte sequence) with length of Mpn/8
 * @return 0 on success, -1 on error
 */
bool* gold_seq(uint32_t c_init, size_t Mpn);


#define VALIDATE(cond, msg) do { \
if (!(cond)) {\
    fprintf(stderr, "[ERROR] %s (%s:%d\n)", msg, __FILE__, __LINE__); \
    return NULL; \
} \
} while(0)


#endif /* GOLD_SEQ_H */