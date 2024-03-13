#include "./../s21_decimal.h"

// Из int в decimal

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int result = 1;
  if (dst) {
    dst->bits[0] = 0;
    dst->bits[1] = 0;
    dst->bits[2] = 0;
    dst->bits[3] = 0;
    if (src < 0) {
      s21_setSign(dst, 1);
      src *= -1;
    }
    dst->bits[0] = src;
    result = 0;
  }
  return result;
}