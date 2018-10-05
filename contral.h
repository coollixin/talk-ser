#ifndef _CONTRAL_H
#define _CONTRAL_H
#include<iostream>
#include<map>
#include"view.h"
using namespace std;
class contral
{
private:
	map<int ,view*> _model;//继承和多态

public:
	contral();
	~contral();
	void process(char *buff,int fd);
};
#endif
