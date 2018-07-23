/*************************************************************************
	> File Name: view.h
	> Author:Sanjingye 
	> Mail: 
	> Created Time: 2018年01月05日 星期五 08时42分41秒
 ************************************************************************/

#ifndef _VIEW_H
#define _VIEW_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include"Graph.h"
//#include<iostream>
//using std::cerr;
//using std::endl;

char getch();
char* s_gets(char* st,int n);
void Register(Graphlnk &G);
bool CheckPassword();
int RootView(Graphlnk &G);
int VisitorsView(Graphlnk &G);
#endif
