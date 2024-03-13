#include "./../s21_decimal.h"

// Возвращает результат умножения указанного Decimal на -1.

int s21_negate(s21_decimal value, s21_decimal *result) {
  s21_copy(s21_reset(result), s21_getSign(value) ? *s21_setSign(&value, 0)
                                                 : *s21_setSign(&value, 1));
  return 0;
}