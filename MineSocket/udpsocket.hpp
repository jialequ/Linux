/*******************************************************
 *  封装一个udpscoket类
 *  实现客户端和服务端的通信
 *  1. 创建套接字
 *  2. 绑定地址信息
 *  3. 发送数据
 *  4. 接收数据
 *  5. 关闭套接字
 ******************************************************/
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
using namespace std;

#define CHECK_RET(q) if((q) == false){return -1;}

class UdpSocket
{
    public:
        UdpSocket()
            :_socketfd(-1)
        {
        }
        ~UdpSocket()
        {
            Close();
        }
        bool Socket()
        {
            _socketfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
            if(_socketfd < 0)
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
            int ret = bind(_socketfd, (sockaddr*)&addr, len);
            if(ret < 0)
            {
                cerr << "bind error" << endl;
                return false;
            }
            return true;
        }
        bool Recv(string &buf,string &ip, uint16_t &port)
        {
            char tmp[4096];
            sockaddr_in peeraddr;
            socklen_t len = sizeof(peeraddr);
            int ret = recvfrom(_socketfd, tmp, 4095, 0, (sockaddr*)&peeraddr, &len);
            if(ret < 0)
            {
                cerr << "recv error" << endl;
                return false;
            }
            buf.assign(tmp, ret);
            ip = inet_ntoa(peeraddr.sin_addr);
            port = ntohs(peeraddr.sin_port);
            return true;
        }
        bool Send(string &data, string &ip,uint16_t port)
        {
            sockaddr_in addr;
            addr.sin_family = AF_INET;
            addr.sin_port = htons(port);
            addr.sin_addr.s_addr = inet_addr(ip.c_str());
            socklen_t len = sizeof(addr);
            int ret = sendto(_socketfd, &data[0], data.size(), 0, (sockaddr*)&addr, len);
            if(ret < 0)
            {
                cerr << "recv" << endl;
                return false;
            }
            return true;
        }
        bool Close()
        {
            if(_socketfd > 0)
            {
                close(_socketfd);
                _socketfd = -1;
            }
            return true;
        }
    private:
        int _socketfd;
};
