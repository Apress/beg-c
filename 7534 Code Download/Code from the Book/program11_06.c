/* Program 11.6 Basics of a family tree */
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

struct Family *get_person(void);       /* Prototype for input function */

struct Date
{
  int day;
   int month;
  int year;
};

struct Family                          /* Family structure declaration */
{
  struct Date dob;
  char name[20];
  char father[20];
  char mother[20];
  struct Family *next;                /* Pointer to next structure    */
  struct Family *previous;           /* Pointer to previous structure */
};

int main(void)
{
  struct Family *first = NULL;        /* Pointer to first person      */
  struct Family *current = NULL;      /* Pointer to current person    */
  struct Family *last = NULL;         /* Pointer to previous person   */
  char more = '\0';                   /* Test value for ending input  */

  for( ; ; )
  {
    printf("\nDo you want to enter details of a%s person (Y or N)? ",
                                        first != NULL?"nother" : "");
    scanf(" %c", &more);
    if(tolower(more) == 'n')
      break;

    current = get_person();

    if(first == NULL)
    {
      first = current;                /* Set pointer to first Family  */
      last = current;                 /* Remember for next iteration  */
    }
    else
    {
      last->next = current;   /* Set next address for previous Family */
      current->previous = last;   /* Set previous address for current */
      last = current;             /* Remember for next iteration      */
    }
  }

  /* Now tell them what we know */

  /* Output Family data in reverse order */
  while (current  != NULL)
  {
    printf("\n%s was born %d/%d/%d, and has %s and %s as parents.",
              current->name, current->dob.day, current->dob.month,
              current->dob. year, current->father,  current->mother );

    last = current;      /* Save pointer to enable memory to be freed */
    current = current->previous;   /* current points to previous list */
    free(last);          /* Free memory for the Family we output      */
  }
  return 0;
}

/*   Function to input data on Family members   */
struct Family *get_person(void)
{
  struct Family *temp;          /* Define temporary structure pointer */

  /* Allocate memory for a structure */
  temp = (struct Family*) malloc(sizeof(struct Family));

  printf("\nEnter the name of the person: ");
  scanf("%s", temp -> name );         /* Read the Family's name       */

  printf("\nEnter %s's date of birth (day month year); ", temp->name);
  scanf("%d %d %d", &temp->dob.day, &temp->dob.month, &temp->dob.year);

  printf("\nWho is %s's father? ", temp->name );
  scanf("%s", temp->father );         /* Get the father's name        */

  printf("\nWho is %s's mother? ", temp->name );
  scanf("%s", temp -> mother );       /* Get the mother's name        */

  temp->next = temp->previous = NULL; /* Set pointers to NULL         */

  return temp;                  /* Return address of Family structure */
}

