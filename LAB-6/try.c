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
    int fd1[2], fd2[2];
    pipe(fd1);
    pipe(fd2);
    pid_t a = fork();

    char str1[10], str2[10]; // Use arrays for strings
    char buffer[10];
    int size;

    if (a == 0)
    {
        close(fd1[1]);
        int readc = read(fd1[0], buffer, 10);
        printf("child read the content from the pipe is %s\n", buffer);

        for (int i = 0; i < readc; i++)
        {
            char ch = toupper(buffer[i]);
            strncat(str2, &ch, 1);
        }

        close(fd1[0]);
        close(fd2[0]);
        
        int writec = write(fd2[1], str2, 10);
        printf("child has written the uppercase of string in pipe successfully\n");
        close(fd2[1]);

        exit(0);
    }
    else if (a > 0)
    {
        printf("parent enter the string: ");
        scanf("%s", str1);

        close(fd1[0]);
        int writep = write(fd1[1], str1, 10);
        printf("parent has written the content in pipe successfully\n");
        close(fd1[1]);

        wait(NULL);

        close(fd2[1]);
        read(fd2[0], buffer, 10);
        printf("parent read the content from the pipe is %s\n", buffer);
        close(fd2[0]);

        exit(0);
    }
}

