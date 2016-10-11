/* Program 4.9 Sums of integers step-by-step */
#include <stdio.h>

int main(void)
{
  long sum = 0L;                       /* Stores the sum of integers      */
  int count = 0;                       /* Number of sums to be calculated */

  /* Prompt for, and read the input count */
  printf("\nEnter the number of integers you want to sum: ");
  scanf(" %d", &count);

  for(int i = 1 ; i <= count ; i++ )
  {
    sum = 0L;                          /* Initialize sum for the inner loop */

    /* Calculate sum of integers from 1 to i */
    for(int j = 1 ; j <= i ; j++ )
      sum += j;

    printf("\n%d\t%ld", i, sum);       /* Output sum of 1 to i */
  }
  return 0;
}

