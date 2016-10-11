/*Exercise 5.1 Summing reciprocals of five values */
#include <stdio.h>

int main(void)
{
  const int nValues = 5;               /* Number of data values     */
  double data[nValues];                /* Stores data values        */
  double reciprocals[nValues];
  double sum = 0.0;                    /* Stores sum of reciprocals */

  printf("Enter five values separated by spaces:\n");
  for(int i = 0 ; i<nValues ; i++)
    scanf("%lf", &data[i]);

  printf("\nYou entered the values:\n");
  for(int i = 0 ; i<nValues ; i++)
    printf("%10.2lf", data[i]);
  printf("\n");

  for(int i = 0 ; i<nValues ; i++)
    reciprocals[i] = 1.0/data[i];

  for(int i = 0 ; i<nValues ; i++)
  {
    sum += reciprocals[i];              /* Accumulate sum of reciprocals */
    if(i>0)
      printf(" + ");
    printf("1/%.2lf", data[i]);
  }
  printf(" = %lf\n", sum);
  return 0;
}

