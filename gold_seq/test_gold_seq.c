#include "gold_seq.h"
#include<stdlib.h>


int main()
{
    uint32_t c_init = 1521;     
    size_t Mpn = 365;
    uint32_t *gseq = gold_seq(c_init, Mpn);
    if (!gseq) return EXIT_FAILURE;
    free(gseq);

    printf("success\n");
    return EXIT_SUCCESS;
}
