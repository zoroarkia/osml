#include <stdio.h>
#include <string.h>
#define SIZE 20

int disk[SIZE] = {0};        // 0=free, 1=allocated
int next[SIZE];              // next block pointer
char files[SIZE][20] = {""}; // file names

void init()
{
    for (int i = 0; i < SIZE; i++)
    {
        disk[i] = 0;
        files[i][0] = '\0';
        next[i] = -1;
    }
}

void allocate(char *name, int start, int end)
{
    if (start < 0 || end >= SIZE || start > end)
    {
        printf("Invalid range\n");
        return;
    }

    int prev = -1;
    int first = -1;

    for (int i = start; i <= end; i++)
    {
        if (disk[i] == 0)
        { // if block is free
            disk[i] = 1;
            strcpy(files[i], name);

            if (prev != -1)
            {
                next[prev] = i;
            }
            else
            {
                first = i;
            }
            prev = i;
        }
    }

    if (prev != -1)
    {
        printf("File '%s' allocated starting at block %d\n", name, first);
    }
    else
    {
        printf("No free blocks found\n");
    }
}

void show()
{
    printf("\nDisk Status:\n");
    for (int i = 0; i < SIZE; i++)
    {
        if (disk[i] == 1)
        {
            printf("%2d: X %s -> %d\n", i, files[i], next[i]);
        }
        else
        {
            printf("%2d: .\n", i);
        }
    }
}

void showFile(char *name)
{
    printf("Blocks for '%s': ", name);

    // Find first block
    int current = -1;
    for (int i = 0; i < SIZE; i++)
    {
        if (disk[i] == 1 && strcmp(files[i], name) == 0)
        {
            // Check if this is the first block
            int isFirst = 1;
            for (int j = 0; j < SIZE; j++)
            {
                if (next[j] == i)
                {
                    isFirst = 0;
                    break;
                }
            }
            if (isFirst == 1)
            {
                current = i;
                break;
            }
        }
    }

    // Follow chain
    while (current != -1)
    {
        printf("%d -> ", current);
        current = next[current];
    }
    printf("-1\n");
}

int main()
{
    init();
    int choice;
    int start, end;
    char name[20];

    while (1)
    {
        printf("\n1. Allocate 2. Show Disk 3. Show File 4. Exit\n> ");
        scanf("%d", &choice);

        if (choice == 1)
        {
            printf("File name: ");
            scanf("%s", name);
            printf("Start-End: ");
            scanf("%d %d", &start, &end);
            allocate(name, start, end);
        }
        else if (choice == 2)
        {
            show();
        }
        else if (choice == 3)
        {
            printf("File name: ");
            scanf("%s", name);
            showFile(name);
        }
        else if (choice == 4)
        {
            return 0;
        }
        else
        {
            printf("Invalid choice\n");
        }
    }
}