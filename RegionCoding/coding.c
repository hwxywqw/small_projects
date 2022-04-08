#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Region{
    int freq[256];      // 频度统计
    int freq_accu[256]; // 积累频度
    int freq_sum;
    unsigned long long list[256];      // 区间计算
    unsigned long long scale;// 区间大小
    unsigned long long min;  // 最小运算区间
};

struct Abyte{
    unsigned char Byte;
    int cnt;
};

int bitlength(unsigned long long n){
    for(int i = 63; i >= 0; i --){
        int m = (n >> i) & 0x0000000000000001;
        if (m) return (i + 1);
    }
    return 0;
}


unsigned char find(unsigned long long num, unsigned long long* list){
    // 返回右值即可，也就是包含now的那个字符
    for (int i = 0; i <= 255; i ++){
        if (num <= list[0]) return 0;
        else if (num >= list[i-1] && num < list[i]){
            return i;
        }
    }
	// int l = 0, r = 255;
    // if (num <= list[0])
    //     return 0;
    // else {
    //     while (r - l > 1){
    //         int mid = l + (r + l)/2;
    //         if (num <= list[mid])
    //             r = mid;
    //         else 
    //             l = mid;
    //     }
    //     if ((num >= list[l]) && (num <= list[r]))
    //         return r;
    //     else
    //         return -1;
    // }
}
