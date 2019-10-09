/**********************************************************************
 *    > File Name    : tcp_select.cpp
 *    > Author       : qujiale
 *    > Created Time : 2019年10月02日 星期三 13时58分36秒
 *    > Description  : 基于select实现一个并发TCP服务器
 *      对select进行封装, 封装一个类实例化一个对象
 **********************************************************************/
#include "tcpsocket.hpp"
#include <iostream>
#include <vector>
using namespace std;

class Select
{
    public:
        Select()
            :_max_fd(-1)
        {
            FD_ZERO(&_set);
        }
        ~Select()
        {}
    public:
        bool Add(TcpSocket &sock)
        {
            int fd = sock.GetFd();
            if(FD_ISSET(fd, &_set))
            {
                //如果在里面就是已经添加过了
                cerr << "The file descriptor is already" << endl;;
                return true;
            }
            FD_SET(fd, &_set);
            _max_fd = _max_fd > fd ? _max_fd : fd;
            return true;
        }
        bool Delete(TcpSocket &sock)
        {
            int fd = sock.GetFd();
            FD_CLR(fd, &_set);
            for(int i = _max_fd; i >= 0; i--)
            {
                if(FD_ISSET(i, &_set))
                {
                    _max_fd = i;
                    return true;
                }
            }
            _max_fd = -1;
            return true;
        }
        bool Wait(vector<TcpSocket> &list, int sec = 3)
        {
            struct timeval tv;
            tv.tv_sec = sec;
            tv.tv_usec = 0;
            //每次定义新的集合进行监控, 避免对象的监控集合被修改
            fd_set tmp_set = _set;
            int count;
            count = select(_max_fd + 1, &tmp_set, NULL, NULL, &tv);
            if(count < 0)
            {
                cout << "select error" << endl;
                perror("select error");
                return false;
            }
            else if(count == 0)
            {
                cout << "wait timeout" << endl;
                return false;
            }
            for(int i = 0; i <= _max_fd; i++)
            {
                if(FD_ISSET(i, &tmp_set))
                {
                    TcpSocket sock;
                    sock.SetFd(i);
                    list.push_back(sock);
                }
            }
            return true;
        }
    private:
        fd_set _set;
        int _max_fd;
};
