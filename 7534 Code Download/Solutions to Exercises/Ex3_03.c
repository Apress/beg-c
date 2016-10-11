/* Exercise 3.3 Calculate a discounted price */
#include <stdio.h>

int main(void)
{
  const int level1 = 30;           /* Quantity over this level are at discount1 */
  const int level2 = 50;           /* Quantity over this level are at discount2 */
  const double discount1 = 0.10;   /* 10% discount */
  const double discount2 = 0.15;   /* 15% discount */
  const double unit_price = 3.50;
  int quantity = 0;
  int save_qty = 0;
  int qty_over_level1 = 0;
  int qty_over_level2 = 0;
  printf("Enter the quantity that you require: ");
  scanf("%d", &quantity);
  save_qty = quantity;

  qty_over_level2 = quantity%level2;
  quantity -= qty_over_level2;        /* Reduce total by level2 quantity       */
  qty_over_level1 = quantity%level1;  /* Quantity over level1 and under level2 */
  quantity -= qty_over_level1;        /* Quantity at no discount               */

  printf("\nThe total price for %d is $%.2lf\n", save_qty,
    unit_price*(quantity + (1.0-discount1)*qty_over_level1 + (1.0-discount2)*qty_over_level2));
  return 0;
}
