/* Program 8.5 The change that does   */
#include <stdio.h>

int change(int* pnumber);              /* Function prototype              */

int main(void)
{
  int number = 10;                    /* Starting Value                   */
  int *pnumber = &number;             /* Pointer to starting value        */
  int result = 0;                     /* Place to put the returned value  */

  result = change(pnumber);
  printf("\nIn main, result = %d\tnumber = %d", result, number);
  return 0;
}

/* Definition of the function change() */
int change(int *pnumber)
{
  *pnumber *= 2;
  printf("\nIn function change, *pnumber = %d\n", *pnumber );
  return *pnumber;
}

