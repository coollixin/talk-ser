/*************************************************************************
	> File Name: pthread.hmZ
	> Mail:mZmZ	> Created Time: 2018年07月18日 星期三 14时46分18秒
 ************************************************************************/

#ifndef _PTHREAD_H
#define _PTHREAD_H
class mpthread
{
public:
    mpthread(int sock1);
    ~mpthread();
private:
    map<int ,struct event* base> _event_map;
    struct event *base _base;
    int _sock1;
}Mpthread,*Mpthread;
#endif
