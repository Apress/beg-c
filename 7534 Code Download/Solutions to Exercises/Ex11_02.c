/* Exercise 11.2 Using a structure representing a person's name. */
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define FIRST_NAME_LEN  31
#define SECOND_NAME_LEN 51
#define NUMBER_LEN      16
#define MAX_NUMBERS     50


/* Structure defining a name */
struct Name
{
  char firstname[FIRST_NAME_LEN];
  char secondname[SECOND_NAME_LEN];
};

/* Structure defining a phone record */
struct PhoneRecord
{
  struct Name name;
  char number[NUMBER_LEN];
};

/* Function prototypes */
void show(struct PhoneRecord record);                       /* Output a phone record         */
bool has_name(struct PhoneRecord record, struct Name name); /* Test for a name               */
struct Name read_name();                                    /* Read a name from the keyboard */

int main(void)
{
  char answer = 'n';
  struct PhoneRecord records[MAX_NUMBERS];                  /* Array of phone records        */
  struct Name aName;                                        /* Stores a name                 */
  int count = 0;                                            /* Number of phone records       */
  bool found = false;                                       /* Records when a name has been found */

  /* Read an arbitrary number of phone records from the keyboard */
  do
  {
    records[count].name = read_name();                 /* Read the name */
    printf("Enter the number for this name: ");
    scanf(" %[ 0123456789]",records[count++].number);  /* Read the number - including spaces */

    printf("Do you want to enter another(y or n)?: ");
    scanf(" %c", &answer);
  }while(count<=MAX_NUMBERS && tolower(answer) == 'y');

  /* Search the array of phone records for a number */
  do
  {
    printf("Enter a name for which you want the number.");
    aName = read_name();
    for(int i = 0 ; i<count ; i++)
    {
      if(has_name(records[i], aName))                 /* Test for the name */
      {
        if(!found)                                    /* If this is the first time */
        {
          found = true;                               /* Reset found flag       */
          printf("The numbers for this name are:\n"); /* and output the heading */
        }
        printf("%s\n", records[i].number);            /* Output the number for the name */
      }
    }
    if(found)                                         /* If the name was found */
      found = false;                                  /* Reset the found flag  */
    else                                              /* Otherwise output message */
      printf("No numbers found for this name.\n");
    printf("Do you want to search for another (y or n)? ");
    scanf(" %c" , &answer);
  }while(tolower(answer) == 'y');

  for(int i = 0 ; i<count ; i++)
    show(records[i]);
  printf("\n");
  return 0;
}

/* Function to output a record */
void show(struct PhoneRecord record)
{
  printf("\n%s %s   %s", record.name.firstname,record.name.secondname, record.number);
}

/* Function to test whether the name is the same as in a record */
bool has_name(struct PhoneRecord record, struct Name name)
{
  return (strcmp(name.firstname, record.name.firstname)==0 && strcmp(name.secondname, record.name.secondname) == 0);
}

/* Function to read a name and store it in a Name structure */
struct Name read_name()
{
    struct Name name;
    printf("Enter a first name: ");
    scanf(" %s", &name.firstname);
    printf("Enter a second name: ");
    scanf(" %s", &name.secondname);
  return name;
}

