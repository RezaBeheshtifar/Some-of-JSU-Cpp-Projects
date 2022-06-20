#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
    pid_t a,b=10;
    a=fork();
    if(a>0)
        b=fork();
    if(b>0)
        fork();
    printf("Hello\n");
    return 0;
}
