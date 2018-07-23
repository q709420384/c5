/*************************************************************************
	> File Name: 5.c
	> Author:Sanjingye 
	> Mail: 
	> Created Time: 2018年04月27日 星期五 22时37分53秒
 ************************************************************************/

#include<stdio.h>

int main()
{
    char y[] = "XiYouLinuxGroup", x[] = "2018";
    char *const p1 = y;
    const char *p2 = y;
    p1 = x;
    p2 = x;
    *p1 = 'x';
    *p2 = 'x';
}
