#include<iostream>
#include"Getlist_view.h"
#include<string.h>
#include"view.h"
#include<stdio.h>
#include<json/json.h>
#include<sys/socket.h>
#include<mysql/mysql.h>
using namespace std;

void Getlist_view::process(Json::Value val ,int fd)
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
    char buff[128] = "select name from online;";
    if(mysql_real_query(mp,buff,strlen(buff)) == 0)
    {
        mp_res = mysql_store_result(mp);
        if(mp_res == NULL)
        {
            send(fd,"fail",4,0);

        }
        else
        {
            char _send[128] = "list:";
            cout<<"come here"<<endl;
            memset(buff,0,sizeof(buff));
            while(mp_row = mysql_fetch_row(mp_res))
            {
                int i;
                for(i = 0; i < mysql_num_fields(mp_res); i++)
                {
                    strcat(buff,mp_row[i]);
                    strcat(buff," ");
                    
                }
            }
            strcat(_send,buff);
            Json::Value val;
            val["data"] = _send;
            val["type"]= TYPE_GETLIST;
            if(-1 == send(fd,val.toStyledString().c_str(),strlen(val.toStyledString().c_str()),0))
            {
                cout<<"send fail"<<endl;
            }
            mysql_free_result(mp_res);
            mysql_close(mp);
       //     recv(fd,buff,127,0);
         //   strcnmp()
            
        }
    }
    
    else
    {
        cout<<"query fail"<<endl;
    }
    
}
