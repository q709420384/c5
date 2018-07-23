/*************************************************************************
	> File Name: t.cpp
	> Author:Sanjingye 
	> Mail: 
	> Created Time: 2018年05月13日 星期日 22时27分55秒
 ************************************************************************/

#include<iostream>
#include<string>
#include<string.h>
using namespace std;

int main()
{
    char str[10] = {"XiYou"};
    string st("XiYouLinux");
    cout << st.c_str() << endl;
    strcpy((char *)st.c_str(), "XiYou");
    cout << st.c_str() << endl;
    
}
