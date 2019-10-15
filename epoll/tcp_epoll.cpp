/**********************************************************************
 *    > File Name    : tcp_epoll.cpp
 *    > Author       : qujiale
 *    > Created Time : 2019年10月15日 星期二 17时21分26秒
 *    > Description  : 基于epoll多路转接IO实现的TCP服务器 
 **********************************************************************/

#include <iostream>
#include <string>
#include <vector>
#include <sys/epoll.h>
#include "tcpsocket.hpp"
using namespace std;

#define MAX_EPOLL 1024
class Epoll 
{
    public:
        Epoll()
            :_epfd(-1)
        {}
        ~Epoll()
        {}
    public:
        bool Init()
        {
            //创建一个eventpoll结构, 包括红黑树和链表
            _epfd = epoll_create(MAX_EPOLL);
            if(_epfd < 0)
            {
                cerr << "epoll_create error" << endl;
                return false;
            }
            return true;
        }

        bool Add(TcpSocket& sock)
        {
            //向创建的eventpoll结构中的红黑树中添加节点epoll_event
            int fd = sock.GetFd();
            epoll_event ev;
            ev.events = EPOLL_CTL_ADD;
            ev.data.fd = fd;
            int ret = epoll_ctl(_epfd, EPOLL_CTL_ADD, fd, &ev); 
            if(ret < 0)
            {
                cerr << "add error" << endl;
                return false;
            }
            return true;
        }
        bool Del(TcpSocket& sock)
        {
            int fd = sock.GetFd();
            int ret = epoll_ctl(_epfd, EPOLL_CTL_DEL, fd, NULL);
            if(ret < 0)
            {
                cerr << "delete error" << endl;
                return false;
            }
            return true;
        }
        bool Wait(vector<TcpSocket>& list, int timeout = 3000)
        {
            epoll_event events[MAX_EPOLL];
            int nfds = epoll_wait(_epfd, events, MAX_EPOLL, timeout);
            if(nfds < 0)
            {
                cerr << "wait error" << endl;
                return false;
            }
            else if(nfds == 0)
            {
                cout << "wait timeout" << endl;
                return false;
            }
            for(int i = 0;i < nfds;i++)
            {
                int fd = events[i].data.fd;
                TcpSocket sock;
                sock.SetFd(fd);
                list.push_back(sock);
            }
            return true;
        }
    private:
        int _epfd;
};

int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        cout << "./tcp_epoll 192.168.60.129 9000" << endl;
        return -1;
    }
    string ip = argv[1];
    uint16_t port = atoi(argv[2]);
    TcpSocket lst_sock;
    CHECK_RET(lst_sock.Socket());
    CHECK_RET(lst_sock.Bind(ip, port));
    CHECK_RET(lst_sock.Listen());
    
    Epoll e;
    e.Init();
    e.Add(lst_sock);

    while(1)
    {
        vector<TcpSocket> list;
        bool ret = e.Wait(list);
        if(ret == false)
        {
            continue;
        }
        for(auto sock : list)
        {
            if(lst_sock.GetFd() == sock.GetFd())
            {
                TcpSocket newsock;
                bool ret = lst_sock.Accept(newsock);
                if(ret == false)
                {
                    continue;
                }
                CHECK_RET(e.Add(newsock));
            }
            else 
            {
                string buf;
                bool ret = sock.Recv(buf);
                if(ret == false)
                {
                    sock.Close();
                    continue;
                }
                cout << "client say: " << buf << endl;
                buf.clear();
                cin >> buf;
                sock.Send(buf);
            }
        }
    }
    lst_sock.Close();
    return 0;
}
