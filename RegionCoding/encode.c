#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "coding.c"
#define SCALE_LEN 16

struct Region arr = {{0},{0},0,{0},1 << 28, 1 << 12}; // 1<<31,1<<23

void encode(void){
    FILE *fin, *fout, *ftmp;
//    char namein[50]="test2.jpg", nameout[50]="out.jpg";
    char namein[50]="articleall.txt", nameout[50]="fileout.txt";
//    char namein[50]="filein.txt", nameout[50]="fileout.txt";
    
// 第一遍读文件: 创建映射区间
    // 构造函数
    fin = fopen(namein, "rb");
    unsigned char ch;
    // 文件读入
    while (fread(&ch, sizeof(const char), 1, fin)){
		arr.freq[ch] ++;
	}
    // 频度统计
    for (int i = 0; i < 256; i ++){
        arr.freq_sum += arr.freq[i];
    }
    // 区间计算
    for (int i = 0; i < 256; i ++){
        arr.list[i] = (i!=0 ? arr.list[i-1] : 0) + ((double)arr.scale / (double)arr.freq_sum * arr.freq[i]);
        // 调整最低区间
//        if ((i != 0) && (arr.freq[i] != 0) && (arr.list[i] - arr.list[i-1] < 10)){
//            arr.list[i] += 10 - (arr.list[i] - arr.list[i-1]);
//        }
    }
    // 避免初始化精度丢失，将后续频度为0的区间定为0
    for (int i = 255; i >= 0; i --){
        arr.list[i] = arr.scale - 1;
        if (arr.freq[i] != 0) break;
    }

    ftmp = fopen("filetmp.txt", "w");
    fprintf(ftmp, "%llu\n", arr.freq_sum);
    for (int i = 0; i < 256; i ++){
        fprintf(ftmp, "%d:%llu\n", i, arr.list[i]);
    }
    fclose(ftmp);

    


// 第二遍读文件: 对文件进行编码
    fseek(fin, 0, SEEK_SET);
	fout = fopen(nameout, "wb");
	int i;
    struct Abyte byte = {0,0};
    unsigned long long tool = 0, R_all, tmp, cmp;
    unsigned long long low = 0;
    unsigned long long high = arr.scale - 1;
    
    while (fread(&ch, 1, 1, fin)){
        R_all = high - low;
        tmp = low;
        low = tmp + (double)R_all / (double)arr.scale * arr.list[ch-1] + 1;
        high= tmp + (double)R_all / (double)arr.scale * arr.list[ch];

        while ((high ^ low) >> 47 == 0){// 从高位到低位
            byte.cnt ++;
            byte.Byte |= ((high >> 47) & 1) << (8-byte.cnt);// 加入输出缓冲区
            
            low  <<= 1;
            high <<= 1;

            if (byte.cnt == 8){// 8位一输出
                fwrite(&byte.Byte, 1, 1, fout);
                byte.cnt = 0;
                byte.Byte = 0;
            }
        }
    }


    // 结尾输出残余的编码
    tmp = (low >> 1) + (high >> 1);
    for (int i = 47; i >= 0; i --){
        byte.cnt ++;
        byte.Byte |= ((tmp >> i) & 1) << (8-byte.cnt);
        if (byte.cnt == 8){// 8位一输出
            fwrite(&byte.Byte, 1, 1, fout);
            byte.cnt = 0;
            byte.Byte = 0;
        }
    }
    if (byte.Byte != 0)
        fwrite(&byte.Byte, 1, 1, fout);

	fclose(fout);
	
    fclose(fin);
	
}


int main(){
    encode();
    return 0;
}
