#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>

int count=0;
sem_t sm;
pthread_t t1,t2;

void* try(){
	
	sem_wait(&sm);
	for(int i=0; i<10; i++)
	{	
		count++;
		printf("%d by %ld\n ",count,pthread_self());
	}
	sem_post(&sm);
}

int main()
{
	sem_init(&sm,0,1);
	pthread_create(&t1,NULL,&try,NULL);
	pthread_create(&t2,NULL,&try,NULL);
	
	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
	
	sem_destroy(&sm);
	printf("%d\n",count);
	
	return 0;
}
