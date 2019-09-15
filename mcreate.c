#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

int main()
{
    pid_t pid = vfork();

    if(pid == 0)
    {
        printf("i am child ---- %d\n",getpid());
        exit(0);
    }
    else
    {
        printf("i am parent ----- %d\n",getpid());
    }
    while(1)
    {
        printf("-------%d\n",getpid()); 
        sleep(1);
    }
    return 0;
}
