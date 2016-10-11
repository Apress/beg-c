/* Exercise 8.1 A function to calculate an average */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

double average(double data[], int count)
{
  double sum = 0.0;
  for(int i = 0 ; i<count ; sum += data[i++])
    ;
  return sum/count;
}

#define CAPACITY_INCREMENT 6  /* Increment in the capacity for data values */

int main(void)
{
   double *data = NULL;      /* Pointer to array of data values          */
   double *newdata = NULL;   /* Pointer to new array of data values      */
   double *averages = NULL;  /* Pointer to array of averages             */
   int count = 0;            /* Number of data values                    */
   int capacity = 0;         /* Number of data values that can be stored */
   char answer = 'n';

   do
   {
     if(count == capacity)
     {
       capacity += CAPACITY_INCREMENT;
       /* Create new array of pointers */
       newdata = (double*)malloc(capacity*sizeof(double));
       /* Create an array of values of type double for each new day and store the address */
       if(data)
       {
         /* Copy the existing values to the new array */
         for(int i = 0 ; i<count ; i++)
           newdata[i] = data[i];
         free(data);          /* Free memory for the old array of pointers */
       }
       data = newdata;        /* copy the address of the new array of pointers */
       newdata = NULL;        /* Reset the pointer                             */
     }

     printf("Enter a data value: ");
     scanf(" %lf", data+count++);
     printf("Do you want to enter another (y or n)? ");
     scanf(" %c", &answer);
   } while(tolower(answer) != 'n');

   printf("\nThe  average of thew values you entered is %10.2lf\n", average(data, count));
   free(data);
   return 0;
}

