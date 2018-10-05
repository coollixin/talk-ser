#!/bin/bash
g++ -o main main.cpp contral.cpp reactor.cpp Register_view.cpp login_view.cpp Getlist_view.cpp Exit_view.cpp Talk_one_view.cpp  Talk_group_view.cpp
Find_view.cpp -L /usr/lib/lib -levent -ljson  -lmysqlclient

