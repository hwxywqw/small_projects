#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>

unsigned long long weak[8], semiweak[24];
int Kinv[56], Ktmp[56][2];
static const int 
Ksub[56] = {57, 49, 41, 33, 25, 17,  9,  1, 58, 50, 42, 34, 26, 18,
			10,  2, 59, 51, 43, 35, 27, 19, 11,  3, 60, 52, 44, 36,
			63, 55, 47, 39, 31, 23, 15,  7, 62, 54, 46, 38, 30, 22,
			14,  6, 61, 53, 45, 37, 29, 21, 13,  5, 28, 20, 12,  4};


// 求初始置换的逆置换
int cmp(const void *a, const void *b){return *(int*)(a+1)-*(int*)(b+1);}
void qsort_dim2(int a[][2], int n){
	int i;
	for (i = 0; i < n; i ++)
		a[i][0] = i + 1;
	for (i = 0; i < n; i ++)
		a[i][1] = Ksub[i];
	qsort(a, n, sizeof(a[0]), cmp);
	for (i = 0; i < n; i ++)
		Kinv[i] = a[i][0];
}

void weakkey(){
	int cnt = 0;
	unsigned long long iniw[4] = {0, ((unsigned long long)1<<28)-1, -1, (((unsigned long long)1<<28)-1) << 28};
	unsigned long long tmp = 0, group = 0;
	for (int j = 0; j < 4; j ++){
		// tmp是去除了奇偶校验位之后的置换前密钥
		for (int i = 0; i < 56; i ++){
			tmp <<= 1;
			tmp |= (iniw[j] >> (56 - Kinv[i])) & 1;
		}
		// 分为奇, 偶置换恢复初始密钥
		for (int k = 7; k >= 0; k --){ // 分为8组
			group = (tmp >> (7*k)) & ((1 << 7) - 1);
			weak[2*j] |= (group<<1); 	 // 奇校验
			weak[2*j + 1] |= (group<<1); // 偶校验
			int num = 0;
			for (int i = 0; i < 7; i++){ // 每8位有几个1
				if (((group >> i) & 1) == 1)
					num ++;
			}
			if (num % 2 == 0)	// 奇校验成功
				weak[2*j] |= 1;
			else				// 偶校验成功
				weak[2*j+1] |= 1;
			if (k != 0){
				weak[2*j] <<= 8;
				weak[2*j+1] <<= 8;
			}
		}
	}
}

void semiweakkey(){
	int cnt = 0;
	unsigned long long iniw[12] = 
	{0x5555555, 0xAAAAAAA, 
	0xFFFFFFF5555555, 0xFFFFFFFAAAAAAA, 
	0x55555555555555, 0xAAAAAAAAAAAAAA, 
	0x55555550000000, 0xAAAAAAA0000000, 
	0X5555555FFFFFFF, 0XAAAAAAAFFFFFFF,
	0xAAAAAAA5555555, 0x5555555AAAAAAA};
	unsigned long long tmp = 0, group = 0;
	for (int j = 0; j < 12; j ++){
		// tmp是去除了奇偶校验位之后的置换前密钥
		for (int i = 0; i < 56; i ++){
			tmp <<= 1;
			tmp |= (iniw[j] >> (56 - Kinv[i])) & 1;
		}
		// 分为奇, 偶置换恢复初始密钥
		for (int k = 7; k >= 0; k --){ // 分为8组
			group = (tmp >> (7*k)) & ((1 << 7) - 1);
			semiweak[2*j] |= (group<<1); 	 // 奇校验
			semiweak[2*j + 1] |= (group<<1); // 偶校验
			int num = 0;
			for (int i = 0; i < 7; i++){ // 每8位有几个1
				if (((group >> i) & 1) == 1)
					num ++;
			}
			if (num % 2 == 0)	// 奇校验成功
				semiweak[2*j] |= 1;
			else				// 偶校验成功
				semiweak[2*j+1] |= 1;
			if (k != 0){
				semiweak[2*j] <<= 8;
				semiweak[2*j+1] <<= 8;
			}
		}
	}
}

int main(){
	qsort_dim2(Ktmp, 56); 
	weakkey();
	semiweakkey();
	for (int i = 0; i < 8; i ++){
		printf("0x%016llx\n", weak[i]);
	}
	for (int i = 0; i < 24; i +=4){
		printf("0x%016llx 0x%016llx\n", semiweak[i], semiweak[i+2]);
		printf("0x%016llx 0x%016llx\n", semiweak[i+1], semiweak[i+3]);
	}
    return 0;
}