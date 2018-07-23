/*************************************************************************
	> File Name: 1.cpp
	> Author:Sanjingye 
	> Mail: 
	> Created Time: 2018年03月26日 星期一 19时22分39秒
 ************************************************************************/

#include<iostream>
using namespace std;
template<class T>
void func(T* )
{
    cout << typeid(T).name() << endl;
    cout << sizeof(T) <<endl;
}
int main()
{
    func((int*)0);
}
