/*Exercise 5.2 Summing 100 data values */
#include <stdio.h>

int main(void)
{
  double data[100];                    /* Stores data values        */
  double sum = 0.0;                    /* Stores sum of reciprocals */
  double sign = 1.0;


  for(int i = 1 ; i<=100 ; i++)
    data[i-1] = 1.0/(2*i*(2*i+1)*(2*i+2));

  for(int i = 0 ; i<100 ; i++)
  {
    sum += sign*data[i];
    sign = -sign;
  }
  /* Output the result */
  printf("\nThe result is %.4lf\n", 4.0*sum+3);
  printf("\nThe result is an approximation of pi, isn't that interesting?");
	return 0;
	}

