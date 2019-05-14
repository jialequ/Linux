/*******************************************************************
描述 : 
  实现条件变量的基本使用
  吃面前提--有人做面
  如果没有现成的面, 等待老板做出来
  老板做出来面, 就要唤醒顾客

  老板不会做太多的面---老板只会提前做一碗面
  如果已经有面做出来, 但是没人吃, 不会再做(等待)
  顾客吃完面后, 老板再来一碗(唤醒老板的等待)
 *******************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>

int have_noodle = 1;
pthread_cond_t boss;
pthread_cond_t customer;
pthread_mutex_t mutex;

void *thr_boss()
{
  while(1)
  {
    pthread_mutex_lock(&mutex);
    //若面没有卖出去, 则等待
    while(have_noodle == 1)
    {
      //等待
      //int pthread_cond_timedwait(pthread_cond_t *restrict cond,
      //    pthread_mutex_t *restrict mutex,
      //    const struct timespec *restrict abstime);
      //  cond:   条件变量
      //  mutex:  互斥锁
      //  abstime:  限时等待时常
      //  限时进行等待, 超时后返回
      //
      //int pthread_cond_wait(pthread_cond_t *restrict cond,
      //    pthread_mutex_t *restrict mutex);
      //   死等
      //pthread_cond_wait 中集合了解锁后挂起的操作(原子操作)
      //有可能还没来得及挂起就已经有人唤醒---白唤醒---导致死等
      pthread_cond_wait(&boss, &mutex);
      //1. 解锁  ->  2. 休眠  ->  3. 被唤醒后加锁
    }
    //面被人卖了, 要再做一碗
    printf("ding niu la mian ~~~ +1\n");
    have_noodle+=1;
    //面做出来了---唤醒顾客
    //int pthread_cond_broadcast(pthread_cond_t *cond);
    //  广播唤醒:  唤醒所有等待的人
    //int pthread_cond_signal(pthread_cond_t *cond);
    //  唤醒至少一个等待的人
    pthread_cond_signal(&customer);
    pthread_mutex_unlock(&mutex);
  }
  return NULL;
}
void *thr_custom()
{
  while(1)
  {
    pthread_mutex_lock(&mutex);
    //若没有现成的面, 等老板做好
    while(have_noodle == 0)
    {
      //等待
      pthread_cond_wait(&customer, &mutex);
    }
    //有面了就可以吃面了
    printf("noodle delicious\n");
    have_noodle-=1;
    //吃完面因为太好吃, 唤醒老板, 再来一碗.
    pthread_mutex_unlock(&mutex);
    pthread_cond_signal(&boss);
  }
  return NULL;
}

int main()
{
  pthread_t tid1,tid2;
  int ret;
  //条件变量初始化
  //int pthread_cond_init(pthread_cond_t *restrict cond,
  //              const pthread_condattr_t *restrict attr);
  //  cond: 条件变量
  //  attr: 属性, 通常置NULL
  pthread_cond_init(&boss, NULL);
  pthread_cond_init(&customer, NULL);
  pthread_mutex_init(&mutex, NULL);
  int i = 0;
  for(i = 0;i < 2;i++)
  {
    ret = pthread_create(&tid1, NULL, thr_boss, NULL);
    if(ret != 0)
    {
       printf("boss error\n");
       return -1;
    }
  }
  for(i = 0;i < 2;i++)
  {
    ret = pthread_create(&tid2, NULL, thr_custom, NULL);
    if(ret != 0)
    {
      printf("custom error\n");
      return -1;
    }
  }
  pthread_join(tid1, NULL);
  pthread_join(tid2, NULL);
  //销毁条件变量
  pthread_cond_destroy(&boss);
  pthread_cond_destroy(&customer);
  pthread_mutex_destroy(&mutex);
  return 0;
}
