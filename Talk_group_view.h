#ifndef _TALK_GROUP_VIEW_H
#include"view.h"
#include<json/json.h>

class Talk_group_view:public view
{
public:
    virtual void process(Json::Value val,int fd);
};
#define _TALK_GROUP_VIEW_H
#endif
