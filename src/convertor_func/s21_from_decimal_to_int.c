#include "./../s21_decimal.h"

// В int из decimal

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int result = 1;
  if (src.bits[1] == 0 && src.bits[2] == 0) {
    *dst = src.bits[0];
    if (s21_getSign(src)) {
      *dst *= -1;
    }
    *dst /= (int)pow(10, s21_getScale(src));
    result = 0;
  }
  return result;
}