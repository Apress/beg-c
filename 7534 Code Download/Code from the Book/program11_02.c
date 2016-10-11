/* Program 11.2   Exercising the horses */
#include <stdio.h>
#include <ctype.h>
int main(void)
{
  struct horse                        /* Structure declaration */
  {
    int age;
    int height;
    char name[20];
    char father[20];
    char mother[20];
  };

  struct horse My_horses[50];         /* Structure array declaration   */
  int hcount = 0;                     /* Count of the number of horses */
  char test = '\0';                   /* Test value for ending         */

  for(hcount = 0; hcount<50 ; hcount++ )
  {
    printf("\nDo you want to enter details of a%s horse (Y or N)? ",
                                              hcount?"nother " : "" );
    scanf(" %c", &test );
    if(tolower(test) == 'n')
       break;

    printf("\nEnter the name of the horse: " );
    scanf("%s", My_horses[hcount].name );  /* Read the horse's name */

    printf("\nHow old is %s? ", My_horses[hcount].name );
    scanf("%d", &My_horses[hcount].age );  /* Read the horse's age  */

    printf("\nHow high is %s ( in hands )? ", My_horses[hcount].name );
    /* Read the horse's height*/
    scanf("%d", &My_horses[hcount].height );

    printf("\nWho is %s's father? ", My_horses[hcount].name );
    /* Get the father's name */
     scanf("%s", My_horses[hcount].father );

    printf("\nWho is %s's mother? ", My_horses[hcount].name );

    /* Get the mother's name  */
    scanf("%s", My_horses[hcount].mother );
  }

  /* Now tell them what we know. */
  for (int i = 0 ; i<hcount ; i++ )
  {
    printf("\n\n%s is %d years old, %d hands high,",
             My_horses[i].name, My_horses[i].age, My_horses[i].height);
    printf(" and has %s and %s as parents.", My_horses[i].father,
                                                 My_horses[i].mother );
  }
  return 0;
}

