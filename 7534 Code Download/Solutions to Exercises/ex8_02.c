/* Exercise 8.2 A function to return a string representation of an integer */
#include <stdio.h>
#include <stdbool.h>

/* Convert an integer to a string        */
/* Caller must allocate string array     */
/* Function returns the string to allow  */
/* Use of the function in an expression. */
char* itoa(int n, char str[])
{
  int i = 0;               /* Loop counter              */
  bool negative = 0;       /* Indicate negative integer */
  int length = 0;          /* Length of string          */
  int temp = 0;            /* Temporary storage         */

  if(negative = (n<0))     /* Is it negative?  */
    n = -n;                /* make it positive */

  /* Generate digit characters in reverse order */
  do
  {
    str[i++] = '0'+n%10;    /* Create a rightmost digit        */
    n /= 10;                /* Remove the digit                */
  }while(n>0);              /* Go again if there's more digits */

  if(negative)              /* If it was negative */
    str[i++] = '-';         /* Append minus       */
  str[i] = '\0';            /* Append terminator  */
  length = i;               /* Save the length    */

  /* Now reverse the string in place */
  /* by switching first and last,    */
  /* second and last but one, etc    */
  for(i = 0 ; i<length/2 ;i++)
  {
    temp = str[i];
    str[i] = str[length-i-1];
    str[length-i-1] = temp;
  }
  return str;                /* Return the string */
}


int main(void)
{
   char str[15];              /* Stores string representation of integer */
   long testdata[] = { 30L, -98L, 0L, -1L, 999L, -12345L};

   for (int i = 0 ; i< sizeof testdata/sizeof(long) ; i++)
     printf("Integer value is %d, string is %s\n", testdata[i], itoa(testdata[i],str));
   return 0;
}

