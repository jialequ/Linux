/**********************************************************************
 *    > File Name    : syscsdn.c
 *    > Author       : qujiale
 *    > Created Time : 2019年09月16日 星期一 11时49分42秒
 *    > Description  :  
 **********************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>

int main()
{
    umask(0);
    int fd = open("./syscsdn.txt", O_RDWR | O_CREAT, 0664);
    if(fd < 0)
    {
        perror("open error");
    }
    char buf[1024] = "my name is qujiale";
    int ret = write(fd, buf, strlen(buf));
    if(ret < 0)
    {
        perror("write error");
    }
    lseek(fd, 0, SEEK_SET);
    memset(buf, 0x00, sizeof(buf));
    ret = read(fd, buf, 1024);
    if(ret < 0)
    {
        perror("read error");
    }
    printf("buf:%s\n",buf);
    return 0;
}
