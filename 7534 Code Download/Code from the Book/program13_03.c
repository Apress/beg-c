/* Program 13.3 Test our timer function */
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <ctype.h>

int main(void)
{
  time_t calendar_start = time(NULL);       /* Initial calendar time    */
  clock_t cpu_start = clock();              /* Initial processor time   */
  int count = 0;                            /* Count of number of loops */
  const int iterations = 1000000;           /* Loop iterations          */
  char answer = 'y';


  printf("Initial clock time = %lu Initial calendar time = %lu\n",
                                     cpu_start, calendar_start);

  while(tolower(answer) == 'y')
  {
    for(int i = 0 ; i<iterations ; i++)
    {
      double x = sqrt(3.14159265);
    }
    printf("\n%ld square roots completed.", iterations*(++count));
    printf("\nDo you want to run some more(y or n)? ");

    scanf("\n%c", &answer);
  }

  clock_t cpu_end = clock();                /* Final cpu time           */
  time_t calendar_end = time(NULL);         /* Final calendar time      */

  printf("\nFinal clock time = %lu Final calendar time = %lu\n",
                                                       cpu_end, calendar_end);
  printf("\nCPU time for %ld iterations is %.2lf seconds\n",
                                count*iterations, ((double)(cpu_end-cpu_start))/CLOCKS_PER_SEC );

  printf("\nElapsed calendar time to execute the program is %8.2lf\n",
                                           difftime(calendar_end, calendar_start));
  return 0;
}

