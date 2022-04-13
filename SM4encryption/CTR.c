#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SM4.c"


void SM4_CTR_encode(unsigned int key[4], unsigned int vector[4]){
    // 对CTR模式而言，加解密的流程是一样的，所以无需分为两个函数
    int cnt = 0, i;
    unsigned int read=0, roundkey[32], input[4]={0}, tmp[4] = {0};
    keygenerate(key, roundkey);
    while((scanf("%x", &read))!=EOF){
        input[cnt/4] <<= 8;
        input[cnt/4] |= read;
        cnt ++;
        if (cnt == 16){
            cnt = 0;
            for (i = 0; i < 4; i ++){
                tmp[i] = vector[i];
            }
            SM4_encode(tmp, roundkey);
            XOR_128(input, tmp);

            for (i = 3; i >= 0; i --){
                if (vector[i] == 0xFFFFFFFF){
                    vector[i] = 0;
                } else {
                    vector[i] = vector[i] + 1;
                    break;
                }
            }
            for (i = 0; i < 4; i ++){
                printf("0x%02x 0x%02x 0x%02x 0x%02x ", (input[i]&0xFF000000)>>24, (input[i]&0xFF0000)>>16, (input[i]&0xFF00)>>8, input[i]&0xFF);
                input[i] = 0;
            }
            puts("");
        }
    }
    if (cnt == 0) return;

    for (i = 0; i < 4; i ++){
        tmp[i] = vector[i];
    }

    input[cnt/4] <<= 8*(cnt%4==0 ? 0 : 4-cnt%4);
    SM4_encode(tmp, roundkey);
    XOR_128(input, tmp);
    for (i = 0; i < cnt; i ++)
        printf("0x%02x ", (input[i/4]>>(8*(3-i%4)) & 0xFF));
}
