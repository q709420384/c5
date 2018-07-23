/*************************************************************************
	> File Name: 1.cpp
	> Author:Sanjingye 
	> Mail: 
	> Created Time: 2018年03月13日 星期二 18时17分09秒
 ************************************************************************/
#include <QtGui/QApplication>
#include "widget.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    Widget w;
    w.show();
    return app.exec();
}
