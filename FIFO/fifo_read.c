/**********************************************************************
 *    > File Name    : fifo.c
 *    > Author       : qujiale
 *    > Created Time : 2019年10月08日 星期二 12时26分14秒
 *    > Description  : 命名管道的基本使用
 *          命名管道可见于文件系统, 会创建一个管道文件(文件只是名字)
 *          管道通信的本质还是内核中的缓冲区
 *          int mkfifo(const char *pathname, mode_t mode);
 *              pathname:   管道文件的路径名
 *              mode    :   创建文件的权限
 *          返回值: 0   失败: -1
 **********************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
int main()
{
    const char* file = "./tmp.fifo";
    umask(0);
    int ret = mkfifo(file, 0664);
    if(ret < 0)
    {
        //如果文件不是因为已经存在而报错, 则退出
        if(errno != EEXIST)
        {
            perror("mkfifo error");
            return -1;
        }
    }
    printf("create fifo success!!\n");
    int fd = open(file, O_RDONLY);
    if(fd < 0)
    {
        perror("open error");
        return -1;
    }
    printf("open fifo success!!\n");
    while(1)
    {
        char buf[1024] = {0};
        int ret = read(fd, buf, 1023);
        if(ret < 0)
        {
            perror("read error");
            return -1;
        }
        else if(ret == 0)
        {
            printf("write close\n");
            return -1;
        }
        printf("buf:[%s]\n", buf);
    }
    close(fd);
    return 0;
}
