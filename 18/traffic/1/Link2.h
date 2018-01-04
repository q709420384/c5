/*************************************************************************
> File Name: Link2.h
> Author:Sanjingye 
> Mail: 
> Created Time: 2018年01月02日 星期二 16时22分45秒
************************************************************************/

#ifndef _LINK2_H
#define _LINK2_H
#include"myerror.h"
#include<sys/types.h>
#include<dirent.h>
#include<iostream>
#include<string.h>
using std::cout;
using std::endl;
using std::cin;：

struct City
{
    string Aname;
    double cost;
    int distance;
    double time;
    City* next;

    City(const char* name = "", double c = -1, int d = -1, double t = -1)
    : Aname(name), cost(c), distance(d), time(t)
    {
        next = NULL:
    }
}

struct CityNode
{
    string Cname;
    City* first;
    CityNode() : Cname(""), first(NULL);
    {}
};

class CityAdj
{
private:
    CityNode* vertex;
    int vexnum;
public:
    CityAdj()
    {
        vexnum = 0;
        DIR* dir;
        struct dirent* ptr;
        dir = opendir("./city/");
        while((ptr = readdir(dir)) != NULL)
        {
            vexnum++;
        }
        vertex = new CityNode[vexnum];
    }
    ~CityNode()
    {
        delete [] vertex;
    }
    void makeEmpty()
    {
        int i = 0;
        City* q;
        while(i < vexnum)
        {
            while(vertex[i]->first != NULL)
            {
                q = vertex[i]->first;
                vertex[i]->first = q->next;
                delete q;
            }
            i++;
        }
        delete [] vexnum;
    }
    void inputRear();
};

void City::inputRear()
{
    City* newnode, *last;
    makeEmpty();

}

#endif
