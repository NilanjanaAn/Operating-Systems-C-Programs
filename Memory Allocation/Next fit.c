// 4. Next Fit - Nilanjana Thakur (205121064)

#include<stdio.h>

int main()
{
	int block[100], process[100];
	int b,p,i,j,r,flag;
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
	printf("\n=================================\n\nResult of Next Fit Allocation:\n\n");
	printf("PROCESS |  SIZE  |  PARTITION SIZE |  ORIGINAL BLOCK NUMBER | INTERNAL FRAGMENTATION\n");
	printf("--------+--------+-----------------+------------------------+-----------------------\n");
	j=0;
	for(i=0;i<p;i++)
	{
		flag=0;
		for(r=0;r<b;r++)
		{
			if(block[(j+r)%b]>=process[i]) // start searching from after the last allocated partition and choose the first one large enough to keep the process
			{
				flag=1;
				printf("  %2d    |  %3d   |    %7d      |           %2d           |         %3d\n",i+1,process[i],block[(j+r)%b],(j+r)%b+1,block[(j+r)%b]-process[i]);
				block[(j+r)%b]-=process[i];
				j=(j+r)%b; // wrap around
				break;
			}
		}
		if(flag==0) // no available partition is large enough to keep the process
			printf("  %2d    |  %3d   |       NONE      |         NONE           |         NONE\n",i+1,process[i]);
	}
}
