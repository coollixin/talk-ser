#ifndef _TALK_ONE_VIEW_H
#include"view.h"
#include<json/json.h>

class Talk_one_view:public view
{
public:
    virtual void process(Json::Value val,int fd);
};
#define _TALK_ONE_VIEW_H
#endif
