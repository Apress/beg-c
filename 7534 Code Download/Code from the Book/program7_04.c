/* Program 7.4  Arrays and pointers - A simple program*/
#include <stdio.h>

int main(void)
{
  char multiple[] = "My string";

  char *p = &multiple[0];
  printf("\nThe address of the first array element  : %p", p);

  p = multiple;
  printf("\nThe address obtained from the array name: %p\n", p);

  return 0;
}

