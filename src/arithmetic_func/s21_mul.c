#include "./../s21_decimal.h"

// Умножение

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_decimal temp = {0};
  s21_decimal val1 = {0};
  int res = 0;
  int pow = 1;
  int sign;
  int exp1;
  int exp2;
  exp1 = s21_getScale(value_1);
  exp2 = s21_getScale(value_2);
  sign = s21_getSign(value_1) != s21_getSign(value_2) ? 1 : 0;
  pow = exp1 * exp2;
  int shift_status = 0;
  if (pow > 28) {
    return POSITIVE_OVERFLOW;
  }
  s21_decimal low = s21_is_less(value_1, value_2) ? value_1 : value_2;
  s21_decimal high = s21_is_less(value_2, value_1) ? value_2 : value_1;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 32; j++) {
      if (get_bit(low.bits[i], j)) {
        val1 = high;
        if (res) {
          if (!shift_status || sign == 0) {
            return POSITIVE_OVERFLOW;
          } else {
            return NEGATIVE_OVERFLOW;
          }
        }
        shift_status = lshifts(&val1, j);
        res = s21_add(temp, val1, &temp);
      }
    }
  }
  *result = temp;
  s21_setScale(result, pow);
  s21_setSign(result, sign);
  return res;
}