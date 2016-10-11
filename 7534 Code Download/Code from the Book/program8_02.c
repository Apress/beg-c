/* Program 8.2 More scope in this one */
#include <stdio.h>
int main(void)
{
  int count = 0;                                /* Declared in outer block */
  do
  {
    int count = 0;                /* This is another variable called count */
    ++count;                      /* this applies to inner count           */
    printf("\ncount = %d ", count);
  }
  while( ++count <= 8 );                    /* This works with outer count */

  /* Inner count is dead, this is outer */
  printf("\ncount = %d\n", count);
  return 0;
}

