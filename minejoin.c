/*****************************************************************
*   Copyright (C) 2019 * Ltd. All rights reserved.
*   
*   File name   : minejoin.c
*   Author      : qujiale
*   Created date: 2019-05-15
*   Description : 线程等待与线程分离的认识
*   int pthread_join(pthread_t thread, void **retval);
*     thread:   指定的线程ID
*     retval:   用于获取线程的退出返回值
*     返回值 : 0    失败: !0 - error
*     功能 : 等待线程退出, 获取返回值, 回收线程资源
*     前提 : 这个被等待的线程必须处于joinable状态
*
*****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>

//线程入口函数(简单打印),退出: 返回一个字符串"nihao"
void *thr_start()
{
  pthread_exit("nihao");
  while(1)
  {
    printf("i am child thread\n");
    sleep(1);
  }
  return NULL;
}
int main()
{
  //1.定义一个tid
  pthread_t tid; 
  //2.线程创建,并判断
  int ret = pthread_create(&tid,NULL,thr_start,NULL);
  if(ret != 0)
  {
    printf("thread create error\n");
    return -1;
  }
  //线程分离
  pthread_detach(tid);
  //线程等待,返回值是一个void**,定义char * 然后取地址
  char *retval = NULL; 
  int err = pthread_join(tid,(void**)&retval);
  if(err = EINVAL)
  {
    printf("thread can not be wait\n");
  }
  printf("retval:%s\n",retval);
  //3.打印一条信息
  while(1)
  {
    printf("i am thread\n");
    sleep(1);
  }
  return 0;
}
