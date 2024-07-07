#include <stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/wait.h>


int main()
{
    int a=fork();
    int file_d = open("d.txt",O_WRONLY);
    
    if(a<0)
    {
        printf("child not created\n");
    }
    else if(a==0)
    {
        printf("child memory\n");
        
        char child_buffer[]="hello";
        
        int write_c = write(file_d, child_buffer ,5);
        
        printf("file descriptor of child %d\n",write_c);
        //printf("word read by child\n");
        //for(int i=0; i<read_c; i++)
        //{
        //    printf("%c",child_buffer[i]);
        //}
        //printf("\n");
        
        printf("child terminated\n");
    }
    else
    {
        printf("parent memory\n");
        wait(NULL);
        
        char parent_buffer[]="world";
        
        int write_d = write(file_d, parent_buffer ,5);
        
        printf("file descriptor of parent %d\n",write_d);
        
        //printf("word read by parent\n");
        //for(int i=0; i<read_p; i++)
        //{
        //    printf("%c",parent_buffer[i]);
        //}
       // printf("\n");
        
        
        printf("parent terminated\n");
    }
    
    return 0;

}
