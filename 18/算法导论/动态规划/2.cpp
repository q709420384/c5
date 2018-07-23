/*************************************************************************
	> File Name: 1.cpp
	> Author:Sanjingye 
	> Mail: 
	> Created Time: 2018年04月10日 星期二 20时58分40秒
 ************************************************************************/

#include<iostream>
#include<time.h> 
#include<stdio.h>
using namespace std;

int arr[100] = {0};
int max(int a, int b)
{
    return a>b?a:b;
}

int CUT(int p[], int n)
{
    if(n == 0)
        return 0;
    if(arr[n] != 0)
    	return arr[n];
    int q = -999;
    for(int i = 1; i <= n; ++i)
    {
        q = max(q, p[i]+CUT(p, n-i));
    }
    arr[n] = q;
    return q;
}

int main()
{
    int n;
    int p[]={0,1,5,8,9,10,17,17,20,24,30};
    cin >> n;
    clock_t start, finish;
    double duration;
    
    start = clock();
    cout << CUT(p, n) << endl;
    finish = clock();
    duration = (double)(finish - start) / CLOCKS_PER_SEC;
    printf( "%f seconds\n", duration );
    for(int i = 1; i <= n; ++i)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}
