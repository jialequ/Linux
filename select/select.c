/**********************************************************************
 *    > File Name    : select.c
 *    > Author       : qujiale
 *    > Created Time : 2019年10月02日 星期三 12时10分05秒
 *    > Description  : 演示select的基本使用, 对标准输入进行监控, 就绪之后进行操作
 *      int select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout);
 *          对大量的描述符进行监控: 默认阻塞
 *          参数:
 *              nfds: 最大的描述符+1
 *           readfds: 可读事件集合
 *          writefds: 可写事件集合
 *         exceotfds: 异常事件集合
 *           timeout: NULL表示永久阻塞, 直到有描述符就绪
 *              timeout.tv_sec: 限时阻塞
 *                           0: 非阻塞
 *          返回值: 
 *              >0 : 表示就绪的描述符个数
 *             ==0 : 没有描述符就绪, 等待超时
 *              <0 : 监控出错
 **********************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>
#include <sys/select.h>

int main()
{
    fd_set set;
    FD_ZERO(&set);  //清空集合
    FD_SET(0,&set); //将标准输入添加监控
    int max_fd = 0;
    while(1)
    {
        struct timeval tv;
        tv.tv_sec = 3;
        tv.tv_usec = 0;
        FD_SET(0,&set); //每次都要重新添加所有描述符
        int nfds = select(max_fd + 1, &set, NULL, NULL, &tv);
        if(nfds < 0)
        {
            printf("select error\n");
            return -1;
        }
        else if(nfds == 0)
        {
            printf("wait timeout\n");
            continue;
        }
        printf("input----------\n");
        //select返回的是就绪集合
        for(int i = 0;i <= max_fd;i++)
        {
            char buf[1024] = {0};
            int ret = read(i, buf, 1023);
            if(ret < 0)
            {
                perror("read error");
                return -1;
            }
            printf("get buf:[%s]\n", buf);
        }
    }
    return 0;
}
