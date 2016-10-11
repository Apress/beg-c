/* Program 11.1 Exercising the horse */
#include <stdio.h>

int main(void)
{
  /* Structure declaration */
  struct horse
  {
    int age;
    int height;
    char name[20];
    char father[20];
    char mother[20];
  };

  struct horse My_first_horse;         /* Structure variable declaration   */

  /* Initialize  the structure variable from input data */
  printf("Enter the name of the horse: " );
  scanf("%s", My_first_horse.name );            /* Read the horse's name   */

  printf("How old is %s? ", My_first_horse.name );
  scanf("%d", &My_first_horse.age );            /* Read the horse's age    */

  printf("How high is %s ( in hands )? ", My_first_horse.name );
  scanf("%d", &My_first_horse.height );         /* Read the horse's height */

  printf("Who is %s's father? ", My_first_horse.name );
  scanf("%s", My_first_horse.father );          /* Get the father's name   */

  printf("Who is %s's mother? ", My_first_horse.name );
  scanf("%s", My_first_horse.mother );          /* Get the mother's name   */

  /* Now tell them what we know */
  printf("\n%s is %d years old, %d hands high,",
       My_first_horse.name, My_first_horse.age, My_first_horse.height);
  printf(" and has %s and %s as parents.\n", My_first_horse.father,
                                            My_first_horse.mother );
  return 0;
}

