/*************************************************************************
	> File Name: 12.c
	> Author:Sanjingye 
	> Mail: 
	> Created Time: 2018年04月28日 星期六 18时21分34秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{
    FILE* p = fopen("Linux.txt", "wb");
    long long a = 0x78756e694c;
    fwrite(&a, sizeof(a), 1, p);
    char* str = (char*)malloc(sizeof(a)+1);
    memset(str, 0, sizeof(a)+1);
    memcpy(str, &a, sizeof(a));
    printf("%lld %s", a, str);
    
    free(str);
}
