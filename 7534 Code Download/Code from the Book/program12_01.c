/* Program 12.1 Writing a file a character at a time */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int LENGTH = 80;                /* Maximum input length   */

int main(void)
{
  char mystr[LENGTH];                 /* Input string           */
  int lstr = 0;                       /* Length of input string */
  int mychar = 0;                     /* Character for output   */
  FILE *pfile = NULL;                 /* File pointer           */
  char *filename = "C:\\myfile.txt";

  printf("\nEnter an interesting string of less than 80 characters:\n");
  fgets(mystr, LENGTH, stdin);        /* Read in a string       */

  /* Create a new file we can write */
  if(!(pfile = fopen(filename, "w")))
  {
    printf("Error opening %s for writing. Program terminated.", filename);
    exit(1);
  }

  lstr = strlen(mystr);
  for(int i = lstr-1 ; i >= 0 ; i--)
    fputc(mystr[i], pfile);           /* Write string to file backward  */

  fclose(pfile);                      /* Close the file                 */

  /* Open the file for reading */
  if(!(pfile = fopen(filename, "r")))
  {
    printf("Error opening %s for reading. Program terminated.", filename);
    exit(1);
  }

  /* Read a character from the file and display it */
  while((mychar = fgetc(pfile)) != EOF)
    putchar(mychar);                  /* Output character from the file */
  putchar('\n');                      /* Write newline                  */

  fclose(pfile);                      /* Close the file                 */
  remove(filename);                   /* Delete the physical file       */
  return 0;
}

