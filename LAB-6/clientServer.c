//see the figure in record book to understand the code

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int main()
{
	int fd1[2],fd2[2];
	pipe(fd1);
	pipe(fd2);
	pid_t a = fork();
	
	char str1[10], str2[10];
	char buffer[10];
	int size;
	
	if(a==0)
	{
		//printf("child memory\n");
		close(fd1[1]); // now for reading close the write
		int readc = read(fd1[0], buffer, 10);
		printf("child read the content from the pipe is %s\n",buffer);
		
		for(int i=0; i<readc; i++)
		{
			//str2[i] = toupper(buffer[i]);
			char ch = toupper(buffer[i]);
			strncat(str2, &ch, 1);
		}

		close(fd1[0]);
		close(fd2[0]); //because when child is writing , parent can not reading
		
		int writec = write(fd2[1], str2, 10);
		printf("child has written the uppercase of string in pipe successfully\n");
		close(fd2[1]); // now for reading close the write
		
		exit(0); 
	}
	
	else if(a > 0)
	{
		printf("parent enter the string: ");
		scanf("%s",str1);
		//size = strlen(str1);
		
		close(fd1[0]); //because when parent is writing , child can not reading
		
		int writep = write(fd1[1], str1, 10);
		printf("parent has written the content in pipe successfully\n");
		close(fd1[1]); // now for reading close the write
		
		wait(NULL);
		
		close(fd2[1]);
		read(fd2[0], buffer, 10);
		printf("parent read the content from the pipe is %s\n",buffer);
		close(fd2[0]);
		
		exit(0);
	}
}
