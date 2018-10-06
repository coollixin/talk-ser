#ifndef _VIEW_H
#define _VIEW_H
#include<iostream>
#include<json/json.h>
using namespace  std;
enum type
{
    TYPE_LOGIN = 0,
    TYPE_REGISTER = 1,
    TYPE_GETLIST = 2,
    TYPE_EXIT = 3,
    TYPE_TALK_ONE = 4,
    TYPE_GROUP = 5,
    TYPE_FIND = 6
};
class view
{
public:
    virtual void process(Json::Value val,int fd) = 0;
};
#endif
