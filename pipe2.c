/**********************************************************************
 *    > File Name    : Grep.c
 *    > Author       : qujiale
 *    > Created Time : 2019年10月08日 星期二 11时20分04秒
 *    > Description  : 管道符的实现 
 **********************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>

int main()
{
    int fd[2];
    int ret = pipe(fd);
    if(ret < 0)
    {
        perror("pipe error");
        return -1;
    }
    int pid1 = fork();
    if(pid1 == 0)    
    {
        //child1
        //不用读端, 关闭
        close(fd[0]);
        dup2(fd[1], 1);
        execlp("ps","ps","-ef",NULL);
        exit(0);
    }
    int pid2 = fork();
    if(pid2 == 0)
    {
        //child2
        //不用写端, 关闭
        close(fd[1]);
        dup2(fd[0], 0);
        execlp("grep","grep","pipe",NULL);
        exit(0);
    }
    close(fd[0]);
    close(fd[1]);
    waitpid(pid1, NULL, 0);
    printf("child1 exit---\n");
    waitpid(pid2, NULL, 0);
    printf("child2 exit---\n");
    return 0;
}

