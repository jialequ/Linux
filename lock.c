/*********************************************************************
  实现互斥锁的基本实用以及线程安全的基本认识
  
  黄牛抢票-----100张票/共有4个黄牛在抢
  
**********************************************************************/ 
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

int ticket = 100;
///互斥锁变量不一定非要全局变量--只要保证要互斥的线程都能访问到就行
pthread_mutex_t mutex;
void *thr_start(void *arg)
{
  while(1)
  {
    //加锁要在临界资源访问之前
    //int pthread_mutex_lock(pthread_mutex_t *mutex);
    // 阻塞加锁:  加不上锁就阻塞
    //int pthread_mutex_trylock(pthread_mutex_t *mutex);
    // 非阻塞加锁:  加不上锁就直接报错返回
    // pthread_mutex_timedlock  限时的阻塞加锁
    pthread_mutex_lock(&mutex);
    if(ticket > 0)
    {
      printf("yellow bull --%d--get a ticket:%d\n",(int)arg,ticket);
      usleep(1000);
      ticket--;
    }
    else
    {
      //加锁之后需要在线程任意有可能退出的地方解锁
      pthread_mutex_unlock(&mutex);
      pthread_exit(NULL);
    }
    pthread_mutex_unlock(&mutex);
  }
  return NULL;
}

int main()
{
  pthread_t tid[4];
  int i = 0,ret;
  
  //初始化互斥锁
  //int pthread_mutex_init(pthread_mutex_t *restrict mutex,const pthread_mutexattr_t *restrict attr);
  //  mutex:    互斥锁变量
  //  attr:     属性,通常置NULL
  pthread_mutex_init(&mutex,NULL);
  for(;i < 4; i++)
  {
    ret = pthread_create(&tid[i], NULL, thr_start, (void*)i);
    if(ret != 0)
    {
      printf("yellow bull no exist!!\n");
      return -1;
    }
  }
  for(i = 0;i < 4; i++)
  {
    pthread_join(tid[i], NULL);
  }

  //int pthread_mutex_destroy(pthread_mutex_t *mutex);
  //mutex:    互斥锁变量
  pthread_mutex_destroy(&mutex);

  return 0;
}
