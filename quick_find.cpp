#include "stdio.h"
#include "time.h"
#include <stdlib.h>

void select(int a[1000],int num,int f_num,int odd);

int main(){
	srand(time(NULL));
	int a[1000]={-1},num,f_num,odd;
	
	printf("input a number between 2~1000 :");
	scanf("%d",&num);
	while (num>999 || num <2){
		printf("input again :");
		scanf("%d",&num);
	}
	
	printf("find which one(0 is median)? ");
	scanf("%d",&f_num);
	while (f_num <0 || f_num >num){
		printf("enter again: ");
		scanf("%d",&f_num);
	}
	
	for (int i = 0; i < num; i++){
		a[i]=rand()%10000;  //make 0-9999 random number
	}
	
	printf("before: ");
	for (int i = 0; i < num; i++){
		printf("%d\t",a[i]); 
	}
	printf("\n");
	num%2==0?odd=0:odd=1;
	select(a,num,f_num,odd);
	
	printf("\nafter: ");
	
	for (int i = 0; i < num; i++){
		printf("%d\t",a[i]); 
	}
}

void select(int a[1000],int num,int f_num,int odd){
	int min,lo,c;double x;
	for(int j = 0 ;j<num;j++){
		lo=j;min=a[j];
		for (int i=j+1;i<num;i++){
			a[i]<min?min=a[i],lo=i:0;
		}
		
		if(f_num==0 && odd == 1){
			j==num/2?printf("that is :%d\n",a[lo]):0;
			
		}
		else if(f_num==0 && odd == 0){
			if(j==num/2){
				x=a[lo]+a[j-1];
				printf("that is :%.1f\n",x/2);
			}
		}
		else if(j==f_num-1){
			printf("that is :%d\n",a[lo]);
			
		}
		if(lo!=j){			
			c=a[j];
			a[j]=a[lo];
			a[lo]=c;
		}
		
	}
	
}
