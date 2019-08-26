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

#include <string>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h> 

