/* Program 12.6 Writing a binary file with an update mode */
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

const int MAXLEN = 30;                    /* Size of name buffer    */

void listfile(char *filename);            /* List the file contents */

int main(void)
{
  const char *filename = "C:\\temp\\mydata.bin";
  char name[MAXLEN];                            /* Stores a name    */
  size_t length = 0;                            /* Length of a name */
  int age = 0;                                  /* Person's age     */
  char answer = 'y';

  FILE *pFile = fopen(filename, "wb+");

  do
  {
    fflush(stdin);                              /* Remove whitespace */

    printf("\nEnter a name less than %d characters:", MAXLEN);
    gets(name);                                 /* Read the name     */

    printf("Enter the age of %s: ", name);
    scanf(" %d", &age);                         /* Read the age      */

    /* Write the name & age to file */
    length = strlen(name);                      /* Get name length   */
    fwrite(&length, sizeof(length), 1, pFile);  /* Write name length */
    fwrite(name, sizeof(char), length, pFile);  /* then the name     */
    fwrite(&age, sizeof(age), 1, pFile);        /* then the age      */

    printf("Do you want to enter another(y or n)?  " );
    scanf("\n%c", &answer);
  } while(tolower(answer) == 'y');

  fclose(pFile);                                /* Close the file    */

  listfile(filename);                           /* List the contents */
  return 0;
}

/* List the contents of the binary file */
void listfile(char *filename)
{
  size_t length = 0;                            /* Name length       */
  char name[MAXLEN];                            /* Stores a name     */
  int age = 0;
  char format[20];                              /* Format string     */

  /* Create the format string for names up to MAXLEN long */
  sprintf(format, "\n%%-%ds Age:%%4d", MAXLEN);

  FILE *pFile = fopen(filename, "rb");          /* Open to read      */
  printf("\nThe contents of %s are:", filename);

  /* Read records as long as we read a length value */
  while(fread(&length, sizeof(length), 1, pFile) == 1)
  {
    if(length+1>MAXLEN)
    {
      printf("\nName too long.");
      exit(1);
    }
    fread(name, sizeof(char), length, pFile);   /* Read the name     */
    name[length] = '\0';                        /* Append terminator */
    fread(&age, sizeof(age), 1, pFile);         /* Read the age      */
    printf(format, name, age);                  /* Output the record */
  }
  fclose(pFile);
}

