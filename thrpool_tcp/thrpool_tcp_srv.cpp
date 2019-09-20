/*************************************************************************
*    > File Name    : thr_pool.cpp
*    > Author       : qujiale
*    > Created Time : 2019年09月08日 星期日 10时32分55秒
*    > Description  : 线程池 + tcp通信服务端
*               任务类:
*                   class MyTask{}
*               线程池类:
*                   class ThreadPool{}
*
*    客户端请求连接:
*
*       连接数<5 : 可以连接上
*           如果任务队列没有满:
*               如果有空闲线程:
*                   添加到任务队列, 线程调用, 通信
*               如果没有空闲线程
*                   在任务队列中等待, 如果有任务退出, 添加到任务队列,重复上面的
*           如果任务队列满了:
*               等待任务队列的处理, 有空位置了就添加
*
*       连接数>5 : 不能连接上, 处于一个阻塞的状态, 如果有别的客户端退出再连接
*************************************************************************/
#include "tcpsocket.hpp"
#include <iostream>
#include <queue>
#include <pthread.h>
#include <vector>
#include <stdlib.h>
#include <thread>
#include <time.h>
#include <unistd.h>
#include <sstream>
using namespace std;

//线程数量
#define MAX_THREAD 10
//队列的大小
#define MAX_QUEUE 10
//类型替换  void 函数指针
typedef void (*handler_t)(TcpSocket*);

class MyTask
{
    //封装数据和方法
    //初始化
    //设置
    //运行
public:
    MyTask(TcpSocket* arg, handler_t handle)
        :_arg(arg)
        ,_handle(handle)
    {}
    void SetTask(TcpSocket* arg,handler_t handle)
    {
        _arg = arg;
        _handle = handle;
        return;
    }
    void Run()
    {
        return _handle(_arg);
    }
private:
    TcpSocket* _arg;
    handler_t _handle;
};

class ThreadPool
{
private:
    //队列
    queue<MyTask> _queue;
    //容量
    int _capacity;
    //锁
    pthread_mutex_t _mutex;
    //两个条件变量
    pthread_cond_t _cond_pro;
    pthread_cond_t _cond_con;
    //线程退出标记
    bool _quit_flag;
    //线程的最大数量
    int _thr_max; 
    //线程退出时,判断当前线程数量,防止单次唤醒有遗漏
    int _thr_cur;
    //存放线程
    vector<thread> _list_thr;
private:
    void thr_start()
    {
        //线程入口函数
        //先加锁,然后判断是否有任务
        //    如果有任务: 执行任务
        //          从任务队列中获取一个任务进行处理
        //    没有任务 : 判断是否要退出
        //          是 : 先解锁再退出, 避免程序卡死
        //        不是 : 等待
        while(1)
        {
            pthread_mutex_lock(&_mutex);
            while(_queue.empty())
            {
                if(_quit_flag == true)
                {
                    cout << "thread" << pthread_self() << "exit" << endl;
                    pthread_mutex_unlock(&_mutex);
                    _thr_cur--;
                    return ;
                }
                pthread_cond_wait(&_cond_con,&_mutex);
            }
            MyTask mt = _queue.front();
            _queue.pop();
            pthread_mutex_unlock(&_mutex);
            pthread_cond_signal(&_cond_pro);
            mt.Run();
        }
        //线程安全的出队
        //任务处理应该放在解锁之后,否则同一时间只有一个线程在处理任务
    }

public:
    ThreadPool(int maxq = MAX_QUEUE,int maxt = MAX_THREAD)
        :_capacity(maxq)
        ,_quit_flag(false)
        ,_thr_max(maxt)
        ,_list_thr(maxt)
    {
        //构造函数,初始化线程池
        //初始化互斥锁和条件变量
        pthread_mutex_init(&_mutex,NULL); 
        pthread_cond_init(&_cond_pro,NULL); 
        pthread_cond_init(&_cond_con,NULL); 
    }
    ~ThreadPool()
    {
        //析构函数,销毁互斥锁和条件变量
        pthread_mutex_destroy(&_mutex);
        pthread_cond_destroy(&_cond_pro);
        pthread_cond_destroy(&_cond_con);
    }
    bool PoolInit()
    {
        _thr_cur = 0;
        //创建线程
        //当前线程数量++
        //并不关心线程的返回值, 创建完成之后线程分离;
        for(int i = 0;i < _thr_max;i++)
        {
            _list_thr[i] = thread(&ThreadPool::thr_start,this);
            _thr_cur++;
            _list_thr[i].detach();
        }
        return true;
    }
    bool AddTask(MyTask &mt)
    {
        //线程安全的任务入队
        pthread_mutex_lock(&_mutex);
        while((int)_queue.size() == _capacity)
        {
            pthread_cond_wait(&_cond_pro,&_mutex); 
        }
        _queue.push(mt);
        pthread_mutex_unlock(&_mutex);
        pthread_cond_signal(&_cond_con);
        return true;
    }
    bool PoolStop()
    {
        //处理完数据之后线程池停止
        pthread_mutex_lock(&_mutex);
        _quit_flag = true;
        pthread_mutex_unlock(&_mutex);
        //如果线程数量 >0, 一直唤醒, 避免唤醒时一些线程在执行或者还没有陷入睡眠, 这个时候会白唤醒
        while(_thr_cur > 0)
        {
            pthread_cond_broadcast(&_cond_con);
            usleep(1000);
        }
        return true;
    }
};

void Handler(TcpSocket* arg)
{
    TcpSocket *newsock = arg;
    while(1)
    {
        //5.接收数据
        string buf;
        bool ret = newsock->Recv(buf);
        if(ret == false)
        {
            newsock->Close();
            return ;
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
    return;
}

int main(int argc,char *argv[])
{
    if(argc != 3)
    {
        cout << "./thrpool_tcp_srv 192.168.60.129 9000" << endl;
        return -1;
    }
    TcpSocket lit_sock;
    string ip = argv[1];
    int i = 0;
    uint16_t port = atoi(argv[2]);
    //1.创建套接字
    CHECK_RET(lit_sock.Socket());
    //2.绑定地址信息
    CHECK_RET(lit_sock.Bind(ip, port));
    //3.开始监听
    CHECK_RET(lit_sock.Listen());
    ThreadPool pool;
    pool.PoolInit();
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
        if(i++ < MAX_QUEUE)
        {
            MyTask mt(newsock, Handler);
            pool.AddTask(mt);
        }
    }
    //7.关闭套接字
    lit_sock.Close();
    pool.PoolStop();
    return 0;
}
