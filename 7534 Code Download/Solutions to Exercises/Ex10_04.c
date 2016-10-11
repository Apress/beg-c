/* Exercise 10.4 A function to read a string terminated by an arbitrary character. */
#include <stdio.h>
#include <string.h>

#define MAX_SIZE     100
#define STRING_COUNT   5

char* getString(char *buffer, char end_char);

void main()
{
  char buffer[MAX_SIZE] = {0};
  int i = 0;
  for(i = 0 ; i<STRING_COUNT ; i++)
  {
    printf("Enter a string terminated by a semi-colon:\n");
    getString(buffer, ';');
    printf("The string you entered was:\n%s\n", buffer);
  }
}

char* getString(char *buffer, char end_char)
{
  size_t i = 0;
  /* Read a character until end_char is entered */
  while((buffer[i++] = getchar()) != end_char)
    ;
  buffer[i-1] = '\0';  /* Overwrite end_char with string terminator */
  return buffer;
}
