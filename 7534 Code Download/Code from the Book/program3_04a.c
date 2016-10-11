/* Program 3.4A Converting uppercase to lowercase using wide characters */
#include <stdio.h>

int main(void)
{
  wchar_t letter = 0;                     /* Stores a character               */

  printf("Enter an uppercase letter:");   /* Prompt for input                 */
  scanf("%lc", &letter);                  /* Read a character                 */

  /* Check whether the input is uppercase */
  if(letter >= L'A')                      /* Is it A or greater?              */
    if (letter <= L'Z')                   /* and is it Z or lower?            */
    {                                     /* It is uppercase                  */
      letter = letter - L'A'+ L'a';       /* Convert from upper- to lowercase */
      printf("You entered an uppercase %lc\n", letter);
    }
    else                                  /* It is not an uppercase letter    */
      printf("Try using the shift key, Bud! I want a capital letter.\n");
  return 0;
}

