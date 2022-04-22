// Banker's Safety Algorithm - Nilanjana Thakur (205121064)

#include<stdio.h>

int main()
{
    int max[10][10],need[10][10],alloc[10][10],avail[10],completed[10]={0},safe[10];
    int i,j,p,r,process,count=0;
    printf("Enter the number of processes: ");
    scanf("%d",&p);
    printf("Enter the number of resources: ");
    scanf("%d",&r);
    printf("\nEnter the allocation for each process: \n");
    for(i=0;i<p;i++)
    {
        printf("\nFor process %d : \n",i+1);
        for(j=0;j<r;j++)
        {	
		printf("	Resource %d: ",j+1);
            scanf("%d",&alloc[i][j]);
        }
    }
    printf("\nEnter the maximum for each process: \n");
    for(i=0;i<p;i++)
    {
        printf("\nFor process %d : \n",i+1);
        for(j=0;j<r;j++)
        {
        	printf("	Resource %d: ",j+1);
            scanf("%d",&max[i][j]);
        }
    }
    printf("\nEnter the number of available resources: \n");
    for(i=0;i<r;i++)
    {
    	printf("For Resource %d: ",i+1);
        scanf("%d",&avail[i]);
    }
    for(i=0;i<p;i++) // calculate the need of each process (need= maximum - allocation)
	{
        for(j=0;j<r;j++)
            need[i][j] = max[i][j] - alloc[i][j];
    }
    do
	{
        process = -1;
        for(i=0;i<p;i++)
		{
            if(completed[i]==0)
			{
                process=i;
				int val=0;
                for(j=0;j<r;j++) // find a process where the need of each resource can be satisfied by avail
				{
                    if(avail[j]>=need[i][j])
					{
						val++;
                    }
                }
                if(val==r)
                	break;
            }
        }
        if(process!=-1)
		{
            printf("\nProcess %d is completed.", process+1);
            safe[count] = process+1; // add this process to the safe sequence
            completed[process] = 1;
            count++;
            for(j=0;j<r;j++) // on completion, the process releases all resources held by it back to the system
			{
                avail[j]+=alloc[process][j];
                alloc[process][j] = 0;
                max[process][j] = 0;
            }
        }
    } while(count != p && process != -1);
    
    if(count == p) // if all processes have completed executing
	{
        printf("\nThe system is in a safe state.\n");
        printf("The safe sequence is: < ");
        for(i=0;i<p;i++)
            printf("%d ",safe[i]);
        printf(">\n");
    }
    else
        printf("\nThe system is in an unsafe state.\n");
    return 0;
}

