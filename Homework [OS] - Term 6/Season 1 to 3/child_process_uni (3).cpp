#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
    pid_t a;
    a=fork();
    if(a>0)
        fork();
    printf("Hello\n");
    return 0;
}
