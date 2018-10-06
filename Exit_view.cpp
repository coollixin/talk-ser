#include<iostream>
#include"Exit_view.h"
#include<string.h>
#include<stdio.h>
#include<unistd.h>
#include<json/json.h>
#include"view.h"
#include<sys/socket.h>
#include<mysql/mysql.h>
using namespace std;
void Exit_view::process(Json::Value val ,int fd)
{
    /*if(val["name"].asString().c_str() == NULL)
    {
        send(fd,"exit",4,0);
    }*/
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
    cout<<val["name"]<<endl;
    char buff[128] = {0};
    sprintf(buff,"delete from online where fd = '%d';",fd);
    if(mysql_real_query(mp,buff,strlen(buff)) == 0)
    {
        cout<<"okk"<<endl;
        
            Json::Value val;
            val["type"] = TYPE_EXIT;
            send(fd,val.toStyledString().c_str(),strlen(val.toStyledString().c_str()),0);
            cout<<"exit"<<endl;
            close(fd);
            mysql_close(mp);
        
    }
    
    else
    {
        cout<<"query fail"<<endl;
    }
    
}
