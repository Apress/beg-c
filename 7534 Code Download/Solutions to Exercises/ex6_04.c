/* Exercise 6.4 Looking for palindromes */
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
  char sentence[500];             /* Stores the sentence to be tested                   */
  char sentence_chars[500];       /* Stores the sentence without punctuation and spaces */
  size_t j = 0;                   /* Index to character position */
  size_t length = 0;              /* Length of a string          */

  printf("Enter a sentence to be tested:\n");
  gets(sentence);

  /* Copy only letters as lowercase */
  for (size_t i = 0 ; i< strlen(sentence) ; i++)
    if(isalpha(sentence[i]))
      sentence_chars[j++] = tolower(sentence[i]);
  sentence_chars[j] = '\0';        /* Append string terminator */

  length = strlen(sentence_chars); /* Get the satring length   */

  /* Compare matching characters in the string                */
  /* If any pair are not the same, then it's not a palindrome */
  for(size_t i = 0 ; i<length/2 ; i++)
    if(sentence_chars[i] != sentence_chars[length-1-i])
    {
      printf("\n The sentence you entered is not a palindrome.\n");
      return 0;
    }
    /* If we arrive here all matching pairs of characters are equal */
    printf("\n The sentence you entered is a palindrome.\n");
    return 0;
}

