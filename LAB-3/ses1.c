#include<stdio.h>
int main()
{
int a;
	if(fork()==0)
	{
		a=a+5;
		printf("value of x %d and y %p \n",a,&a);
	}
	else{
		a=a-5;
		printf("value of u %d and v %p \n",a,&a);
	}
}
