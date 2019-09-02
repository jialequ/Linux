/*****************************************************************
 *   Copyright (C) 2019 * Ltd. All rights reserved.
 *   
 *   File name   : mbar.c
 *   Author      : qujiale
 *   Created date: 2019-08-29
 *   Description : 
 *
 *****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#include <stdio.h>
#include<unistd.h>
int main()
{
  int i=0;
  char bar[11]="\0";
  const char *lable="|/-\\";
  for(;i <= 10;i++)
  {
    printf("\033[1m\033[45;33m[%-10s][%d%%][%c]\033[0m\r",bar,i * 10,lable[i%4]);
    bar[i]='#';
    fflush(stdout);
    usleep(20000);
  }
  printf("\n");
  return 0;
}
