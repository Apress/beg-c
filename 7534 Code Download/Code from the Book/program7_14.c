/* Program 7.14 Sorting strings */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define BUFFER_LEN 100                 /* Length of input buffer            */
#define NUM_P 100                      /* maximum number of strings         */

int main(void)
{
  char buffer[BUFFER_LEN];            /* space to store an input string    */
  char *pS[NUM_P] = { NULL };         /* Array of string pointers          */
  char *pTemp = NULL;                 /* Temporary pointer                 */
  int i = 0;                          /* Loop counter                      */
  bool sorted = false;                /* Indicated when strings are sorted */
  int last_string = 0;                /* Index of last string entered      */

  printf("\nEnter successive lines, pressing Enter at the"
                  " end of each line.\nJust press Enter to end.\n\n");
  while((*fgets(buffer, BUFFER_LEN, stdin) != '\n') && (i < NUM_P))
  {
    pS[i] = (char*)malloc(strlen(buffer) + 1);
    if(pS[i]==NULL)                   /* Check for no memory allocated     */
    {
      printf(" Memory allocation failed. Program terminated.\n");
      return 1;
    }
    strcpy(pS[i++], buffer);
  }
  last_string = i;                    /* Save last string index            */

  /* Sort the strings in ascending order */
  while(!sorted)
  {
    sorted = true;
    for(i = 0 ; i<last_string-1 ; i++)
      if(strcmp(pS[i], pS[i + 1]) > 0)
      {
        sorted = false;               /* We were out of order              */
        pTemp= pS[i];                 /* Swap pointers pS[i]               */
        pS[i] = pS[i + 1];            /*       and                         */
        pS[i + 1]  = pTemp;           /*     pS[i + 1]                     */
      }
  }

  /* Displayed the sorted strings */
  printf("\nYour input sorted in order is:\n\n");
  for(i = 0 ; i<last_string ; i++)
  {
    printf("%s\n", pS[i] );
    free( pS[i] );
    pS[i] = NULL;
  }
  return 0;
}

