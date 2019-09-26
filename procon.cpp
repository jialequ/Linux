/*************************************************************************
*    > File Name    : procon.cpp
*    > Author       : qujiale
*    > Created Time : 2019年09月07日 星期六 23时06分48秒
*    > Description  : 使用vector模拟实现线程安全的环形队列, 信号量 
*************************************************************************/

#include <iostream>
#include <thread>
#include <vector>
#include <semaphore.h>
using namespace std;

#define MAXQ 10

class RingQueue
{
public:
    RingQueue(int maxq = MAXQ)
        :_queue(maxq)
        ,_capacity(maxq)
        ,_read(0)
        ,_write(0)
    {
        //初始化三个信号量, 给出对应的初始值
        sem_init(&_lock,0,1);
        sem_init(&_idle_space,0,maxq);
        sem_init(&_data_space,0,0);
    }
    ~RingQueue()
    {
        sem_destroy(&_lock);
        sem_destroy(&_idle_space);
        sem_destroy(&_data_space);
    }
    bool RingPush(int data)
    {
        //如果没有空暇空间, 陷入等待, 直到有了再加锁操作
        //不可以先加锁, 如果加锁了但是队列里面还没有空间了这个时候消费者也不能解锁, 会陷入死等:
        sem_wait(&_idle_space);
        sem_wait(&_lock);
        _queue[_write] = data;
        _write = (_write + 1) % _capacity;
        sem_post(&_lock);
        sem_post(&_data_space);
        return true;
    }
    bool RingPop(int &data)
    {
        sem_wait(&_data_space);
        sem_wait(&_lock);
        data = _queue[_read];
        _read = (_read + 1) % _capacity;
        sem_post(&_lock);
        sem_post(&_idle_space);
        return true;
    }

private:
    //环形队列
    vector<int> _queue;
    int _capacity;
    int _read;
    int _write;
    //线程安全
    sem_t _lock;
    sem_t _idle_space;
    sem_t _data_space;
};

void thr_pro(RingQueue *q)
{
    int data = 0;
    while(1)
    {
        q->RingPush(data);
        cout << "producer produced a data---------------" << data++ << endl;
    }
}
void thr_con(RingQueue *q)
{
    int data;
    while(1)
    {
        q->RingPop(data);
        cout << "consumer get a data" << data << endl;
    }
}

int main()
{
    vector<thread> list_pro(4);
    vector<thread> list_con(4);
    RingQueue q;
    for(int i = 0;i < 4;i++)
    {
        list_pro[i] = thread (thr_pro,&q);
    }
    for(int i = 0;i < 4;i++)
    {
        list_con[i] = thread (thr_con,&q);
    }
    for(int i = 0;i < 4;i++)
    {
        list_pro[i].join();
        list_con[i].join();
    }
    return 0;
}
