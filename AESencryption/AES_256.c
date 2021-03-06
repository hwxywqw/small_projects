#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#define SIZE_G              4   // 组大小，32*4 = 128 位
#define SIZE_192_G          6
#define SIZE_256_G          8
#define SIZE_128_ROUND      10  // 十轮迭代
#define SIZE_128_ROUNDKEY   44  // 11个子密钥，每个128位，由4个32位表示
#define SIZE_192_ROUND      12 
#define SIZE_192_ROUNDKEY   52 
#define SIZE_256_ROUND      14 
#define SIZE_256_ROUNDKEY   60 

/*
支持AES128、192、256加解密运算
*/

static const unsigned int 
Rcon[10] = {
0x01000000, 0x02000000, 0x04000000, 0x08000000, 0x10000000,
0x20000000, 0x40000000, 0x80000000, 0x1b000000, 0x36000000},

Colu[] = {0x02, 0x03, 0x01, 0x01, 0x01, 0x02, 0x03, 0x01, 0x01, 0x01, 0x02, 0x03, 0x03, 0x01, 0x01, 0x02},
Cinv[] = {0x0e, 0x0b, 0x0d, 0x09, 0x09, 0x0e, 0x0b, 0x0d, 0x0d, 0x09, 0x0e, 0x0b, 0x0b, 0x0d, 0x09, 0x0e},

Sbox[256] = {
0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76, 
0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0, 
0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15, 
0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75, 
0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84, 
0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf, 
0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8, 
0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2, 
0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73, 
0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb, 
0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79, 
0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08, 
0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a, 
0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e, 
0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf, 
0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16, },

Sinv[256] = {
0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb, 
0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb, 
0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e, 
0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25, 
0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92, 
0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84, 
0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06, 
0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b, 
0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73, 
0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e, 
0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b, 
0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4, 
0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f, 
0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef, 
0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61, 
0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d, };

unsigned int key[SIZE_256_G], roundkey[SIZE_256_ROUNDKEY];
unsigned int FunG(unsigned int word, int round);
unsigned int* KeyExpansion(unsigned int key[], unsigned int roundkey[], int len);
unsigned int SubByte_inv(unsigned int Byte){return Sinv[Byte];}
unsigned int SubByte(unsigned int Byte){return Sbox[Byte];}
unsigned int SubWord(unsigned int Word);
void AddRoundkey(unsigned int state[SIZE_G], unsigned int key[SIZE_128_ROUND], int round);
void ShiftRows(unsigned int state[SIZE_G]);
void ShiftRows_inv(unsigned int state[SIZE_G]);
void MixColumns(unsigned int state[SIZE_G]);
void MixColumns_inv(unsigned int state[SIZE_G]);

unsigned int GFmul(unsigned int a, unsigned int b){
    const unsigned int irrP = 0x11b;
    unsigned int result = 0;
    while (b > 0){
        if ((b & 1) == 1) result ^= a;
        a <<= 1;
        if ((a & 0x100) == 0x100) a ^= irrP;
        a &= 0xff; b >>= 1;
    }return result;
}

unsigned int* AESencode(unsigned int in[], unsigned int roundkey[], int len){
    // 128位AES加密
    int ROUND = (len == 128) ? SIZE_128_ROUND :
                (len == 192) ? SIZE_192_ROUND :
                (len == 256) ? SIZE_256_ROUND :
                               SIZE_128_ROUND ;
    int i, j, k;
    unsigned int* state = in;
    AddRoundkey(state, roundkey, 0);        // 轮密钥加

    // 10轮迭代
    for (i = 1; i < ROUND; i ++){
        // S盒字节代替(一次16位，一共8次)
        for (j = 0; j < SIZE_G; j ++){
        	unsigned int tmp = 0;
            for (k = 0; k < 4; k ++){
            	tmp |= SubByte((state[j] >> (8 * k)) & 0xFF) << (8 * k);
			}
			state[j] = tmp;
		}
        ShiftRows(state);                   // 行移位
        MixColumns(state);                  // 列混淆
        AddRoundkey(state, roundkey, i);    // 轮密钥加
    } 
    // S盒字节代替
    for (j = 0; j < SIZE_G; j ++){
    	unsigned int tmp = 0;
        for (k = 0; k < 4; k ++){
        	tmp |= SubByte((state[j] >> (8 * k)) & 0xFF) << (8 * k);
		}
		state[j] = tmp;
	}
    ShiftRows(state);                       // 行移位
    AddRoundkey(state, roundkey, i);        // 轮密钥加
    return state;
}

unsigned int* AESdecode(unsigned int in[], unsigned int roundkey[], int len){
    int ROUND = (len == 128) ? SIZE_128_ROUND :
                (len == 192) ? SIZE_192_ROUND :
                (len == 256) ? SIZE_256_ROUND :
                               SIZE_128_ROUND ;
    int i, j, k;
    unsigned int* state = in;
    AddRoundkey(state, roundkey, ROUND); // 轮密钥加
    for (i = ROUND-1; i > 0; i --){
        // S盒字节代替(一次16位，一共8次)
        for (j = 0; j < SIZE_G; j ++){
        	unsigned int tmp = 0;
            for (k = 0; k < 4; k ++){
            	tmp |= SubByte_inv((state[j] >> (8 * k)) & 0xFF) << (8 * k);
			}
			state[j] = tmp;
		}
        ShiftRows_inv(state);                   // 行移位
        AddRoundkey(state, roundkey, i);    // 轮密钥加
        MixColumns_inv(state);                  // 列混淆
    } 
    // S盒字节代替
    for (j = 0; j < SIZE_G; j ++){
    	unsigned int tmp = 0;
        for (k = 0; k < 4; k ++){
        	tmp |= SubByte_inv((state[j] >> (8 * k)) & 0xFF) << (8 * k);
		}
		state[j] = tmp;
	}
    ShiftRows_inv(state);                       // 行移位
    AddRoundkey(state, roundkey, i);        // 轮密钥加
    return state;
}

int main(){
    /*
    评测机的换行符为\r\n，需要两次getchar();
    */
//	freopen("in.txt","r",stdin);
    int n, kind, i, j, len;
	unsigned int str[4]={0};
    char buff[40]={0};

	scanf("%d %d", &len, &n); 
    getchar();getchar();getchar();getchar();    // 吞掉\n0x
    int GROUP = (len == 128) ? SIZE_G :
                (len == 192) ? SIZE_192_G :
                (len == 256) ? SIZE_256_G :
                               SIZE_G ;

    for (i = 0; i < SIZE_G; i ++){
        fgets(buff, 9, stdin);
        sscanf(buff, "%x", &str[i]);
    }
    getchar();getchar();getchar();getchar();

    for (i = 0; i < GROUP; i ++){
        fgets(buff, 9, stdin);
        sscanf(buff, "%x", &key[i]);
    }getchar();getchar();

    scanf("%d", &kind);

	KeyExpansion(key, roundkey, GROUP);
	
	if (kind)
		for (int i = 0; i < n; i ++)
			AESencode(str, roundkey, len);
	else
		for (int i = 0; i < n; i ++)
			AESdecode(str, roundkey, len);

	printf("0x%08x%08x%08x%08x", str[0], str[1], str[2], str[3]);
    return 0;
}



unsigned int SubWord(unsigned int Word){
    unsigned int ans = 0;
    for (int i = 0; i < 4; i ++){
        ans |= Sbox[(Word >> (8 * i)) & 0xFF] << (8 * i);
    }
    return ans;
}

unsigned int FunG(unsigned int word, int round){ 
    /* 
    对32位的处理,返回值
    KeyExpansion_128的子调用
    输入为: 下标为4K-1的元素, 和第j轮迭代
    */
    unsigned int ans = 0;
    // RotWord
    word = ((word & 0xFFFFFF) << 8) | ((word & 0xFF000000) >> 24);
    // SubByte
    for (int i = 0; i < 4; i ++){
        ans |= SubByte((word >> (8 * i)) & 0xFF) << (8 * i);
    }
    ans ^= Rcon[round];
    return ans;
}

unsigned int* KeyExpansion(unsigned int key[], unsigned int roundkey[], int GROUP){
    int i, j;
    int times = (GROUP == SIZE_G)     ? SIZE_128_ROUNDKEY :
                (GROUP == SIZE_192_G) ? SIZE_192_ROUNDKEY :
                (GROUP == SIZE_256_G) ? SIZE_256_ROUNDKEY :
                                        SIZE_128_ROUNDKEY ;
    for (i = 0; i < GROUP; i ++){
        roundkey[i] = key[i];
    }
    for (; i < times; i ++){
        unsigned int temp = roundkey[i-1];
        if (i % GROUP == 0)
            temp = FunG(temp, i/GROUP - 1);
        else if ((GROUP > 6) && (i % GROUP == 4))
            temp = SubWord(temp);
        roundkey[i] = roundkey[i - GROUP] ^ temp;
    }
    return roundkey;
}


void AddRoundkey(unsigned int state[SIZE_G], unsigned int key[SIZE_128_ROUND], int round){
    // 轮密钥加: 对128位的处理,操作指针
    unsigned int p;
    for (p = round * SIZE_G; p < (round + 1)*SIZE_G; p ++){
        state[p%4] ^= key[p];
    }
}

void ShiftRows(unsigned int state[SIZE_G]){
    // 行移位: 对128位的处理,操作指针
    int i, j;
    unsigned int tmp[4] = {0}, mod = 0xFF000000;
    for (i = 0; i < SIZE_G; i ++){ // 字内
        for (j = 0; j < SIZE_G; j ++){ // 字间
            tmp[j] |= state[(j+i)%4] & mod;
        }
        mod >>= 8;
    }
    for (i = 0; i < SIZE_G; i ++){
        state[i] = tmp[i];
    }
}

void ShiftRows_inv(unsigned int state[SIZE_G]){
    // 行移位: 对128位的处理,操作指针
    int i, j;
    unsigned int tmp[4] = {0}, mod = 0xFF000000;
    for (i = 0; i < SIZE_G; i ++){ // 字内
        for (j = 0; j < SIZE_G; j ++){ // 字间
            tmp[j] |= state[(j-i+4)%4] & mod;
        }
        mod >>= 8;
    }
    for (i = 0; i < SIZE_G; i ++){
        state[i] = tmp[i];
    }
}

void MixColumns(unsigned int state[SIZE_G]){
    // 列混淆: 对128位的处理,操作指针
    int i, j;
    unsigned int tmp[4] = {0};
    for (i = 0; i < SIZE_G; i ++){ // 字内
    tmp[i] =
    ((GFmul(0x02, ((state[i]>>24)&0xFF))^GFmul(0x03, ((state[i]>>16)&0xFF))^GFmul(0x01, ((state[i]>>8)&0xFF))^GFmul(0x01, (state[i]&0xFF)))<<24)|
    ((GFmul(0x01, ((state[i]>>24)&0xFF))^GFmul(0x02, ((state[i]>>16)&0xFF))^GFmul(0x03, ((state[i]>>8)&0xFF))^GFmul(0x01, (state[i]&0xFF)))<<16)|
    ((GFmul(0x01, ((state[i]>>24)&0xFF))^GFmul(0x01, ((state[i]>>16)&0xFF))^GFmul(0x02, ((state[i]>>8)&0xFF))^GFmul(0x03, (state[i]&0xFF)))<<8)|
    (GFmul(0x03, ((state[i]>>24)&0xFF))^GFmul(0x01, ((state[i]>>16)&0xFF))^GFmul(0x01, ((state[i]>>8)&0xFF))^GFmul(0x02, (state[i]&0xFF)));
    }
    for (i = 0; i < SIZE_G; i ++){
        state[i] = tmp[i];
    }
}

void MixColumns_inv(unsigned int state[SIZE_G]){
    // 列混淆: 对128位的处理,操作指针
    int i, j;
    unsigned int tmp[4] = {0};
    for (i = 0; i < SIZE_G; i ++){ // 字内
    tmp[i] =
    ((GFmul(0x0e, ((state[i]>>24)&0xFF))^GFmul(0x0b, ((state[i]>>16)&0xFF))^GFmul(0x0d, ((state[i]>>8)&0xFF))^GFmul(0x09, (state[i]&0xFF)))<<24)|
    ((GFmul(0x09, ((state[i]>>24)&0xFF))^GFmul(0x0e, ((state[i]>>16)&0xFF))^GFmul(0x0b, ((state[i]>>8)&0xFF))^GFmul(0x0d, (state[i]&0xFF)))<<16)|
    ((GFmul(0x0d, ((state[i]>>24)&0xFF))^GFmul(0x09, ((state[i]>>16)&0xFF))^GFmul(0x0e, ((state[i]>>8)&0xFF))^GFmul(0x0b, (state[i]&0xFF)))<<8)|
    (GFmul(0x0b, ((state[i]>>24)&0xFF))^GFmul(0x0d, ((state[i]>>16)&0xFF))^GFmul(0x09, ((state[i]>>8)&0xFF))^GFmul(0x0e, (state[i]&0xFF)));
    }
    for (i = 0; i < SIZE_G; i ++){
        state[i] = tmp[i];
    }
}
