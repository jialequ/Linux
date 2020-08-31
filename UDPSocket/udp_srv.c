/**********************************************************************
 *    > File Name    : udp_srv.c
 *    > Author       : qujaile
 *    > Created Time : 2020年08月28日 星期五 11时17分02秒
 *    > Description  : UDP服务端
 **********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main(int argc, char* argv[])
{
    //判断输入合法性
    if(argc != 3)
    {
        printf("./udp_srv 192.168.60.129 9000\n");
        return -1;
    }
    const char* ip_addr = argv[1];
    uint16_t port = atoi(argv[2]);
    //1.创建套接字
    int sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if(sockfd < 0)
    {
        perror("socket error");
        return -1;
    }
    //2.绑定地址信息
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(ip_addr);
    socklen_t len = sizeof(struct sockaddr_in);
    int ret = bind(sockfd, (struct sockaddr*)&addr, len);
    if(ret < 0)
    {
        perror("bind error");
        return -1;
    }
    while(1)
    {
        //3.接收数据
        char buf[1024] = {0};
        struct sockaddr_in cli_addr;
        socklen_t cli_len = sizeof(cli_addr);
        ret = recvfrom(sockfd, buf, 1023, 0, (struct sockaddr*)&cli_addr, &cli_len);
        if(ret < 0)
        {
            perror("recv error");
            return -1;
        }
        printf("client say: %s\n", buf);
        
        //4.发送数据
        printf("server say: ");
        fflush(stdout);
        memset(buf, 0x00, 1024);
        scanf("%s", buf);
        ret = sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr*)&cli_addr, cli_len);
        if(ret < 0)
        {
            perror("sendto error");
            return -1;
        }
    }
    //5.关闭套接字
    close(sockfd);
    return 0;
}
