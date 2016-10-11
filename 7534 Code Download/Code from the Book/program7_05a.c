/* Program 7.5A Arrays and pointers taken further */
#include <stdio.h>

int main(void)
{
  char multiple[] = "another string";

  printf("\nAddress of second element: %p", &multiple[1]);
  printf("\nValue of multiple+1      : %p\n", multiple+1);
  return 0;
}

