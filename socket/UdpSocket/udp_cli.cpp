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
  //这个地址是服务端地址, 为了让客户端知道数据发送到哪里
  std::string ip = argv[1];
  uint16_t port = atoi(argv[2]);

  UdpSocket sock;
  CHECK_RET(sock.Socket());
  //客户端并不推荐手动绑定地址
  //CHECK_RET(sock.Bind(ip, port));
  struct sockaddr_in srv_addr;
  srv_addr.sin_family = AF_INET;
  srv_addr.sin_port = htons(port);
  srv_addr.sin_addr.s_addr = inet_addr(ip.c_str());
  while(1)
  {
    std::string buf;
    fflush(stdout);
    std::cout << "client say:";
    std::cin >> buf;
    CHECK_RET(sock.Send(buf, &srv_addr));

    CHECK_RET(sock.Recv(buf, &srv_addr));
    std::cout << "server say:" << buf << std::endl;;
  }
  sock.Close();
}

