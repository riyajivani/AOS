#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int count = 0;
pthread_mutex_t mutex;

void* start_routine()
{
   
        printf("thread created\n");
        printf("process id: %d\n",getpid());
        for(int i=0; i<10; i++)
        {
            pthread_mutex_lock(&mutex);
            
            count+=1; 
            printf("count %d ",count);
            
            pthread_mutex_unlock(&mutex); 
        }
        printf("\n");
        sleep(3);
        printf("thread ended\n");
          
}

int main()
{
    pthread_t t1,t2;
    
    pthread_mutex_init(&mutex,NULL);
    pthread_create(&t1,NULL,&start_routine,NULL); //& means we passing address
    pthread_create(&t2,NULL,&start_routine,NULL);
    pthread_mutex_destroy(&mutex);
    
    
    pthread_join(t1,NULL);   
    pthread_join(t2,NULL);
}
