/* Program 10.4 Reading hexadecimal and octal values */
#include <stdio.h>

int main(void)
{
  int i = 0;
  int j = 0;
  int k = 0;
  int n = 0;

  printf("Input:\n");
  n = scanf(" %d %x %o", &i , &j, &k );

  printf("\nOutput:\n");
  printf("%d values read.", n);
  printf("\ni = %d   j = %d   k = %d\n", i, j, k );

/*  Alternative to statement above
  printf("\ni = %x   j = %X   k = %d\n", i, j, k );
*/

  return 0;
}

