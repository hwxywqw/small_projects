#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

char buff[50000+5], example[26][100];
int sta[26] = {0}, cnt[26][2];
static const char alphabet[26] = {
	'e','t','a','o','i','n','s','h','r','d','l','c',
	'u','m','w','f','g','y','p','b','v','k','j','x','q','z'};
char relat[26][2];

void sort_dim1(char a[][2], int n){
	int i, j;
	char flag=0, hold[2];
	for(i = 0; i < n-1; i ++){
		flag = 0;
		for(j=0; j<n-1-i; j++)
		if(a[j][0] > a[j+1][0]){
			hold[0] = a[j][0];hold[1] = a[j][1];
			a[j][0] = a[j+1][0];a[j][1] = a[j+1][1];
			a[j+1][0] = hold[0];a[j+1][1] = hold[1];
			flag = 1;
		}
		if (0==flag) break;
	}
}

int cmp(const void *a, const void *b){return *(int*)(a+1)-*(int*)(b+1);}
void sort_dim2(int a[][2], int n){
	int i, j, flag=0, hold[2];
	for (i = 0; i < n; i ++){
		a[i][0] = 'a' + i;
		a[i][1] = sta[i];
	}
	for(i = 0; i < n-1; i ++){
		flag = 0;
		for(j=0; j<n-1-i; j++)
		if(a[j][1] < a[j+1][1]){
			hold[0] = a[j][0];hold[1] = a[j][1];
			a[j][0] = a[j+1][0];a[j][1] = a[j+1][1];
			a[j+1][0] = hold[0];a[j+1][1] = hold[1];
			flag = 1;
		}
		if (0==flag) break;
	}
	for (i = 0; i < n; i ++){
		relat[i][0] = (char)a[i][0];
		relat[i][1] = alphabet[i];
	}
	printf("possible mistake:");
	for (i = 1; i < 26; i ++){
		if ((sta[i]-sta[i+1]) < 3*sta[i+1]/100){
			printf("[%c,%c]", alphabet[i], alphabet[i+1]);
		} 
	}puts("");
	sort_dim1(relat, n);
}



int main(){
	FILE *in, *out, *fpw;
	in  = fopen("articleall.txt",  "r");
	fpw = fopen("translateall.txt", "w");
	out = fopen("results.txt", "w");

	// 统计
	int i, j, k, tmp=0, d1, d2;
	char from, to, tmp1, tmp2;
	while (fgets(buff, 50000, in) != NULL){
		for(i=0; i<strlen(buff); i++){
			sta[buff[i] - 'a']++;
			if ((i>=100) && (i-tmp>1000) && example[buff[i]-'a'][0]==0){
				tmp = i;
				strncpy(example[buff[i]-'a'], &buff[i-45], 90);
			}
		}
	}

	// 建立映射关系
	sort_dim2(cnt, 26);

	// 使用例子
	for (i = 0; i < 26; i ++){
		for (j = 0; j < strlen(example[i]); j ++){
			example[i][j] = relat[example[i][j]-'a'][1];
		}
	}
	for (i = 0; i < 26; i ++){
		printf("%c:%c\n", relat[i][0], relat[i][1]);
	}
	
	k = 0;
	while(1){
		printf("%s\nexchange a and b:(a b/Y/E)", example[k]);
		scanf("%c", &from); getchar();
		if (from == 'Y') {
			k ++;
		} else if (from == 'E') {
			k = 26;
		} else {
			scanf("%c", &to); getchar();
			printf("");
			
			for (j = 0; j < 26; j ++){
				if (from == relat[j][1]) d1 = j;
				if (to   == relat[j][1]) d2 = j;
			}
			tmp = relat[d1][1];
			relat[d1][1] = relat[d2][1];
			relat[d2][1] = tmp;
			for (i = 0; i < 26; i ++){
				for (j = 0; j < strlen(example[i]); j ++){
					if (example[i][j] == from)
						example[i][j] = to;
					else if (example[i][j] == to)
						example[i][j] = from;
				}
			}
		}
		from = 0;
		if (k == 26){
			for (i = 0; i < 26; i ++){
				fprintf(out, "%c:%c\n", relat[i][0], relat[i][1]);
			}
			fseek(in, 0, SEEK_SET);
			while (fgets(buff, 50000, in) != NULL){
				for(i=0; i<strlen(buff); i++){
					buff[i] = relat[buff[i]-'a'][1];
				}
				fprintf(fpw, "%s", buff);
			}
			break;
		}
	}

	fclose(in);
	fclose(out);
	fclose(fpw);
	return 0;
}


