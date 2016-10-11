/* Program 11.8 The operation of a union */
#include <stdio.h>

int main(void)
{
  union u_example
  {
    float decval;
    int pnum;
    double my_value;
  } U1;

  U1.my_value = 125.5;
  U1.pnum = 10;
  U1.decval = 1000.5f;
  printf("\ndecval = %f   pnum = %d   my_value = %lf",
                     U1.decval, U1.pnum, U1.my_value );

  printf("\nU1 size = %d\ndecval size = %d   pnum size = %d   my_value"
                              " size = %d",sizeof U1, sizeof U1.decval,
                                  sizeof U1.pnum, sizeof U1.my_value);
  return 0;
}

