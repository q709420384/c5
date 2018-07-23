/*************************************************************************
	> File Name: 11.c
	> Author:Sanjingye 
	> Mail: 
	> Created Time: 2018年04月28日 星期六 19时04分49秒
 ************************************************************************/

#include<stdio.h>

struct icd
{
    int a;
    char b;
    double c;
};

struct cdi
{
    char a;
    double b;
    int c;
};

struct AA{

    char a;

	double c;
    //int b;

    //char c; 

}__attribute__((aligned (2)));
int main()
{
    printf("%zu %zu %d\n", sizeof(struct icd), sizeof(struct cdi), sizeof(struct AA));
    return 0;
}
