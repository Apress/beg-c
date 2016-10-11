/* Program 10.11 Outputting character data */
#include <stdio.h>
#include <wchar.h>
#include <limits.h>
#include <ctype.h>
#include <wctype.h>

int main(void)
{
  int count = 0;
  char ch = 0;
  printf("\nThe printable characters are the following:\n");

  /* Iterate over all values of type char */
  for(int code = 0 ; code <= CHAR_MAX ; code++)
  {
    ch = (char)code;
    if(isprint(ch))
    {
      if(count++ % 32 == 0)
        printf("\n");
      printf("%c", ch);
    }
  }

  /* Use wprintf() to output wide characters */
  count = 0;
  wchar_t wch = 0;
  wprintf(L"\n\nThe alphabetic characters and their codes are the following:\n");

  /* Iterate over the lowercase wide character letters */
  for(wchar_t wch = L'a' ; wch <= L'z' ; wch++)
  {
    if(count++ % 3 == 0)
      wprintf(L"\n");

    wprintf(L" %lc    %#x    %lc    %#x", wch, (long)wch, towupper(wch),
                                                        (long)towupper(wch));
  }
  return 0;
}

