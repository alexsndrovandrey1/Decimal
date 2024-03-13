#include "./../s21_decimal.h"

// Сложение

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal* result) {
  int status = 0, sign_1 = s21_getSign(value_1), sign_2 = s21_getSign(value_2);
  for (int i = 0; i < 4; i += 1) result->bits[i] = 0;
  if (sign_1 == sign_2) {
    s21_alignmentScale(&value_1, &value_2);
    if (s21_addBit(value_1, value_2, result)) {
      if ((!s21_getScale(value_1) || !s21_getScale(value_2)) && !sign_1) {
        status = 1;
      } else if ((!s21_getScale(value_1) || !s21_getScale(value_2)) && sign_1) {
        status = 2;
      } else if (s21_getScale(value_1) > 0 && s21_getScale(value_2) > 0) {
        s21_setScale(s21_decreaseScale(&value_1, 1), s21_getScale(value_1) - 1);
        s21_setScale(s21_decreaseScale(&value_2, 1), s21_getScale(value_2) - 1);
        status = s21_add(value_1, value_2, result);
      }
    } else {
      s21_setScale(s21_setSign(result, sign_1), s21_getScale(value_1));
    }
  } else if (sign_1 && !sign_2) {
    status = s21_sub(value_2, *s21_setSign(&value_1, 0), result);
  } else if (!sign_1 && sign_2) {
    status = s21_sub(value_1, *s21_setSign(&value_2, 0), result);
  }
  return status;
}