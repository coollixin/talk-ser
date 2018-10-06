#include<iostream>
#include"view.h"
using namespace std;
class Login_view:public view
{
public:
    virtual	void process(Json::Value val,int fd);
};
