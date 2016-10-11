/* Program 12.8 Viewing the contents of a file */
#include <stdio.h>
#include <ctype.h>
#include <string.h>

const int MAXLEN = 256;                    /* Maximum file path length      */
const int DISPLAY = 80;                    /* Length of display line        */
const int PAGE_LENGTH = 20;                /* Lines per page                */

int main(int argc, char *argv[])
{
  char filename[MAXLEN];                   /* Stores the file path          */
  FILE *pfile;                             /* File pointer                  */
  unsigned char buffer[DISPLAY/4 - 1];     /* File input buffer             */
  int count = 0;                           /* Count of characters in buffer */
  int lines = 0;                           /* Number of lines displayed     */

  if(argc == 1)                            /* No file name on command line? */
  {
    printf("Please enter a filename: ");   /* Prompt for input              */
    fgets(filename, MAXLEN, stdin);        /* Get the file name entered     */

    /* Remove the newline if it's there */
    int len = strlen(filename);
    if(filename[len-1] == '\n')
      filename[len-1] = '\0';
  }
  else
    strcpy(filename, argv[1]);             /* Get 2nd command line string   */

    /* File can be opened OK?        */
    if(!(pfile = fopen(filename, "rb")))
    {
      printf("Sorry, can't open %s", filename);
      return -1;
    }
  while(!feof(pfile))                      /* Continue until end of file    */
  {
    if(count < sizeof buffer)              /* If the buffer is not full     */
      buffer[count++] = (unsigned char)fgetc(pfile);    /* Read a character */
    else
    { /* Output the buffer contents, first as hexadecimal */
      for(count = 0; count < sizeof buffer; count++)
        printf("%02X ", buffer[count]);
      printf("| ");                        /* Output separator              */

      /* Now display buffer contents as characters */
      for(count = 0; count < sizeof buffer; count++)
        printf("%c", isprint(buffer[count]) ? buffer[count]:'.');
      printf("\n");                        /* End the line                  */
      count = 0;                           /* Reset count                   */

      if(!(++lines%PAGE_LENGTH))           /* End of page?                  */
       if(getchar()=='E')                  /* Wait for Enter                */
         return 0;                         /* E pressed                     */
    }
  }

  /* Display the last line, first as hexadecimal */
  for(int i = 0; i < sizeof buffer; i++)
    if(i < count)
      printf("%02X ", buffer[i]);          /* Output hexadecimal            */
    else
      printf("   ");                       /* Output spaces                 */
  printf("| ");                            /* Output separator              */

  /* Display last line as characters */
  for(int i = 0; i < count; i++)
    /* Output character    */
    printf("%c",isprint(buffer[i]) ? buffer[i]:'.');
  /* End the line          */
  printf("\n");
  fclose(pfile);                           /* Close the file                */
  return 0;
}

