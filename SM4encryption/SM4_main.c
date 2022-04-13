#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SM4.c"

int main(){
//	freopen("in.txt","r",stdin);
    int n, i, cnt, kind;
    char buff[50], tmp[50];
    unsigned int input[4], key[4], roundkey[32];
    gets(buff); sscanf(buff, "%d", &n);
    gets(buff);
        for (i = 2, cnt = 0; cnt < 4; cnt++, i += 8){
            memset(tmp, 0, 50*sizeof(tmp[0]));
            strncpy(tmp, &buff[i], 8);
            sscanf(tmp, "%x", &input[cnt]);
        }
    gets(buff);
        for (i = 2, cnt = 0; cnt < 4; cnt++, i += 8){
            memset(tmp, 0, 50*sizeof(tmp[0]));
            strncpy(tmp, &buff[i], 8);
            sscanf(tmp, "%x", &key[cnt]);
        }
    gets(buff); sscanf(buff, "%d", &kind);


    keygenerate(key, roundkey);

    if (kind)
		for (int i = 0; i < n; i ++)
			SM4_encode(input, roundkey);
	else
		for (int i = 0; i < n; i ++)
			SM4_decode(input, roundkey);

	printf("0x%08x%08x%08x%08x", input[0], input[1], input[2], input[3]);
}
