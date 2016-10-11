/* Program 2.4 Simple calculations */
#include <stdio.h>

int main(void)
{
  int Total_Pets;
  int Cats;
  int Dogs;
  int Ponies;
  int Others;

  /* Set the number of each kind of pet */
  Cats = 2;
  Dogs = 1;
  Ponies = 1;
  Others = 46;

  /* Calculate the total number of pets */
  Total_Pets = Cats + Dogs + Ponies + Others;

  printf("We have %d pets in total", Total_Pets);  /* Output the result */
  return 0;
}

