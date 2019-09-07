/*************************************************************************
*    > File Name    : pro_con.cpp
*    > Author       : qujiale
*    > Created Time : 2019年09月07日 星期六 17时54分29秒
*    > Description  : 使用信号量实现生产者与消费者模型 
*************************************************************************/

#include <iostream>
#include <thread>
#include <vector>
#include <semaphore.h>
using namespace std;

#define MAXQ 5 

class RingQueue
{
public:
    RingQueue(int maxq = MAXQ)
        :_capacity(maxq)
         ,_queue(maxq)
         ,_step_read(0)
         ,_step_write(0)
    {
        sem_init(&_lock, 0, 1);
        sem_init(&_idle_space, 0, maxq);
        sem_init(&_data_space, 0, 0);
    }
    ~RingQueue()
    {
        sem_destroy(&_lock);
        sem_destroy(&_data_space);
        sem_destroy(&_idle_space);
    }
    bool QueuePush(int data)
    {
        //不需显式判断队列是否满了, sem_wait本身就有一个计数, 如果满了会阻塞
        sem_wait(&_idle_space);
        sem_wait(&_lock);
        _queue[_step_write] = data;
        _step_write = (_step_write + 1) % _capacity;
        sem_post(&_lock);
        sem_post(&_data_space);
        return true;
    }
    bool QueuePop(int &data)
    {
        sem_wait(&_data_space);
        sem_post(&_lock);
        data = _queue[_step_read];
        _step_read = (_step_read + 1) % _capacity;
        sem_post(&_lock);
        sem_post(&_idle_space);
        return true; 
    }
private:
    //环形队列
    vector<int> _queue;
    int _capacity;
    int _step_read;
    int _step_write;
    //线程安全
    sem_t _lock;
    sem_t _idle_space;
    sem_t _data_space;
};

void* thr_producer(RingQueue *q)
{
    int data = 0;
    while(1)
    {
        q->QueuePush(data);
        cout << "put  data----------" << data++ << endl;
    }
}
void* thr_consumer(RingQueue *q)
{
    int data = 0;
    while(1)
    {
        q->QueuePop(data);
        cout << "pop  data" << endl;
    }
}

int main()
{
    RingQueue q;
    vector<thread> list_con(4);
    vector<thread> list_pro(4);
    for(int i = 0;i < 4;i++)
    {
        list_pro[i] = thread (thr_producer, &q);
    }
    for(int i = 0;i < 4;i++)
    {
        list_con[i] = thread (thr_consumer, &q);
    }
    for(int i = 0;i < 4;i++)
    {
        list_con[i].join();
        list_pro[i].join();
    }
    return 0;
}
