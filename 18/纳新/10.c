/*************************************************************************
	> File Name: 10.c
	> Author:Sanjingye 
	> Mail: 
	> Created Time: 2018年04月28日 星期六 18时09分43秒
 ************************************************************************/

#include<stdio.h>

#define YEAR 2018
#define LEVELONE(x) "XiyouLinux "#x"\n"
#define LEVELTWO(x) LEVELONE(x)
#define MULTIPLY(x,y) x*y

int main()
{
    int x = MULTIPLY(1 + 2, 3);
    printf("%d\n", x);
    printf(LEVELONE(YEAR));
    printf(LEVELTWO(YEAR));
}
