#include "./../s21_decimal.h"

s21_decimal *s21_reset(s21_decimal *value) {
  for (int i = 0; i < 4; i += 1) value->bits[i] = 0;
  return value;
}