#include "stdio.h"
#include "time.h"
#include <stdlib.h>

void select(int a[1000],int num);
int main(){
	srand(time(NULL));
	int a[1000]={-1},num;
	printf("input a number between 2~1000 :");
	scanf("%d",&num);
	while (num>999 || num <2){
		printf("input again :");
		scanf("%d",&num);
	}
	for (int i = 0; i < num; i++){
		a[i]=rand()%10000;  //make 0-99 random number
	}
	printf("排序前: ");
	for (int i = 0; i < num; i++){
		printf("%d\t",a[i]); 
	}
	printf("\n");
	select(a,num);
	printf("排序後: ");
	for (int i = 0; i < num; i++){
		printf("%d\t",a[i]); 
	}
	printf("\n");
	system("pause");
	return 0;
}

void select(int a[1000],int num){
	int min,lo,c;
	for(int j = 0 ;j<num;j++){
		lo=j;min=a[j];
		for (int i=j+1;i<num;i++){
			a[i]<min?min=a[i],lo=i:0;
		}
		if(lo!=j){			
			c=a[j];
			a[j]=a[lo];
			a[lo]=c;
		}
	}
	
}
