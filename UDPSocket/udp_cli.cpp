/**********************************************************************
 *    > File Name    : udp_cli.cpp
 *    > Author       : qujaile
 *    > Created Time : 2020年08月28日 星期五 11时17分09秒
 *    > Description  : UDP客户端 
 **********************************************************************/

#include <iostream>
#include <string>
#include <cstdio>
#include <stdlib.h>
#include <unistd.h>//系统调用close接口
#include <netinet/in.h>//地址接口定义接口
#include <arpa/inet.h>//字节序转换接口
#include <sys/socket.h>//套接字接口
using namespace std;

class UDPSocket
{
public:
    UDPSocket()
        :_sockfd(-1)
    {}
    bool Socket()
    {
        //1.创建套接字
        _sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
        if(_sockfd < 0)
        {
            cout << "socket error" << endl;
            return false;
        }
        return true;
    }
    bool Bind(const string& ip, uint16_t port)
    {
        //2.绑定地址信息
        struct sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_port = htons(port);
        addr.sin_addr.s_addr = inet_addr(ip.c_str());
        socklen_t len = sizeof(struct sockaddr_in);
        int ret = bind(_sockfd, (struct sockaddr*)&addr, len);
        if(ret < 0)
        {
            cout << "bind error" << endl;
            return false;
        }
        return true;
    }
    bool SendTo(const string& data, const string& ip, uint16_t port)
    {
        //3.发送数据
        //发送数据首先要知道对端的地址信息, 所以要先定义一下, 然后将传进来的ip, port设置进去
        struct sockaddr_in peeraddr;
        peeraddr.sin_family = AF_INET;
        peeraddr.sin_port = htons(port);
        peeraddr.sin_addr.s_addr = inet_addr(ip.c_str());
        socklen_t len = sizeof(struct sockaddr_in);
        int ret = sendto(_sockfd, data.c_str(), data.size(), 0, (struct sockaddr*)&peeraddr, len);
        if(ret < 0)
        {
            cout << "sendto error" << endl;
            return false;
        }
        return true;
    }
    bool RecvFrom(string* buf, string* ip = NULL, uint16_t* port = NULL)
    {
        //4.接收数据
        //接收数据不仅要接收数据, 还要接受对端的地址信息, 便于回复信息, 所以我们要获取对端的地址信息
        struct sockaddr_in peeraddr; //用于获取对端地址
        socklen_t len = sizeof(sockaddr_in);
        char tmp[4096] = {0};
        int ret = recvfrom(_sockfd, tmp, 4096, 0, (struct sockaddr*)&peeraddr, &len);
        if(ret < 0)
        {
            cout << "recv error" << endl;
            return false;
        }
        //assign : 给buf申请ret大小的空间, 从tmp中拷贝ret长度数据进去
        buf->assign(tmp, ret);
        if(ip != NULL)
        {
            //inet_ntoa : 将网络字节序整数IP地址转换为点分十进制字符串地址
            *ip = inet_ntoa(peeraddr.sin_addr); 
        }
        if(port != NULL)
        {
            //ntohs : 将网络字节序端口转换为本机字节序端口
            *port = ntohs(peeraddr.sin_port);
        }
        return true;
    }
    void Close()
    {
        close(_sockfd);
        _sockfd = -1;
        return ;
    }
private:
    int _sockfd;
};

#define CHECK_RET(q) if((q) == false){return -1;}

int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        cout << "em : ./udp_cli 192.168.60.129 9000" << endl;
        return -1;
    }
    string ip_addr = argv[1];
    uint16_t port_addr = atoi(argv[2]);

    UDPSocket sock;
    //1.创建套接字
    CHECK_RET(sock.Socket());
    //2.绑定地址信息
    //CHECK_RET(sock.Bind(ip_addr, port_addr));
    while(1)
    {
        //3.发送信息
        cout << "client say: ";
        fflush(stdout);
        string buf;
        cin >> buf;
        CHECK_RET(sock.SendTo(buf, ip_addr, port_addr));

        //4.接收数据
        buf.clear();
        CHECK_RET(sock.RecvFrom(&buf));
        cout << "server say: " << buf << endl;
    }
    sock.Close();
    return 0;
}
