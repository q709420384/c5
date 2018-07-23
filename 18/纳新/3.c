/*************************************************************************
	> File Name: 3.c
	> Author:Sanjingye 
	> Mail: 
	> Created Time: 2018年04月27日 星期五 22时16分22秒
 ************************************************************************/

#include<stdio.h>

static int a = 2018;

static void func(void)
{
    static int b;
    printf("a = %d, b = %d\n", a++, ++b);
}

int main()
{
    func();
    func();
    func();
}
