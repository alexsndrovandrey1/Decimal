#include "./../s21_decimal.h"

// Округляет указанное Decimal число до ближайшего целого числа
// в сторону отрицательной бесконечности.

int s21_floor(s21_decimal value, s21_decimal *result) {
  if (!s21_truncate(value, s21_reset(result)) && s21_getSign(value) &&
      !s21_is_equal(*result, value))
    s21_sub(*result, ((s21_decimal){{1, 0, 0, 0}}), result);
  return 0;
}