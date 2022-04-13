#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SM4.c"

/*
int main(){
	freopen("in.txt","r",stdin);
    int n, i, cnt, kind;
    char buff[50], tmp[50];
    unsigned int key[4], vector[4], roundkey[32];

    gets(buff);
        for (i = 2, cnt = 0; cnt < 4; cnt++, i += 8){
            memset(tmp, 0, 50*sizeof(tmp[0]));
            strncpy(tmp, &buff[i], 8);
            sscanf(tmp, "%x", &key[cnt]);
        }
    gets(buff);
        for (i = 2, cnt = 0; cnt < 4; cnt++, i += 8){
            memset(tmp, 0, 50*sizeof(tmp[0]));
            strncpy(tmp, &buff[i], 8);
            sscanf(tmp, "%x", &vector[cnt]);
        }
    gets(buff); sscanf(buff, "%d", &kind);

    if (kind == 1){
        SM4_CBC_encode(key, vector);
    } else {
        SM4_CBC_decode(key, vector);
    }
}
*/


void SM4_CBC_encode(unsigned int key[4], unsigned int vector[4]){
    int cnt = 0, i;
    unsigned int read=0, roundkey[32], input[4]={0};
    keygenerate(key, roundkey);
    while((scanf("%x", &read))!=EOF){
        input[cnt/4] <<= 8;
        input[cnt/4] |= read;
        cnt ++;
        if (cnt == 16){
            cnt = 0;
            XOR_128(input, vector);
            SM4_encode(input, roundkey);
            for (i = 0; i < 4; i ++){
                printf("0x%02x 0x%02x 0x%02x 0x%02x ", (input[i]&0xFF000000)>>24, (input[i]&0xFF0000)>>16, (input[i]&0xFF00)>>8, input[i]&0xFF);
                vector[i] = input[i];
                input[i] = 0;
            }
            puts("");
        }
    }
    int rest = 16 - cnt;
    do {
        input[cnt/4] <<= 8;
        input[cnt/4] |= rest;
    }while (cnt ++ < 15);

    XOR_128(input, vector);
    SM4_encode(input, roundkey);
    for (i = 0; i < 4; i ++){
        printf("0x%02x 0x%02x 0x%02x 0x%02x ", (input[i]&0xFF000000)>>24, (input[i]&0xFF0000)>>16, (input[i]&0xFF00)>>8, input[i]&0xFF);
    }

}

void SM4_CBC_decode(unsigned int key[4], unsigned int vector[4]){
    int cnt = 0, i;
    unsigned int read = 0, roundkey[32], input[4]={0};
    keygenerate(key, roundkey);
    scanf("%x", &read);
    do {
        if (cnt == 16){
            cnt = 0;
            unsigned int tmp[4];
            for (i = 0; i < 4; i ++){
                tmp[i] = input[i];
            }
            SM4_decode(input, roundkey);
            XOR_128(input, vector);
            for (i = 0; i < 4; i ++){
                vector[i] = tmp[i];
            }
            for (i = 0; i < 4; i ++){
                printf("0x%02x 0x%02x 0x%02x 0x%02x ", (input[i]&0xFF000000)>>24, (input[i]&0xFF0000)>>16, (input[i]&0xFF00)>>8, input[i]&0xFF);
                input[i] = 0;
            }
            puts("");
        }
        input[cnt/4] <<= 8;
        input[cnt/4] |= read;
        cnt ++;
    } while((scanf("%x", &read))!=EOF);

	SM4_decode(input, roundkey);
    XOR_128(input, vector);
    int last = input[3] & 0xFF, flag = 0;
    if (last <= 16 && cnt!=0){
        for (cnt = 15; cnt >= 16-last; cnt --){
            if ((input[cnt/4]>>(8*(3-cnt%4)) & 0xFF) != last){
                flag = 1;
                break;
            }
        }
        if (flag == 0){
            for (i = 0; i < 16-last; i ++){
                printf("0x%02x ", (input[i/4]>>(8*(3-i%4)) & 0xFF));
            }
        }
    } else {flag = 1;}

    if (flag == 1){
    	for (i = 0; i < 4; i ++){
            printf("0x%02x 0x%02x 0x%02x 0x%02x ", (input[i]&0xFF000000)>>24, (input[i]&0xFF0000)>>16, (input[i]&0xFF00)>>8, input[i]&0xFF);
            input[i] = 0;
        }
	}
}
