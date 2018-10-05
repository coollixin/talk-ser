/*************************************************************************
	> File Name: Register.h
	> Author: 
	> Mail: 
	> Created Time: 2018年07月17日 星期二 15时46分35秒
 ************************************************************************/

#ifndef _REGISTER_H
#define _REGISTER_H
#include<iostream>
#include"view.h"
using namespace std;
class Register_view :public view
{
public:
    virtual void process(Json::Value val,int fd);
};
#endif
