/* Exercise 10.2 Reading monetary amounts separated by commas and spaces. */
/*
  You only need to ensure that the input format string specifies that '$',
  spaces, and commas are ignored.
*/
#include <stdio.h>

void main()
{
  double amounts[4] = {0.0};
  double total = 0.0;
  int i = 0;

   printf("Enter the four amounts:\n");
   for(i = 0 ; i<4 ; i++)
   {
     scanf("%*[ ,$]%lf", &amounts[i]);
     total += amounts[i];
   }
     
   printf("The total of the input is: $%.2lf\n", total);
}

