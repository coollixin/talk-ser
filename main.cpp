#include<iostream>
#include"contral.h"
#include<stdlib.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
using namespace std;

contral Contral;
void run(int fd);
int create_sockfd(const char* ip,int port)
{
    int fd = socket(AF_INET,SOCK_STREAM,0);
    if(-1 == fd)
    {
        cout<<"fd fail"<<endl;
    }
    struct sockaddr_in caddr;
    caddr.sin_family = AF_INET;
    caddr.sin_port = htons(port);
    caddr.sin_addr.s_addr = inet_addr(ip);
    if(-1 == bind(fd,(struct sockaddr*)&caddr,sizeof(caddr)))
    {
        cout<<"bind fail"<<endl;
    }
    if(-1 == listen(fd,5))
    {
        cout<<"listen fail"<<endl;
    }
    return fd;
    
}
int main(int argc,char *argv[])
{	
    const char* ip = "127.0.0.1";
    int  port = 8000;
    int fd  = create_sockfd(ip,port);
	run(fd);

	return 0;
}
