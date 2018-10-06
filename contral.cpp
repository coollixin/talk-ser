#include<iostream>
#include<map>
#include"contral.h"
#include<json/json.h>
#include"view.h"
#include<stdlib.h>
#include"login_view.h"
#include"Register_view.h"
#include"Getlist_view.h"
#include"Exit_view.h"
#include"Talk_one_view.h"
#include"Talk_group_view.h"
#include"Find_view.h"
contral::contral()
{
	_model.insert(make_pair(TYPE_LOGIN,new Login_view()));
	_model.insert(make_pair(TYPE_REGISTER,new Register_view()));
	_model.insert(make_pair(TYPE_GETLIST,new Getlist_view()));
    _model.insert(make_pair(TYPE_EXIT,new Exit_view()));
    _model.insert(make_pair(TYPE_TALK_ONE,new Talk_one_view()));
    _model.insert(make_pair(TYPE_GROUP,new Talk_group_view()));
    //……
    _model.insert(make_pair(TYPE_FIND,new Find_view()));
}
contral::~contral()
{}
void contral::process(char *buff,int fd)
{
	//解析   buff  
    //->type
    //需要解析buff，得到sli端的消息类型然后再map表查并调用相应的处理方法
    cout<<fd<<endl;
    Json::Value val;
    Json::Reader read;
    if(read.parse(buff,val) == -1)
    {
        cout<<"json.read fail"<<endl;
    }
    //int i = atoi(val["type"].asString().c_str());
   // cout<<root["type"].asString()<<endl;
    int i = val["type"].asInt();
    cout<<"come "<<i<<endl;
	_model[i]->process(val,fd);
}
