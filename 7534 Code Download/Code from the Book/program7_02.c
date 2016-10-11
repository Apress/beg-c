/* Program 7.2  What's the pointer */
#include <stdio.h>

int main(void)
{
  long num1 = 0;
  long num2 = 0;
  long *pnum = NULL;

  pnum = &num1;                                 /* Get address of num1       */
  *pnum = 2;                                    /* Set num1 to 2             */
  ++num2;                                       /* Increment num2            */
  num2 += *pnum;                                /* Add num1 to num2          */

  pnum = &num2;                                 /* Get address of num2       */
  ++*pnum;                                      /* Increment num2 indirectly */

  printf ("\nnum1 = %ld  num2 = %ld  *pnum = %ld  *pnum + num2 = %ld\n",
                                      num1, num2, *pnum, *pnum + num2);
  return 0;
}

