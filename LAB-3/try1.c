#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>

int main()
{
    int a;
    
    a=fork();
    
    if(a<0)
    {
        printf("process not created\n");
    }
    else if(a==0)
    {
    	printf("child created\n"); //here child become orphan bcz parent terminated first.
        //execlp("/bin/ls","ls",NULL); 
        //printf("child user id %d\n",getuid());
       //printf("child group id %d\n",getgid());
       printf("child process id is %d \n",getpid());
		printf("child process's parent id is %d \n",getppid());
		sleep(2);
       printf("child terminated\n"); //exexlp is system call so its priority is first. so it override this
       //printf stmt.
    }
    
    else
    {
                
		printf("parent created\n");  //according to fcfs parent runs first 
		//printf("parent user id %d\n",getuid());
		//printf("parent group id %d\n",getgid());
		printf("parent process id is %d \n",getpid());
		printf("parent process's parent id is %d \n",getppid());
        //sleep(5);//algo is still fcfs, but now parent wait for 5 second. but child terminate after parent
        //wait(NULL);  //it fetches the value from child process. null provided by child
        printf("parent terminated\n");
    }
    
    return 0;
}
