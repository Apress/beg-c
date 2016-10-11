/* Exercise 12.1 Writing strings to a file. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BUFFER_SIZE 50

/* Function prototypes */
char *read_string(char *buffer, int *pbuffer_size);

int main(void)
{
  FILE *pFile = NULL;                     /* File pointer                   */
  char *filename = "C:\\myfile.txt";      /* Name of the file to be written */
  char answer = 'n';
  size_t str_length = 0;
  int buffer_size = BUFFER_SIZE;
  char *buffer = malloc(buffer_size);     /* Create initial buffer          */

  pFile = fopen(filename, "w");           /* Create file to be written      */
  if(!pFile)
  {
    printf("Error opening %s for writing. Program terminated.", filename);
    exit(1);
  }

  do
  {
    /* Get a string from the keyboard */
    printf("Enter a string:\n");
    read_string(buffer, &buffer_size);              /* Read a string into buffer   */
    str_length = strlen(buffer);                    /* Get the string length       */
    fwrite(&str_length, sizeof(size_t), 1, pFile);  /* Write string length to file */
    fwrite(buffer, str_length, 1, pFile);           /* Write string to file        */

    printf("Do you want to enter another (y or n)? ");
    scanf(" %c", &answer);
    fflush(stdin);                                   /* Flush to lose the newline   */
  }while(tolower(answer) == 'y');

  fclose(pFile);                                    /* Close file */
  printf("\nFile write complete\n");
  if(buffer)
    free(buffer);
    return 0;
 }

/* Reads a string of arbitrary length from the keyboard  */
/* If the string exceeds the buffer capacity, the buffer */
/* is increased automatically.                           */
char *read_string(char *buffer, int *pbuffer_size)
{
  char *temp = NULL;                      /* Used to hold new buffer address */
  int position = 0;                       /* Current free position in buffer */

  while((buffer[position++] = getchar()) != '\n')
    if(position >= *pbuffer_size-1)         /* Is the buffer full? */
    { /* Increase the size of the buffer */
      *pbuffer_size += BUFFER_SIZE;        /* New buffer size     */
      temp = (char*)malloc(*pbuffer_size); /* Create new buffer   */
      buffer[position] = '\0';             /* So we can copy it   */
      strcpy(temp, buffer);                /* Copy old to new     */
      free(buffer);                        /* Free the old        */
      buffer = temp;                       /* Save address of new */
      temp = NULL;
    }
  buffer[position-1] = '\0';              /* Overwrite newline with terminator */
  return buffer;
}
