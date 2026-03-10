#include<stdio.h>

int main()
{
    int n,i,time=0,completed=0,highest,idx;

    printf("Enter number of processes: ");
    scanf("%d",&n);

    int pid[n],at[n],bt[n],pri[n];
    int rt[n],ct[n],tat[n],wt[n];

    for(i=0;i<n;i++)
    {
        pid[i]=i+1;

        printf("\nEnter Arrival Time of P%d: ",i+1);
        scanf("%d",&at[i]);

        printf("Enter Burst Time of P%d: ",i+1);
        scanf("%d",&bt[i]);

        printf("Enter Priority of P%d: ",i+1);
        scanf("%d",&pri[i]);

        rt[i]=bt[i];
    }

    printf("\nGantt Chart:\n");

    while(completed<n)
    {
        highest=9999;
        idx=-1;

        for(i=0;i<n;i++)
        {
            if(at[i]<=time && rt[i]>0 && pri[i]<highest)
            {
                highest=pri[i];
                idx=i;
            }
        }

        if(idx!=-1)
        {
            printf("|P%d",pid[idx]);

            rt[idx]--;
            time++;

            if(rt[idx]==0)
            {
                completed++;
                ct[idx]=time;
                tat[idx]=ct[idx]-at[idx];
                wt[idx]=tat[idx]-bt[idx];
            }
        }
        else
        {
            time++;
        }
    }

    printf("|\n\n");

    printf("PID\tAT\tBT\tPRI\tCT\tTAT\tWT\n");

    for(i=0;i<n;i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
        pid[i],at[i],bt[i],pri[i],ct[i],tat[i],wt[i]);
    }

    return 0;
}
