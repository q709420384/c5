/*************************************************************************
	> File Name: 15.c
	> Author:Sanjingye 
	> Mail: 
	> Created Time: 2018年05月02日 星期三 23时44分57秒
 ************************************************************************/

#include<stdio.h>

#define MAX 100
int paixu(int *arr, int n)
{
    int jishu[MAX], oushu[MAX], i, j, ji = 0, ou = 0;
    for(i = 0; i < n; ++i)
    {
        if(arr[i] % 2 == 0)
            oushu[ou++] = arr[i];
        else
            jishu[ji++] = arr[i];
    }
    for(i = 0; i < ji; ++i)
    {
        arr[i] = jishu[i];
    }
    for( j = 0; i < n; ++i,++j)
    {
        arr[i] = oushu[j];
    }
}
int main()
{
    int arr[MAX] = {0};
    int n, i;
    printf("请输入元素个数:");
    scanf("%d", &n);
    for(i = 0; i < n; ++i)
    {
        scanf("%d", &arr[i]);
    }
    paixu(arr, n);
    for(i = 0; i < n; ++i)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}
