/* Exercise 6.2 Analyze comma-separated list of words */
#include <stdio.h>
#include <string.h>

int main(void)
{
  char list[5000];         /* Stores the list of comma separated words   */
  char words[500][20];     /* Array for 500 words of up to 20 characters */
  const char comma = ',';
  const char space = ' ';
  int word_count = 0;      /* Number of words found */
  int word_length = 0;     /* Current word length   */
  int index = 0;           /* Character position    */

  printf("Enter a comma separated list of words:\n");
  gets(list);              /* Read the list of words */

  /* Find words in list */
  while(list[index] != '\0')
  {
    /* Skip over spaces and commas */
    while(list[index] == space || list[index] == comma)
      ++index;

    /* Copy characters that are not space, comma or \0 as part of a word */
    while(list[index] != space && list[index] != comma && list[index] != '\0')
     words[word_count][word_length++] = list[index++];

    words[word_count++][word_length] = '\0';    /* Append terminator         */
    word_length = 0;                            /* Reset ready for next word */
  }

  /* List the words that were found */
  printf("\nThe words in the list are:\n");
  for(index = 0 ; index<word_count ; index++)
    printf("%s\n",words[index]);

	return 0;
}

