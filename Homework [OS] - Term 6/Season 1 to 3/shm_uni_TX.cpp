#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>

//TX
int main()
{
	const int SIZE=4096;
	const char* name="os";
	const char* m0="Hello";
	const char* m1="world!";
	int shm_fd;
	void* ptr;

	shm_fd=shm_opem(name,O_CREAT|O_RDRW,0666);
	ftruncate(shm_fd,SIZE);
	ptr=mmap(0,SIZE,PORT_WRITE,MAP_SHARED,shm_fd,0);
	sprintf(ptr,"%s",m0);
	ptr+=strlen(m0);

	sprintf(ptr,"%s",m1);
	ptr+=strlen(m1);

	return 0;
}
