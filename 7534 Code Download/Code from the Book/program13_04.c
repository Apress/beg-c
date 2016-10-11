/* Program 13.4        Getting date data with ease */
#include <stdio.h>
#include <time.h>

int main(void)
{
  const char *Day[7] = {
                   "Sunday"  , "Monday", "Tuesday", "Wednesday",
                   "Thursday", "Friday", "Saturday"
                       };
  const char *Month[12] = {
                     "January",   "February", "March",    "April",
                     "May",       "June",     "July",     "August",
                     "September", "October",  "November", "December"
                          };
  const char *Suffix[4] = { "st", "nd", "rd", "th" };
  enum sufindex { st, nd, rd, th } sufsel = th;       /* Suffix selector */

  struct tm *OurT = NULL;              /* Pointer for the time structure */
  time_t Tval = 0;                     /* Calendar time                  */

  Tval = time(NULL);                   /* Get calendar time              */
  OurT = localtime(&Tval);             /* Generate time structure        */

  switch(OurT->tm_mday)
  {
    case 1: case 21: case 31:
      sufsel= st;
      break;
    case 2: case 22:
      sufsel= nd;
      break;
    case 3: case 23:
      sufsel= rd;
      break;
    default:
      sufsel= th;
      break;
  }

  printf("Today is %s the %d%s %s %d", Day[OurT->tm_wday],
    OurT->tm_mday, Suffix[sufsel], Month[OurT->tm_mon], 1900 + OurT->tm_year);
  printf("\nThe time is %d : %d : %d",
    OurT->tm_hour, OurT->tm_min, OurT->tm_sec );
  return 0;
}

