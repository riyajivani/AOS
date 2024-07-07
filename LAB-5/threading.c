#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void* start_routine()
{
    printf("thread created\n");
    printf("process id: %d\n",getpid());
    sleep(3);
    printf("thread ended\n");
       
}

int main()
{
    pthread_t t1,t2;
    pthread_create(&t1,NULL,&start_routine,NULL); //& means we passing address
    pthread_create(&t2,NULL,&start_routine,NULL);
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
}
