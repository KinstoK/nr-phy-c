#include "gold_seq.h"

#define NC 1600

//使用nint32_t循环缓存+压缩位输出
uint32_t* gold_seq(uint32_t c_init, size_t Mpn)
{
    VALIDATE(c_init <= 0x7FFFFFFF, "c-init must be 31-bit");
    VALIDATE(Mpn > 0, "Mpn must be positive");

    size_t xl_x2_len = NC + Mpn;
    
    // ---------- x1[0..30] and x2[0..30] ----------
    uint32_t x1 = 1;
    uint32_t x2 = c_init;

    // ---------- 分配内存gold seq ----------
    size_t n_uint32_t = Mpn / 32 + (size_t)(Mpn % 32 > 0);
    uint32_t *out = (uint32_t*)malloc(n_uint32_t * sizeof(uint32_t));
    if (!out) return NULL;  // 返回空指针

    // ---------- 设定x1和x2第31位 ---------- 
    x1 += (((x1 >> 3) & 1U ) ^ (x1 & 1U)) << 31;
    x2 += (((x2 >> 3) & 1U) ^ ((x2 >> 2) & 1U) ^ ((x2 >> 1) & 1U) ^ (x2 & 1U)) << 31;
    
    
    // ---------- 计算1568-1599位的比特 ---------- 
    uint32_t mask1, mask2;
    for(size_t i = 32; i < NC; ++i)
    {
        mask1 = ((x1 >> (i - 31 + 3) % 32) & 1U) ^ ((x1 >> (i - 31) % 32) & 1U);
        mask2 = ((x2 >> (i - 31 + 3) % 32) & 1U) ^ ((x2 >> (i - 31 + 2) % 32) & 1U) ^ ((x2 >> (i - 31 + 1) % 32) & 1U) ^ ((x2 >> (i - 31) % 32) & 1U); 

        // 位运算+赋值(先用and提取，在用or赋值)
        x1 = (x1 & ~(1U << (i - 32) % 32)) | (mask1 << (i - 32) % 32);
        x2 = (x2 & ~(1U << (i - 32) % 32)) | (mask2 << (i - 32) % 32);

    }

    // ---------- 计算1600-x1_x2_len位并赋值out ----------
    uint32_t sum = 0;
    for(size_t i = NC, j = 0; i < xl_x2_len; ++i)
    {
        mask1 = ((x1 >> (i - 31 + 3) % 32) & 1U) ^ ((x1 >> (i - 31) % 32) & 1U);
        mask2 = ((x2 >> (i - 31 + 3) % 32) & 1U) ^ ((x2 >> (i - 31 + 2) % 32) & 1U) ^ ((x2 >> (i - 31 + 1) % 32) & 1U) ^ ((x2 >> (i - 31) % 32) & 1U); 

        x1 = (x1 & ~(1U << (i - 32) % 32)) | (mask1 << (i - 32) % 32);
        x2 = (x2 & ~(1U << (i - 32) % 32)) | (mask2 << (i - 32) % 32);

        sum += ((mask1 ^ mask2) << ((i - NC) % 32));
        out[j] = sum;  //每一次都会写入out[j]，确保for循环内所有写入out操作执行完毕
        j += (size_t)((i - NC) % 32 == 31);  //根据目前索引执行j++还是j+0
        sum *= (uint32_t)((i - NC) % 32 != 31);  //根据目前索引执行保留原数值还是置零
    }
    return out;
}
