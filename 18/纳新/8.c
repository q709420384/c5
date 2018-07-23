/*************************************************************************
	> File Name: 8.c
	> Author:Sanjingye 
	> Mail: 
	> Created Time: 2018年04月28日 星期六 18时04分50秒
 ************************************************************************/

#include<stdio.h>

int f(unsigned int num)
{
    unsigned int i;
    for(i = 0; num; i++)
    {
        num &= (num - 1);
    }
    return i;
}
int main()
{
    printf("%d\n", f(7));
}
