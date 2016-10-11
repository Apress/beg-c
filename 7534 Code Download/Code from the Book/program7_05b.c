/* Program 7.5B Arrays and pointers taken further */
#include <stdio.h>

int main(void)
{
  char multiple[] = "another string";

  printf(" first element: %p\n", multiple);
  printf("second element: %p\n", multiple + 1);
  printf(" third element: %p\n", multiple + 2);
  return 0;
}

