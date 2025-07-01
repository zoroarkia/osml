#include <stdio.h>

int main()
{
    int i, j, k, l, n, m;
    int p[20];  // reference string
    int fr[10]; // frames
    int fs[10]; // usage flags
    int flag1, flag2;
    int pf = 0; // page fault count
    int index = 0;
    float pr;

    printf("Enter the length of the reference string: ");
    scanf("%d", &n);

    printf("Enter the reference string: ");
    for (i = 0; i < n; i++)
        scanf("%d", &p[i]);

    printf("Enter number of frames: ");
    scanf("%d", &m);

    for (i = 0; i < m; i++)
        fr[i] = -1; // initialize frames as empty

    for (j = 0; j < n; j++)
    {
        flag1 = 0; // page found flag
        flag2 = 0; // empty frame found flag

        // Check if page is already in frames
        for (i = 0; i < m; i++)
        {
            if (fr[i] == p[j])
            {
                flag1 = 1;
                flag2 = 1;
                break;
            }
        }

        // If page not found, check for empty frame
        if (flag1 == 0)
        {
            for (i = 0; i < m; i++)
            {
                if (fr[i] == -1)
                {
                    fr[i] = p[j];
                    flag2 = 1;
                    pf++; // page fault
                    break;
                }
            }
        }

        // If page not found and no empty frame → replace LRU page
        if (flag2 == 0)
        {
            // Initialize usage flags to 0
            for (i = 0; i < m; i++)
                fs[i] = 0;

            // Check recent usage of pages in frames by looking back in reference string
            k = j - 1;
            l = 0;
            while (l < m && k >= 0)
            {
                for (i = 0; i < m; i++)
                {
                    if (fr[i] == p[k] && fs[i] == 0)
                    {
                        fs[i] = 1; // mark page as recently used
                        l++;
                        break;
                    }
                }
                k--;
            }

            // Find frame whose page was least recently used (fs[i] == 0)
            for (i = 0; i < m; i++)
            {
                if (fs[i] == 0)
                {
                    index = i;
                    break;
                }
            }

            fr[index] = p[j]; // replace LRU page with new page
            pf++;             // page fault
        }

        // Display frames after each page request
        for (i = 0; i < m; i++)
            printf("%d\t", fr[i]);
        printf("\n");
    }

    printf("Number of page faults: %d\n", pf);
    pr = ((float)pf / n) * 100;
    printf("Page fault rate = %.2f%%\n", pr);

    return 0;
}