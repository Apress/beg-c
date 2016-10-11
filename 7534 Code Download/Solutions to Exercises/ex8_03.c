/* Exercise 8.3 A function to return a string representation of an integer with a given width */
#include <stdio.h>

/* Convert an integer to a string with a fixed width.      */
/* if the widh is too small, the minimum width is assumed. */
char* itoa(int n, char str[], int width)
{
  int i = 0;               /* Loop counter              */
  int j = 0;               /* Loop counter              */
  int negative = 0;        /* Indicate negative integer */
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

  /* Shift the string to the right and insert blanks */
  if(width>length)
  {
    for(i=length, j = width ; i>= 0 ; i--, j--)
      str[j] = str[i];
    for(i = 0 ; i<width-length ; i++)
      str[i] = ' ';
  }
  return str;                /* Return the string */
}


int main(void)
{
   char str[15];              /* Stores string representation of integer */
   long testdata[] = { 30L, -98L, 0L, -1L, 999L, -12345L};

   for (int i = 0 ; i< sizeof testdata/sizeof(long) ; i++)
     printf("Integer value is %10d, string is %s\n", testdata[i], itoa(testdata[i],str, 14));
   return 0;
}

