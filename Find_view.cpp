#include<iostream>
#include"Find_view.h"
#include<mysql/mysql.h>
#include<string.h>
#include<string>
#include<sys/socket.h>
#include<stdlib.h>
#include<stdio.h>
#include"contral.h"
#include<unistd.h>
extern contral Contral;
using namespace std;
void Find_view::process(Json::Value val,int fd)
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
    sprintf(buff,"select *from  usrs where name = '%s' and mail = '%s';",val["name"].asString().c_str(),val["mail"].asString().c_str());
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
            pid_t pid = fork();
            if(pid == -1){cout<<"pid fail"<<endl;}
            if(pid == 0)
            {

                execl("./b.sh","b.sh",(char *)0);
        //        send(fd,"ok",2,0);
                perror("execl error");
                //exit(0);
            }
            if(pid == 1)
            {
               // wait(NULL);
                cout<<"main over"<<endl;
            }
            send(fd,"ok",2,0);
        }
    }

}
