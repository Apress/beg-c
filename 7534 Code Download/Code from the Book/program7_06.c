/* Program 7.6 Different types of arrays */
#include <stdio.h>

int main(void)
{
  long multiple[] = {15L, 25L, 35L, 45L};
  long * p = multiple;

  for(int i = 0 ; i<sizeof(multiple)/sizeof(multiple[0]) ; i++)
    printf("\naddress p+%d (&multiple[%d]): %d   *(p+%d) value: %d",
                        i,           i,    p+i,      i,      *(p+i));
  printf("\n    Type long occupies: %d bytes\n", sizeof(long));
  return 0;
}

