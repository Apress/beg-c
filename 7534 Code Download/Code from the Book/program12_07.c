/* Program 12.7 Writing, reading and updating a binary file */
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

const int MAXLEN = 30;                            /* Size of name buffer     */
const char *dirpath = "C:\\temp\\";               /* Directory path for file */
const char *file = "mydata.bin";                  /* File name               */

/* Structure encapsulating a name and age */
struct Record
{
  char name[MAXLEN];
  int age;
};

void listfile(char *filename);                    /* List the file contents   */
void updatefile(char *filename);                  /* Update the file contents */
struct Record *getrecord(struct Record *precord); /* Read a record from stdin */
void getname(char *pname);                        /* Read a name from stdin   */
void writefile(char *filename, char *mode);       /* Write records to a file  */
void writerecord(struct Record *precord, FILE *pFile);
struct Record * readrecord(struct Record *precord, FILE *pFile);
int findrecord(struct Record *precord, FILE *pFile);
void duplicatefile(struct Record *pnewrecord,
                                    int index, char *filename, FILE *pFile);

int main(void)
{
  char filename[strlen(dirpath)+strlen(file)+1];  /* Stores file path        */
  strcpy(filename, dirpath);                      /* Copy directory path     */
  strcat(filename, file);                         /*  and append file name   */

  /* Choose activity option */
  char answer = 'q';
  while(true)
  {
    printf("\nChoose from the following options:"
           "\nTo list the file contents enter  L"
           "\nTo create a new file enter       C"
           "\nTo add new records enter         A"
           "\nTo update existing records enter U"
           "\nTo delete the file enter         D"
           "\nTo end the program enter         Q\n : ");
    scanf("\n%c", &answer);

    switch(tolower(answer))
    {
      case 'l':                                 /* List file contents      */
        listfile(filename);
        break;
        case 'c':                               /* Create new file         */
        writefile(filename,"wb+");
        printf("\nFile creation complete.");
        break;
      case 'a':                                 /* Append records          */
        writefile(filename, "ab+");
        printf("\nFile append complete.");
        break;
      case 'u':                                 /* Update existing records */
        updatefile(filename);
        break;
      case 'd':
        printf("Are you sure you want to delete %s (y or n)? ", filename);
        scanf("\n%c", &answer);
        if(tolower(answer) == 'y')
          remove(filename);
        break;
      case 'q':                                 /* Quit the program        */
        printf("\nEnding the program.", filename);
        return 0;
      default:
        printf("Invalid selection. Try again.");
        break;
    }
  }
  return 0;
}

/* Read the name and age for a record from the keyboard */
struct Record *getrecord(struct Record *precord)
{
  /* Verify the argument is good */
  if(!precord)
  {
    printf("No Record object to store input.");
    return NULL;
  }

  printf("\nEnter a name less than %d characters:", MAXLEN);
  getname(precord->name);                     /* readf the name    */

  printf("Enter the age of %s: ", precord->name);
  scanf(" %d", &precord->age);                /* Read the age      */
  return precord;
}

/* Read a name from the keyboard */
void getname(char *pname)
{
  fflush(stdin);
  fgets(pname, MAXLEN, stdin);        /* Read the name     */
  int len = strlen(pname);
  if(pname[len-1] == '\n')         /* if there's a newline */
    pname[len-1] = '\0';           /* overwrite it         */
}

/* Write a new record to the file at the current position */
void writerecord(struct Record *precord, FILE *pFile)
{
  /* Verify the arguments are good */
  if(!precord)
  {
    printf("No Record object to write to the file.");
    return;
  }
  if(!pFile)
  {
    printf("No stream pointer for the output file.");
    return;
  }

  /* Write the name & age to file */
  size_t length = strlen(precord->name);                 /* Get name length   */
  fwrite(&length, sizeof(length), 1, pFile);             /* Write name length */
  fwrite(precord->name, sizeof(char), length, pFile);    /* then the name     */
  fwrite(&precord->age, sizeof(precord->age), 1, pFile); /* then the age      */
}

/* Reads a record from the file at the current position */
struct Record * readrecord(struct Record *precord, FILE *pFile)
{
  /* Verify the arguments are good */
  if(!precord)
  {
    printf("No Record object to store data from the file.");
    return NULL;
  }
  if(!pFile)
  {
    printf("No stream pointer for the input file.");
    return NULL;
  }

  size_t length = 0;                                    /* Name length      */
  fread(&length, sizeof(length), 1, pFile);             /* Read the length  */
  if(feof(pFile))                                       /* If it's end file */
    return NULL;                                        /* return NULL      */

  /* Verify the name can be accommodated */
  if(length+1>MAXLEN)
  {
    fprintf(stderr, "\nName too long. Ending program.");
    exit(1);
  }

  fread(precord->name, sizeof(char), length, pFile);    /* Read the name     */
  precord->name[length] = '\0';                         /* Append terminator */
  fread(&precord->age, sizeof(precord->age), 1, pFile); /* Read the age      */

  return precord;
}

/* Write to a file */
void writefile(char *filename, char *mode)
{
  char answer = 'y';

  FILE *pFile = fopen(filename, mode);    /* Open the file                 */
  if(pFile == NULL)                       /* Verify file is open           */
  {
    fprintf(stderr, "\n File open failed.");
    exit(1);
  }

  do
  {
    struct Record record;                 /* Stores a record name & age    */

    writerecord(getrecord(&record), pFile); /* Get record & write the file */

    printf("Do you want to enter another(y or n)?  " );
    scanf("\n%c", &answer);
    fflush(stdin);                        /* Remove whitespace             */
  } while(tolower(answer) == 'y');

  fclose(pFile);                          /* Close the file                */
}

/* List the contents of the binary file */
void listfile(char *filename)
{
  /* Create the format string for names up to MAXLEN long */
  /* format array length allows up to 5 digits for MAXLEN */
  char format[15];                           /* Format string              */
  sprintf(format, "\n%%-%ds Age:%%4d", MAXLEN);

  FILE *pFile = fopen(filename, "rb");       /* Open file to read          */
  if(pFile == NULL)                          /* Check file is open         */
  {
    printf("Unable to open %s. Verify it exists.\n", filename);
    return;
  }

  struct Record record;                      /* Stores a record            */
  printf("\nThe contents of %s are:", filename);

  while(readrecord(&record, pFile) != NULL)  /* As long as we have records */
    printf(format, record.name, record.age); /* Output the record          */

  printf("\n");                              /* Move to next line          */

  fclose(pFile);                             /* Close the file             */
}

/* Modify existing records in the file */
void updatefile(char *filename)
{  char answer = 'y';

  FILE *pFile = fopen(filename, "rb+");      /* Open the file for update   */
  if(pFile == NULL)                          /* Check file is open         */
  {
    fprintf(stderr, "\n File open for updating records failed.");
    return;
  }

  struct Record record;                      /* Stores a record            */
  int index = findrecord(&record, pFile);    /* Find the record for a name */
  if(index<0)                                /* If the record isn't there  */
  {
    printf("\nRecord not found.");           /* ouput a message            */
    return;                                  /* and we are done.           */
  }

  printf("\n%s is aged %d,", record.name, record.age);
  struct Record newrecord;                   /* Stores replacement record  */
  printf("\nYou can now enter the new name and age for %s.", record.name);
  getrecord(&newrecord);                       /* Get the new record         */

  /* Check if we can update in place */
  if((strlen(record.name) == strlen(newrecord.name)))
  { /* Name lengths are the same so we can */
    /* Move to start of old record         */
    fseek(pFile,
          -(long)(sizeof(size_t)+strlen(record.name)+sizeof(record.age)),
          SEEK_CUR);

    writerecord(&newrecord, pFile);          /* Write the new record       */
    fflush(pFile);                           /* Force the write            */
  }
  else
    duplicatefile(&newrecord, index, filename, pFile);

  printf("File update complete.\n");
}

/* Duplicate the existing file replacing the record to be update */
/* The record to be replaced is index records from the start     */
void duplicatefile(struct Record *pnewrecord, int index, char *filename, FILE *pFile)
{
    /* Create and open a new file */
  char tempname[L_tmpnam];
  if(tmpnam(tempname) == NULL)
  {
    printf("\nTemporary file name creation failed.");
    return;
  }
  char tempfile[strlen(dirpath)+strlen(tempname)+1];
  strcpy(tempfile, dirpath);                  /* Copy original file path  */
  strcat(tempfile, tempname);                 /* Append temporary name    */
  FILE *ptempfile = fopen(tempfile, "wb+");

  /* Copy first index records from old file to new file */
  rewind(pFile);                              /* Old file back to start    */
  struct Record record;                       /* Store for a record        */
  for(int i = 0 ; i<index ; i++)
    writerecord(readrecord(&record, pFile), ptempfile);


  writerecord(pnewrecord, ptempfile);         /* Write the new record      */
  readrecord(&record,pFile);                  /* Skip the old record       */

  /* Copy the rest of the old file to the new file */
  while(readrecord(&record,pFile))
    writerecord(&record, ptempfile);

  /* close the files */
  if(fclose(pFile)==EOF)
    printf("\n Failed to close %s", filename);
  if(fclose(ptempfile)==EOF)
    printf("\n Failed to close %s", tempfile);

  if(remove(filename))                        /* Delete the old file       */
  {
    printf("\nRemoving the old file  failed. Check file in %s", dirpath);
    return;
  }

  /* Rename the new file same as original */
  if(rename(tempfile, filename))
    printf("\nRenaming the file copy failed. Check file in %s", dirpath);
}

/* Find a record                          */
/* Returns the index number of the record */
/* or -1 if the record is not found.      */
int findrecord(struct Record *precord, FILE *pFile)
{
  char name[MAXLEN];
  printf("\nEnter the name for the record you wish to find: ");
  getname(name);

  rewind(pFile);                       /* Make sure we are at the start */
  int index = 0;                       /* Index of current record       */

  while(true)
  {
    readrecord(precord, pFile);
    if(feof(pFile))                     /* If end-of-file was reached    */
      return -1;                        /* record not found              */
    if(!strcmp(name, precord->name))
      break;
    ++index;
  }
  return index;                         /* Return record index           */
}

