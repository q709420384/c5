/*************************************************************************
	> File Name: 1.cpp
	> Author:Sanjingye 
	> Mail: 
	> Created Time: 2018年01月02日 星期二 14时56分08秒
 ************************************************************************/

#include<iostream>
#include"Link.h"
#include<string>
using namespace std;

int main()
{
    List<string> namelist;
    namelist.inputRear("./city/");
    namelist.output();
}

