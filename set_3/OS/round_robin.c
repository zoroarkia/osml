#include <stdio.h>
#include <limits.h>

int main()
{
    int pro[100], at[100], bt[100], wt[100], ct[100], tat[100], rt[100];
    int inQueue[100] = {0}, isCompleted[100] = {0};
    int queue[100], front = 0, rear = 0;
    int n, tq, t = 0, done = 0;
    float total_tat = 0, total_wt = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter time quantum: ");
    scanf("%d", &tq);

    for (int i = 0; i < n; i++)
    {
        pro[i] = i + 1;
        printf("Enter AT and BT for Process %d: ", pro[i]);
        scanf("%d %d", &at[i], &bt[i]);
        rt[i] = bt[i];
    }

    // Start by adding the first arriving process
    int current_time = 0;
    for (int i = 0; i < n; i++)
    {
        if (at[i] == 0)
        {
            queue[rear++] = i;
            inQueue[i] = 1;
        }
    }

    while (done < n)
    {
        if (front == rear)
        {
            // Idle CPU, jump to next available arrival time
            for (int i = 0; i < n; i++)
            {
                if (!isCompleted[i] && !inQueue[i])
                {
                    current_time = at[i];
                    queue[rear++] = i;
                    inQueue[i] = 1;
                    break;
                }
            }
            continue;
        }

        int idx = queue[front++];

        int execTime = (rt[idx] >= tq) ? tq : rt[idx];
        rt[idx] -= execTime;
        current_time += execTime;

        // Add newly arrived processes during this time
        for (int i = 0; i < n; i++)
        {
            if (at[i] <= current_time && !inQueue[i] && !isCompleted[i])
            {
                queue[rear++] = i;
                inQueue[i] = 1;
            }
        }

        if (rt[idx] > 0)
        {
            queue[rear++] = idx; // Not finished, requeue
        }
        else
        {
            ct[idx] = current_time;
            tat[idx] = ct[idx] - at[idx];
            wt[idx] = tat[idx] - bt[idx];
            total_tat += tat[idx];
            total_wt += wt[idx];
            isCompleted[idx] = 1;
            done++;
        }
    }

    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", pro[i], at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    printf("\nAverage TAT: %.2f\n", total_tat / n);
    printf("Average WT : %.2f\n", total_wt / n);
    return 0;
}