/**********************************************************************
 *    > File Name    : csdn.c
 *    > Author       : qujiale
 *    > Created Time : 2019年09月16日 星期一 10时37分18秒
 *    > Description  : 标准库IO接口的使用 
 **********************************************************************/

#include <stdio.h>
#include <string.h>

int main()
{
    FILE *fp = fopen("./csdn.txt","w+");
    if(fp == NULL)
    {
        perror("fopen error");
        return -1;
    }
     char buf[1024] = "my name is qujiale";
    fwrite(buf,strlen(buf),1,fp);
    fseek(fp,0,SEEK_SET);
    memset(buf,0x00,1024); 
    fread(buf,1024,1,fp);
    printf("buf:%s\n",buf);
    return 0;
}
