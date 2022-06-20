#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>

//RX
int main()
{
	const int SIZE=4096;
	const char* name="os";
	int shm_fd;
	void* ptr;

	shm_fd=shm_opem(name,O_RDONLY,0666);
	ftruncate(shm_fd,SIZE);
	ptr=mmap(0,SIZE,PORT_READ,MAP_SHARED,shm_fd,0);
	printf("%s",(char*)ptr);
	shm_unlink(name);

	return 0;
}
