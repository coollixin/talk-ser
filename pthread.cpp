/*************************************************************************
	> File Name: pthread.cpp
	> Author: 
	> Mail: 
	> Created Time: 2018年07月18日 星期三 14时59分17秒
 ************************************************************************/

#include<iostream>
#include"pthread.h"
using namespace std;
pthread::pthread(int sock1)
{

    _sock1 = sock1;
    _event_map[sock1,_base];
    //启动子线程
}
pthread::~pthread()
{}

