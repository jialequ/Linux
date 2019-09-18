all:tcp_cli thread_tcp_srv
thread_tcp_srv:thread_tcp_srv.cpp
	g++ $^ -o $@ -lpthread
th_tcp_srv_tech:th_tcp_srv_tech.cpp
	g++ $^ -o $@ -lpthread
process_tcp_srv:process_tcp_srv.cpp
	g++ $^ -o $@
tcp_srv:tcp_srv.cpp
	g++ $^ -o $@
tcp_cli:tcp_cli.cpp
	g++ $^ -o $@
