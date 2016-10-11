/* Program 4.8 While programming and summing integers */
#include <stdio.h>

int main(void)
{
  long sum = 0L;                       /* The sum of the integers            */
  int i = 1;                           /* Indexes through the integers       */
  int count = 0;                       /* The count of integers to be summed */

  /* Get the count of the number of integers to sum */
  printf("\nEnter the number of integers you want to sum: ");
  scanf(" %d", &count);

  /* Sum the integers from 1 to count */
  while(i <= count)
    sum += i++;

  printf("Total of the first %d numbers is %ld\n", count, sum);
  return 0;
}

