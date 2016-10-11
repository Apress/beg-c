/* Program 11.4   Daisy chaining the horses */
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

int main(void)
{
  struct horse                        /* Structure declaration       */
  {
    int age;
    int height;
    char name[20];
    char father[20];
    char mother[20];
    struct horse *next;               /* Pointer to next structure   */
  };

  struct horse *first = NULL;         /* Pointer to first horse      */
  struct horse *current = NULL;       /* Pointer to current horse    */
  struct horse *previous = NULL;      /* Pointer to previous horse   */

  char test = '\0';                   /* Test value for ending input */

  for( ; ; )
  {
    printf("\nDo you want to enter details of a%s horse (Y or N)? ",
                                       first != NULL?"nother " : "" );
    scanf(" %c", &test );
    if(tolower(test) == 'n')
      break;

    /* Allocate memory for a structure */
    current = (struct horse*) malloc(sizeof(struct horse));

    if(first == NULL)
      first = current;                /* Set pointer to first horse  */

    if(previous != NULL)

      previous -> next = current; /* Set next pointer for previous horse */

    printf("\nEnter the name of the horse: ");
    scanf("%s", current -> name);     /* Read the horse's name       */

    printf("\nHow old is %s? ", current -> name);
    scanf("%d", &current -> age);     /* Read the horse's age        */

    printf("\nHow high is %s ( in hands )? ", current -> name );
    scanf("%d", &current -> height);  /* Read the horse's height     */

    printf("\nWho is %s's father? ", current -> name);
    scanf("%s", current -> father);   /* Get the father's name       */

    printf("\nWho is %s's mother? ", current -> name);
    scanf("%s", current -> mother);   /* Get the mother's name       */

    current->next = NULL;             /* In case it's the last...    */
    previous = current;               /* Save address of last horse  */
  }

  /* Now tell them what we know. */
  current = first;                    /* Start at the beginning      */

  while (current != NULL)      /* As long as we have a valid pointer */
  { /* Output the data*/
    printf("\n\n%s is %d years old, %d hands high,",
                       current->name, current->age, current->height);
    printf(" and has %s and %s as parents.", current->father,
                                               current->mother);
    previous = current;    /* Save the pointer so we can free memory */
    current = current->next;          /* Get the pointer to the next */
    free(previous);                   /* Free memory for the old one */
  }
  return 0;
}

