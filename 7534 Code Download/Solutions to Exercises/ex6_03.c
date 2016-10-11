/* Exercise 6.3 A random thought for the day */
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(void)
{
  char thoughts[][50] = {"Wherever you go, there you are!",
                         "A nod is as good as a wink to a blind horse.",
                         "Many hands make light work.",
                         "Too many cooks spoil the broth.",
                         "A rolling stone gathers no moss.",
                         "A wise man will cover the hole in his carpet."};

  srand((unsigned int)time(NULL));

  printf("Today's thought is:\n%s\n", thoughts[rand()%(sizeof thoughts/sizeof thoughts[0])]);
  return 0;
}

