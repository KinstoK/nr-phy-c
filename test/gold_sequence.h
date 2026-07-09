#ifndef GOLD_SEQUENCE_H
#define GOLD_SEQUENCE_H

#include <stdint.h>
#include <stddef.h>

#define VALIDATE(cond, msg) do { \
    if (!(cond)) { \
        fprintf(stderr, "[ERROR] %s (%s:%d)\n", msg, __FILE__, __LINE__); \
        return -1; \
    } \
} while(0)

int gold_seq(uint32_t cinit, size_t Mpn, uint8_t *out);

#endif /* GOLD_SEQUENCE_H */
