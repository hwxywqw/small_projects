#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#pragma GCC optimize("O3")

static const int 
Pini[64] = {58, 50, 42, 34, 26, 18, 10,  2, 60, 52, 44, 36, 28, 20, 12,  4,
			62, 54, 46, 38, 30, 22, 14,  6, 64, 56, 48, 40, 32, 24, 16,  8,
			57, 49, 41, 33, 25, 17,  9,  1, 59, 51, 43, 35, 27, 19, 11,  3,
			61, 53, 45, 37, 29, 21, 13,  5, 63, 55, 47, 39, 31, 23, 15,  7},

Pinv[64] = {40,  8, 48, 16, 56, 24, 64, 32, 39,  7, 47, 15, 55, 23, 63, 31,
			38,  6, 46, 14, 54, 22, 62, 30, 37,  5, 45, 13, 53, 21, 61, 29,
			36,  4, 44, 12, 52, 20, 60, 28, 35,  3, 43, 11, 51, 19, 59, 27,
			34,  2, 42, 10, 50, 18, 58, 26, 33,  1, 41,  9, 49, 17, 57, 25},

Ksub1[56] ={57, 49, 41, 33, 25, 17,  9,  1, 58, 50, 42, 34, 26, 18,
			10,  2, 59, 51, 43, 35, 27, 19, 11,  3, 60, 52, 44, 36,
			63, 55, 47, 39, 31, 23, 15,  7, 62, 54, 46, 38, 30, 22,
			14,  6, 61, 53, 45, 37, 29, 21, 13,  5, 28, 20, 12,  4},

Ksub2[48] ={14, 17, 11, 24,  1,  5,  3, 28, 15,  6, 21, 10,
			23, 19, 12,  4, 26,  8, 16,  7, 27, 20, 13,  2,
			41, 52, 31, 37, 47, 55, 30, 40, 51, 45, 33, 48,
			44, 49, 39, 56, 34, 53, 46, 42, 50, 36, 29, 32},

Kext[48] = {32,  1,  2,  3,  4,  5,  4,  5,  6,  7,  8,  9,
			8,  9, 10, 11, 12, 13, 12, 13, 14, 15, 16, 17,
			16, 17, 18, 19, 20, 21, 20, 21, 22, 23, 24, 25,
			24, 25, 26, 27, 28, 29, 28, 29, 30, 31, 32,  1 },

Kleft[16] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1},

Pbox[32] = {16, 7, 20, 21, 29, 12, 28, 17,  1, 15, 23, 26,  5, 18, 31, 10,
			2,  8, 24, 14, 32, 27,  3,  9, 19, 13, 30,  6, 22, 11,  4, 25},

Sbox[8][64] ={{14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,
			0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8,
			4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0,
			15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13},

			{15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10,
			3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,
			0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15,
			13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9},

			{10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8,
			13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1,
			13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7,
			1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12},

			{7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15,
			13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9,
			10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4,
			3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14},

			{2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9,
			14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6,
			4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14,
			11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3},

			{12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11,
			10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8,
			9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6,
			4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13},

			{4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1,
			13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6,
			1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2,
			6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12},

			{13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7,
			1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2,
			7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8,
			2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}};
			
unsigned long long roundkey[16] = {0};


unsigned long long iniPermutation(unsigned long long word){
	unsigned long long ans = 0;
	for (int i = 0; i < 64; i ++){
		ans <<= 1;
		ans |= (word >> (64 - Pini[i])) & 1;
	}
	return ans;
}

unsigned long long invPermutation(unsigned long long word){
	unsigned long long ans = 0;
	for (int i = 0; i < 64; i ++){
		ans <<= 1;
		ans |= (word >> (64 - Pinv[i])) & 1;
	}
	return ans;
}

unsigned long long funcF(unsigned long long r, unsigned long long key){
	unsigned long long result = 0;
	// ????????????
	for (int i = 0; i < 48; i ++){
		result <<= 1;
		result |= (r >> (32 - Kext[i])) & 1;
	}
	// ????????????
	result ^= key;
	// S???: ???????????????
	unsigned long long tmp = 0;
	for (int i = 7; i >= 0; i --){
		int add = ((result >> (6*i + 4)) & 2) | ((result >> (6*i)) & 1);
		int num = (result >> (6*i + 1)) & ((1 << 4) - 1);
		tmp |= (unsigned long long)(Sbox[7-i][((add) << 4) + num]) << (4*i);
	}
	// P???: ????????????
	result = 0;
	for (int i = 0; i < 32; i ++){
		result <<= 1;
		result |= (tmp >> (32 - Pbox[i])) & 1;
	}

	return result;
}


unsigned long long encode(unsigned long long word, unsigned long long key){
	unsigned long long ans, left, right, tmp;
	word = iniPermutation(word);
	left = word >> 32;
	right = word & (((unsigned long long)1 << 32) - 1);
	for (int t = 0; t < 16; t ++){
		tmp = left;
		left = right;
		right = tmp ^ funcF(right, roundkey[t]);
	}
	word = (right << 32) | left;
	ans = invPermutation(word);
	return ans;
}

unsigned long long decode(unsigned long long word, unsigned long long key){
	unsigned long long ans, left, right, tmp;
	word = iniPermutation(word);
	right = word >> 32;
	left = word & (((unsigned long long)1 << 32) - 1);
	for (int t = 0; t < 16; t ++){
		tmp = right;
		right = left;
		left = tmp ^ funcF(left, roundkey[15-t]);
	}
	word = (left << 32) | right;
	ans = invPermutation(word);
	return ans;
}


void keygenerate(unsigned long long key){
	unsigned long long C=0, D=0, tmp=0, ans=0;
	// ??????8?????????????????????K'=[C0,D0]
	for (int i = 0; i < 56; i ++){
		tmp <<= 1;
		tmp |= (key >> (64 - Ksub1[i])) & 1;
	}
	C = tmp >> 28;
	D = tmp & ((1 << 28) - 1);
	// ?????????????????????16????????????
	for (int i = 0; i < 16; i ++){
		C = (C >> (28 - Kleft[i])) + ((C & ((1 << (28 - Kleft[i])) -1)) << Kleft[i]);
		D = (D >> (28 - Kleft[i])) + ((D & ((1 << (28 - Kleft[i])) -1)) << Kleft[i]);
		tmp = (C << 28) | D;
		ans = 0;
		for (int j = 0; j < 48; j ++){
			ans <<= 1;
			ans |= (tmp >> (56 - Ksub2[j])) & 1;
		}
		roundkey[i] = ans;
	}
}

int main(){
//	freopen("in.txt","r",stdin);
	int n, kind;
	unsigned long long str, key, ans;
	scanf("%d %llx %llx %d", &n, &str, &key, &kind);
	keygenerate(key);
	
	if (kind)
		for (int i = 0; i < n; i ++)
			str = encode(str, key);
	else
		for (int i = 0; i < n; i ++)
			str = decode(str, key);

	printf("0x%016llx", str);
	return 0;
}
