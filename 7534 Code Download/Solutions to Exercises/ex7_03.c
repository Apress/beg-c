/* Exercise 7.3 Removing spaces and puctuation from a string */
#include <stdio.h>
#include <ctype.h>

#define BUFFER_LEN 500             /* Length of input buffer     */

int main(void)
{
   char buffer[BUFFER_LEN];        /* Input buffer                */
   char *pbuffer1 = buffer;        /* Pointer to buffer position  */
   char *pbuffer2 = buffer;        /* Pointer to buffer position  */

   /* Read a string */
   printf("Enter a string of up to %d characters:\n", BUFFER_LEN);
   while((*pbuffer1++ = getchar()) != '\n')
     ;
   *pbuffer1 = '\0';               /* Append string terminator         */
   pbuffer1 = buffer;              /* Reset pointer to start           */
   while(*pbuffer1 != '\0')        /* Loop until the end of the string */
   {
     if(ispunct(*pbuffer1) || isspace(*pbuffer1))
     {                             /* If it's space or puctuation   */
       ++pbuffer1;                 /* go to the next character      */
       continue;
     }
     else
       *pbuffer2++ = *pbuffer1++;  /* otherwise, copy the character */
   }
   *pbuffer2 = '\0';               /* Append string terminator      */
   printf("\nWith the spaces and punctuation removed, the string is now:\n%s\n", buffer);
	 return 0;
}

