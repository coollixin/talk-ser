/*************************************************************************
	> File Name: Find_pw.h
	> Author: 
	> Mail: 
	> Created Time: 2018年08月31日 星期五 19时50分04秒
 ************************************************************************/
#include"view.h"
//#ifndef _FIND_VIEW_H
class Find_view:public view
{
public:
    virtual void process(Json::Value val,int fd);
};
//#define _FIND_VIEW_H
//#endif
