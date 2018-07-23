/*************************************************************************
	> File Name: 13.c
	> Author:Sanjingye 
	> Mail: 
	> Created Time: 2018年04月28日 星期六 19时07分54秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct a
{
    char* name;
    int num;
}A;

void func(A *a)
{
    a = (A*)malloc(sizeof(A));
    strcpy(a->name, "XiyouLinuxGroup");
    a->num = 2018;
}

int main()
{
    A *a;
    func(a);
    printf("%s %d\n", a->name, a->num);
    return 0;
}
