/*************************************************************************
	> File Name: jjalloc.cpp
	> Author:Sanjingye 
	> Mail: 
	> Created Time: 2018年03月26日 星期一 20时32分36秒
 ************************************************************************/

#include<iostream>
#include<vector>
#include"jjalloc.h"
using namespace std;

int main()
{
    int ia[5] = {0, 1, 2, 3, 4};
    unsigned int i;

    vector<int, JJ::allocator<int>> iv(ia, ia + 5);
    for(i = 0; i < iv.size(); i++)
        cout << iv[i] << " ";
    cout << endl;
}
