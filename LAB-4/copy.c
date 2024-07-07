#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>

int main() 
{
    int file_a = open("a.txt",O_RDONLY);
    char buffer[100];

    
    if(file_a < 0)
    {
        printf("file a is not opened\n");
    }
    else{
        
        int read_a = read(file_a, buffer ,80);
        
        if(read_a < 0)
        {
             printf("file a is not read\n");   
        }
        
        else{ 
               
             int file_b = open("b.txt",O_WRONLY); 
             
             if(file_b < 0)
             {
                printf("file b is not opened\n");
             }
             
             else{
                
                int write_b = write(file_b, buffer ,read_a);
                
                if(write_b < 0)
                {
                    printf("file b is not write\n");
                }
                else{
                
                    if(read_a == write_b)
                    {
                        printf("copied successfully....\n");
                    }
                 }
                
             }
        
        }
        
    }

    return 0;
}
