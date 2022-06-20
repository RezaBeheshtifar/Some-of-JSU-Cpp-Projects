#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
    int i;
    pid_t a;

    printf("MAIN: a=%i\n",a);
    printf("MAIN: i=%i\n",i);
    i=5;
    printf("MAIN: i=%i\n",i);
    a=fork();
    if(a==0)
    {
        printf("FORK: a=%i\n",a);
        printf("FORK: i=%i\n",i);
    }
    if(a>0)
    {
        i++;
        printf("PARENT: a=%i\n",a);
        printf("PARENT: i=%i\n",i);
    }

    return 0;
}
