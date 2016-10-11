/* Program 6.3 Joining strings */
#include <stdio.h>

int main(void)
{
  char str1[40] = "To be or not to be";
  char str2[] = ",that is the question";
  int count1 = 0;                /* Length of str1 */
  int count2 = 0;                /* Length of str2 */

  /* find the length of the first string */
  while (str1[count1])          /* Increment count till we reach the string */
    count1++;                   /* terminating character.                 */

  /* Find the length of the second string */
  while (str2[count2])          /* Count characters in second string      */
    count2++;

  /* Check that we have enough space for both strings  */
  if(sizeof str1 < count1 + count2 + 1)
    printf("\nYou can't put a quart into a pint pot.");
  else
  {  /* Copy 2nd string to end of the first  */

     count2 = 0;                 /* Reset index for str2 to 0   */
    while(str2[count2])          /* Copy up to null from str2   */
      str1[count1++] = str2[count2++];

    str1[count1] = '\0';         /* Make sure we add terminator */
    printf("\n%s\n", str1 );     /* Output combined string      */

  }
  return 0;
}

