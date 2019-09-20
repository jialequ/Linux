all:tcp_cli thrpool_tcp_srv
tcp_cli:tcp_cli.cpp 
	g++ -std=c++11 $^ -o $@ -lpthread
thrpool_tcp_srv:thrpool_tcp_srv.cpp 
	g++ -std=c++11 $^ -o $@ -lpthread
