#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
  printf("!!僵尸进程!!\n");
	int pid = fork();
	if(pid == 0)
	{
		sleep(5);//五秒钟后退出子进程
		exit(0);
	}
  uint64_t a = 0;//8个字节(无符号长整型)
  while(1)
  {
    a++;
    usleep(1000);
  }
	return 0;
}
