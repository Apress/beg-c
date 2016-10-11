/* Program 3.9 Testing cases */
#include <stdio.h>

int main(void)
{
  char answer = 0;                /* Stores an input character */

  printf("Enter Y or N: ");
  scanf(" %c", &answer);

  switch (answer)
  {
    case 'y': case 'Y':
      printf("\nYou responded in the affirmative.");
      break;

    case 'n': case 'N':
      printf("\nYou responded in the negative.");
      break;

    default:
      printf("\nYou did not respond correctly...");
      break;
  }
  return 0;
}

