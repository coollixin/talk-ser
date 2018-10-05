#include<iostream>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<event.h>
#include<stdlib.h>
#include"contral.h"
#include<assert.h>
#include<unistd.h>
using namespace std;
extern contral Contral;
int fd[2];
void listen_cb(int fd, short event,void *arg);
void cli_cb(int fd,short event,void *arg);
void run(int listen_fd)
{
	//liten_fd  ->监听  -》listen_cb
    struct event_base *lib_base = event_base_new();
    struct event* listen_event = event_new(lib_base,listen_fd,EV_READ | EV_PERSIST,listen_cb,lib_base);
    if(NULL == listen_event)
    {
        cout<<"event listen fail"<<endl;
        return ;
    }
    event_add(listen_event,NULL);
    event_base_dispatch(lib_base);
}

void listen_cb(int fd,short event,void *arg)
{
	struct event_base *lib_base = (struct event_base*)arg;
    struct sockaddr_in caddr;
    socklen_t len = sizeof(caddr);
    int cli_fd = accept(fd,(struct sockaddr*)&caddr,&len);
    if(cli_fd == -1)
    {
        cout<<"cli_fd accept fail"<<endl;
        return ;
    }
    else
    {
        cout<<"accept sucess"<<endl;
    }
        struct event* cli_event = event_new(lib_base,cli_fd,EV_READ |EV_PERSIST ,cli_cb,lib_base);
        if(NULL == cli_event)
        {
            cout<<"cli event create fail"<<endl;
            return;
        }
        event_add(cli_event,NULL);
    
	//cli_fd  -》监听  -》cli_cb
}
void cli_cb(int fd, short event,void* arg)
{
    struct event_base* lib_base = (struct event_base*)arg;
    char buff[128] = {0};
    //cout<<"recv 1"<<endl;
    if(0 < recv(fd,buff,127,0))
    {
        cout<<"sucess recv"<<buff<<endl;
        Contral.process(buff,fd);
    }


//	buff->contral;	Contral.process(buff,fd)
}


	
