#include "./../s21_decimal.h"

// В float из decimal

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int result = 1;
  if (dst) {
    double tmp = 0;
    int exp = 0;
    for (int i = 0; i < 96; i++) {
      if ((src.bits[i / 32] & (1 << i % 32)) != 0) tmp += pow(2, i);
    }
    if ((exp = s21_getScale(src)) > 0) {
      for (int i = exp; i > 0; i--, tmp /= 10.0)
        ;
    }
    *dst = (float)tmp;
    if (s21_getSign(src)) {
      *dst *= -1;
    }
    result = 0;
  }
  return result;
}
