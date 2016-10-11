/* Exercise 9.4 Convert one or more floating-point values into a single string */
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdbool.h>

char* to_string(int count, double first, ...);  /* Converts doubles to a string separated by commas */
char* fp_to_str(double x);                      /* Converts x to a string                           */
char* int_to_str(int n);                        /* Converts n to a string                           */

int main(void)
{
  char *str = NULL;                  /* Pointer to the string of values */
  double values[] = { 1.245, -3.5, 6.758, 33.399, -1.02 };

  printf("\nThe numerical valueas are:\n");
  for(int i = 0 ; i<5 ; i++)
    printf("%8.3f", values[i]);

  str = to_string(sizeof values/sizeof(double), values[0], values[1], values[2], values[3], values[4]);

  printf("\n\nThe string of values is:\n%s\n", str);

  free(str);                         /* Free memory for string */
  return 0;
}

/*******************************************************************
 * Function to convert one or more floating-point values to a      *
 * string with the values separated by commas.                     *
 * This function allocates memory that must be freed by the caller *
 *******************************************************************/
char* to_string(int count, double first, ...)
{
  va_list parg = NULL;          /* Pointer to variable argument   */
  char* str = NULL;             /* Pointer to the joined strings  */
  char *temp = NULL;            /* Temporary string pointer       */
  char *value_str = 0;          /* Pointer to a value string      */
  const char *separator = ",";  /* Separator in values string     */
  size_t separator_length = 0;  /* Length of separator string     */
  size_t length = 0;            /* Length of a string             */
  int i = 0;                    /* Loop counter                   */

  separator_length = strlen(separator);

  va_start(parg,first);         /* Initialize argument pointer */

  str = fp_to_str(first);       /* convert the first value     */

  /* Get the remaining arguments, convert them and append to the string */
  while(--count>0)
  {
    value_str = fp_to_str(va_arg(parg, double));    /* Get next argument */
    length = strlen(str) + strlen(value_str) + separator_length +1;
    temp = (char*)malloc(length); /* Allocate space for string with argument added */
    strcpy(temp, str);            /* Copy the old string         */
    free(str);                    /* Release old memory          */
    str = temp;                   /* Store new memory address    */
    temp = NULL;                  /* Reset pointer               */
    strcat(str,separator);        /* Append separator            */
    strcat(str,value_str);        /* Append value string         */
    free(value_str);              /* Release value string memory */
  }
  va_end(parg);                   /* Clean up arg pointer        */
  return str;
}

/***************************************************************************
 * Converts the floating-point argument to a string.                       *
 * Result is with two decimal places.                                      *
 * Memory is allocated to hold the string and must be freed by the caller. *
 ***************************************************************************/
char* fp_to_str(double x)
{
  char *str = NULL;                 /* Pointer to string representation     */
  char *integral = NULL;            /* Pointer to integral part as string   */
  char *fraction = NULL;            /* Pointer to fractional part as string */
  size_t length = 0;                /* Total string length required         */

  integral = int_to_str((int)x);    /* Get integral part as a string with a sign */

  /* Make x positive */
  if(x<0)
    x = -x;
  /* Get fractional part as a string */
  fraction = int_to_str((int)(100.0*(x+0.005-(int)x)));

  length = strlen(integral)+strlen(fraction)+2;  /* Total length including point and terminator */

  /* Fraction must be two digits so allow for it */
  if(strlen(fraction)<2)
    ++length;

  str = (char*)malloc(length);        /* Allocate memory for total */
  strcpy(str, integral);              /* Copy the integral part    */
  strcat(str, ".");                   /* Append decimal point      */

  if(strlen(fraction)<2)              /* If fraction less than two digits */
    strcat(str,"0");                  /* Append leading zero       */

  strcat(str, fraction);              /* Append fractional part    */

  /* Free up memory for parts as strings */
  free(integral);
  free(fraction);

  return str;
}

/***************************************************************************
 * Converts the integer argument to a string.                              *
 * Memory is allocated to hold the string and must be freed by the caller. *
 ***************************************************************************/
char* int_to_str(int n)
{
  char *str = NULL;                    /* pointer to the string */
  int length = 1;                      /* Number of characters in string(at least 1 for terminator */
  int temp = 0;
  bool negative = false;               /* Indicates sign of n */

  /* Check for negative value */
  if(negative = (n<0))
  {
    n = -n;
    ++length;                          /* For the minus character */
  }

  /* Increment length by number of digits in n */
  temp = n;
  do
  {
    ++length;
  }
  while((temp /= 10)>0);

  str = (char*)malloc(length);        /* Allocate space required */

  if(negative)                        /* If it was negative      */
    str[0] = '-';                     /* Insert the minus sign   */

  str[--length] = '\0';               /* Add the terminator to the end */

  /* Add the digits starting from the end */
  do
  {
    str[--length] = '0'+n%10;
  }while((n /= 10) > 0);

  return str;
}
