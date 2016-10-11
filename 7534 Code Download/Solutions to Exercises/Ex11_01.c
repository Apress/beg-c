/* Exercise 11.1 Using a structure representing a length. */
#include <stdio.h>
#include <ctype.h>

#define INCHES_PER_FOOT 12
#define FEET_PER_YARD    3

struct Length
{
  unsigned int yards;
  unsigned int feet;
  unsigned int inches;
};

struct Length add(struct Length first, struct Length second);
void show(struct Length length);

int main(void)
{
  char answer = 'n';
  struct Length length;
  struct Length total = { 0,0,0};
  int i = 0;
  do
  {
    printf("Enter a length in yards, feet, and inches: ");
    scanf(" %d %d %d", &length.yards, &length.feet, &length.inches);
    total = add(total,length);
    printf("Do you want to enter another(y or n)?: ");
    scanf(" %c", &answer);
    fflush(stdin);
  }while(tolower(answer) == 'y');
  printf("The total of all the lengths is: ");
  show(total);
  printf("\n");
  return 0;
}

struct Length add(struct Length first, struct Length second)
{
  unsigned long inches = 0;
  struct Length sum;
  inches = first.inches + second.inches+
    INCHES_PER_FOOT*(first.feet+second.feet+FEET_PER_YARD*(first.yards+second.yards));
  sum.inches = inches%INCHES_PER_FOOT;
  sum.feet = inches/INCHES_PER_FOOT;
  sum.yards = sum.feet/FEET_PER_YARD;
  sum.feet %= FEET_PER_YARD;
  return sum;
}

void show(struct Length length)
{
  printf("%d yards %d feet %d inches", length.yards,length.feet, length.inches);
}
