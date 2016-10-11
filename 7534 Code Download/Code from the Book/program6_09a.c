/* Program 6.9A Finding occurrences of one wide character string in another  */
#include <stdio.h>
#include <wchar.h>

int main(void)
{
  wchar_t text[100];             /* Input buffer for string to be searched */
  wchar_t substring[40];         /* Input buffer for string sought         */

  printf("\nEnter the string to be searched(less than 100 characters):\n");
  fgetws(text, 100, stdin);
  printf("\nEnter the string sought (less than 40 characters ):\n");
  fgetws(substring, 40, stdin);

  /* overwrite the newline character in each string */
  text[wcslen(text)-1] = L'\0';
  substring[wcslen(substring)-1] = L'\0';

  printf("\nFirst string entered:\n%S\n", text);
  printf("\nSecond string entered:\n%S\n", substring);

  /* Convert both strings to uppercase. */
  for(int i = 0 ; (text[i] = towupper(text[i])) ; i++);
  for(int i = 0 ; (substring[i] = towupper(substring[i])) ; i++);

    printf("\nThe second string %s found in the first.",
              ((wcsstr(text, substring) == NULL) ? "was not" : "was"));
  return 0;
}

