#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

int main()
{
	printf("%d, %d, %d, %d, %d, %d ",getpid(),getppid(),getuid(),getgid(),geteuid(),getegid());
}
