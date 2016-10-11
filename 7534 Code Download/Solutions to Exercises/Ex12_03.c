/* Exercise 12.3 Writing names and phone numbers to a file. */
/*
  This solution uses a PhoneRecord structure with the name and number stored in
  arrays with a fixed size. This allows the file operations to be very simple.
  You can just read or write a PhoneRecord structure since its size is fixed.

  If you wanted to allocate space for the name and number dynamically, then
  you would have to expolicitly write the name and number as well as the
  PhoneRecord structure. You would also need to include the length of each
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
PhoneRecord read_phonerecord();              /* Read a name and number from the keyboard   */
Name read_name();                            /* Read a name from the keyboard              */
void list_records(char *filename);           /* List all the records in the file           */
void show_record(PhoneRecord record);        /* Output name and number from a phone record */

int main(void)
{
  FILE *pFile = NULL;                        /* Output file pointer            */
  char *filename = "C:\\records.bin";        /* Name of the file to be written */
  char answer = 'n';
  PhoneRecord record;
  bool file_empty = true;


  printf("Do you want to enter some phone records(y or n)?: ");
  scanf(" %c", &answer);
  if(tolower(answer) == 'y')
  {
    pFile = fopen(filename, "a+");           /* Open/create file to be written */
    if(!pFile)
    {
      printf("Error opening %s for writing. Program terminated.", filename);
      exit(1);
    }

    /* Read an arbitrary number of phone records from the keyboard */
    do
    {
      record = read_phonerecord();                 /* Read the name and number */
      fwrite(&record, sizeof record, 1, pFile);

      printf("Do you want to enter another(y or n)?: ");
      scanf(" %c", &answer);
    }while(tolower(answer) == 'y');

    fclose(pFile);                                    /* Close file */
    printf("\nFile write complete.");
  }
  printf("\nDo you want to list the records in the file(y or n)? ");
    scanf(" %c", &answer);
  if(tolower(answer) == 'y')
    list_records(filename);
  return 0;
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

/* Outputs the name and number from a phone record */
void show_record(PhoneRecord record)
{
  printf("\n%s %s   %s", record.name.firstname, record.name.secondname, record.number);
}
