/* Program 8.4 The change that doesn't  */
#include <stdio.h>

int change(int number);                /* Function prototype              */

int main(void)
{
  int number = 10;                    /* Starting Value                  */
  int result = 0;                     /* Place to put the returned value */

  result = change(number);
  printf("\nIn main, result = %d\tnumber = %d", result, number);
  return 0;
}

/* Definition of the function change() */
int change(int number)
{
  number = 2 * number;
  printf("\nIn function change, number = %d\n", number);
  return number;
}

