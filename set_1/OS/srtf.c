#include <stdio.h>
#include <limits.h>
int main()
{
    int pro[100], at[100], bt[100], wt[100], ct[100], tat[100], remaining_bt[100], rt[100], n;

    int t = 0, completed = 0;
    float total_tat = 0, total_wt = 0;
    printf("no of process");
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        pro[i] = i + 1;
        printf("Enter the at and bt for process %d", pro[i]);
        scanf("%d %d", &at[i], &bt[i]);
        remaining_bt[i] = bt[i];
        rt[i] = at[i];
    }

    while (completed < n)
    {
        int idx = -1;
        int min = INT_MAX;
        for (int i = 0; i < n; i++)
        {
            if (at[i] <= t && remaining_bt[i] > 0 && remaining_bt[i] < min)
            {
                min = remaining_bt[i];
                idx = i;
            }
        }
        if (idx == -1)
        {
            t++;
            continue;
        }
        remaining_bt[idx]--;
        t++;
        if (remaining_bt[idx] == 0)
        {
            ct[idx] = t;
            tat[idx] = ct[idx] - at[idx];
            wt[idx] = tat[idx] - bt[idx];
            total_wt += wt[idx];
            total_tat += tat[idx];
            completed++;
        }
    }
    printf("\n process \t at \t bt \t ct \t tat \t wt \n");
    for (int i = 0; i < n; i++)
    {
        printf("%d \t %d \t %d \t %d \t %d \t %d \t \n", pro[i], at[i], bt[i], ct[i], tat[i], wt[i]);
    }
    printf("avg tat %f", total_tat / n);
    printf("avg wt %f", total_wt / n);

    return 0;
}