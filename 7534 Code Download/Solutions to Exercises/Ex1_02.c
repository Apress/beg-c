/* Exercise 1.2 Output a name and address in a single statement */
#include <stdio.h>

int main(void)
{
  /* The compiler will automatically join strings together into
     a single string when they immediately follow one another   */
  printf("\nGeorge Washington"
         "\n3200 George Washington Memorial Parkway"
         "\nMount Vernon\nVirginia 22121\n");
  return 0;
}
