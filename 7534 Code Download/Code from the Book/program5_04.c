/* Program 5.4 Reusing the numbers stored */
#include <stdio.h>

int main(void)
{
  int numbers[10];                     /* Array storing 10 values     */
  int count = 10;                      /* Number of values to be read */
  long sum = 0L;                       /* Sum of the numbers          */
  float average = 0.0f;                /* Average of the numbers      */

  printf("\nEnter the 10 numbers:\n");        /* Prompt for the input */

  /* Read the ten numbers to be averaged */
  for(int i = 0; i < count; i++)
  {
    printf("%2d> ",i+1);
    scanf("%d", &numbers[i]);          /* Read a number */
    sum += numbers[i];                 /* Add it to sum */
  }

  average = (float)sum/count;          /* Calculate the average */

  for(int i = 0; i < count; i++)
    printf("\nGrade Number %d was %d", i+1, numbers[i]);

  printf("\nAverage of the ten numbers entered is: %f\n", average);
  return 0;
}

