#include <stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/wait.h>


int main()
{
    int a=fork();
    int file_c = open("c.txt",O_RDONLY);
    
    if(a<0)
    {
        printf("child not created\n");
    }
    else if(a==0)
    {
        printf("child memory\n");
        char child_buffer[10];
        int read_c = read(file_c, child_buffer ,6);
        
        printf("word read by child\n");
        for(int i=0; i<read_c; i++)
        {
            printf("%c",child_buffer[i]);
        }
        printf("\n");
        printf("child terminated\n");
    }
    else
    {
        printf("parent memory\n");
        char parent_buffer[10];
        int read_p = read(file_c, parent_buffer ,5);
        
        printf("word read by parent\n");
        for(int i=0; i<read_p; i++)
        {
            printf("%c",parent_buffer[i]);
        }
        printf("\n");
        
        //wait(NULL);
        printf("parent terminated\n");
    }
    
    return 0;

}
