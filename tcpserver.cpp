/*************************************************************************
	> File Name: tcpserver.cpp
	> Author: 
	> Mail: 
	> Created Time: 2018年08月03日 星期五 15时07分13秒
 ************************************************************************/
#include<stdlib.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>
#include<json/json.h>
#include<pthread.h>
#include<sys/socket.h>
#include<string.h>
#include<string>
#include<iostream>
#include"contral.h"
#include"tcpserver.h"
#include<map>
using namespace std;
pthread_t id;
extern contral Contral;
struct event_base *base;
void *fun(void *arg)
{
    int readpipe = (int)arg;
    base = event_base_new();
    if(base == NULL){cout<<"child phtread libevent init fail"<<endl;}
    struct event *pipe_event = event_new(base,readpipe,
                                        EV_READ | EV_PERSIST,cli_cd,arg);
    event_add(pipe_read_event,NULL);
    event_base_dispatch(base;)
}
tcpserver::tcpserver(char *ip,unsigned short port,int pth_num)
{
    int  _listen_fd = socket(AF_INET,SOCK_STREAM,0);
    if(_listen_fd == -1) { cout<<"fd fail"<<endl;}
    struct sockaddr_in caddr;
    caddr.sin_family = AF_INET;
    caddr.sin_port = htons(port);
    caddr.sin_addr_s.addr = inet_addr(ip);
    if(-1 == bind(_listen_fd,(struct sockaddr *)&caddr,sizeof(caddr))
    {
        cout<<"bind fail"<<endl;       
    }
    if(-1 == listen(_listen_fd,5))
    {
        cout<<"listen fail"<<endl;
    }
    _base = event_base_new();
    if(_base == NULL){cout<<"libevent init fail"<<endl;}
    if(-1 == pipe(_pipe)){cout<<"create pipe failure"<<endl;}
        
}
void cli_cd(int fd,short event,void *arg)
{
    int buff[128] = {0};
    int arg = (int)arg;
    int size = 0;
    if(arg == fd)
    {
        int clifd = 0;
        struct event *client_event = event_new(base,clifd,
                                               EV_READ |EV_PERSIST,cli_cd,arg);
        _pth_num_map.insert(make_pair(clifd,event_event));
        event_add(client_event,NULL);

    }
    else
    {
        size = recv(fd,buff,1024,0);
        cout<<"buff:"<<buff<<endl;
        if(size <= 0)
        {
            event_free(_pth_num_map[fd]);
            _pth_num_map.erase(fd);
            close(fd);
            cout<<"one client shutdown"<<endl;
            Contral.process("client_close_exception",fd);
            return;
        }
        Json::Reader read;
        Json::Value val;
        if(read.parse(buff,root))
        {
            if(val["type"].asInt == TYPE_EXIT)
            {
                event_free(_pth_num_map[fd]);
                _pth_num_map.erase(fd);
            }
        }
        Contral.process(buff,fd);
    }
}
void listen_cd(int fd, short event, void *arg)
{
    _base = (struct event_base*)arg;
    struct sockaddr_in caddr;
    socklen_t len = sizeof(caddr);
     int listenfd = accept(fd,(struct sockaddr*)&caddr,&len);
    if(listenfd == -1){cout<<"listenfd error"<<endl;}
    else{cout<<"accept sucess"<<endl;}
   char buff[1024] = {0};
    sprintf(buff,"%d",listenfd);
    write(_base->_pipe[1],(void *)&listenfd,sizeof(int));
}
void tcpserver::run()
{
    //监听listen_fd ->listen_cd 
    _base = event_base_new();
   struct event* listen_event = event_new(_base,_listen_fd,EV_READ | EV_PERSIST,listen_cd,_base);
    if(listen_event == NULL){cout<<"event listen error"}
    event_add(listen_event,NULL);
    event_base_dispatch(_base);
}
tcpserver::~tcpserver()
{
    close(_listen_fd);
    event_base_free(_base);    
}

