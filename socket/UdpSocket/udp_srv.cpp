/*****************************************************************
*   Copyright (C) 2019 * Ltd. All rights reserved.
*   
*   File name   : udp_srv.cpp
*   Author      : qujiale
*   Created date: 2019-05-17
*   Description : 通过UdpSocket实现udp服务端程序 
*
*****************************************************************/

#include "udpsocket.hpp"
#define CHECK_RET(q) if((q) == false){return -1;}
int main(int argc, char *argv[])
{
  if(argc != 3)
  {
    printf("./udp_srv ip port\n");
    return -1;
  }

  std::string ip = argv[1];
  uint16_t port = atoi(argv[2]);
  //创建一个sock类
  UdpSocket sock;
  //创建套接字
  CHECK_RET(sock.Socket());
  //绑定地址
  CHECK_RET(sock.Bind(ip, port));
  while(1)
  {
    std::string buf;
    //客户端地址信息
    struct sockaddr_in cli_addr;
    //服务端先接收客户端信息
    CHECK_RET(sock.Recv(buf, &cli_addr));
    std::cout << "client say:" << buf << std::endl;
    std::cout << "server say:";
    fflush(stdout);
    std::cin >> buf;
    //响应信息到客户端
    CHECK_RET(sock.Send(buf, &cli_addr));
  }
  sock.Close();
}

