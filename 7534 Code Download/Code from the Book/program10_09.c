/* Program 10.9 Variations on a single integer */
#include <stdio.h>

int main(void)
{
  int k = 678;

  printf("%%d   %%o   %%x   %%X");  /* Display format as heading */
  printf("\n%d  %o  %x  %X", k, k, k, k );      /* Display values */

  /* Display format as heading then display the values */
  printf("\n\n%%8d       %%-8d      %%+8d      %%08d      %%-+8d");
  printf("\n%8d  %-8d  %-+8d  %08d  %-+8d\n", k, k, k, k, k );
  return 0;
}

