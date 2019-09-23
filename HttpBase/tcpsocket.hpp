/*****************************************************************
*   Copyright (C) 2019 * Ltd. All rights reserved.
*   
*   File name   : tcpsocket.hpp
*   Author      : qujiale
*   Created date: 2019-05-22
*   Description : 在这里属于用c++封装tcpsocket类
*     创建套接字
*       bool Socket()
*     绑定地址信息
*       bool Bind(std::string &ip, uint16_t port)
*     服务端开始监听
*       bool Listen(int baklog = 5)
*     客户端发起链接请求
*       bool Connect(std::string &ip, uint16_t port)
*     服务端获取已经链接完成的客户端新建的socket
*       bool Accept(TcpSocket clisock, struct sockaddr_in *addr)
*
*     接收数据
*       bool 非常危险
*       bool Recv(std::string &buf)
*     发送数据
*       bool Send(std::string &buf)
*     关闭套接字
*       bool Close()
*****************************************************************/
#include <iostream>
#include <string>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h> 
using namespace std;

#define CHECK_RET(q) if((q) == false){return -1;}

class TcpSocket
{
    public:
        TcpSocket()
            :_sockfd(-1)
        {}
        ~TcpSocket()
        {
            Close();
        }
        bool Socket()
        {
            _sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
            if(_sockfd < 0)
            {
                cerr << "socket error" << endl;
                return false;
            }
            return true;
        }
        bool Bind(const string &ip, uint16_t port)
        {
            sockaddr_in addr;
            addr.sin_family = AF_INET;
            addr.sin_port = htons(port);
            addr.sin_addr.s_addr = inet_addr(ip.c_str());
            socklen_t len = sizeof(addr);
            int ret = bind(_sockfd, (sockaddr*)&addr, len);
            if(ret < 0)
            {
                cerr << "bind error" << endl;
                return false;
            }
            return true;
        }
        bool Listen(int Backlog = 5)
        {
            int ret = listen(_sockfd, Backlog);
            if(ret < 0)
            {
                cerr << "listen error" << endl;
                return false;
            }
            return true;
        }
        bool Connect(string &ip, uint16_t port)
        {
            sockaddr_in srv_addr;
            srv_addr.sin_family = AF_INET;
            srv_addr.sin_addr.s_addr = inet_addr(&ip[0]);
            srv_addr.sin_port = htons(port);
            socklen_t len = sizeof(srv_addr);
            int ret = connect(_sockfd, (sockaddr*)&srv_addr, len);
            if(ret < 0)
            {
                cerr << "connect error" << endl;
                return false;
            }
            return true;
        }
        bool Accept(TcpSocket &newsock)
        {
            sockaddr_in addr;
            socklen_t len = sizeof(addr);
            int fd = accept(_sockfd, (sockaddr*)&addr, &len);
            if(fd < 0)
            {
                cerr << "accept error" << endl;
                return false;
            }
            newsock._sockfd = fd;
            return true;
        }
        bool Send(string &buf)
        {
            int ret = send(_sockfd, &buf[0], buf.size(), 0);
            if(ret < 0)
            {
                cerr << "send error" << endl;
                return false;
            }
            return true;
        }
        bool Recv(string &buf)
        {
            char tmp[4096] = {0};
            int ret = recv(_sockfd, tmp, 4095, 0);
            if(ret < 0)
            {
                cerr << "recv error" << endl;
                return false;
            }
            else if(ret == 0)
            {
                cerr << "connect over" << endl;
                return false;
            }
            buf.assign(tmp, ret);
            return true;
        }
        bool Close()
        {
            if(_sockfd > 0)
            {
                close(_sockfd);
                _sockfd = -1;
            }
            return true;
        }
    private:
        int _sockfd;
};
