#include <stdio.h>

int main()
{
  int n, m, i, j, k;
  int p[50];  // reference string
  int fr[10]; // frames
  int pf = 0; // page fault count
  int flag1, flag2;
  int index;
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

  for (i = 0; i < n; i++)
  {
    flag1 = 0; // page found flag
    flag2 = 0; // empty frame found flag

    // Check if page is already in frames
    for (j = 0; j < m; j++)
    {
      if (fr[j] == p[i])
      {
        flag1 = 1;
        flag2 = 1;
        break;
      }
    }

    // If page not found in frames
    if (flag1 == 0)
    {
      // Check for empty frame
      for (j = 0; j < m; j++)
      {
        if (fr[j] == -1)
        {
          fr[j] = p[i];
          pf++; // page fault
          flag2 = 1;
          break;
        }
      }
    }

    // If page not found and no empty frame, replace page optimally
    if (flag1 == 0 && flag2 == 0)
    {
      int farthest = i;
      index = -1;

      // Find the page in frames that will NOT be used for the longest time in future
      for (j = 0; j < m; j++)
      {
        int found = 0;
        for (k = i + 1; k < n; k++)
        {
          if (fr[j] == p[k])
          {
            if (k > farthest)
            {
              farthest = k;
              index = j;
            }
            found = 1;
            break;
          }
        }
        // If page not found in future, this is best candidate to replace
        if (found == 0)
        {
          index = j;
          break;
        }
      }

      // Replace page at index
      fr[index] = p[i];
      pf++;
    }

    // Display current frames
    for (j = 0; j < m; j++)
      printf("%d\t", fr[j]);
    printf("\n");
  }

  printf("Number of page faults: %d\n", pf);
  pr = ((float)pf / n) * 100;
  printf("Page fault rate = %.2f%%\n", pr);

  return 0;
}