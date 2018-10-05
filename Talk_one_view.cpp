#include<iostream>
#include"Talk_one_view.h"
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<json/json.h>
#include<sys/socket.h>
#include<mysql/mysql.h>
using namespace std;
void Talk_one_view::process(Json::Value val ,int fd)
{
    MYSQL *mp = mysql_init((MYSQL*)0);
    MYSQL_RES *mp_res;
    MYSQL_ROW mp_row;
    if(!mysql_real_connect(mp,"127.0.0.1","root","123456",NULL,3306,NULL,0))
    {
        cout<<"sql connect fail;errno:"<<endl;
        return ;
    }
    if(mysql_select_db(mp,"usr"))
    {
        cout<<"mysql db fail"<<endl;
        return;
    }
    char buff[128] = {0};
    char name[10] = {0};
    //得到A-》B A的name
    sprintf(buff,"select *from online where fd = '%d';",fd);
    
    if(mysql_real_query(mp,buff,strlen(buff)) == 0)
    {
        mp_res = mysql_store_result(mp);
        mp_row = mysql_fetch_row(mp_res);
        if(mp_row != NULL)
        {
            strcat(name, mp_row[0]);
            cout<<name<<endl;
        }
        else
        {
            cout<<"-1"<<endl;
        }
    }
    memset(buff,0,sizeof(buff));
    sprintf(buff,"select* from online where name = '%s'",val["name"].asString().c_str());
    if(mysql_real_query(mp,buff,strlen(buff)) == 0)
    {
       
       mp_res = mysql_store_result(mp);
       mp_row = mysql_fetch_row(mp_res);
        if(mp_row == NULL)
        {
            cout<<" mp fail"<<endl;
            return;
        }
        else
        {

            char buf[128] = {0};
            strcat(buf,name);
            strcat(buf,"\n");
            strcat(buf,val["data"].asString().c_str());
            int c =  atoi(mp_row[1]);
            cout<<" c:"<<c<<endl;
            Json::Value val;
            val["type"] = TYPE_TALK_ONE;
            val["data"] = buf;
            cout<<val["type"].asInt()<<endl;
            cout<<val["data"].asString().c_str();
            if(-1 == send(c,val.toStyledString().c_str(),strlen(val.toStyledString().c_str()),0) == -1)
            {
                cout<<"json fail"<<endl;
            }
        
        }
    }
    
    else
    {
        cout<<"query fail"<<endl;
    }
    
}
