# GDB init — pre-configured breakpoints for gold_seq debugging

break test_gold_seq.c:9
break gold_seq.c:15     # VLA x1[xl_x2_len]
break gold_seq.c:20     # x2 init loop
break gold_seq.c:24     # x1/x2 gold seq loop
break gold_seq.c:26     # x1[i] = ...
break gold_seq.c:27     # x2[i] = ...
break gold_seq.c:29     # out[j++] = x1[i] ^ x2[i]

echo \n=== BREAKPOINTS SET. Type 'r' to run, 'n' to step, 'c' to continue ===\n
