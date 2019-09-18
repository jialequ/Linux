/**********************************************************************
 *    > File Name    : tcp_srv.cpp
 *    > Author       : qujiale
 *    > Created Time : 2019年09月18日 星期三 08时53分14秒
 *    > Description  : 基于TCP协议的服务端多线程版本 
 **********************************************************************/
#include <pthread.h>
#include "tcpsocket.hpp"

void* thr_start(void* arg)
{
    TcpSocket *newsock = (TcpSocket*)arg;
    while(1)
    {
        //5.接收数据
        string buf;
        bool ret = newsock->Recv(buf);
        if(ret == false)
        {
            newsock->Close();
            return NULL;
        }
        cout << "client say: " << buf << endl;
        //6.发送数据
        buf.clear();
        cin >> buf;
        newsock->Send(buf);
    }
    //完成之后关闭套接字, 释放资源
    newsock->Close();
    delete newsock;
    return NULL;
}

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
    while(1)
    {
        //4.获取新建连接
        //如果将这个newsock放在外面而且没有*的话, 会造成多个线程操作一块空间, 造成覆盖
        //如果放进来的话, 这个时候当while循环进行完毕的时候会进行析构, 也不行, 不能析构, 要一直通信
        //所以我们给*newsock, 每次都新创建一块空间来存放这个新的newsock, 这样每个人都操作自己的, 不会影响别人
        TcpSocket *newsock = new TcpSocket(); 
        bool ret = lit_sock.Accept(*newsock);
        if(ret == false)
        {
            delete newsock;
            continue;
        }
        pthread_t tid;
        pthread_create(&tid, NULL, thr_start, (void*)newsock);
        pthread_detach(tid);
    }
    //7.关闭套接字
    lit_sock.Close();
    return 0;
}
