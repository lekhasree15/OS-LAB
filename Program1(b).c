#include <stdio.h>

struct Process {
    int pid, at, bt, rt, ct, wt, tat, completed;
};

int main() {
    int n, choice;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    for(int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("\nProcess %d\n", i + 1);
        printf("Arrival Time: ");
        scanf("%d", &p[i].at);
        printf("Burst Time: ");
        scanf("%d", &p[i].bt);
        p[i].rt = p[i].bt;
        p[i].completed = 0;
    }

    printf("\n1. SJF Non-Preemptive");
    printf("\n2. SJF Preemptive (SRTF)");
    printf("\nEnter choice: ");
    scanf("%d", &choice);

    int time = 0, completed = 0;
    float total_wt = 0, total_tat = 0;

    switch(choice) {

        case 1:
            while(completed < n) {
                int idx = -1;
                int min_bt = 9999;

                for(int i = 0; i < n; i++) {
                    if(p[i].at <= time && p[i].completed == 0) {
                        if(p[i].bt < min_bt) {
                            min_bt = p[i].bt;
                            idx = i;
                        }
                    }
                }

                if(idx != -1) {
                    time += p[idx].bt;
                    p[idx].ct = time;
                    p[idx].tat = p[idx].ct - p[idx].at;
                    p[idx].wt = p[idx].tat - p[idx].bt;

                    p[idx].completed = 1;
                    completed++;

                    total_wt += p[idx].wt;
                    total_tat += p[idx].tat;
                } else {
                    time++;
                }
            }
            break;

        case 2:
            while(completed < n) {
                int idx = -1;
                int min_rt = 9999;

                for(int i = 0; i < n; i++) {
                    if(p[i].at <= time && p[i].rt > 0) {
                        if(p[i].rt < min_rt) {
                            min_rt = p[i].rt;
                            idx = i;
                        }
                    }
                }

                if(idx != -1) {
                    p[idx].rt--;
                    time++;

                    if(p[idx].rt == 0) {
                        p[idx].ct = time;
                        p[idx].tat = p[idx].ct - p[idx].at;
                        p[idx].wt = p[idx].tat - p[idx].bt;

                        completed++;
                        total_wt += p[idx].wt;
                        total_tat += p[idx].tat;
                    }
                } else {
                    time++;
                }
            }
            break;

        default:
            printf("Invalid Choice!");
            return 0;
    }

    printf("\nPID\tAT\tBT\tCT\tWT\tTAT\n");
    for(int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt,
               p[i].ct, p[i].wt, p[i].tat);
    }

    printf("\nAverage Waiting Time = %.2f", total_wt/n);
    printf("\nAverage Turnaround Time = %.2f\n", total_tat/n);

    return 0;
}
