#include <stdio.h>

int main()
{
    int pro[100], at[100], bt[100], wt[100], ct[100], tat[100], n;

    int t = 0, completed = 0;
    float avg_tat = 0, avg_wt = 0;
    printf("no of process: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        pro[i] = i + 1;
        printf("Enter the at and bt for process %d: ", pro[i]);
        scanf("%d %d", &at[i], &bt[i]);
    }

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (at[j] > at[j + 1])
            {
                int t = at[j];
                at[j] = at[j + 1];
                at[j + 1] = t;

                t = bt[j];
                bt[j] = bt[j + 1];
                bt[j + 1] = t;

                t = pro[j];
                pro[j] = pro[j + 1];
                pro[j + 1] = t;
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        if (t < at[i])
            t = at[i];

        ct[i] = t + bt[i];
        t = ct[i];
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
    }

    printf("\n process \t at \t bt \t ct \t tat \t wt \n");
    for (int i = 0; i < n; i++)
    {
        printf("\t%d \t %d \t %d \t %d \t %d \t %d \t \n", pro[i], at[i], bt[i], ct[i], tat[i], wt[i]);
    }
    for (int i = 0; i < n; i++)
    {
        avg_tat += tat[i];
        avg_wt += wt[i];
    }
    printf("\n\navg tat %f", avg_tat / n);
    printf("\navg wt %f", avg_wt / n);

    return 0;
}