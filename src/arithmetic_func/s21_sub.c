#include "./../s21_decimal.h"

// Вычитание

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal* result) {
  int status = 0, sign_1 = s21_getSign(value_1), sign_2 = s21_getSign(value_2);
  for (int i = 0; i < 4; i += 1) result->bits[i] = 0;
  if (sign_1 != sign_2) {
    status =
        s21_add(*s21_setSign(&value_1, 0), *s21_setSign(&value_2, 0), result);
    status = status ? (sign_1 ? 2 : 1) : status;
    s21_setSign(result, sign_1);
  } else {
    s21_alignmentScale(&value_1, &value_2);
    if (!s21_is_equal(value_1, value_2)) {
      s21_setSign(&value_1, 0);
      s21_setSign(&value_2, 0);
      if (s21_is_less(value_1, value_2)) {
        status = s21_add(*s21_convert(&value_1), value_2, result);
        s21_setSign(result, !sign_2);
      } else {
        status = s21_add(*s21_convert(&value_2), value_1, result);
        s21_setSign(result, sign_1);
      }
    }
  }
  return status;
}