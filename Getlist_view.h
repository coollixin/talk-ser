/*************************************************************************
	> File Name: git_list.h
	> Author: 
	> Mail: 
	> Created Time: 2018年07月25日 星期三 10时52分52秒
 ************************************************************************/

#ifndef _GIT_LIST_H
#include<iostream>
#include"view.h"
class Getlist_view:public view
{
public:
    virtual void process(Json::Value val,int fd);
};
#define _GIT_LIST_H
#endif
