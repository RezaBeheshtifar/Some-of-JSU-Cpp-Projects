#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main()
{
    int pipefd[2];
    pid_t cpid;
    const int BSIZE = 100;
    char buf[BSIZE];


   if (pipe(pipefd) == -1) {
       perror("pipe");
       exit(EXIT_FAILURE);
   }

   cpid = fork();
   if (cpid == -1) {
       perror("fork");
       exit(EXIT_FAILURE);
   }

   if (cpid == 0) {    /* Child reads from pipe */
       read(pipefd[0], buf, BSIZE);
       printf(buf);
       write(pipefd[1], "bye\n\0", 5);
       close(pipefd[0]);
       close(pipefd[1]); 
       exit(EXIT_SUCCESS);

   } else {            /* Parent writes argv[1] to pipe */
       write(pipefd[1], "salaam\n\0", 8);
       sleep(1); 
       read(pipefd[0], buf, BSIZE);
       printf(buf);
       close(pipefd[1]);          
       close(pipefd[0]);
       exit(EXIT_SUCCESS);
   }
}
