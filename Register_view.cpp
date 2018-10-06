#include<iostream>
#include"Register_view.h"
#include<mysql/mysql.h>
#include<string.h>
#include<string>
#include<sys/socket.h>
#include<stdio.h>
#include<json/json.h>
using namespace std;

void Register_view::process(Json::Value val,int fd)
{
   // cout<<val["naem"]<<endl;
    cout<<"Register_view"<<endl;
    MYSQL *mp = mysql_init((MYSQL*)0);
    MYSQL_RES *mp_res;
    if(!mysql_real_connect(mp,"127.0.0.1","root","123456",NULL,3306,NULL,0))
    {
        cout<<"mysql connect fail "<<endl;
        return ;
    }
    if(mysql_select_db(mp,"usr"))
    {
        cout<<"mysql select fail"<<endl;
        return ;
    }
    char buff[128] = {0};
    sprintf(buff,"insert into  usrs values('%s','%s','%s');",val["name"].asString().c_str(),val["pw"].asString().c_str(),val["mail"].asString().c_str());
    if(mysql_real_query(mp,buff,strlen(buff)))
    {
        cout<<"mysql query fail"<<endl;
        return ;
    }
    else
    {
        cout<<"you have Register_view one"<<endl;

        if(-1 == send(fd,"ok",2,0))
        {
            cout<<"send fail"<<endl;
        }

    }
    

}
