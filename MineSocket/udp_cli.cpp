/**********************************************************************
 *    > File Name    : udp_cli.cpp
 *    > Author       : qujiale
 *    > Created Time : 2019年09月18日 星期三 00时08分14秒
 *    > Description  : 基于UDP协议的客户端程序 
 **********************************************************************/

#include "udpsocket.hpp"

int main(int argc, char *argv[])
{
    if(argc != 3)
    {
        cout << "./udp_cli ServerIP ServerPort" << endl;
        return -1;
    }
    UdpSocket clisock;
    string srv_ip = argv[1];
    uint16_t srv_port = atoi(argv[2]);
    //1.创建套接字
    CHECK_RET(clisock.Socket());
    //2.绑定地址信息
    //不推荐手动绑定, 使用时系统自已会分配一个合适的IP地址和port
    //CHECK_RET(clisock.Bind(srv_ip,8000));
    while(1)
    {
        //3.发送数据
        string buf;
        cin >> buf;
        CHECK_RET(clisock.Send(buf,srv_ip, srv_port));
        buf.clear();
        CHECK_RET(clisock.Recv(buf, srv_ip, srv_port));
        cout << "srv say : " << buf << endl;
    }
    CHECK_RET(clisock.Close());
    return 0;
}
