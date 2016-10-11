/* Program 11.3 Pointing out the horses */
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>          /* For malloc() */

int main(void)
{
  struct horse              /* Structure declaration */
  {
    int age;
    int height;
    char name[20];
    char father[20];
    char mother[20];
  };

  struct horse *phorse[50]; /* pointer to structure array declaration */
  int hcount = 0;           /* Count of the number of horses          */
  char test = '\0';         /* Test value for ending input            */

  for(hcount = 0; hcount < 50 ; hcount++ )
  {
    printf("\nDo you want to enter details of a%s horse (Y or N)? ",
                                               hcount?"nother " : "" );
    scanf(" %c", &test );
    if(tolower(test) == 'n')
      break;

    /* allocate memory to hold a structure    */
    phorse[hcount] = (struct horse*) malloc(sizeof(struct horse));

    printf("\nEnter the name of the horse: " );
    scanf("%s", phorse[hcount]->name );  /* Read the horse's name */

    printf("\nHow old is %s? ", phorse[hcount]->name );
    scanf("%d", &phorse[hcount]->age );  /* Read the horse's age  */

    printf("\nHow high is %s ( in hands )? ", phorse[hcount]->name );
    scanf("%d", &phorse[hcount]->height ); /* Read the horse's height */

    printf("\nWho is %s's father? ", phorse[hcount]->name );
    scanf("%s", phorse[hcount]->father );  /* Get the father's name */

    printf("\nWho is %s's mother? ", phorse[hcount]->name );
    scanf("%s", phorse[hcount]->mother );  /* Get the mother's name */
  }

  /* Now tell them what we know. */
  for (int i = 0 ; i < hcount ; i++ )
  {
    printf("\n\n%s is %d years old, %d hands high,",
                  phorse[i]->name, phorse[i]->age, phorse[i]->height);
    printf(" and has %s and %s as parents.",
                                phorse[i]->father, phorse[i]->mother);
    free(phorse[i]);
  }
  return 0;
}

