#include <stdio.h>
#include <limits.h>

int main()
{
    int pro[100], at[100], bt[100], wt[100], ct[100], tat[100], pr[100], rt[100], completed[100], n;

    int t = 0, done = 0;
    float total_tat = 0, total_wt = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        pro[i] = i + 1;
        printf("Enter AT, BT, Priority for Process %d: ", pro[i]);
        scanf("%d %d %d", &at[i], &bt[i], &pr[i]);
        rt[i] = bt[i]; // remaining time should be burst time
        completed[i] = 0;
    }

    while (done < n)
    {
        int idx = -1;
        int high_priority = INT_MAX;

        for (int i = 0; i < n; i++)
        {
            if (at[i] <= t && !completed[i] && rt[i] > 0 && pr[i] < high_priority)
            {
                high_priority = pr[i];
                idx = i;
            }
        }

        if (idx != -1)
        {
            rt[idx]--;
            t++;

            if (rt[idx] == 0)
            {
                completed[idx] = 1;
                done++;
                ct[idx] = t;
                tat[idx] = ct[idx] - at[idx];
                wt[idx] = tat[idx] - bt[idx];
                total_tat += tat[idx];
                total_wt += wt[idx];
            }
        }
        else
        {
            t++; // no process is ready, so just increment time
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