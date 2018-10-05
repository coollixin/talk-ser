#include<iostream>
#include<json/json.h>
#include<string>
#include<string.h>
#include<arpa/inet.h>
#include<event.h>
#include<sys/socket.h>
#include<unistd.h>
#include<pthread.h>
using namespace std;
const char *IP = "127.0.0.1";
enum type
{
    TYPE_LOGIN = 0,
    TYPE_REGISTER = 1,
    TYPE_GETLIST = 2,
    TYPE_EXIT = 3,
    TYPE_TALK_ONE = 4,
    TYPE_GROUP = 5,
    TYPE_FIND = 6
};
unsigned int Port = 8000;
void login_success(int fd);
bool AllisNum(char* str)
{
        
    for (int i = 0; i < strlen(str)-1; i++)
    {
        int tmp = (int)str[i];
        if (tmp >= 48 && tmp <= 57)
        {
            continue;
        }
        else
        {
            return false;
        }
    }
    return true;
}
void run(int fd);
void* fun(void *arg)
{
    long c = (long )arg;
    while(1)
    {
        char buff[128] = {0};
        //char list[128] = {0};
        memset(buff,0,128);
        recv(c,buff,127,0);
        Json::Value val;
        Json::Reader read;

        if(read.parse(buff,val) == -1)
        {
            cout<<"json read fail"<<endl;
        }
        if(val["type"].asInt() == TYPE_GETLIST)
        {
           cout<<val["data"].asString()<<endl;
            continue;
            //close(c);
           // pthread_exit(NULL);
        }
         if(val["type"].asInt() == TYPE_EXIT)
        {
            close(c);
            pthread_exit(NULL);
            return 0;
        }
        if(val["type"].asInt() == TYPE_TALK_ONE)
        {
            cout<<"你有新的消息（name and message）："<<endl;
            cout<<"*******************************"<<endl;
            cout<<val["data"].asString()<<endl;
            cout<<"*******************************"<<endl;
        }
        if(val["type"].asInt() == TYPE_GROUP)
        {
            cout<<"群发消息"<<endl;
            cout<<"*******************************"<<endl;
            cout<<val["data"].asString()<<endl;
            cout<<"*******************************"<<endl;
        }
    }
}
void find_pw(int fd);
void Login(int fd);
void Register(int fd);
void exit(int fd)
{    char buff[128] = {0};
    int choice;
    cout<<"确定退出吗:1 yes  2 no"<<endl;
    cin>>choice;
    if(choice == 1)
    {
        Json::Value val;
        val["type"] = TYPE_EXIT;
	//将其发送给服务器
        if(-1== send(fd,val.toStyledString().c_str(),strlen(val.toStyledString().c_str()),0) )
        {
            cout<<"sli send fail"<<endl;
            return;
        }
    }
    else
    {
        return;
    }
}
void run(int fd)
{
    while(1)
    {
	cout<<"1.login 2.register  3.find password 4.exit"<<endl;

	int choice;
	cin>>choice;

	switch(choice)
	{
		case 1:
			{
				Login(fd);
			}break;
		case 2:
			{
				Register(fd);
			}break;
        case 3:
            {
                find_pw(fd);
            }break;
        case 4:
			{
				//exit(fd);
                cout<<">_<"<<endl;
                return;
			}break;

		default:
			{
				cout<<"cin error"<<endl;
			}
	}
    }
}
void Register(int fd)
{

    char send_buff[128] = {0};
	char name[20] = {0};
    char mail[20] = {0};
	cout<<"please cin name:"<<endl;
	cin>>name;

	char pw[20] = {0};
	cout<<"please cin password"<<endl;
	cin>>pw;
    while (strlen(pw) < 7 || AllisNum(pw))
    {
        cout<<"The password is too simple and not all numbres,please try again"<<endl;
         memset(pw, 0, 128);
         cin >> pw;
    }
    cout<<"input imail"<<endl;
    cin>>mail;
    Json::Value val;
	char buff[128]={0};
    val["type"] = TYPE_REGISTER;
    val["name"] = name;
    val["pw"] = pw;
    val["mail"] = mail;
	//将其发送给服务器
   if(-1== send(fd,val.toStyledString().c_str(),strlen(val.toStyledString().c_str()),0) )
    {
        cout<<"sli send fail"<<endl;
    }
    if(-1 == recv(fd,send_buff,127,0))
    {
        cout<< "sli recv fail"<<endl;
    }
    if(strncmp(send_buff,"ok",2) == 0)
    {
        cout<<"you have success Register "<<endl;
    }
    else
    {
        cout<<"Register fail"<<endl;
    }

}
void find_pw(int fd)
{
    char name[20] = {0};
    char mail[20] = {0};
    cout<<"please input name"<<endl;
    cin>>name;
    cout<<"please input mail"<<endl;
    cin>>mail;
    Json::Value val;
    val["type"] = TYPE_FIND;
    val["name"] = name;
    val["mail"] = mail;
    char send_buff[128] = {0};
    if(-1 == send(fd,val.toStyledString().c_str(),strlen(val.toStyledString().c_str()),0))
    {
        cout<<"json send fail"<<endl;
    }
    memset(send_buff,0,sizeof(send_buff));
    recv(fd,send_buff,127,0);
    if(strncmp(send_buff,"ok",2) == 0)
    {
        cout<<"you have success find_pw"<<endl;
        //接受服务器的回应
	
    
        //成功-》
		Login(fd);

    }
    else
    {
        cout<<"operator fail"<<endl;
    }
}
void Login(int fd)
{
    char send_buff[128] = {0};
	char name[20] = {0};
	cout<<"please cin name:"<<endl;
	cin>>name;
	char pw[20] = {0};
	cout<<"please cin password"<<endl;
	cin>>pw;
    Json::Value val;
    val["type"] = TYPE_LOGIN;
    val["name"] = name;
    val["pw"] = pw;
	//将其发送给服务器
    if(-1 == send(fd,val.toStyledString().c_str(),strlen(val.toStyledString().c_str()),0))
    {
        cout<<"json send fail"<<endl;
    }
    memset(send_buff,0,sizeof(send_buff));
    recv(fd,send_buff,127,0);
    if(strncmp(send_buff,"ok",2) == 0)
    {
        cout<<"you have success Login"<<endl;
        //接受服务器的回应
	
    
        //成功-》
		login_success(fd);

    }
    else
    {
        cout<<"Login in fail ,please check out name and password"<<endl;
        cout<<"是否选择找回密码：1.yes 2.no"<<endl;
        int choice;
        cin>>choice;
        if(choice == 1)
        {
            find_pw(fd);
        }

    }

		//失败-》return
}
void get_list(int fd)
{
    Json::Value val;
    val["type"] = TYPE_GETLIST;
    if(-1 == (send(fd,val.toStyledString().c_str(),strlen(val.toStyledString().c_str()),0)))
    {
        cout<<"getlist send fail"<<endl;
    }
    sleep(1);
}
void talk_one(int fd)
{
    get_list(fd);
    cout<<"talk_who"<<endl;
    char buff[10] = {0};
    cin>>buff;
    Json::Value val;
    val["type"] = TYPE_TALK_ONE;
    val["name"] = buff;
    cout<<"input:"<<endl;
    while(1)
    {
        char cuff[128] = {0};
        cin>>cuff;
        if(strncmp(cuff,"end",3) == 0)
        {
            break;
        }
        val["data"] = cuff;
        if(-1 == send(fd,val.toStyledString().c_str(),strlen(val.toStyledString().c_str()),0))
        {
            cout<<"send fail"<<endl;
        }
    }
    sleep(1);
}
void talk_group(int fd)
{
    get_list(fd);
    Json::Value val;
    val["type"] = TYPE_GROUP;
    cout<<"input:"<<endl;
    while(1)
    {
        char cuff[128] = {0};
        cin>>cuff;
        if(strncmp(cuff,"end",3) == 0)
        {
            break;
        }
        val["data"] = cuff;
        if(-1 == send(fd,val.toStyledString().c_str(),strlen(val.toStyledString().c_str()),0))
        {
            cout<<"send fail"<<endl;
        }
    }
    sleep(1);
}

void login_success(int fd)
{
    
    pthread_t id;
    pthread_create(&id,NULL,fun,(void*)fd);
	while(1){
    cout<<"1.get list"<<endl;
	cout<<"2.talk one"<<endl;
	cout<<"3.talk group"<<endl;
	cout<<"4.exit"<<endl;
	int choice;
	cin>>choice;
	switch(choice)
	{
        case 1:
        {
            cout<<"The function  is get list"<<endl;
            get_list(fd);
        }break;
        case 2:
        {
            cout<<"The function is talk one to one"<<endl;
            talk_one(fd);
        }break;
        case 3:
        {
            cout<<"The function is  talk group"<<endl;
            talk_group(fd);
        }break;
        case 4:
        {
            exit(fd);
            return;
        }break;
        default :
        {
            break;
        }
	}
   }
    
}

