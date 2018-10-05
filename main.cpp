/*************************************************************************
	> File Name: main.cpp
	> Author: 
	> Mail: 
	> Created Time: 2018年07月15日 星期日 23时58分03秒
 ************************************************************************/

#include<iostream>
#include<sys/socket.h>
#include<arpa/inet.h>
using namespace std;
void run(int fd);
int main()
{
    int fd = socket(AF_INET,SOCK_STREAM,0);
    if(fd == -1)
    {
        cout<<"socket fd  fail"<<endl;
    }
    struct sockaddr_in caddr;
    caddr.sin_family = AF_INET;
    caddr.sin_port = htons(8000);
    caddr.sin_addr.s_addr = inet_addr("127.0.0.1");
   
    if(-1 == connect(fd,(struct sockaddr*)&caddr,sizeof(caddr)))
    {
        cout<<"connect fail"<<endl;
    }
    run(fd);
    return 0;
}
