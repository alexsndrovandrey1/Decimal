#include "./../s21_decimal.h"

// Равно ==

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  int result = 1;
  if (s21_getSign(value_1) == s21_getSign(value_2)) {
    s21_alignmentScale(&value_1, &value_2);
    for (int i = 95; i >= 0; i--) {
      if (s21_getbit(value_1, i) != s21_getbit(value_2, i)) {
        result = 0;
        break;
      }
    }
  } else if (!(s21_isNull(value_1) && s21_isNull(value_2))) {
    result = 0;
  }
  return result;
}