/*************************************************************************
	> File Name: myerror.h
	> Author:Sanjingye 
	> Mail: 
	> Created Time: 2018年01月02日 星期二 15时36分34秒
 ************************************************************************/

#ifndef _MYERROR_H
#define _MYERROR_H
#include<error.h>
void my_err(const char* err_string,int line)
{
	fprintf(stderr,"line:%d",__LINE__);
	perror(err_string);
	exit(1);
}
#endif
