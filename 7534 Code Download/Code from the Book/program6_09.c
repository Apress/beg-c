/* Program 6.9 Finding occurrences of one string in another  */
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
  char text[100];                /* Input buffer for string to be searched */
  char substring[40];            /* Input buffer for string sought         */

  printf("\nEnter the string to be searched(less than 100 characters):\n");
  fgets(text, sizeof(text), stdin);

  printf("\nEnter the string sought (less than 40 characters ):\n");
  fgets(substring, sizeof(substring), stdin);

  /* overwrite the newline character in each string */
  text[strlen(text)-1] = '\0';
  substring[strlen(substring)-1] = '\0';

  printf("\nFirst string entered:\n%s\n", text);
  printf("\nSecond string entered:\n%s\n", substring);

  /* Convert both strings to uppercase. */
  for(int i = 0 ; (text[i] = toupper(text[i])) ; i++);
  for(int i = 0 ; (substring[i] = toupper(substring[i])) ; i++);

   printf("\nThe second string %s found in the first.",
              ((strstr(text, substring) == NULL) ? "was not" : "was"));
  return 0;
}

