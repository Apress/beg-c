/* Program 10.6 Reading a string with gets() */
#include <stdio.h>
#include <string.h>          /* For strlen() in the alternate code */

int main(void)
{
  char initial[2] = {0};
  char name[80] = {0};

  printf("Enter your first initial: ");
  gets(initial);
  printf("Enter your name: " );
  gets(name);

/* A safer version of the 4 lines above is as follows:*/
/*
  printf("Enter your first initial: ");
  fgets(initial, sizeof(initial), stdin);
  fflush(stdin);
  printf("Enter your name: " );
  fgets(name, sizeof(name), stdin);
  size_t length = strlen(name);
  name[length-1] = name[length];
*/

  if(initial[0] != name[0])
    printf("\n%s,you got your initial wrong.\n", name);
  else
    printf("\nHi, %s. Your initial is correct. Well done!\n", name);
  return 0;
}

