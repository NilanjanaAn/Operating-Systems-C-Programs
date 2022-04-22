// 5. Priority (Preemptive) Algorithm - Nilanjana Thakur (205121064)

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
	int rem_time;
	int priority;
} process;

process* input();
process* sort(process*);
void prio(process*);
int maxArrived(process*, int);
int maxNext(process*);

int n;

int main()
{
	process* list=input();
	list=sort(list);
	prio(list);
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
		printf("Enter the priority: ");
		scanf("%d",&p.priority);
		p.completion_time=0;
		p.waiting_time=0;
		p.ta_time=0;
		p.rem_time=p.burst_time;
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

void prio(process* list)
{
	int i,j,curr,oldcurr,finished=0;
	int start_time,end_time,curr_time;
	int wait=0;
	double sum_wait=0.0, sum_ta=0.0;
	start_time=list[0].arrival_time;
	curr_time=start_time;
	printf("\n\nOUTPUT\n======\n\n");
	printf("%-16s | %-16s | %-16s | %-16s | %-16s | %-16s | %-16s\n","Process number","Arrival Time","Burst Time","Priority","Waiting Time","Completion Time","Turn Around Time");
	printf("-----------------+------------------+------------------+------------------+------------------+------------------+-----------------\n");
	
	while(1)
	{
		curr=maxArrived(list,curr_time);
		if(curr==-1)
		{
			curr=maxNext(list);
			curr_time=list[curr].arrival_time;
			curr=maxArrived(list, curr_time);
		}
		list[curr].rem_time--;
		if(list[curr].rem_time==0)
		{
			finished++;
			list[curr].completion_time=curr_time+1;
			list[curr].ta_time=list[curr].completion_time-list[curr].arrival_time;
			list[curr].waiting_time=list[curr].ta_time-list[curr].burst_time;
			printf("%-7s%2d%-7s | %-7s%2d%-7s | %-7s%2d%-7s | %-7s%2d%-7s | %-7s%2d%-7s | %-7s%2d%-7s | %-7s%2d%-7s\n","",list[curr].number,"","",list[curr].arrival_time,"","",list[curr].burst_time,"","",list[curr].priority,"","",list[curr].waiting_time,"","",list[curr].completion_time,"","",list[curr].ta_time,"");
			sum_wait+=list[curr].waiting_time;
			sum_ta+=list[curr].ta_time;
			if(finished==n)
			{
				end_time=list[curr].completion_time;
				break;
			}
		}
		curr_time++;
	}
	
	printf("\n-> Average waiting time = %.2f/%d = %.2f\n",sum_wait,n,sum_wait/(double)n);
	printf("\n-> Average turn around time = %.2f/%d = %.2f\n",sum_ta,n,sum_ta/(double)n);
	printf("\n-> Schedule length = %d - %d = %d\n",end_time,start_time,end_time-start_time);
}

int maxArrived(process *list, int time) // finds the process with maximum priority among the list of all arrived processes which haven't already executed
{
	int i,maxpos=-1;
	float max=999999; // maximum priority = minimum value
	for(i=0;i<n;i++)
	{
		if(list[i].completion_time==0 && list[i].arrival_time<=time && list[i].priority<max)
		{
			max=list[i].priority;
			maxpos=i;
		}
	}
	return maxpos;
}

int maxNext(process *list) // finds the next process which hasn't already executed
{
	int i;
	for(i=0;i<n;i++)
	{
		if(list[i].completion_time==0)
			return i;
	}
	return -1;
}
