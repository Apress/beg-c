/* Exercise 12.4 Writing names and phone numbers to a file. */
/*
  This solution uses a PhoneRecord structure with the name and number stored in
  arrays with a fixed size. This allows the file operations to be very simple.
  You can just read or write a PhoneRecord structure since its size is fixed.

  If you wanted to allocate space for the name and number dynamically, then
  you would have to explicitly write the name and number strings as well as the
  PhoneRecord structure to the file. You would also need to include the length of each
  data item in the file so you knew how much to read back.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define FIRST_NAME_LENGTH  31
#define SECOND_NAME_LENGTH 51
#define NUMBER_LENGTH      21


/* Structure defining a name  */
/* Also defines the Name type */
typedef struct NName
{
  char firstname[FIRST_NAME_LENGTH];
  char secondname[SECOND_NAME_LENGTH];
} Name;

/* Structure defining a phone record */
/* Also defines the PhoneRecord type */
typedef struct PPhoneRecord
{
  Name name;
  char number[NUMBER_LENGTH];
} PhoneRecord;


/* Function prototypes */
PhoneRecord read_phonerecord();                       /* Read a name and number from the keyboard     */
Name read_name();                                     /* Read a name from the keyboard                */
void list_records(char *filename);                    /* List all the records in the file             */
void show_record(PhoneRecord record);                 /* Output name and number from a phone record   */
void find_numbers(Name name, char *filename);         /* Find numbers corresponding to a given name   */
void add_record(char *filename);                      /* Add a new name and number to the file        */
void delete_records(Name name, char *filename);       /* Delete records for a given name              */
void list_records();                                  /* List all the records in the file             */
void show_operations();                               /* Displays operations supported by the program */
int equals(Name name1, Name name2);                   /* Compare two names for equality               */


int main(void)
{
  FILE *pFile = NULL;                                 /* File pointer                         */
  char *filename = "C:\\records.bin";                 /* Name of the file holding the records */
  char answer = 'n';                                  /* Stores input responses               */
  show_operations();                                  /* Display the available operations     */

  for(;;)
  {
    printf("\nEnter a letter to select an operation: ");
    scanf(" %c", &answer);
    switch(toupper(answer))
    {
      case 'A':                                       /* Add a new name and number record  */
        add_record(filename);
        break;
      case 'D':                                       /* Delete records for a given name   */
        delete_records(read_name(), filename);
        break;
      case 'F':                                       /* Find the numbers for a given name */
        find_numbers(read_name(), filename);
        break;
      case 'L':                                       /* List all the name/number records  */
        list_records(filename);
        break;
      case 'Q':                                       /* Quit the program                  */
        return 0;
      default:
        printf("\nInvalid selection try again.");
        show_operations();
        break;
    }
  }
 }

/* Reads a name and number from the keyboard and creates a PhoneRecord structure */
PhoneRecord read_phonerecord()
{
  PhoneRecord record;
  record.name = read_name();
  printf("Enter the number: ");
  scanf(" %[ 0123456789]",record.number);  /* Read the number - including spaces */
  return record;
}

/* Outputs the name and number from a phone record */
void show_record(PhoneRecord record)
{
  printf("\n%s %s   %s", record.name.firstname,record.name.secondname, record.number);
}

/* Add a new name and number */
void add_record(char *filename)
{
  FILE *pFile = NULL;
  PhoneRecord record;

  if(!(pFile = fopen(filename, "a+")))         /* Open/create file to be written in append mode */
  {
    printf("Error opening %s for writing. Program terminated.", filename);
    exit(1);
  }
  record = read_phonerecord();                 /* Read the name and number */
  fwrite(&record, sizeof record, 1, pFile);
  fclose(pFile);                               /* Close file               */
  printf("\nNew record added.");
}

/* Read a name from the keyboard and create a Name structure for it */
Name read_name()
{
  Name name;
  printf("Enter a first name: ");
  scanf(" %s", &name.firstname);
  printf("Enter a second name: ");
  scanf(" %s", &name.secondname);
  return name;
}

/* Delete records for a given name */
/* To delete one or more records we can copy
   the contents of the existing file to a new
   file, omitting the records that are to be
   deleted. We can then delete the old file and
   rename the new file to have the old file
   name.
*/
void delete_records(Name name, char *filename)
{
  FILE *pFile = NULL;
  FILE *pNewFile = NULL;
  char *pnewfilename = NULL;
  char answer = 'n';
  PhoneRecord record;

  if(!(pFile = fopen(filename, "r")))         /* Open current file to read it */
  {
    printf("Error opening %s for reading. Program terminated.", filename);
    exit(1);
  }

  pnewfilename = tmpnam(NULL);                       /* Create temporary file name      */
  if(!(pNewFile = fopen(pnewfilename, "w")))         /* Open temporary file to write it */
  {
    printf("Error opening %s for writing. Program terminated.", pnewfilename);
    fclose(pFile);
    exit(1);
  }

  /* Copy existing file contents to temporary file, omitting deleted records */
  for(;;)
  {
    fread(&record, sizeof record, 1, pFile);      /* Read a record                  */
    if(feof(pFile))                               /* End of file read ?             */
      break;                                      /* Yes-quit copy loop             */

    if(equals(name, record.name))                 /* Is the record this name ?      */
    {
      printf("\nFound a record:");                /* Ys, so it's a delete candidate */
      show_record(record);
      printf("\nDo you really want to delete it(y or n)? ");
      scanf(" %c", &answer);
      if(tolower(answer) == 'y')                  /* If it's to be deleted          */
        continue;                                 /* Skip the copying               */
    }
    fwrite(&record, sizeof record, 1, pNewFile);  /* copy current record            */
  }
  fclose(pFile);
  fclose(pNewFile);

  if(!(pNewFile = fopen(pnewfilename, "r")))      /* Open temporary file to read it */
  {
    printf("Error opening %s for reading. Program terminated.", pnewfilename);
    exit(1);
  }
  if(!(pFile = fopen(filename, "w")))             /* Open original file to write it */
  {
    printf("Error opening %s for writing. Program terminated.", filename);
    exit(1);
  }

  /* Copy contents of new temporary file back to old file          */
  /* This overwrites the original contents because the mode is "w" */
  for(;;)
  {
    fread(&record, sizeof record, 1, pNewFile);   /* Read temporary file */
    if(feof(pNewFile))                            /* If we read EOF      */
      break;                                      /* We are done         */

    fwrite(&record, sizeof record, 1, pFile);     /* Write record to original file */
  }
  fclose(pFile);                                  /* Close the original file   */
  fclose(pNewFile);                               /* Close the temporary file  */
  remove(pnewfilename);                           /* Delete the temporary file */
  printf("Delete complete.");
}

/* List all the records in the file */
void list_records(char *filename)
{
  FILE *pFile;
  PhoneRecord record;
  bool file_empty = true;               /* File empty flag          */

  if(!(pFile = fopen(filename, "r")))   /* Open the file to read it */
  {
    printf("Error opening %s for reading. Program terminated.", filename);
    exit(1);
  }

  /* List the file contents */
  for(;;)
  {
    fread(&record, sizeof record, 1, pFile);
    if(feof(pFile))
      break;
    file_empty = false;          /* We got a record so set empty flag false */
    show_record(record);         /* output the record                       */
  }
  fclose(pFile);                 /* Close the file */

  /* Check whether there were any records */
  if(file_empty)
    printf("The file contains no records.\n");
  else
    printf("\n");
}

/* Displays the operations that are supported by the program */
void show_operations()
{
  printf("The operations available are:"
    "\nA: Add a new name and number entry."
    "\nD: Delete all existing entries for a name."
    "\nF: Find the number(s) for a given name."
    "\nL: List all the entries in the file."
    "\nQ: Quit the program.");
}

/* Find numbers corresponding to a given name */
void find_numbers(Name name, char *filename)
{
  FILE *pFile = NULL;
  PhoneRecord record;
  bool name_found = false;                       /* Name found flag           */

  if(!(pFile = fopen(filename, "r")))            /* Open the file to read it  */
  {
    printf("Error opening %s for reading. Program terminated.", filename);
    exit(1);
  }

  /* Search the records read from the file */
  for(;;)
  {
    fread(&record, sizeof record, 1, pFile);     /* Read a record             */
    if(feof(pFile))
      break;
   if(equals(name,record.name))                  /* Is it the name requested? */
   {
     if(!name_found)                   /* Is this the first time we found it? */
     {
       name_found = true;                        /* Yes so set flag to true   */
       printf("The numbers for this name are:"); /* Output initial message    */
     }
     printf("\n%s",record.number);               /* Output the number         */
   }
  }
  fclose(pFile);                                 /* Close the file            */

  /* Check for name not found */
  if(!name_found)
    printf("The name was not found.\n");
  else
    printf("\n");
}

/* Compare two names for equality */
int equals(Name name1, Name name2)
{
  return (strcmp(name1.firstname, name2.firstname)==0) && (strcmp(name1.secondname, name2.secondname)==0);
}
