// 3. Worst Fit - Nilanjana Thakur (205121064)

#include<stdio.h>

int main()
{
	int block[100], process[100];
	int b,p,i,j,max,index;
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
	printf("\n=================================\n\nResult of Worst Fit Allocation:\n\n");
	printf("PROCESS |  SIZE  |  PARTITION SIZE |  ORIGINAL BLOCK NUMBER | INTERNAL FRAGMENTATION\n");
	printf("--------+--------+-----------------+------------------------+-----------------------\n");
	for(i=0;i<p;i++)
	{
		max=-1;
		for(j=0;j<b;j++) /* search for the partition large enough to keep the process but causing most internal fragmentation,
							i.e. the space remaining after assigning the process to that parition should be maximum */
		{
			if(block[j]>=process[i])
			{
				if(max<block[j]-process[i])
				{
					max=block[j]-process[i];
					index=j;
				}
			}
		}
		if(max!=-1)
		{
			printf("  %2d    |  %3d   |    %7d      |           %2d           |         %3d\n",i+1,process[i],block[index],index+1,block[index]-process[i]);
			block[index]-=process[i];
		}
		else // no available partition is large enough to keep the process
			printf("  %2d    |  %3d   |       NONE      |         NONE           |         NONE\n",i+1,process[i]);
	}
}
