/* Program 10.3 Floating-Point Input */
#include <stdio.h>

int main(void)
{
  float fp1 = 0.0f;
  float fp2 = 0.0f;
  float fp3 = 0.0f;
  int value_count = 0;

  printf("Input:\n");
  value_count = scanf("%f %f %f", &fp1, &fp2, &fp3);

/* Alternative to statement above
  value_count = scanf("%e %g %f", &fp1, &fp2, &fp3);
*/

  printf("\nOutput:\n");
  printf("Return value = %d", value_count);
  printf("\nfp1 = %f  fp2 = %f  fp3 = %f\n", fp1, fp2, fp3);
  return 0;
}

