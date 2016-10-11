/* Program 7.1 A simple program using pointers */
#include <stdio.h>

int main(void)
{
  int number = 0;                 /* A variable of type int initialized to  0 */
  int *pointer = NULL;            /* A pointer that can point to type int     */

  number = 10;
  printf("\nnumber's address: %p", &number);            /* Output the address */
  printf("\nnumber's value: %d\n\n", number);           /* Output the value   */

  pointer = &number;              /* Store the address of number in pointer   */

  printf("pointer's address: %p", &pointer);            /* Output the address */
  printf("\npointer's size: %d bytes", sizeof(pointer)); /* Output the size   */
  printf("\npointer's value: %p", pointer);  /* Output the value (an address) */
  printf("\nvalue pointed to: %d\n", *pointer);       /* Value at the address */
  return 0;
}

