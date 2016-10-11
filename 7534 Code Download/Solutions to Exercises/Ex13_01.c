/* Exercise 13.1 Defining a COMPARE(x,y) macro */
/*
  One advantage of the compare macro is that is works with numeric values of any type.
  Another advantage is that there is no function call overhead.
  A disadvantage is the the result is a literal that is an integer. If you were to
  assume the result was the same as the arguments to the macro in the printf()
  calls for floating-point value arguments you would get the wrong result.
*/
#include <stdio.h>

#define COMPARE(x,y) (((x)<(y)) ? -1 : (((x)==(y)) ? 0 : 1))


int main(void)
{
  int a = 5, b = 5, c = 10;
  printf("\n COMPARE(%d, %d) = %d", a, b, COMPARE(a,b));
  printf("\n COMPARE(%d, %d) = %d", a, c, COMPARE(a,c));
  printf("\n COMPARE(%d, %d) = %d", c, b, COMPARE(c,b));
  printf("\n COMPARE(%d, %d) = %d", a+b, c-b, COMPARE(a+b,c-b));

  double x = 24.5, y = 28.0, z = 3.5;
  printf("\n COMPARE(%.2f, %.2f) = %d", x, y, COMPARE(x,y));
  printf("\n COMPARE(%.2f, %.2f) = %d", y, z, COMPARE(y,z));
  printf("\n COMPARE(%.2f, %.2f) = %d", x+z, y, COMPARE(x+z,y));
  return 0;
}
