#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>

int main(){
	int fd[2],write_to_file,read_count;
	pipe(fd);
	char * str="hello";
	char buff[5];
	write_to_file=write(fd[1],str,5);
	if(write_to_file == 5){printf("written successfully\n");}
	read_count=read(fd[0],buff,5);
	if(read_count == 5){printf("content(%s) read from the file successfully\n",buff);}
}
