/* Program 13.5        Getting the day for a given date */
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
  enum sufindex { st, nd, rd, th } sufsel = th;  /* Suffix selector */

  int day = 0;                         /* Stores a day...           */
  int month = 0;                       /* month...                  */
  int year = 0;                        /* and year for a date       */

  struct tm birthday;                  /* A birthday time structure */

  /* Set the structure members we don't care about */
  birthday.tm_hour = birthday.tm_min = 0;
  birthday.tm_sec = 1;
  birthday.tm_isdst = -1;

  printf("Enter your birthday as integers, day month year."
             "\ne.g. Enter 1st February 1985 as 1 2 1985. : ");
  scanf(" %d %d %d", &day, &month, &year);

  birthday.tm_mon = month-1;
  birthday.tm_mday = day;
  birthday.tm_year = year-1900;

  if(mktime(&birthday) == (time_t)-1)
  {
    printf("\nOperation failed.");
    return 0;
  }

  switch(birthday.tm_mday)
  {
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

  printf("\nYour birthday, the %d%s %s %d, was a %s",
                 birthday.tm_mday, Suffix[sufsel], Month[birthday.tm_mon],
                            1900 + birthday.tm_year, Day[birthday.tm_wday]);

  return 0;
}

