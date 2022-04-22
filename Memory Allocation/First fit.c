// 1. First Fit - Nilanjana Thakur (205121064)

#include<stdio.h>

int main()
{
	int block[100], process[100];
	int b,p,i,j,flag;
	printf("Enter the number of blocks: ");
	scanf("%d",&b);
	printf("Enter the block sizes in order:\n");
	for(i=0;i<b;i++)
	{
		printf("Block %d -> ",i+1);
		scanf("%d",&block[i]);
	}
	printf("\nEnter the number of processes: ");
	scanf("%d",&p);
	printf("Enter the process sizes in order:\n");
	for(i=0;i<p;i++)
	{
		printf("Process %d -> ",i+1);
		scanf("%d",&process[i]);
	}
	printf("\n=================================\n\nResult of First Fit Allocation:\n\n");
	printf("PROCESS |  SIZE  |  PARTITION SIZE |  ORIGINAL BLOCK NUMBER | INTERNAL FRAGMENTATION\n");
	printf("--------+--------+-----------------+------------------------+-----------------------\n");
	for(i=0;i<p;i++)
	{
		flag=0;
		for(j=0;j<b;j++)
		{
			if(block[j]>=process[i]) // choose the first available partition that is large enough to keep the process
			{
				flag=1;
				printf("  %2d    |  %3d   |    %7d      |           %2d           |         %3d\n",i+1,process[i],block[j],j+1,block[j]-process[i]);
				block[j]-=process[i];
				break;
			}
		}
		if(flag==0) // no available partition is large enough to keep the process
			printf("  %2d    |  %3d   |       NONE      |         NONE           |         NONE\n",i+1,process[i]);
	}
}
