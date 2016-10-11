/* Example 6.4 Arrays of strings */
#include <stdio.h>

int main(void)
{
  char str[][40] =  {
                      "To be or not to be"   ,
                      ", that is the question"
                    };
  int count[] = {0, 0};                /* Lengths of strings  */

  /* find the lengths of the  strings */
  for(int i = 0 ; i<2 ; i++)
    while (str[i][count[i]])
      count[i]++;

  /* Check that we have enough space for both strings  */
  if(sizeof str[0] < count[0] + count[1] + 1)
    printf("\nYou can't put a quart into a pint pot.");
  else
  {  /* Copy 2nd string to first */
    count[1] = 0;
    while((str[0][count[0]++] = str[1][count[1]++]));

    printf("\n%s\n", str[0]);    /* Output combined string */
  }
  return 0;
}

