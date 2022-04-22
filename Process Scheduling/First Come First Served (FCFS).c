// 1. First Come First Served (FCFS Algorithm) - Nilanjana Thakur (205121064)

#include<stdio.h>
#include<stdlib.h>

typedef struct
{
	int number;
	int arrival_time;
	int burst_time;
	int ta_time;
	int waiting_time;
	int completion_time;
} process;

process* input();
process* sort(process *);
void fcfs(process*);

int n;

int main()
{
	process* list=input();
	list=sort(list);
	fcfs(list);
	return 0;
}

process* input()
{
	int i,j,k;
	process *list;
	process p;
	printf("INPUT\n=====\n\n");
	printf("Enter the number of processes: ");
	scanf("%d",&n);
	list=(process*)calloc(n,sizeof(process));
	for(i=0;i<n;i++)
	{
		printf("\nFor process %d:\n---------------\n",i+1);
		p.number=i+1;
		printf("Enter the arrival time: ");
		scanf("%d",&p.arrival_time);
		printf("Enter the burst time: ");
		scanf("%d",&p.burst_time);
		list[i]=p;
	}
	return list;
}

process* sort(process *list)
{
	int i,j,flag;
	process temp;
	for(i=0;i<n-1;i++)
    {
    	flag=0;
        for(j=i+1;j<n;j++)
        {
            if(list[i].arrival_time>list[j].arrival_time) // comparing values of arrival times
            { 
				// swapping the structures for sorting
                temp=list[i];
                list[i]=list[j];
                list[j]=temp;
                flag=1;
            }
        }
        if(flag==0) // sorted
        	break;
    }
    return list;
}

void fcfs(process* list)
{
	int i,j;
	int start_time,end_time;
	int wait=0;
	double sum_wait=0.0, sum_ta=0.0;
	start_time=list[0].arrival_time;
	printf("\n\nOUTPUT\n======\n\n");
	printf("%-16s | %-16s | %-16s | %-16s | %-16s | %-16s\n","Process number","Arrival Time","Burst Time","Waiting Time","Completion Time","Turn Around Time");
	printf("-----------------+------------------+------------------+------------------+------------------+-------------------\n");
	for(i=0;i<n;i++)
	{
		wait-=list[i].arrival_time;
		wait=(wait<0)?0:wait;
		list[i].waiting_time=wait;
		sum_wait+=wait;
		list[i].completion_time=list[i].arrival_time+wait+list[i].burst_time;
		list[i].ta_time=wait+list[i].burst_time;
		sum_ta+=list[i].ta_time;
		wait=list[i].burst_time+list[i].waiting_time+list[i].arrival_time;
		printf("%-7s%2d%-7s | %-7s%2d%-7s | %-7s%2d%-7s | %-7s%2d%-7s | %-7s%2d%-7s | %-7s%2d%-7s\n","",list[i].number,"","",list[i].arrival_time,"","",list[i].burst_time,"","",list[i].waiting_time,"","",list[i].completion_time,"","",list[i].ta_time,"");
	}
	end_time=list[n-1].completion_time;
	printf("\n-> Average waiting time = %.2f/%d = %.2f\n",sum_wait,n,sum_wait/(double)n);
	printf("\n-> Average turn around time = %.2f/%d = %.2f\n",sum_ta,n,sum_ta/(double)n);
	printf("\n-> Schedule length = %d - %d = %d\n",end_time,start_time,end_time-start_time);
}
