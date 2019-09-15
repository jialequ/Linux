#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>

int main()
{
  int pid = fork();
  if(pid < 0)
  {
    perror("fork error");
    exit(-1);
  }
  else if(pid == 0)
  {
    sleep(5);
    exit(0);
  }

  int statu;
  int ret; 
  while((ret = waitpid(pid,&statu,WNOHANG)) == 0)
  {
    printf("打麻将\n");
    sleep(1);
  }
  printf("%d--%d\n",ret,pid);
  while(1)
  {
    printf("--------------------\n");
    sleep(1);
  }
  return 0;
}
