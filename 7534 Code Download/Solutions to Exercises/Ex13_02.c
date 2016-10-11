/* Exercise 13.2 A function to produce a string containing the current time */
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

/******************************************
 * Function that returns time as a string *
 * arg = 0 result is in 12 hour format    *
 * arg = 1 result is in 24 hour format    *
 ******************************************/
char *time_str(int n)
{
  bool afternoon = true;
  time_t now = time(NULL);
  struct tm *ptime = localtime(&now);

  if(!n)
    if(ptime->tm_hour > 12)
    {
      afternoon = true;
      ptime->tm_hour -= 12;
    }
  static char result[12];
  sprintf(result, "%2d:%2d:%2d%s",
          ptime->tm_hour, ptime->tm_min, ptime->tm_sec, afternoon ? "pm" : "am");
  return result;
}

int main(void)
{
  printf("\nTime is %s", time_str(0));
  printf("\nTime is %s", time_str(1));
  return 0;
}
