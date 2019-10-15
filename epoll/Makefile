all:tcp_epoll tcp_cli 
tcp_epoll:tcp_epoll.cpp
	g++ -std=c++11 $^ -o $@
tcp_cli:tcp_cli.cpp
	g++ $^ -o $@
