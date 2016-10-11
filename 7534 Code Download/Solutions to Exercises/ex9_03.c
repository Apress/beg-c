/* Exercise 9.3 Join array of strings into a single string */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STRINGS 100                         /* Maximum string count                        */
#define BUFFER_SIZE 50                          /* Initial input buffer size                   */

char* join_strings(char *strings[], int count); /* Joins array of strings into a single string */
char* read_string(char terminator);             /* Reads a string from the keyboard            */

int main(void)
{
  char *pStrings[MAX_STRINGS];       /* Array of pointers to strings */
  char *joined_strings = NULL;       /* Pointer to the joined string */
  int count = 0;                     /* Number of strings entered    */
  char answer = 'y';                 /* Confirms more input          */
  char terminator = '*';             /* Terminator for string entry  */

  /* Read the strings */
  while(count<MAX_STRINGS && tolower(answer)=='y')
  {
    printf("Enter a string terminated by an asterisk:\n");
    pStrings[count++] = read_string(terminator);

    printf("Do you want to enter another: ");
    scanf(" %c", &answer);
    fflush(stdin);                     /* Lose newline following character entry */
  }

  joined_strings = join_strings(pStrings, count);
  printf("\nHere are the strings as a single string:\n%s\n", joined_strings);

  free(joined_strings);                /* Free memory for joined strings   */
  for(int i = 0 ; i<count ; i++)           /* Free memory for original strings */
    free(pStrings[i]);
  return 0;
}

/*******************************************************************
 * Function to join an array of strings                            *
 * this function allocates memory that must be freed by the caller *
 *******************************************************************/
char* join_strings(char *strings[], int count)
{
  char* str = NULL;             /* Pointer to the joined strings  */
  size_t total_length = 0;      /* Total length of joined strings */
  size_t length = 0;            /* Length of a string             */

  /* Find total length of joined strings */
  for(int i = 0 ; i<count ; i++)
  {
    total_length += strlen(strings[i]);
    if(strings[i][strlen(strings[i])-1] != '\n')
      ++total_length;           /* For newline to be added */
  }
  ++total_length;               /* For joined string terminator */

  str = (char*)malloc(total_length);  /* Allocate memory for joined strings */
  str[0] = '\0';                      /* Empty string we can append to      */

  /* Append all the strings */
  for(int i = 0 ; i<count ; i++)
  {
    strcat(str, strings[i]);
    length = strlen(str);

    /* Check if we need to insert newline */
    if(str[length-1] != '\n')
    {
      str[length] = '\n';             /* Append a newline       */
      str[length+1] = '\0';           /* followed by terminator */
    }
  }
  return str;
}

/***************************************************************************
 * Reads a string of any length.                                           *
 * The string is terminated by the chracter passed as the argument.        *
 * Memory is allocated to hold the string and must be freed by the caller. *
 ***************************************************************************/
char* read_string(char terminator)
{
  char *buffer = NULL;            /* Pointer to the input buffer */
  int buffersize = BUFFER_SIZE;   /* Current buffer capacity     */
  int length = 0;                 /* String length               */
  char *temp = NULL;              /* Temporary buffer pointer    */

  buffer = (char*)malloc(BUFFER_SIZE);  /* Initial buffer */
  /* Read the string character by character */
  for(;;)
  {
    /* Check for string terminator */
    if((buffer[length] = getchar()) == terminator)
      break;
    else
      ++length;

    /* Check for buffer overflow */
    if(length == buffersize)
    {
      buffersize += BUFFER_SIZE;          /* Increase buffer size */
      temp = (char*)malloc(buffersize);   /* Allocate new buffer  */

      /* Copy characters from old buffer to new */
      for(int i = 0 ; i<length ; i++)
        temp[i] = buffer[i];

      free(buffer);                       /* Free memory for old buffer */
      buffer = temp;                      /* Store new buffer address   */
      temp = NULL;                        /* Rest temp pointer          */
    }
  }
  buffer[length] = '\0';                  /* Append string terminator                  */
  temp = (char*)malloc(length+1);         /* Allocate exact memory required for string */
  strcpy(temp, buffer);                   /* Copy the string       */
  free(buffer);                           /* Free the buffer memory */
  return temp;
}
