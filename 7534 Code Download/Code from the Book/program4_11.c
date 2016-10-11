/* Program 4.11 Reversing the digits */
#include <stdio.h>

int main(void)
{
  int number = 0;                      /* The number to be reversed */
  int rebmun = 0;                      /* The reversed number       */
  int temp = 0;                        /* Working storage           */

  /* Get the value to be reversed */
  printf("\nEnter a positive integer: ");
  scanf(" %d", &number);

  temp = number;                       /* Copy to working storage  */

  /* Reverse the number stored in temp */
  do
  {
    rebmun = 10*rebmun + temp % 10;    /* Add the rightmost digit    */
    temp = temp/10;                    /* Remove the rightmost digit */
  } while (temp);                      /* Continue while temp>0      */

  printf ("\nThe number %d reversed is  %d rebmun ehT\n",
                                               number, rebmun );
  return 0;
}

