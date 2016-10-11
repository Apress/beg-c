/*Exercise 4.1 Generate a multiplication table */
#include <stdio.h>

int main(void)
{
  int width = 0;                       /* Box width       */
  int height = 0;                      /* Box height      */

  printf("Enter the box width and height size separated by a space: ");
  scanf("%d", &width);
  scanf("%d", &height);

  for(int row = 0 ; row<height ; row++)
  {
    printf("\n");                      /* Start new row      */
    for(int col = 0 ; col<width ; col++)
    {
      if(row == 0||row==height-1)      /* 1st or last row?    */
      {
          printf("*");                 /* Yes - all asterisks */
          continue;
      }
      /* An * in 1st & last column, otherwise a space */
      printf("%c", ((col==0 || col==width-1) ? '*' :' '));
    }
  }
  printf("\n");
	return 0;
}

