/* Exercise 7.1 Calculating a floating-point average using pointers */
/*********************************************************************
 * In this solution I allocate a some memory and when it is full     *
 * allocate a new, larger amount of memory and copy the contents of  *
 * the old memory to the new. I then free the old memory. This       *
 * process repeats as often as necessary.                            *
**********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(void)
{
  double *values = NULL;     /* Pointer to memory holding data values       */
  double *temp = NULL;       /* Pointer to newly allocated memory           */
  double sum = 0.0;          /* Sum of values                               */
  int capacity = 0;          /* Maximum number of values that can be stored */
  int increment = 5;         /* Capacity increment for dynamic allocation   */
  int count = 0;             /* Number of values read                       */
  char answer = 'n';

  do
  {
    if(count == capacity)    /* Check if there is spare memory */
    {
      capacity += increment; /* Increase the capacity of memory by increment */
      temp = (double*)malloc((capacity)*sizeof(double)); /* and allocate it  */
      if(!temp)              /* If memory was not allocated */
      {                      /* Output a message  and end   */
        printf("Memory allocation failed. Terminating program.");
        exit(1);
      }
      if(!values)            /* Are there any values?                  */
        values = temp;       /* No - so just copy address of new memory */
      else                   /* Yes - so copy data from old to new      */
      {
        for(int i = 0 ; i<count ; i++)
          *(temp + i) = *(values + i);
        free(values);        /* Free the old memory */
        values = temp;       /* Copy address of new */
      }
      temp = NULL;           /* Reset pointer       */
    }

    printf("Enter a value: ");
    scanf("%lf", values+count++);

    printf("Do you want to enter another(y or n)? ");
    scanf(" %c", &answer);
  }while(tolower(answer) == 'y');

  /* Now sum the values */
  for(int i = 0 ; i<count ; i++)
    sum += *(values+i);

  /* Output the average */
  printf("\n The average of the the values you entered is %.2lf.\n", sum/count);
  free(values);     /* We are done - so free the memory */
  return 0;
}

