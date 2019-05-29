/*******************************************************************
 线程的创建 : 
  int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
                            void *(*start_routine) (void *), void *arg);
      thread : 输出型参数, 用于获取新创建的线程ID
      attr : 线程属性, 通常置空
      start_routine : 线程入口函数, 传入函数地址 
      arg : 传递给线程的参数,
      返回值:0    失败: 非0---error
 *******************************************************************/
#include <stdio.h>
#include <error.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

void* thr_start(void *arg)
{
  //线程终止
  //sleep(3);
  //pthread_exit(NULL);
  //打印此线程
  while(1)
  {
    printf("i am new thread----------%s\n",(char*)arg);
    sleep(1);
  }
  return NULL;
}

int main()
{
  //1.定义一个参数,tid,获取新线程的ID
  pthread_t tid;
  //2.创建线程并且判断是否创建成功
  int ret = pthread_create(&tid, NULL, thr_start, (void*)"love you");
  if(ret != 0)
  {
    printf("create error");
    return -1;
  }
  sleep(5);
  pthread_cancel(tid);//睡眠5秒钟后取消指定线程
  
  //3.打印一下主线程(睡一秒)
  
  while(1)
  {
    printf("i am thread----------%p\n",tid);
    sleep(1);
  }
  return 0;
}
