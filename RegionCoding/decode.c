#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "coding.c"
#define SCALE_LEN 16

struct Region arr = {{0},{0},0,{0},1 << 28, 1 << 12}; // 1<<31,1<<23

void decode(void){
    FILE *fin, *fout, *ftmp;
    char namein[50]="fileout.txt", nameout[50]="filedecode.txt";
//	char namein[50]="out.jpg", nameout[50]="decode.jpg";

    ftmp = fopen("filetmp.txt", "r");
    fscanf(ftmp, "%llu", &arr.freq_sum);
    for (int i = 0, a; i < 256; i ++){
        fscanf(ftmp, "%d:%llu\n", &a, &arr.list[i]);
    }
    fclose(ftmp);

    fin = fopen(namein, "rb");
    fout = fopen(nameout, "wb");
    int i, j;
    unsigned long long now = 0;
    unsigned long long low = 0, high = arr.scale - 1;

    // 初始化64位
    unsigned char ch, out;
    for (i = 0; i < 6; i ++){
        now <<= 8;
        fread(&ch, 1, 1, fin);
        now |= ch;
    }
    out = find(now, arr.list);
    fwrite(&out, 1, 1, fout);
    arr.freq_sum --;
	if (arr.freq_sum == 0)  goto out;
    high = arr.list[out]-1;
    low = arr.list[out-1];

    // 循环读入，解码
    int num;
    unsigned long long R_all, tmp, R_flr, cmp;
    struct Abyte byte = {0,0};
    fread(&byte.Byte, 1, 1, fin);
    byte.cnt = 8;
    while (1){
        while ((high ^ low) >> 47 == 0){// 从高位到低位
            now = (now << 1) | ((byte.Byte >> (byte.cnt-1)) & 1);
            byte.cnt --;
            
            high <<= 1;
            low <<= 1;
            
            if (byte.cnt == 0){
                if (fread(&byte.Byte, 1, 1, fin))
                	byte.cnt = 8;
                else{
                	while (1){
                		R_all = high - low;
				        R_flr = now  - low;
				
				        // 对应区间序号
				        tmp = (double)R_flr / (double)R_all * arr.scale;
				        out = find(tmp, arr.list);
				        fwrite(&out, 1, 1, fout);
				        arr.freq_sum --;
				        if (arr.freq_sum == 0)  goto out;
				        
				        tmp = low;
				        low = tmp + (double)R_all / (double)arr.scale * (out != 0 ? arr.list[out-1] : 0) + 1;
				        high= tmp + (double)R_all / (double)arr.scale * arr.list[out];
					}
				}
            }
        }
        R_all = high - low;
        R_flr = now  - low;

        // 对应区间序号
        tmp = (double)R_flr / (double)R_all * arr.scale;
        out = find(tmp, arr.list);
        fwrite(&out, 1, 1, fout);
        arr.freq_sum --;
        if (arr.freq_sum == 0) break;

        // 上下区间�
		tmp  = low;
        low  = tmp + (double)R_all / (double)arr.scale * (out != 0 ? arr.list[out-1] : 0) + 1;
        high = tmp + (double)R_all / (double)arr.scale * arr.list[out];
    }
    
    out:

    fclose(fin);
	fclose(fout);
}



int main(){
    decode();
    return 0;
}
