// 2. Shortest Job First (SJF) Algorithm - Nilanjana Thakur (205121064)

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
process* sort(process*);
void sjf(process*);
int minArrived(process*, int);
int minNext(process*);

int n;

int main()
{
	process* list=input();
	list=sort(list);
	sjf(list);
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
		p.completion_time=0;
		p.waiting_time=0;
		p.ta_time=0;
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

void sjf(process* list)
{
	int i,j,curr,oldcurr;
	int start_time,end_time;
	int wait=0;
	double sum_wait=0.0, sum_ta=0.0;
	curr=minArrived(list,list[0].arrival_time);
	start_time=list[curr].arrival_time;
	printf("\n\nOUTPUT\n======\n\n");
	printf("%-16s | %-16s | %-16s | %-16s | %-16s | %-16s\n","Process number","Arrival Time","Burst Time","Waiting Time","Completion Time","Turn Around Time");
	printf("-----------------+------------------+------------------+------------------+------------------+-------------------\n");
	for(i=0;i<n;i++)
	{
		wait-=list[curr].arrival_time;
		wait=(wait<0)?0:wait;
		list[curr].waiting_time=wait;
		sum_wait+=wait;
		list[curr].completion_time=list[curr].arrival_time+wait+list[curr].burst_time;
		list[curr].ta_time=wait+list[curr].burst_time;
		sum_ta+=list[curr].ta_time;
		wait=list[curr].burst_time+list[curr].waiting_time+list[curr].arrival_time;
		printf("%-7s%2d%-7s | %-7s%2d%-7s | %-7s%2d%-7s | %-7s%2d%-7s | %-7s%2d%-7s | %-7s%2d%-7s\n","",list[curr].number,"","",list[curr].arrival_time,"","",list[curr].burst_time,"","",list[curr].waiting_time,"","",list[curr].completion_time,"","",list[curr].ta_time,"");
		oldcurr=curr;
		curr=minArrived(list,list[curr].completion_time);
		if(curr==-1)
		{
			curr=minNext(list);
			curr=minArrived(list, list[curr].arrival_time);
		}
	}
	end_time=list[oldcurr].completion_time;
	printf("\n-> Average waiting time = %.2f/%d = %.2f\n",sum_wait,n,sum_wait/(double)n);
	printf("\n-> Average turn around time = %.2f/%d = %.2f\n",sum_ta,n,sum_ta/(double)n);
	printf("\n-> Schedule length = %d - %d = %d\n",end_time,start_time,end_time-start_time);
}

int minArrived(process *list, int time) // finds the process with minimum burst time among the list of all arrived processes which haven't already executed
{
	int i,min=99999,minpos=-1;
	for(i=0;i<n;i++)
	{
		if(list[i].completion_time==0 && list[i].arrival_time<=time && list[i].burst_time<min)
		{
			min=list[i].burst_time;
			minpos=i;
		}
	}
	return minpos;
}

int minNext(process *list) // finds the next process which hasn't already executed
{
	int i;
	for(i=0;i<n;i++)
	{
		if(list[i].completion_time==0)
			return i;
	}
	return -1;
}
