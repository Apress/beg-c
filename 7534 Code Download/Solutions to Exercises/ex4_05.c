/* Ex4.5  A Modified Guessing Game */
#include <stdio.h>
#include <stdlib.h>                   /* I added this for the exercise */
#include <ctype.h>                    /* I added this for the exercise */

int main(void)
{
  int chosen = 15;                    /* The lucky number            */
  int guess = 0;                      /* Stores a guess              */
  int count = 3;                      /* The maximum number of tries */
  const int MAXVALUE = 20;                         /* I added this for the exercise */
  char answer = 'N';                               /* I added this for the exercise */

  printf("\nThis is a guessing game.");

  /* I changed the following statement for the exercise */
  printf("\nI have chosen a number between 1 and %d"
                                     " which you must guess.\n", MAXVALUE);
  do                                              /* I added this for the exercise */
  {                                               /* I added this for the exercise */

    chosen = rand()*(MAXVALUE-1.0)/RAND_MAX +1.0; /* I added this for the exercise */
    /* The calculation for chosen will be done as a floating-point calculation */
    /* because of the 1.0 in the first parentheses forces this. The result of  */
    /* the calculation will be automatically converted to type int because     */
    /* chosen is of type int.                                                  */

    count = 3;                                    /* I added this for the exercise */
    for( ; count>0 ; --count)
    {
      printf("\nYou have %d tr%s left.", count, count == 1 ? "y" : "ies");
      printf("\nEnter a guess: ");      /* Prompt for a guess  */
      scanf("%d", &guess);              /* Read in a guess     */

      /* Check for a correct guess */
      if (guess == chosen)
      {
        printf("\nYou guessed it!\n");
        return 0;                       /* End the program     */
      }

      /* Check for an invalid guess */
      if(guess<1 || guess > 20)
        printf("I said between 1 and 20.\n ");
      else
        printf("Sorry. %d is wrong.\n", guess);
    }
    printf("\nYou have had three tries and failed. The number was %d\n",
                                                                  chosen);
    printf("Do you want another go(Y or N)? ");   /* I added this for the exercise */
    scanf(" %c", &answer);                        /* I added this for the exercise */
  } while(toupper(answer) == 'Y');                /* I added this for the exercise */
  return 0;
}

