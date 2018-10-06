#include<iostream>
#include"login_view.h"
#include<mysql/mysql.h>
#include<string.h>
#include<string>
#include<sys/socket.h>
#include<stdio.h>
#include"contral.h"
extern contral Contral;
using namespace std;
void Login_view::process(Json::Value val,int fd)
{
   // cout<<"login_view"<<endl;
    MYSQL *mp = mysql_init((MYSQL*)0);
    MYSQL_RES *mp_res;
    MYSQL_ROW mp_row;
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
    sprintf(buff,"select *from  usrs where name = '%s' and pw = '%s';",val["name"].asString().c_str(),val["pw"].asString().c_str());
    if(mysql_real_query(mp,buff,strlen(buff)) == 0)
    {

        mp_res = mysql_store_result(mp);
        mp_row = mysql_fetch_row(mp_res);
        if(mp_row == NULL)
        {
            if(-1 == send(fd,"fail",4,0))
            {
                cout<<"send fail"<<endl;
            
            }
        }
    
        else
        {
            memset(buff,0,sizeof(buff)) ;
            sprintf(buff,"insert into online values('%s','%d');",val["name"].asString().c_str(),fd);
            if(mysql_real_query(mp,buff,strlen(buff)) == 0)
            {
                send(fd,"ok",2,0);    
                cout<<"online insert"<<endl;
                mysql_free_result(mp_res);
                mysql_close(mp);
            }
            else
            {
                cout<<"online insert fail"<<endl;
                send(fd,"fail",4,0);
            }
        }
    }

}
