#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
    pid_t pid;
    pid=fork();
    if(pid<0)
    {
        printf("fork failed.\n");
        return 1;
    }
    else if(pid==0)
    {
        for(int i=0;i<100;i++)
            printf("000000000\n");
    }
    else
    {
        for(int i=0;i<100;i++)
            printf("xxxxxxxxx\n");
    }
    return 0;
}
