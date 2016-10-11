/* Program 12.5 Investigating the family.*/
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/* Global Data */
const int NAME_MAX = 20;

struct
{
  char *filename;                              /* Physical file name         */
  FILE *pfile;                                 /* File pointer               */
} global = {"C:\\myfile.bin", NULL };

/* Structure types */
struct Date                                   /* Structure for a date        */
{
  int day;
  int month;
  int year;
};

typedef struct family                         /* Structure for family member */
{
  struct Date dob;
  char name[NAME_MAX];
  char pa_name[NAME_MAX];
  char ma_name[NAME_MAX];
}Family;

/* Function prototypes */
bool get_person(Family *pfamily);                /* Input function           */
void getname(char *name);                        /* Read a name              */
void show_person_data(void);                     /* Output function          */
void get_parent_dob(Family *pfamily);            /* Function to find pa & ma */


int main(void)
{
  Family member;                               /* Stores a family structure */

  if(!(global.pfile = fopen(global.filename, "wb")))
  {
    printf("\nUnable to open %s for writing.\n", global.filename);
    exit(1);
  }

  while(get_person(&member))                    /* As long as we have input */
    fwrite(&member, sizeof member, 1, global.pfile); /*    write it away    */

  fclose(global.pfile);                   /* Close the file now its written */

  show_person_data();                     /* Show what we can find out      */

  if(remove(global.filename))
    printf("\nUnable to delete %s.\n", global.filename);
  else
    printf("\nDeleted %s OK.\n", global.filename);
  return 0;
}

/* Function to input data on Family members */
bool get_person( Family *temp)
{
  static char more = '\0';                    /* Test value for ending input */

  printf("\nDo you want to enter details of a%s person (Y or N)? ",
                                       more != '\0'?"nother " : "" );

  scanf(" %c", &more);

  if(tolower(more) == 'n')
          return false;

  printf("\nEnter the name of the person: ");
  getname(temp->name);                               /* Get the person's name  */

  printf("\nEnter %s's date of birth (day month year); ", temp->name);
  scanf(" %d %d %d", &temp->dob.day, &temp->dob.month, &temp->dob.year);


  printf("\nWho is %s's father? ", temp->name);
  getname(temp->pa_name);                             /* Get the father's name  */

  printf("\nWho is %s's mother? ", temp->name);
  getname(temp->ma_name);                             /* Get the mother's name  */

  return true;
}

/* Read a name from the keyboard */
void getname(char *name)
{
  fflush(stdin);                                      /* Skip whitespace         */
  fgets(name, NAME_MAX, stdin);
  int len = strlen(name);
  if(name[len-1] == '\n')                             /* If last char is newline */
    name[len-1] = '\0';                               /* overwrite it            */
}

/* Function to output data on people on file   */
void show_person_data(void)
{
  Family member;                       /* Structure to hold data from file  */
  fpos_t current = 0;                  /* File position                     */

  /* Open file for binary read */
  if(!(global.pfile = fopen(global.filename, "rb")))
  {
    printf("\nUnable to open %s for reading.\n", global.filename);
    exit(1);
  }

  /* Read data on person */
  while(fread(&member, sizeof member, 1, global.pfile))
  {
    fgetpos(global.pfile, &current);   /* Save current position             */
    printf("\n\n%s's father is %s, and mother is %s.",
             member.name, member.pa_name, member.ma_name);
    get_parent_dob(&member);           /* Get parent data                   */
    fsetpos(global.pfile, &current);   /* Position file to read next        */
  }
   fclose(global.pfile);               /* Close the file                    */
}

void getname(char *name);

/* Function to find parents' dates of birth. */
void get_parent_dob(Family *pmember)
{
  Family relative;                             /* Stores a relative         */
  int num_found = 0;                           /* Count of relatives found  */

  rewind(global.pfile);                        /* Set file to the beginning */

  /* Get the stuff on a relative */
  while(fread(&relative, sizeof(Family), 1, global.pfile))
  {
    if(strcmp(pmember->pa_name, relative.name) == 0)   /*Is it pa?         */
    { /* We have found dear old dad */
      printf("\n Pa was born on %d/%d/%d.",
            relative.dob.day, relative.dob.month, relative.dob.year);

      if(++num_found == 2)                     /* Increment parent count    */
        return;                                /* We got both so go home    */
    }
    else
      if(strcmp(pmember->ma_name, relative.name) == 0) /*Is it ma?         */
      { /* We have found dear old ma */
        printf("\n Ma was born on %d/%d/%d.",
                relative.dob.day, relative.dob.month, relative.dob.year);

        if(++num_found == 2)                   /* Increment parent count    */
            return;                            /* We got both so go home    */
      }
  }
}

