/* Program 8.7 A function to increase your salary */
#include <stdio.h>

long *IncomePlus(long* pPay);          /* Prototype for increase function */

int main(void)
{
  long your_pay = 30000L;             /* Starting salary                 */
  long *pold_pay = &your_pay;         /* Pointer to pay value            */
  long *pnew_pay = NULL;              /* Pointer to hold return value    */

  pnew_pay = IncomePlus( pold_pay );
  printf("\nOld pay = $%ld", *pold_pay);
  printf("   New pay = $%ld\n", *pnew_pay);
  return 0;
}

/* Definition of function to increment pay */
long *IncomePlus(long *pPay)
{
  *pPay += 10000L;                    /* Increment the value for pay      */
  return pPay;                        /* Return the address               */
}

