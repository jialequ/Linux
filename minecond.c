/*****************************************************************
 *   Copyright (C) 2019 * Ltd. All rights reserved.
 *   
 *   File name   : minecond.c
 *   Author      : qujiale
 *   Created date: 2019-05-22
 *   Description : 实现条件变量的基本使用
 *     吃面----前提是有人做面 
 *     如果没有现成的面, 等待老板做出来
 *     老板做出来面, 就要唤醒顾客
 *
 *     老板不会做太多的面----只会提前做一碗面
 *     如果已经有面做出来, 但是没人吃, 不会再做(等待)
 *     顾客吃碗面后, 老板再来一碗 (唤醒老板的等待)
 *
 *     因为noodle是全局条件, 多个线程都会修改, 是一个临界资源, 要用锁进行保护
 *****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>

//定义一碗面
int noodle = 1;
//创建条件变量(与互斥锁搭配使用)
pthread_cond_t cond;
//创建一个互斥锁
pthread_mutex_t mutex;

//线程入口函数(老板)
void *boss()
{
  while(1)
  {
    //加锁
    pthread_mutex_lock(&mutex);
    if(noodle == 1)
    {
      //判断有没有面, 如果有一碗面, 陷入等待.条件变量等待
      pthread_cond_wait(&cond, &mutex);
    }
    //面被人买了, 再做一碗, 告诉顾客我生产了一碗面(唤醒顾客)
    printf("niu rou la mian------------+1\n");
    noodle += 1;
    pthread_cond_signal(&cond);
    //解锁
    pthread_mutex_unlock(&mutex);
  }
  return NULL;
}

//线程入口函数(顾客)
void *cus()
{
  while(1)
  {
    //加锁
    pthread_mutex_lock(&mutex);
    //若没有现成的面, 等老板做好
    if(noodle == 0)
    {
      pthread_cond_wait(&cond, &mutex);
    }
    //有面了就可以开心的吃了, 吃完了面就-1
    printf("noodle delicious-----\n");
    noodle -=1;
    //解锁
    pthread_mutex_unlock(&mutex);
    //吃碗面因为太好吃因此再来一碗(唤醒老板做面)
    pthread_cond_signal(&cond);
  }
  return NULL;
}
int main()
{
  pthread_t tid1, tid2;
  int ret;
  //条件变量初始化
  pthread_cond_init(&cond, NULL);
  //互斥锁初始化
  pthread_mutex_init(&mutex, NULL);
  //创建两个线程(判断)
  ret = pthread_create(&tid1, NULL, boss, (NULL);
  if(ret != 0)
  {
    printf("boss error!\n");
    return -1;
  }
  ret = pthread_create(&tid2, NULL, cus, NULL);
  if(ret != 0)
  {
    printf("cus error!\n");
    return -1;
  }
  //线程等待(并不关心返回值)
  pthread_join(tid1, NULL);
  pthread_join(tid2, NULL);
  //销毁条件变量
  pthread_cond_destroy(&cond);
  //销毁互斥锁
  pthread_mutex_destroy(&mutex);
  return 0;
}
