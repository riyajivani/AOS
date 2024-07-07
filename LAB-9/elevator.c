#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int size;
int arr[100];
int direction;
int head=50;
int seek[100];
int seekSize;
int overhead=0;
int position;
int left=0;
int right=199;

int cmpfunc(const void*a , const void*b){
	return (*(int*)a - *(int*)b);
}

void elevator()
{
	qsort(arr,size,sizeof(int),cmpfunc);
	
	
	if(direction==1){
		int j=0,i=1;
		while(arr[j]<=head){
			j++;
			position=j; //82 in our example and I store position of 82 to get position of 43 later
		}
		
		
		seek[i-1]=arr[j]; //82
		overhead=arr[j]-head;
		j=j+1;
		
		for(i,j;j<size;j++,i++) //going right
		{
			seek[i]=arr[j];
			overhead=overhead+(arr[j]-seek[i-1]);
		}
		
		overhead=overhead+(right-arr[size-1]); //199-190
		seek[i++]=right;
		j=position-1; //43
		overhead=overhead+(right-arr[j]); //199-43
		seek[i++]=arr[j--]; //43 added in seek array
		
		for(i,j;j>=0;i++,j--)  //going left
		{
			seek[i]=arr[j];
			overhead=overhead+(seek[i-1]-arr[j]);
		}
		seekSize=i;
		
	}else if(direction==0)
	{
		int j=0,i=1;
		while(arr[j]<=head){
			j++;
			position=j; //82 in our example and i store position of 82
		}
		j=j-1; // at 43
		overhead= head - arr[j];  //50-43
		seek[i-1]=arr[j--]; //43		
		
		for(i,j;j>=0;i++,j--)  //going left
		{
			seek[i]=arr[j];
			overhead=overhead+(seek[i-1]-arr[j]);
		}
		
		overhead = overhead + (arr[0]-left); //16-0
		seek[i++]=left;
		j=position;
		overhead = overhead + (arr[j]-left); //82-0
		seek[i++]=arr[j++]; //82 in seek and after that j points to 140
		
		for(i,j;j<size;j++,i++) //going right
		{
			seek[i]=arr[j];
			overhead=overhead+(arr[j]-seek[i-1]);
		}
		
		seekSize=i;
	}
	else
	{
		printf("please choose valid direction\n");
	}
	
		
}

int main()
{
	printf("enter the total no. of sequence element: ");
	scanf("%d",&size);
	
	printf("enter sequence\n");
	for(int i=0; i<size; i++){
		scanf("%d",&arr[i]);
	}
	
	printf("enter diection(1 for right to left and 0 for left to right): ");
	scanf("%d",&direction);
	
	elevator();
	
	printf("seek sequence is : ");
	for(int k=0; k<seekSize; k++){
		printf("%d ",seek[k]);
	}
	
	printf("\noverhead is %d\n",overhead);

	return 0;
}
