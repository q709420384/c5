/*************************************************************************
	> File Name: 2.c
	> Author:Sanjingye 
	> Mail: 
	> Created Time: 2018年04月15日 星期日 20时43分32秒
 ************************************************************************/

#include<stdio.h>

#define PRINTINT(num, ...) printf("%d\n", num, ##__VA_ARGS__)

int main()
{
    PRINTINT(1, 2);
    PRINTINT((1, 2));
    return 0;
}
