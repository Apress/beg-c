/* Program 8.6 The functional approach to string sorting */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool str_in(const char **);            /* Function prototype for str_in    */
void str_sort(const char *[], int);    /* Function prototype for str_sort  */
void swap( void **p1,  void **p2);     /* Swap two pointers                */
void str_out(char *[], int);           /* Function prototype for str_out   */

const size_t BUFFER_LEN =  256;
const size_t NUM_P = 50;

/* Function main - execution starts here */
int main(void)
{
  char *pS[NUM_P];                     /* Array of string pointers         */
  int count = 0;                       /* Number of strings read           */

  printf("\nEnter successive lines, pressing Enter at the end of"
                         " each line.\nJust press Enter to end.\n");

  for(count = 0; count < NUM_P ; count++)        /* Max of NUM_P strings   */
    if(!str_in(&pS[count]))                      /* Read a string          */
      break;                                     /* Stop input on 0 return */

  str_sort( pS, count);                          /* Sort strings           */
  str_out( pS, count);                           /* Output strings         */
  return 0;
}

/*******************************************************
 *      String input routine                           *
 *  Argument is a pointer to a pointer to a constant   *
 *  string which is const char**                       *
 *  Returns false for empty string and returns true    *
 *  otherwise. If no memory is obtained or if there    *
 *  is an error reading from the keyboard, the program *
 *  is terminated by calling exit().                   *
 *******************************************************/
bool str_in(const char **pString)
{
  char buffer[BUFFER_LEN];            /* Space to store input string  */

  if(gets(buffer) == NULL )           /* NULL returned from gets()?   */
  {
    printf("\nError reading string.\n");
    exit(1);                          /* Error on input so exit       */
  }

  if(buffer[0] == '\0')               /* Empty string read?           */
    return false;

  *pString = (char*)malloc(strlen(buffer) + 1);

  if(*pString == NULL)                /* Check memory allocation      */
  {
    printf("\nOut of memory.");
    exit(1);                          /* No memory allocated so exit  */
  }

  strcpy(*pString, buffer);           /* Copy string read to argument */
  return true;
}

/****************************************************
 *      String sort routine                         *
 * First argument is array of pointers to strings   *
 * which is of type char*[].                        *
 * Second argument is the number of elements in the *
 * pointer array - i.e. the number of strings       *
 ****************************************************/
void str_sort(const char *p[], int n)
{
  char *pTemp = NULL;                 /* Temporary pointer               */
  bool sorted = false;                /* Strings sorted indicator        */
  while(!sorted)                      /* Loop until there are no swaps   */
  {
    sorted = true;                    /* Initialize to indicate no swaps */
    for(int i = 0 ; i<n-1 ; i++ )
      if(strcmp(p[i], p[i + 1]) > 0)
      {
        sorted = false;               /* indicate we are out of order    */
        swap(&p[i], &p[i+1]);         /* Swap the pointers               */
      }
  }
}

/****************************************************
 *      String output routine                       *
 * First argument is an array of pointers to        *
 * strings which is the same as char**              *
 * The second argument is a count of the number of  *
 * pointers in the array i.e. the number of strings *
 ****************************************************/
void str_out(char *p[] , int n)
{
  printf("\nYour input sorted in order is:\n\n");
  for (int i = 0 ; i<n ; i++)
  {
    printf("%s\n", p[i]);             /* Display a string           */
    free(p[i]);                       /* Free memory for the string */
    p[i] = NULL;
  }
  return;
}

/******************************************
*      Swap two pointers                  *
* The arguments are type pointer to void* *
* so pointers can be any type*.           *
*******************************************/

void swap( void **p1,  void **p2)
{
  void *pt = *p1;
  *p1 = *p2;
  *p2 = pt;
}

