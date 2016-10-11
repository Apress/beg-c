/* Exercise 7.2 Storing and displaying proverbs in order of length */
/***************************************************************************
 * This program will read any number of proverbs of any length.            *
 * The input buffer has a default size that is increased automatically     *
 * if it is not large enough. The current contents of the old buffer       *
 * are copied to the new and the old buffer is released before input       *
 * continues.                                                              *
 * The same applies to the number of proverbs. If the initial capacity     *
 * for pointers to proverbs is exceeded, a larger space is allocated       *
 * and the existing pointers are copied to the new memory before releasing *
 * the old memory.                                                         *
 * You could add printf() statements to record when new memory is allocated*
 * Values for BUFFER_LEN, BUFFER_LEN_INCR, and CAPACITY_INCR are set low   *
 * so as to cause frequent reallocation of memory for you to track.        *
 * In a practical program they would be set much higher to avoid           *
 * frequent allocation and release of memory.                              *
****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_LEN 5          /* Initial length of input buffer     */
#define BUFFER_LEN_INCR 2     /* Increment to buffer length         */
#define CAPACITY_INCR 2       /* Increment to capacity for proverbs */

int main(void)
{
   char **pProverbs = NULL;        /* Pointer to string pointer           */
   char **temp = NULL;             /* Temporary pointer to string pointer */
   int capacity = 0;               /* Number of proverbs that can be stored */
   int count = 0;                  /* Number of proverbs read               */
   char *pbuffer = NULL;           /* Pointer to buffer        */
   char *pstart = NULL;            /* Pointer to buffer start  */
   char *pstr = NULL;              /* Pointer to a string      */
   int buffer_length = BUFFER_LEN; /* Buffer length            */

   pbuffer = (char*)malloc(BUFFER_LEN);  /* Initial buffer size   */
   pstart = pbuffer;                     /* Store start of buffer */

   for(;;)
   {
     if(count==capacity)
     {
       capacity += CAPACITY_INCR;
       temp = (char**)malloc(capacity*sizeof(char*));
       if(!temp)              /* If memory was not allocated */
       {                      /* Output a message  and end   */
         printf("Memory allocation failed. Terminating program.");
         exit(1);
       }

       if(!pProverbs)         /* Are there any proverbs?                 */
         pProverbs = temp;    /* No - so just copy address of new memory */
       else                   /* Yes - so copy data from old to new      */
       {
         for(int i = 0 ; i<count ; i++)
           *(temp+i) = *(pProverbs+i);
         free(pProverbs);     /* Free the old memory */
         pProverbs = temp;    /* Copy address of new */
       }
       temp = NULL;           /* Reset pointer       */
     }
      printf("Enter a proverb or press Enter to end:\n");

     /* Read a proverb */
     while((*pbuffer++ = getchar()) != '\n')
     {
       if(pbuffer-pstart == buffer_length)     /* Check for buffer full  */
       {
         buffer_length += BUFFER_LEN_INCR;     /* Increase buffer length */
         pstr = (char*)malloc(buffer_length);  /* Allocate new buffer    */

         /* Copy old buffer contents to new */
         for(int i = 0; i<pbuffer-pstart ; i++)
           *(pstr+i) = *(pstart+i);

         pbuffer = pstr+(pbuffer-pstart);      /* Address of next position in new */
         free(pstart);                         /* Release old buffer memory       */
         pstart = pstr;                        /* Set to start of new buffer      */
         pstr = NULL;                          /* Reset pointer                   */
       }
     }

     /* check for empty line indicating end of input */
     if((pbuffer-pstart)<2)
       break;

     /* Check for string too long */
     if((pbuffer - pstart) == BUFFER_LEN && *(pbuffer-1)!= '\n')
     {
       printf("String too long – maximum %d characters allowed.",
                                                       BUFFER_LEN);
       pbuffer = pstart;
       continue;
     }
     *(pbuffer-1) = '\0';                  /* Add string terminator */
     pbuffer = pstart;

     *(pProverbs+count) = (char*)malloc(strlen(pstart)+1);
     strcpy(*(pProverbs+count++),pstart);
   }

   /* Order the proverbs from shortest to longest */
  for(int i = 0 ; i<count-1 ; i++)
    for(int j = i+1 ; j<count ; j++)
      if(strlen(*(pProverbs+i))>strlen(*(pProverbs+j)))
      {
        pstr = *(pProverbs+i);
        *(pProverbs+i) = *(pProverbs+j);
        *(pProverbs+j) = pstr;
      }

   /* Output all the strings */
   printf("\nIn ascending length order, the proverbs you entered are:\n");
   for (int i = 0 ; i<count ; i++ )
   {
      printf("\n%s", *(pProverbs + i));
      free(*(pProverbs + i));   /* Release the memory for the proverb  */
      *(pProverbs + i) = NULL;  /* Set pointer back to NULL for safety */
   }
   free(pProverbs);             /* Release memory for the pointers     */
   free(pstart);                /* Release memory for the buffer       */
}

