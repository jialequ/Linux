/**********************************************************************
 *    > File Name    : tcp_srv.cpp
 *    > Author       : qujiale
 *    > Created Time : 2019年09月18日 星期三 08时53分14秒
 *    > Description  : 基于TCP协议的服务端程序 
 **********************************************************************/

#include "tcpsocket.hpp"
#include "tcp_select.hpp"
#include <vector>
int main(int argc,char *argv[])
{
    if(argc != 3)
    {
        cout << "./tcp_srv 192.168.60.129 9000" << endl;
        return -1;
    }
    TcpSocket lit_sock;
    string ip = argv[1];
    uint16_t port = atoi(argv[2]);
    //1.创建套接字
    CHECK_RET(lit_sock.Socket());
    //2.绑定地址信息
    CHECK_RET(lit_sock.Bind(ip, port));
    //3.开始监听
    CHECK_RET(lit_sock.Listen());

    Select s;
    s.Add(lit_sock);
    
    while(1)
    {
        vector<TcpSocket> list;
        bool ret = s.Wait(list);
        if(ret == false)
        {
            continue;
        }
        for(auto sock : list)
        {
            if(sock.GetFd() == lit_sock.GetFd())
            {
                //4.获取新建连接
                //监听套接字
                TcpSocket newsock; 
                ret = lit_sock.Accept(newsock);
                if(ret == false)
                {
                    continue;
                }
                s.Add(newsock);
            }
            else 
            {
                //5.接收数据
                string buf;
                ret = sock.Recv(buf);
                if(ret == false)
                {
                    s.Delete(sock);
                    sock.Close();
                    continue;
                }
                cout << "client say: " << buf << endl;
                //6.发送数据
                buf.clear();
                cout << "server say: ";
                fflush(stdout);
                cin >> buf;
                sock.Send(buf);
            }
        }
    }
    //7.关闭套接字
    lit_sock.Close();
    return 0;
}
