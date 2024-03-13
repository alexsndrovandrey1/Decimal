#include "./../s21_decimal.h"

//  Возвращает целые цифры указанного Decimal числа;
// любые дробные цифры отбрасываются, включая конечные нули.

int s21_truncate(s21_decimal value, s21_decimal *result) {
  s21_copy(s21_reset(result),
           s21_getScale(value) ? *s21_decreaseScale(&value, s21_getScale(value))
                               : value);
  return 0;
}
