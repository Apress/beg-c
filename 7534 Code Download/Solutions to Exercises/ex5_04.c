/*Exercise 5.4 Table of reciprocals, squares, cubes, and fourth powers. */
#include <stdio.h>

int main(void)
{
  double data[11][5];                   /* Stores data values          */
  double value = 2.0;                   /* Value to be stored in array */
  int row = 0;                          /* Loop index                  */
  int col = 0;                          /* Loop index                  */


  for(int row = 0 ; row<11 ; row++)
	{
    data[row][0] = value;
		value += 0.1;
  }

  for(int row = 0 ; row<11 ; row++)
  {
    data[row][1] = 1.0/data[row][0];               /* 1/x     */
    data[row][2] = data[row][0]*data[row][0];      /* x*x     */
    data[row][3] = data[row][2]*data[row][0];      /* x*x*x   */
    data[row][4] = data[row][3]*data[row][0];      /* x*x*x*x */
  }


  printf("\n           x   ");
  printf("          1/x  ");
  printf("          x*x  ");
  printf("         x*x*x ");
  printf("        x*x*x*x");

    for(int row = 0 ; row<11 ; row++)
  {
    printf("\n");
    for(col = 0 ; col<5 ; col++)
      printf("%15.4lf", data[row][col]);
  }

  printf("\n");
	return 0;
}

