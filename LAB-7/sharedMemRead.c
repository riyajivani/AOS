#include<stdio.h>
#include<sys/mman.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/shm.h>

int main()
{
	const char* name = "myfile";
	int size = 4096;
	int sfd;
	void* ptr;
	
	sfd = shm_open(name,O_RDWR,0777);
	
	ftruncate(sfd,size);
	ptr = mmap(NULL,size,PROT_READ,MAP_SHARED,sfd,0);
	
	printf("%s",(char*)ptr);
}
