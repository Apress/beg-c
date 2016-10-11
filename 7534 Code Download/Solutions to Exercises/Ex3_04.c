/*Exercise 3.4 A calculator that allows multiple calculations */
#include <stdio.h>

int main(void)
{
  double number1 = 0.0;                /* First operand value a decimal number  */
  double number2 = 0.0;                /* Second operand value a decimal number */
  char operation = 0;                  /* Operation - must be +, -, *, /, or %  */
  char answer = 0;                     /* Added to store answer for continuing  */

start:                                 /* Label added for goto destination */
   printf("\nEnter the calculation as number operator number\n"); /*Modified */
   scanf("%lf %c %lf", &number1, &operation, &number2);

  /* Code to check the input goes here */
  switch(operation)
  {
    case '+':                              /* No checks necessary for add       */
      printf("= %lf\n", number1 + number2);
      break;

    case '-':                               /* No checks necessary for subtract */
      printf("= %lf\n", number1 - number2);
      break;

    case '*':                               /* No checks necessary for multiply */
      printf("= %lf\n", number1 * number2);
      break;

    case '/':
      if(number2 == 0)                      /* Check second operand for zero    */
        printf("\n\n\aDivision by zero error!\n");
    else
      printf("= %lf\n", number1 / number2);
        break;

    case '%':                               /* Check second operand for zero    */
      if((long)number2 == 0)
        printf("\n\n\aDivision by zero error!\n");
    else
      printf("= %ld\n", (long)number1 % (long)number2);
        break;

    default:                          /* Operation is invalid if we get to here */
      printf("\n\n\aIllegal operation!\n");
  }
  /* The following statements added to prompt for continuing */
  printf("\n Do you want to do another calculation? (y or n): ");
  scanf(" %c", &answer);
  if(answer == 'y' || answer == 'Y')
    goto start;                       /* Go back to the beginning */
  return 0;
}

