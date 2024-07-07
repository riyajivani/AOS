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
	
	sfd = shm_open(name,O_CREAT|O_RDWR,0777); //open with us only, not in shared memory
	
	ftruncate(sfd,size);
	ptr = mmap(NULL,size,PROT_WRITE,MAP_SHARED,sfd,0);
	
	sprintf(ptr,"%s","hello from shared memory"); //write in shared memory with pointer
	printf("content written to shared memory");
	
	
		
}
