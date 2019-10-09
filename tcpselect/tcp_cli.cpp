/**********************************************************************
 *    > File Name    : tcp_cli.cpp
 *    > Author       : qujiale
 *    > Created Time : 2019年09月18日 星期三 09时23分12秒
 *    > Description  : 基于TCP协议的客户端程序 
 **********************************************************************/

#include "tcpsocket.hpp"

int main(int argc, char *argv[])
{
    if(argc != 3)
    {
        cout << "./tcp_cli srv_ip srv_port" << endl;
        return -1;
    }
    TcpSocket sock;
    string srv_ip = argv[1];
    uint16_t srv_port = atoi(argv[2]);
    //1.创建套接字
    CHECK_RET(sock.Socket());
    //2.绑定地址信息(通常不需要自己绑定)
    //3.发起链接请求
    CHECK_RET(sock.Connect(srv_ip, srv_port));
    while(1)
    {
        //4.发送数据
        string buf;
        cin >> buf;
        bool ret = sock.Send(buf);
        if(ret == false)
        {
            sock.Close();
            return -1;
        }
        //5.接收数据
        buf.clear();
        ret = sock.Recv(buf);
        if(ret == false)
        {
            sock.Close();
            return -1;
        }
        cout << "srv say: " << buf <<  endl;
    }
    //6.关闭套接字
    sock.Close();
    return 0;
}
