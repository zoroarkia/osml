#include <stdio.h>

int fr[20], m; // frames array and number of frames

void display()
{
  int i; // declare loop variable at the top
  for (i = 0; i < m; i++)
    printf("%d\t", fr[i]);
  printf("\n");
}

int main()
{
  int n, i, j; // declare all variables at top
  int p[50];   // page references
  int pf = 0;  // page fault count
  int top = 0; // pointer for FIFO replacement
  int flag1, flag2;
  float pr;

  printf("Enter the length of the reference string: ");
  scanf("%d", &n);

  printf("Enter the reference string: ");
  for (i = 0; i < n; i++)
  {
    scanf("%d", &p[i]);
  }

  printf("Enter number of frames: ");
  scanf("%d", &m);

  // Initialize all frames as empty
  for (i = 0; i < m; i++)
  {
    fr[i] = -1;
  }

  printf("\nPage frames after each page request:\n");

  for (j = 0; j < n; j++)
  {
    flag1 = 0; // page found flag
    flag2 = 0; // empty frame found flag

    // Check if page is already in frames
    for (i = 0; i < m; i++)
    {
      if (fr[i] == p[j])
      {
        flag1 = 1; // page hit
        break;
      }
    }

    // If page not found in frames
    if (flag1 == 0)
    {
      // Check if there is any empty frame
      for (i = 0; i < m; i++)
      {
        if (fr[i] == -1)
        {
          fr[i] = p[j];
          pf++;      // page fault occurs
          flag2 = 1; // page placed in empty frame
          break;
        }
      }
    }

    // If page not found and no empty frame, replace page using FIFO
    if (flag1 == 0 && flag2 == 0)
    {
      fr[top] = p[j];
      top = (top + 1) % m; // circular increment of pointer
      pf++;                // page fault occurs
    }

    display();
  }

  printf("\nTotal Page Faults = %d\n", pf);
  pr = ((float)pf / n) * 100;
  printf("Page Fault Rate = %.2f%%\n", pr);

  return 0;
}