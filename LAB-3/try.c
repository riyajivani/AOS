#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

int main()
{
	pid_t a; //shared memory
	int x=10;
	
	a=fork(); //child process created.
	a=fork(); 
	//a=fork();
	
	printf("hello\n"); 
	
	//printf("%d",a);
	
	/*parent writes hello and for the very first time child is duplicate of parent. so child also print hello.
	copy of child = (2^(no. of fork)) - 1*/
	
	if(a<0)
	{
		printf("child not created successfully\n");
	}
	else if(a==0)
	{
		//x=x+10;
		//printf("child x %d\n",x);
		//printf("child process memory\n");  // if else if else ic child process
		
		printf("child process id is %d \n",getpid());
		printf("child process's parent id is %d \n",getppid());
	}
	else
	{
		//printf("parent process memory\n");
		//x=x*10;
		//printf("parent x %d\n",x);
		
		printf("parent process id is %d \n",getpid());
		printf("parent process's parent id is %d \n",getppid());
	}
	
	//printf("hello\n");
	printf("%d\n",x);
	
	return 0;
}
 
