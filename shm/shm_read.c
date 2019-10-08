/**********************************************************************
 *    > File Name    : shm.c
 *    > Author       : qujiale
 *    > Created Time : 2019年10月08日 星期二 16时13分03秒
 *    > Description  : 共享内存的基本操作
 *          1. 创建
 *          2. 建立映射
 *          3. 内存操作
 *          4. 解除映射
 *          5. 删除
 **********************************************************************/

#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/shm.h>
#define IPC_KEY 0x12345678

int main()
{
    //1.创建
    //int shmget(key_t key, size_t size, int shmflg);
    //参数:
    //    key   : 共享内存标识符
    //      可以使用define宏定义, 也可以使用ftok函数进行生成, 但是一般推荐使用define更好一点
    //    size  : 共享内存大小
    //    shmflg: 选项标志
    //      IPC_CREAT    共享内存不存在则创建, 存在则打开
    //      IPC_EXCL     与IPC_CREAT同用, 共享内存存在则报错
    //      shm_mode     权限
    //返回值: 
    //    标识符(代码中的操作句柄)    失败:-1
    int shmid = shmget(IPC_KEY, 32, IPC_CREAT | 0664); 
    if(shmid < 0)
    {
        perror("shmget error");
        return -1;
    }
    //2.建立映射
    //void *shmat(int shmid, const void *shmaddr, int shmflg);
    //参数
    //    shmid  : 标识符
    //    shmaddr: 置空-映射首地址由操作系统分配
    //    shmflg : 映射成功后的操作权限
    //      SHM_RDONLY  只读              
    //      0           默认-可读可写
    //返回值：
    //    映射首地址    失败返回:-1
    char* shm_start = shmat(shmid, NULL, 0);
    if(shm_start == (void*)-1)
    {
        perror("shmat error");
        return -1;
    }
    //3.操作
    int i = 0;
    while(1)
    {
        printf("%s", shm_start);
        sleep(1);
    }
    //4.解除映射
    //int shmdt(const void *shmaddr);
    //  shmaddr:     映射首地址
    shmdt(shm_start);
    //5.删除共享内存
    //int shmctl(int shmid, int cmd, struct shmid_ds *buf);
    //      shmid:   操作句柄
    //      cmd  :   操作类型
    //          IPC_RMID    删除共享内存
    //      buf  :   设置/获取共享内存信息
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}
