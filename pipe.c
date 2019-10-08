/**********************************************************************
 *    > File Name    : pipe.c
 *    > Author       : qujiale
 *    > Created Time : 2019年10月08日 星期二 08时39分11秒
 *    > Description  : 匿名管道的基本使用
 *      int pipe(int pipefd[2]);
 *          pipefd: 输出型参数---用于获取管道操作句柄
 *              pipefd[0]: 管道的读取端
 *              pipefd[1]: 管道的写入端
 *          返回值: 0   失败: -1
 **********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main()
{
    //创建管道
    int pipefd[2];
    int ret = pipe(pipefd);
    if(ret < 0)
    {
        perror("pipe error");
        return -1;
    }
    //使用匿名管道实现子进程与父进程之间的通信
    //父进程写, 子进程读
    int pid = fork();
    if(pid < 0)
    {
        return -1;
    }
    else if (pid == 0)
    {
        //child
        close(pipefd[1]);
        char buf[1024] = {0};
        ret = read(pipefd[0], buf, 1023);
        if(ret < 0)
        {
            perror("read error");
        }
        else
        {
            printf("buf:[%s]\n", buf);
        }
    }
    else
    {
        //parent
        close(pipefd[1]);
        sleep(1000);
        int i = 0;
        while(1)
        {
            const char* ptr = "Acesses";
            i += write(pipefd[1], ptr, strlen(ptr));
            printf("ret:%d\n", i);
        }
    }
    return 0;
}

