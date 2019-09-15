#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main()
{
    printf("i am parent ---- %d\n",getpid());
    pid_t pid = fork();
    if(pid < 0)
    {
        perror("fork error");
    }
    else if(pid == 0)
    {
        sleep(3);
        printf("i am child ---- %d\n",getpid());
        exit(0);
    }

    wait(NULL);
    while(1)
    {
        printf("i am ----%d\n",getpid());
        sleep(1);
    }
    return 0;
}
