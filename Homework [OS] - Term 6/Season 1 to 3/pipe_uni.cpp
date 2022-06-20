#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define READ_END 0
#define WRITE_END 1

int main()
{
	char wmsg[25]="Greeting";
	char rmsg[25];
	int fd[2];
	pid_t pid;

    	if(pipe(fd)==-1)
	{
		printf("pipe failed.");
		return 1;
	}
	pid=fork();
	if(pid<0)
	{
		printf("fork faile.");
		return 1;
	}
	if(pid>0)
	{
		close(fd[READ_END]);
		write(fd[WRITE_END],wmsg,25);
		close(fd[WRITE_END]);
	}
	else
	{
		close(fd[WRITE_END]);
		read(fd[READ_END],rmsg,25);
		printf(rmsg);
		close(fd[READ_END]);
	}
	return 0;
}
