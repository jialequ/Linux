//shell
//1.等待用户输入
//2.解析输入数据
//3.创建子进程(程序替换(execlp(ls,ls,-l,NULL)))
//4.等待子进程退出
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <fcntl.h>
char *argv[32];
char buf[1024] = {0};
int argc = 0;
int redirect_flag = 0;
char *redirect_file = NULL;

int do_face()
{
  //等待标准输入
  printf("[qujiale@]$");
  fflush(stdout);
  //%[^\n] 获取字符串,直到遇到\n
  //%*c 将一个字符从缓冲区取出
  if(scanf("%[^\n]%*c",buf) != 1)
  {
    getchar();
    return -1;
  }
  return 0;
}
int do_parse()
{
  argc = 0;
  //解析输入的数据
  char *ptr = buf;
  while(*ptr != '\0')
  {
    if(!isspace(*ptr))
    {
      //当前位置是非空白字符
      argv[argc++] = ptr;
      while(!isspace(*ptr) && *ptr != '\0')
      {
        ptr++;
      }
    }
    *ptr = '\0'; //解析了一个字符串
    ptr++;//开始进行下一个
  }
  argv[argc] = NULL;
  return 0;
}
int build_in()
{

  //判断命令是否是内建命令
  if(strcmp(argv[0],"cd") == 0)
  {
    //int chdir(const char *path)
    //改变当前工作路径
    chdir(argv[1]);
    return -1;
  }
  return 0;
}
int do_redirect()
{
  //ls -l   >>  tmp.txt
  redirect_flag = 0;
  redirect_file =NULL;
  char *ptr = buf;
  while(*ptr != '\0')
  {
    if(*ptr == '>')
    {
      redirect_flag = 1;
      *ptr = '\0';
      ptr++;
      if(*ptr == '>')
      {
        redirect_flag = 2;
        *ptr = '\0';
        ptr++;
      }
      while(*ptr != '\0' && isspace(*ptr))
      {
        ptr++;
      }
      redirect_file = ptr;
      while(*ptr != '\0' && !isspace(*ptr))
      {
        ptr++;
      }
      *ptr = '\0';
    }
    ptr++;
  }
  printf("redirect_file:%s redirect_flag:%d\n", redirect_file, redirect_flag);
  return 0;
}
int main()
{
  int ret = 0;
  while(1)
  {
    ret = do_face();
    if(ret < 0)
    {
      continue;
    }
    ret = do_redirect();
    if(ret < 0)
    {
      continue;
    }
    ret = do_parse();
    if(ret < 0)
    {
      continue;
    }
    ret = build_in();
    if(ret < 0)
    {
      continue;
    }

    //创建子进程---执行任务
    int pid = fork();
    if(pid < 0)
    {
      continue;
    }
    else if(pid == 0)
    {
      //子进程---执行其他任务---程序替换
      int fd = 1;
      if(redirect_flag == 1)
      {
        //清空重定向
        fd = open(redirect_file,O_WRONLY | O_CREAT | O_TRUNC ,0664);
        if(fd < 0)
        {
          exit(-1);
        }
      }
      else if(redirect_flag == 2)
      {
        //追加重定向
        fd = open(redirect_file,O_WRONLY | O_CREAT | O_APPEND ,0664);
        if(fd < 0)
        {
          exit(-1);
        }
      }
      dup2(fd,1);
      if(execvp(argv[0],argv) < 0)
      {
        perror("");
      }
      //替换失败就退出
      exit(0);
      //等待子进程退出,避免僵尸进程
    }
    wait(); 
  }   
  return 0;
}
