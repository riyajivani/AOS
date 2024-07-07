#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>

int main(){
	int fd1[2],fd2[2],write_to_file,read_count;
	pipe(fd1),pipe(fd2);
	pid_t a;
	char * str1="hello parent";
	char* str2="hello child";
	char buff[10];
	a=fork();

	if(a<0)
	{
		printf("child not created\n");
	}
	else if(a>0){
		//close this because while parent is writing at that time child cannot read
		close(fd1[0]);
		write_to_file=write(fd1[1],str1,10);
		if(write_to_file == 10){printf("parent wrote content successfully\n");}
		close(fd1[1]);
		wait(NULL);
		close(fd2[1]);
		read(fd2[0],buff,10);
		printf("content(%s) read by parent from the file successfully\n",buff);
		close(fd2[0]);
		exit(0);
		
	}
	else{
		//in case it gets preempted b4 close function
		close(fd1[1]);
		read_count=read(fd1[0],buff,10);
		if(read_count == 10){printf("content(%s) read by child from the file successfully\n",buff);}
		close(fd2[0]);
		write(fd2[1],str2,10);
		printf("child wrote content in pipe 2\n");
		close(fd2[1]);
		exit(0);
	}
	
}
