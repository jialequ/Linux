#include <stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

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
        exit(255);
    }
    //pid_t wait(&status);
    //  status : 用于获取退出原因
    //int status;
    //wait(&status);
    
    //pid_t waitpid(pid_t pid, int *status, int options);
    //  pid : 指定进程的pid
    //  status : 获取退出原因
    //  opt : 0 || WNOHANG 用于设定非阻塞
    int statu;
    int ret;
    while((ret = waitpid(pid,&statu,WNOHANG)) == 0)
    {
        printf("打麻将\n");
        sleep(1);
    }

    //正常退出 
    if(WIFEXITED(statu))
    {
        printf("%d---%d-----child exit code:%d\n",ret,pid,WEXITSTATUS(statu)); 
    }
    if(WIFSIGNALED(statu))
    {
        printf("exit signal:%d\n",WTERMSIG(statu));
    }
    while(1)
    {
        printf("--leihoua---\n");
        sleep(1);
    }
    return 0;
}
