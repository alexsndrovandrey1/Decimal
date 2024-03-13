#include "./../s21_decimal.h"

// Больше >

int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
  int result = 0;
  int sign_1 = s21_getSign(value_1), sign_2 = s21_getSign(value_2);
  if (!(s21_isNull(value_1) && s21_isNull(value_2))) {
    if (sign_1 != sign_2) {
      if (sign_1 == 0) {
        result = 1;
      } else {
        result = 0;
      }
    } else {
      s21_alignmentScale(&value_1, &value_2);
      for (int i = 95; i >= 0; i--) {
        int bit_1 = s21_getbit(value_1, i), bit_2 = s21_getbit(value_2, i);
        if (bit_1 != bit_2) {
          if (bit_1 != 0) {
            result = (sign_1 == 0) ? 1 : 0;
            break;
          } else {
            result = (sign_1 == 0) ? 0 : 1;
            break;
          }
        }
      }
    }
  }
  return result;
}