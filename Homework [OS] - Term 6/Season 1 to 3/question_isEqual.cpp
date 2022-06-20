#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
    for(int i=0;i<5;i++)
        fork();
    printf("Hello\n");
    return 0;
}

////////////////////////

#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
    fork();
    fork();
    fork();
    fork();
    fork();
    printf("Hello\n");
    return 0;
}