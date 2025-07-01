#include <stdio.h>

int main()
{
  int page_size, num_pages;
  int page_table[50];
  int i;
  int page_number, offset;
  int frame_number, physical_address;

  printf("Enter the page size (in bytes): ");
  scanf("%d", &page_size);

  printf("Enter number of pages in page table: ");
  scanf("%d", &num_pages);

  printf("Enter frame number of each page (page 0 to page %d):\n", num_pages - 1);
  for (i = 0; i < num_pages; i++)
  {
    printf("Frame number for page %d: ", i);
    scanf("%d", &page_table[i]);
  }

  printf("Enter logical address (page number and offset): ");
  scanf("%d %d", &page_number, &offset);

  if (page_number < 0 || page_number >= num_pages)
  {
    printf("Invalid page number.\n");
    return 1;
  }

  if (offset < 0 || offset >= page_size)
  {
    printf("Invalid offset.\n");
    return 1;
  }

  frame_number = page_table[page_number];
  physical_address = (frame_number * page_size) + offset;

  printf("Frame Number = %d\n", frame_number);
  printf("Physical Address = %d\n", physical_address);

  return 0;
}