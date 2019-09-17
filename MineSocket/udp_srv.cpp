/**********************************************************************
 *    > File Name    : udp_srv.cpp
 *    > Author       : qujiale
 *    > Created Time : 2019年09月17日 星期二 23时14分38秒
 *    > Description  : 实现传输层基于UDP协议的服务端程序 
 **********************************************************************/

#include "udpsocket.hpp"

int main(int argc, char *argv[])
{
    if(argc != 3)
    {
        cout << "./udp_srv 192.168.60.129 9000" << endl;
        return -1;
    }
    UdpSocket sock;
    string cli_ip = argv[1];
    uint16_t cli_port = atoi(argv[2]);
    //1.创建套接字
    CHECK_RET(sock.Socket());
    //2.绑定地址信息
    CHECK_RET(sock.Bind("192.168.60.129",9000));
    while(1)
    {
        //3.接收数据
        string buf;
        CHECK_RET(sock.Recv(buf, cli_ip, cli_port));
        cout << "cli say : " << buf << endl;
        //4.发送数据
        buf.clear();
        cin >> buf;
        CHECK_RET(sock.Send(buf, cli_ip, cli_port));    
    }
    //5.关闭套接字
    sock.Close();
}
