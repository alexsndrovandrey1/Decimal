#include "./../s21_decimal.h"

s21_decimal *s21_copy(s21_decimal *dest, s21_decimal src) {
  for (int i = 0; i < 4; i += 1) dest->bits[i] = src.bits[i];
  return dest;
}