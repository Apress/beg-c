/*Exercise 5.3 Handling monetary values as integers */
#include <stdio.h>

int main(void)
{
  float amounts[5];                     /* Stores data values        */
  long dollars[5];
  long cents[5];

  printf("Enter five monetary values separated by spaces:\n");
  for(int i = 0 ; i<5 ; i++)
    scanf("%f", &amounts[i]);

  for(int i = 0 ; i<5 ; i++)
  {
    dollars[i] = (long)amounts[i];
    cents[i] = (long)(100.0*(amounts[i]-dollars[i]));
  }

  printf("\n");
  for(int i = 0 ; i<5 ; i++)
    printf("  $%d.%02d", dollars[i], cents[i]);

  printf("\n");
  return 0;
}

