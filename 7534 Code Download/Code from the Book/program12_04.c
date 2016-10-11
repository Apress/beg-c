/* Program 12.4  A prime example using binary files */
#include <stdio.h>
#include <stdlib.h>
#include <math.h >                     /* For square root function sqrt() */

/* Function prototypes */
int test_prime(unsigned long long N);
void put_primes(void);
int check(unsigned long long buffer[], size_t count, unsigned long long N);

/* Global data */
const unsigned int MEM_PRIMES = 100;  /* Count of number of primes in memory */

struct
{
  char *filename;                                  /* File name for primes   */
  FILE *pfile;                                     /* File stream pointer    */
  int nrec;                                        /* Number of file records */

  unsigned long long primes[MEM_PRIMES];           /* Array to store primes  */
  size_t index;                    /* Index of free location in array primes */

} global = { "C:\\myfile.bin",                     /* Physical file name     */
             NULL,                                 /* File pointer value     */
             0,                                    /* File record count      */
             {2ULL, 3ULL, 5ULL},                   /* primes array values    */
             3                                     /* Number of primes       */
           };


int main(void)
{
  unsigned long long trial = 5ULL;                        /* Prime candidate */
  unsigned long num_primes = 3UL;                         /* Prime count     */
  unsigned long total = 0UL;                              /* Total required  */

  printf("How many primes would you like?  ");
  scanf("%lu", &total);                 /* Total is how many we need to find */
  total = total<4UL ? 4UL:total;        /* Make sure it is at least 4        */

  /* Prime finding and storing loop */
  while(num_primes < total)             /* Loop until we get total required  */
  {
    trial += 2ULL;                      /* Next value for checking           */
    if(test_prime(trial))               /* Check if trial is prime           */
    {                                   /* Positive value means prime        */
      global.primes[global.index++] = trial;   /* so store it                */
      num_primes++;                     /* Increment total number of primes  */

      if(global.index == MEM_PRIMES)    /* Check if array is full            */
      {
        /* File opened OK?   */
        if(!(global.pfile = fopen(global.filename, "ab")))
        { /* No, so explain and end the program */
          printf("\nUnable to open %s to append\n", global.filename);
          exit(1);
        }
        /* Write the array    */
        fwrite(global.primes, sizeof(unsigned long long),
                                               MEM_PRIMES, global.pfile);

        fclose(global.pfile);              /* Close the file                  */
        global.index = 0U;                 /* Reset count of primes in memory */
        global.nrec++;                     /* Increment file record count     */
      }
    }
  }

  if(total>MEM_PRIMES)                   /* If we wrote some to file         */
    put_primes();                        /* Display the contents of the file */
  if(global.index)                       /* Display any left in memory       */
    for(size_t i = 0; i<global.index ; i++)
    {
      if(i%5 == 0)
        printf("\n");                              /* Newline after five     */
      printf("%12llu", global.primes[i]);          /* Output a prime         */
    }

  if(total>MEM_PRIMES)                             /* Did we need a file?    */
    if(remove(global.filename))                    /* then delete it.        */
      printf("\nFailed to delete %s\n", global.filename); /* Delete failed   */
    else
      printf("\nFile %s deleted.\n", global.filename);    /* Delete OK       */
  return 0;
}

/*******************************************************************
 * Function to test if a number, N, is prime using primes in       *
 * memory and on file                                              *
 * First parameter N - value to be tested                          *
 * Return value - a positive value for a prime, zero otherwise     *
 *******************************************************************/
int test_prime(unsigned long long N)
{
  unsigned long long buffer[MEM_PRIMES]; /* local buffer for primes from file */

  int k = 0;

  if(global.nrec > 0)                            /* Have we written records? */
  {
    if(!(global.pfile = fopen(global.filename, "rb"))) /* Then open the file */
    {
      printf("\nUnable to open %s to read\n", global.filename);
      exit(1);
    }

    for(size_t i = 0; i < global.nrec ; i++)
    { /* Check against primes in the file first */
      /* Read primes */
      fread(buffer, sizeof( long long), MEM_PRIMES, global.pfile);
      if((k = check(buffer, MEM_PRIMES, N)) >= 0)  /* Prime or not?          */
      {
        fclose(global.pfile);                      /* Yes, so close the file */
        return k;                                  /* 1 for prime, 0 for not */
      }
    }
    fclose(global.pfile);                          /* Close the file         */
  }

  return check(global.primes, global.index, N); /* Check against primes in memory */
}

/*******************************************************************
 * Function to check whether an integer, N, is divisible by any    *
 * of the elements in the array pbuffer up to the square root of N.*
 * First parameter buffer - an array of primes                     *
 * second parameter count - number of elements in pbuffer          *
 * Third parameter N - the value to be checked                     *
 * Return value - 1 if N is prime, zero if N is not a prime,       *
 *               -1 for more checks                                *
 *******************************************************************/
int check(unsigned long long buffer[], size_t count, unsigned long long N)
{
  /* Upper limit */
  unsigned long long root_N = (unsigned long long)(1.0 + sqrt(N));

  for(size_t i = 0 ; i<count ; i++)
  {
    if(N % buffer[i] == 0ULL )               /* Exact division?              */
      return 0;                              /* Then not a prime             */

    if(buffer[i] > root_N)                   /* Divisor exceeds square root? */
      return 1;                              /* Then must be a prime         */
  }
  return -1;                                 /* More checks necessary...     */
}

/*******************************************
 * Function to output primes from the file *
 *******************************************/
void put_primes(void)
{
  unsigned long long buffer[MEM_PRIMES];      /* Buffer for a block of primes */

  if(!(global.pfile = fopen( global.filename, "rb"))) /* Open the file        */
  {
    printf("\nUnable to open %s to read primes for output\n", global.filename);
    exit(1);
  }

  for (size_t i = 0U ; i< global.nrec ; i++)
  {
    /* Read a block of primes   */
    fread(buffer, sizeof( unsigned long long), MEM_PRIMES, global.pfile);

    for(size_t j = 0 ; j<MEM_PRIMES ; j++)             /* Display the primes */
    {
      if(j%5 == 0U)                                    /* Five to a line     */
        printf("\n");
      printf("%12llu", buffer[j]);                     /* Output a prime     */
    }
  }
  fclose(global.pfile);                                /* Close the file     */
}

