/* Program 13.1 Debugging using preprocessing directives */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Macro to generate pseudo-random number from 0 to NumValues */
#define random (NumValues) ((int)(((double)(rand())*(NumValues))/(RAND_MAX+1.0)))

#define iterations 6
#define test                            /* Select testing output       */
#define testf                           /* Select function call trace  */
#define repeatable                      /* Select repeatable execution */

/* Function prototypes */
int sum(int, int);
int product(int, int);
int difference(int, int);

int main(void)
{
  int funsel = 0;                      /* Index for function selection       */
  int a = 10, b = 5;                   /* Starting values                    */
  int result = 0;                      /* Storage for results                */

  /* Function pointer array declaration */
  int (*pfun[])(int, int) = {sum, product, difference};

  /* Conditional code for repeatable execution */
#ifdef repeatable
  srand(1);
#else
  srand((unsigned int)time(NULL));     /* Seed random number generation      */
#endif

  /* Execute random function selections */
  int element_count = sizeof(pfun)/sizeof(pfun[0]);
  for(int i = 0 ; i < iterations ; i++)
  {
    /* Generate random index to pfun array */

    funsel = random(element_count);
    if( funsel>element_count-1 )
    {
      printf("\nInvalid array index = %d", funsel);
      exit(1);
    }

 #ifdef test
    printf("\nRandom index = %d", funsel);
 #endif

    result = pfun[funsel](a , b);      /* Call random function               */
    printf("\nresult = %d", result );
  }
  return 0;
}

/* Definition of the function sum */
int sum(int x, int y)
{
#ifdef testf
  printf("\nFunction sum called args %d and %d.", x, y);
#endif

  return x + y;
}

/* Definition of the function product */
int product( int x, int y )
{
  #ifdef testf
  printf("\nFunction product called args %d and %d.", x, y);
  #endif

  return x * y;
}

/* Definition of the function difference */
int difference(int x, int y)
{
  #ifdef testf
  printf("\nFunction difference called args %d and %d.", x, y);
  #endif

  return x - y;
}

