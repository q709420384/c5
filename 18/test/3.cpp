/*************************************************************************
	> File Name: 3.cpp
	> Author:Sanjingye 
	> Mail: 
	> Created Time: 2018年04月01日 星期日 19时58分29秒
 ************************************************************************/


#include<iostream>
#include<math.h>
using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;
    int s = n - 1;
    pow(s, m - 2);
    s = s * n * (n -2);
    cout << s << endl;
}
