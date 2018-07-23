/*************************************************************************
	> File Name: 2.cpp
	> Author:Sanjingye 
	> Mail: 
	> Created Time: 2018年03月28日 星期三 09时51分46秒
 ************************************************************************/

#include<iostream>
#include<stdio.h>
using namespace std;

int a[8] = {2,3,4,5,6,7};
void fun(int* pa, int n)
{
    for(int i = 0; i < n-1; i++)
        *(pa + 7) += *(pa + i);
}
int main()
{
    int x,y,z;
    x = 3;y=5;
    x = x+y;
    y=x-y;
    x=x-y;
    cout << "x=" << x <<" y="<<y<<endl;
    return 0;
}

