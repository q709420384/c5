/*************************************************************************
	> File Name: 2.c
	> Author:Sanjingye 
	> Mail: 
	> Created Time: 2018年04月27日 星期五 21时51分00秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main()
{
    int a[3][2] = {2,0,1,8};
    int i = 0;
    char *str = (char*)malloc(sizeof(char) * 20);
    memset(str, 0, 20);
    strcpy(str, "\0101\\xb2");

    printf("%zu %zu %d\n", sizeof(a), sizeof(a[1][1] = 0), a[1][1]);
    printf("%zu %zu\n", sizeof(str), strlen(str));
    printf("\0101\\xb2");
}
