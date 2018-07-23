/*************************************************************************
	> File Name: 1.cpp
	> Author:Sanjingye 
	> Mail: 
	> Created Time: 2018年05月21日 星期一 19时51分55秒
 ************************************************************************/

#include<iostream>
using namespace std;

float Div(int a, int b)
{
    if(b == 0)
    {
        double x = 0;
        throw x; //抛出异常,抛出异常之后不进行后面的语句
    }
    return a/b;
}
int main()
{
    int a = 10;
    int b = 0;
    float result = 1;
    try
    {
        result = Div(a, b);
    }
    catch(int)
    {
        cout << "Div Error, b == 0" << endl;
    }
    catch(short)
    {
        cout << "Div Error(short), b" << endl;
    }
    catch(...)
    {
        cout << "Div Error(...)" << endl;
    }
    cout << "result = " << result << endl;
}
 
