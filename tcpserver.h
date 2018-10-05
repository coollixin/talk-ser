/*************************************************************************
	> File Name: tcpserver.h
	> Author: 
	> Mail: 
	> Created Time: 2018年08月03日 星期五 09时33分22秒
 ************************************************************************/

#ifndef _TCPSERVER_H
#define _TCPSERVER_H
#include<iostream>
using namespace std;
class tcpserver
{
public:
    tcpserver(char *ip,unsigned short port,int pth_num);
    ~tcpserver();
    void run();
    void create_socket_pair();
    void create_pth();
private:
    struct event_base* _base;
    vector<int[2]> _sockpair_base;
    int _listen_fd;
    map<int,int> _pth_num_map;
};Tcpserver,*Ptcpserver;
#endif
