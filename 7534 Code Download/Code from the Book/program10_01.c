/* Program 10.1        Exercising formatted input */
#include <stdio.h>
#include <wchar.h>           /* For wscanf() version */

const size_t SIZE = 20;      /* Max characters in a word */

int main(void)
{
  int value_count = 0;       /* Count of input values read */
  float fp1 = 0.0;           /* Floating-point value read  */
  int i = 0;                 /* First integer read         */
  int j = 0;                 /* Second integer read        */
  char word1[SIZE] = " ";    /* First string read          */
  char word2[SIZE] = " ";    /* Second string read         */
  int byte_count = 0;        /* Count of input bytes read  */

  value_count = scanf("%f %d %d %[abcdefghijklmnopqrstuvwxyz] %*1d %s%n",
     &fp1, &i , &j, word1, word2, &byte_count);

/* Alternative 1
  value_count = scanf("%4f %d %d %*d %[abcdefghijklmnopqrstuvwxyz] %*1d %[^o]%n",
                                           &fp1, &i , &j, word1, word2, &byte_count);
*/


/* Alternative 2
  value_count = scanf("%4f %4d %d %*d %[abcdefghijklmnopqrstuvwxyz] %*1d %[^o]%n",
                                           &fp1, &i , &j, word1, word2, &byte_count);
*/

/* You could also use wscanf() to read the data, reading the two strings
   as wide-character strings.

  wchar_t wword1[SIZE] = " ";
  wchar_t wword2[SIZE] = " ";
  value_count = wscanf(L"%f %d %d %l[abcdefghijklmnopqrstuvwxyz] %*1d %ls%n",
                               &fp1, &i , &j, wword1, wword2, &byte_count);

*/

  printf("\nCount of bytes read = %d\n", byte_count);
  printf("\nCount of values read = %d\n", value_count);
  printf("\nfp1 = %f   i = %d   j = %d", fp1, i, j);
  printf("\nword1 = %s   word2 = %s\n", word1, word2);

/* Replacement for line above for wide-character strings version

  printf("\nwword1 = %ls   wword2 = %ls\n", wword1, wword2);

*/

  return 0;
}

