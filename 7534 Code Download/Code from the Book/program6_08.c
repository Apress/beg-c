/* Program 6.8 Testing characters in a string */
#include <stdio.h>
#include <ctype.h>

int main(void)
{
  char buffer[80];               /* Input buffer               */
  int i = 0;                     /* Buffer index               */
  int num_letters = 0;           /* Number of letters in input */
  int num_digits = 0;            /* Number of digits in input  */

  printf("\nEnter an interesting string of less than 80 characters:\n");
  gets(buffer);                  /* Read a string into buffer  */


  while(buffer[i] != '\0')
  {
    if(isalpha(buffer[i]))
      num_letters++;             /* Increment letter count     */
    if(isdigit(buffer[i++]))
      num_digits++;              /* Increment digit count      */
  }
  printf("\nYour string contained %d letters and %d digits.\n",
                                              num_letters, num_digits);
  return 0;
}

