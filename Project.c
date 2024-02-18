#include <stdio.h>
#include <stdlib.h>
#include<conio.h>  

struct priority_scheduling {
    char process_name;
    int burst_time;
    int waiting_time;
    int turn_around_time;
    int priority;
};

void fcfs(int n);
void sjf_non_preemptive(int n);
void sjf_preemptive(int n);
void priority(int n);
void round_robin(int n);

int main() {
    int choice, n;
    
    printf("Enter the total number of processes: ");
    scanf("%d", &n);
    
    printf("Select the scheduling algorithm:\n");
    printf("1. FCFS\n");
    printf("2. SJF non-preemptive\n");
    printf("3. SJF preemptive\n");
    printf("4. Priority Scheduling\n");
    printf("5. Round Robin\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    
    switch (choice) {
        case 1:
            fcfs(n);
            break;
        case 2:
            sjf_non_preemptive(n);
            break;
        case 3:
            sjf_preemptive(n);
            break;
        case 4:
            priority(n);
            break;
        case 5:
            round_robin(n);
            break;
        default:
            printf("Invalid choice\n");
            break;
    }
    
    return 0;
}

void fcfs(int n) {
    int bt[30],wait_t[30],turn_ar_t[30],i,j;
    double av_wt_t=0.0,avturn_ar_t=0.0;
    printf("\nEnter The Process Burst Time\n");
    for(i=0;i<n;i++)  
    {
        printf("P[%d]:",i+1);
        scanf("%d",&bt[i]);
    }
    wait_t[0]=0;   
    for(i=1;i<n;i++)
    {
        wait_t[i]=0;
        for(j=0;j<i;j++)
            wait_t[i]+=bt[j];
    }
    printf("\nProcess\t  Burst Time\t  Waiting Time\t  Turnaround Time");
    for(i=0;i<n;i++)
    {
        turn_ar_t[i]=bt[i]+wait_t[i];
        av_wt_t+=wait_t[i];
        avturn_ar_t+=turn_ar_t[i];
        printf("\nP[%d]\t\t%d\t\t%d\t\t%d",i+1,bt[i],wait_t[i],turn_ar_t[i]);
    }
    av_wt_t/=i;
    avturn_ar_t/=i; 
    printf("\nAverage Waiting Time:%lf",av_wt_t);
    printf("\nAverage Turnaround Time:%lf",avturn_ar_t);
}

void sjf_non_preemptive(int n) {
    int burst_time[20],p[20],waiting_time[20],tat[20],i,j,total=0,pos,temp;
    float avg_waiting_time,avg_tat;
    printf("\nEnter the Burst Time of each process:\n");
    for(i=0;i<n;i++)
    {
        printf("P[%d]:",i+1);
        scanf("%d",&burst_time[i]);
        p[i]=i+1;         
    }
    for(i=0;i<n;i++)
    {
        pos=i;
        for(j=i+1;j<n;j++)
        {
            if(burst_time[j]<burst_time[pos])
                pos=j;
        }
        temp=burst_time[i];
        burst_time[i]=burst_time[pos];
        burst_time[pos]=temp;
        temp=p[i];
        p[i]=p[pos];
        p[pos]=temp;
    }
    waiting_time[0]=0;            
    for(i=1;i<n;i++)
    {
        waiting_time[i]=0;
        for(j=0;j<i;j++)
            waiting_time[i]+=burst_time[j];
        total+=waiting_time[i];
    }
    avg_waiting_time=(float)total/n;      
    total=0;
    printf("\nProcess\t  Burst Time\t  Waiting Time\t  Turnaround Time");
    for(i=0;i<n;i++)
    {
        tat[i]=burst_time[i]+waiting_time[i];   
        total+=tat[i];
        printf("\nP[%d]\t\t%d\t\t%d\t\t%d",p[i],burst_time[i],waiting_time[i],tat[i]);
    }
    avg_tat=(float)total/n;    
    printf("\nAverage Waiting Time: %f",avg_waiting_time);
    printf("\nAverage Turnaround Time: %f\n",avg_tat);
}

void sjf_preemptive(int n) {
    int arrival_time[10], burst_time[10], temp[10];
    int i, smallest, count = 0, time;
    double wait_time = 0, turnaround_time = 0, end;
    float average_waiting_time, average_turnaround_time;
    for(i = 0; i < n; i++)
    {
        printf("\nEnter Details of P[%d] :",i+1);
        printf("\nArrival Time: ");
        scanf("%d", &arrival_time[i]);
        printf("Burst Time: ");
        scanf("%d", &burst_time[i]); 
        temp[i] = burst_time[i];
    }
    burst_time[9] = 9999;  
    printf("\nProcess\t   Burst Time\t  Completion Time\t  Waiting Time\t  Turnaround Time\n");
    for(time = 0; count != n; time++)
    {
        smallest = 9;
        for(i = 0; i < n; i++)
        {
            if(arrival_time[i] <= time && burst_time[i] < burst_time[smallest] && burst_time[i] > 0)
            {
                smallest = i;
            }
        }
        burst_time[smallest]--;
        if(burst_time[smallest] == 0)
        {
            count++;
            end = time + 1;
            wait_time = wait_time + end - arrival_time[smallest] - temp[smallest];
            turnaround_time = turnaround_time + end - arrival_time[smallest];
            printf("P[%d]\t\t%d\t\t%.0lf\t\t\t%.0lf\t\t%.0lf\n", smallest + 1, temp[smallest], end, end - arrival_time[smallest] - temp[smallest], end - arrival_time[smallest]);
        }
    }
    average_waiting_time = wait_time / n; 
    average_turnaround_time = turnaround_time / n;
    printf("\nAverage Waiting Time: %lf", average_waiting_time);
    printf("\nAverage Turnaround Time: %lf", average_turnaround_time);
}

void priority(int n) {
    int total = 0,i,j;
    struct priority_scheduling temp_process;
    int position;
    double average_waiting_time, average_turnaround_time;
    struct priority_scheduling *process = malloc(n * sizeof(struct priority_scheduling));
    printf("Enter the  Burst Time and Priority of each process:\n");
    for (i = 0,j=1; i < n; i++,j++) {
        printf("\nEnter the details of the process P[%d]\n",j);
        printf("Enter the burst time: ");
        scanf("%d",&process[i].burst_time);
        printf("Enter the priority: ");
        scanf("%d",&process[i].priority);
    }
    for (i = 0; i < n; i++) {
        position = i;
        for (j = i + 1; j < n; j++) {
        if (process[j].priority > process[position].priority)
            position = j;
        }
        temp_process = process[i];
        process[i] = process[position];
        process[position] = temp_process;
    }
    process[0].waiting_time = 0;
    for (int i = 1; i < n; i++) {
        process[i].waiting_time = 0;
        for (int j = 0; j < i; j++) {
        process[i].waiting_time += process[j].burst_time;
        }
        total += process[i].waiting_time;
    }
    average_waiting_time = (float) total / (float) n;
    total = 0;
    printf("\nProcess\t  Burst Time\t  Waiting Time\t  Turnaround Time");
    for (i = 0,j=1; i < n; i++,j++) {
        process[i].turn_around_time = process[i].burst_time + process[i].waiting_time;
        total += process[i].turn_around_time;
        printf("\nP[%d]\t\t%d\t\t%d\t\t%d",j, process[i].burst_time, process[i].waiting_time, process[i].turn_around_time);
    }
    average_turnaround_time = (float) total / (float) n;
    printf("\nAverage Waiting Time : %lf", average_waiting_time);
    printf("\nAverage Turnaround Time : %lf\n", average_turnaround_time);
}

void round_robin(int n) {
    int i, sum=0, count=0, y, quant, wt=0, tat=0, at[10], bt[10], temp[10];  
    float avg_wt, avg_tat;  
    y = n;
    for(i=0; i<n; i++)  
    {  
        printf("\nEnter the details of P[%d]\n", i+1);  
        printf("Arrival time is: "); 
        scanf("%d", &at[i]);  
        printf("Burst time is: ");  
        scanf("%d", &bt[i]);  
        temp[i] = bt[i];  
    }  
    printf("Enter the Time Quantum for the process: ");  
    scanf("%d", &quant);  
    printf("\nProcess\t  Burst Time\t  Waiting Time\t  Turnaround Time");
    for(sum=0, i = 0; y!=0;)  
    {  
    if(temp[i] <= quant && temp[i] > 0)    
    {  
        sum = sum + temp[i];  
        temp[i] = 0;  
        count=1;  
        }     
        else if(temp[i] > 0)  
        {  
            temp[i] = temp[i] - quant;  
            sum = sum + quant;    
        }  
        if(temp[i]==0 && count==1)  
        {  
            y--;   
            printf("\nP[%d]\t\t%d\t\t%d\t\t%d",i+1,bt[i],sum-at[i]-bt[i],sum-at[i]);  
            wt = wt+sum-at[i]-bt[i];  
            tat = tat+sum-at[i];  
            count =0;     
        }  
        if(i==n-1)  
        {  
            i=0;  
        }  
        else if(at[i+1]<=sum)  
        {  
            i++;  
        }  
        else  
        {  
            i=0;  
        }  
    }  
    avg_wt = wt * 1.0/n;  
    avg_tat = tat * 1.0/n;  
    printf("\nAverage Turn Around Time: %f", avg_wt);  
    printf("\nAverage Waiting Time: %f", avg_tat);  
    getch();  
}
