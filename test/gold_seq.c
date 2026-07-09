#include "gold_seq.h"

#define NC 1600

bool* gold_seq(uint32_t c_init, size_t Mpn)
{
    VALIDATE(c_init <= 0x7FFFFFFF, "c-init must be 31-bit");
    VALIDATE(Mpn > 0, "Mpn must be positive");

    size_t xl_x2_len = NC + Mpn;
    
    bool x1[xl_x2_len];  // VLA不得被初始化
    x1[0] = true;

    bool x2_init_arr[31] = {(bool) 0};
    for(uint8_t i = 0; i < 31; x2_init_arr[i] = (c_init >> (30 - i)) & 1U, ++i);
    bool x2[xl_x2_len];
    for(uint8_t i = 0; i < 31; x2[i] = x2_init_arr[i], ++i);

    // gold seq
    bool *out = (bool*)calloc(Mpn, sizeof(bool));

    for(uint32_t i = 31, j = 0; i < xl_x2_len; ++i)
    {
        x1[i] = x1[i - 31 + 3] ^ x1[i - 31];
        x2[i] = x2[i - 31 + 3] ^ x2[i - 31 + 2] ^ x2[i - 31 + 1] ^ x2[i - 31];
        if (i >= NC)
            out[j++] = x1[i] ^ x2[i];
    }

    return out;
}