#include<pthread.h>
#include<stdio.h>

#define size 5

int count=0,in=0,out=0,item=0;

pthread_mutex_t lock;

int buff[size];

void* produce()
{
	for(int i=0;i<10;i++)
	{
		item++;
		pthread_mutex_lock(&lock);
		while(count==size)
		{
			pthread_mutex_unlock(&lock);
			pthread_mutex_lock(&lock);
		}
		buff[in]=item;
		printf("producer produced item %d at location %d\n",item,in);
		in = (in+1)%size;
		count++;
		pthread_mutex_unlock(&lock);
	}
}
void* consumer(){
	for(int i=0;i<10;i++)
	{
		pthread_mutex_lock(&lock);
		while(count==0)
		{
			pthread_mutex_unlock(&lock);
			pthread_mutex_lock(&lock);
		}
		item=buff[out];
		printf("consumer consumed item %d at location %d\n",item,out);
		out = (out+1)%size;
		count--;
		pthread_mutex_unlock(&lock);
	}
}
int main(){
	pthread_t prod,con;
	pthread_create(&prod,NULL,&produce,NULL);
	pthread_create(&con,NULL,&consumer,NULL);
	
	pthread_join(prod,NULL);
	pthread_join(con,NULL);
}
