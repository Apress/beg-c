/* Exercise 10.3 A function to output double values in a given width. */
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_COUNT 100

void show(double array[], size_t array_size, unsigned int field_width);

void main()
{
  double array[MAX_COUNT] = {0.0};
  int count = 0;
  char answer = 'n';
  do
  {
    printf("Enter a value: ");
    scanf("%lf", &array[count++]);
    printf("Do you want to enter another (y or n)?: ");
    scanf(" %c",&answer);
  }while(count<= MAX_COUNT && tolower(answer) == 'y');

  show(array, count, 12);
  
   printf("\n");
}

void show(double array[], size_t array_size, unsigned int field_width)
{
  char format[10] = "%";   /* Holds the format string */
  char width_str[4];       /* Holds the width value in character form */
  size_t i = 0;
  size_t j = 1;

  /* Get width value as characters */
  do
  {
    width_str[i++] = '0'+field_width%10;
  }while((field_width /= 10) != 0);

  /* Append width characters in reverse order to format */
  do
  {
    format[j++] = width_str[--i];
  }while(i>0);
  format[j] = '\0';
  strcat(format, "lf");     /* Append specification for double */

  /* Output the values five to a line */
  for(j = 0 ; j<array_size ; j++)
  {
    if(j%5 == 0)
      printf("\n");
    printf(format, array[j]);
  }
}
