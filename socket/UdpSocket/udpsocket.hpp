/*****************************************************************
*   Copyright (C) 2019 * Ltd. All rights reserved.
*   
*   File name   : udpsocket.hpp
*   Author      : qujiale
*   Created date: 2019-05-17
*   Description : 实现udpsocket类封装udp常用操作 
*
*****************************************************************/

#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

class UdpSocket
{
  public:
    UdpSocket():_sock(-1){}
    ~UdpSocket(){}
    //创建套接字
    bool Socket()
    {
      _sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
      if(_sock < 0)
      {
        perror("socket error");
        return false;
      }
      return true;
    }
    //为套接字绑定地址,声明IP 和 port
    bool Bind(std::string &ip, uint16_t port)
    {
      //创建地址信息, IPV4类型
      struct sockaddr_in addr;
      //地址域
      addr.sin_family = AF_INET;
      //端口
      addr.sin_port = htons(port);
      //inet_addr : 把一个IPV4的点分十进制的字符串IP地址转换成网络主机地址(大端)
      //地址
      addr.sin_addr.s_addr = inet_addr(ip.c_str());
      socklen_t len = sizeof(struct sockaddr_in);
      //绑定
      int ret = bind(_sock, (struct sockaddr*)&addr, len);
      if(ret < 0)
      {
        perror("bind error\n");
        return false;
      }
      return true;
    }
    //接收数据,udp整条接收,不用关心数据长度
    bool Recv(std::string &buf, struct sockaddr_in *saddr)
    {
      char tmp[1500] = {0};
      socklen_t len = sizeof(struct sockaddr_in);
      int ret = recvfrom(_sock, tmp, 1500, 0, (struct sockaddr *)saddr, &len);
      if(ret < 0)
      {
        perror("recvfrom error\n");
        return false;
      }
      buf.assign(tmp, ret);
      return true;
    }
    //发送信息
    bool Send(std::string &buf,struct sockaddr_in *daddr)
    {
      socklen_t len = sizeof(struct sockaddr_in);
      int ret = sendto(_sock, buf.c_str(), buf.size(), 0, (struct sockaddr *)daddr, len);
      if(ret < 0)
      {
        perror("sendto error\n");
        return false;
      }
      return true;
    }
    //关闭套接字
    void Close()
    {
      close(_sock);
      _sock = -1;
    }
  private:
    int _sock;
};

