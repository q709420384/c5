/*************************************************************************
	> File Name: 1.c
	> Author:Sanjingye 
	> Mail: 
	> Created Time: 2018年04月15日 星期日 20时33分10秒
 ************************************************************************/

#include<stdio.h>

int func(unsigned int num)
{
    unsigned int i;
    for(i = 0; num; ++i)
    {
        num &= (num - 1);
    }
    return i;
}

int main()
{
    printf("%d\n", func(9));
}
