#include <check.h>
#include <stdio.h>

#include "./../s21_decimal.h"

START_TEST(is_less_1) {
  s21_decimal value1 = {{0, 0, 0, 0}};
  s21_decimal value2 = {{0, 0, 0, 0}};
  int state = s21_is_less(value1, value2);
  int state2 = s21_is_less(value2, value1);
  ck_assert_int_eq(state, FALSE);
  ck_assert_int_eq(state2, FALSE);
  ck_assert_int_eq(state, state2);
}
END_TEST

START_TEST(is_less_2) {
  s21_decimal value1 = {{1, 0, 0, 0}};
  s21_decimal value2 = {{0, 0, 0, 0}};
  int state = s21_is_less(value1, value2);
  int state2 = s21_is_less(value2, value1);
  ck_assert_int_eq(state, FALSE);
  ck_assert_int_eq(state2, TRUE);
}
END_TEST

START_TEST(is_less_3) {
  s21_decimal value1 = {{0, 0, 0, 0}};
  s21_decimal value2 = {{0, 0, 0, 0}};
  value1.bits[MID] = 1;
  value2.bits[LOW] = S21_MAX_UINT;
  int state = s21_is_less(value1, value2);
  int state2 = s21_is_less(value2, value1);
  ck_assert_int_eq(state, FALSE);
  ck_assert_int_eq(state2, TRUE);
}
END_TEST

START_TEST(is_less_4) {
  s21_decimal dst1 = {{0, 1, 0, 0}}, dst2 = {{4294967295, 0, 0, 0}};
  float kek = 0;
  s21_from_decimal_to_float(dst1, &kek);
  float mem = 0;
  s21_from_decimal_to_float(dst2, &mem);
  ck_assert_int_eq(s21_is_less(dst1, dst2), FALSE);
  ck_assert_int_eq(s21_is_less(dst2, dst1), TRUE);
}
END_TEST

START_TEST(is_less_5) {
  s21_decimal dst1, dst2;
  s21_from_float_to_decimal(-1.21, &dst1);
  s21_from_float_to_decimal(-1.2, &dst2);
  ck_assert_int_eq(s21_is_less(dst1, dst2), TRUE);
  ck_assert_int_eq(s21_is_less(dst2, dst1), FALSE);
}
END_TEST

START_TEST(is_less_6) {
  s21_decimal dst1, dst2;
  s21_from_float_to_decimal(1.2345, &dst1);
  s21_from_float_to_decimal(-1.2, &dst2);
  ck_assert_int_eq(s21_is_less(dst1, dst2), FALSE);
  ck_assert_int_eq(s21_is_less(dst2, dst1), TRUE);
}
END_TEST

START_TEST(is_less_7) {
  s21_decimal test_value_1 = {{5000, 0, 0, 0}};
  s21_decimal test_value_2 = {{5000, 0, 0, 2147483648}};
  int state1 = s21_is_less(test_value_1, test_value_2);
  ck_assert_int_eq(state1, FALSE);
  int state2 = s21_is_less(test_value_2, test_value_1);
  ck_assert_int_eq(state2, TRUE);
}
END_TEST

START_TEST(is_less_8) {
  s21_decimal test_value_1 = {{0, 0, 0, 0}};
  s21_decimal test_value_2 = {{0, 0, 0, 0}};
  float fNum = 250.0;
  s21_from_float_to_decimal(fNum, &test_value_1);
  int iNum = 250;
  s21_from_int_to_decimal(iNum, &test_value_2);
  int state1 = s21_is_less(test_value_1, test_value_2);
  ck_assert_int_eq(state1, FALSE);
  int state2 = s21_is_less(test_value_2, test_value_1);
  ck_assert_int_eq(state2, FALSE);
}
END_TEST

START_TEST(is_less_9) {
  s21_decimal test_value_1 = {{0, 0, 0, 0}};
  s21_decimal test_value_2 = {{0, 0, 0, 0}};
  float fNum = 250.001;
  s21_from_float_to_decimal(fNum, &test_value_1);
  int iNum = 250;
  s21_from_int_to_decimal(iNum, &test_value_2);
  int state1 = s21_is_less(test_value_1, test_value_2);
  ck_assert_int_eq(state1, FALSE);
  int state2 = s21_is_less(test_value_2, test_value_1);
  ck_assert_int_eq(state2, TRUE);
}
END_TEST

START_TEST(is_less_10) {
  s21_decimal test_value_1 = {{0, 0, 0, 0}};
  s21_decimal test_value_2 = {{0, 0, 0, 0}};
  float fNum = -S21_MAX_INT;
  s21_from_float_to_decimal(fNum, &test_value_1);
  int iNum = S21_MAX_INT;
  s21_from_int_to_decimal(iNum, &test_value_2);
  int state1 = s21_is_less(test_value_1, test_value_2);
  ck_assert_int_eq(state1, TRUE);
  int state2 = s21_is_less(test_value_2, test_value_1);
  ck_assert_int_eq(state2, FALSE);
}
END_TEST

START_TEST(is_less_11) {
  s21_decimal test_value_1 = {{0, 0, 0, 0}};
  s21_decimal test_value_2 = {{0, 0, 0, 0}};
  float fNum1 = -0.000011;
  s21_from_float_to_decimal(fNum1, &test_value_1);
  float fNum2 = -0.000012;
  s21_from_float_to_decimal(fNum2, &test_value_2);
  int state1 = s21_is_less(test_value_1, test_value_2);
  ck_assert_int_eq(state1, FALSE);
  int state2 = s21_is_less(test_value_2, test_value_1);
  ck_assert_int_eq(state2, TRUE);
}
END_TEST

START_TEST(is_less_12) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  ck_assert_int_eq(0, s21_is_less(val1, val2));
}
END_TEST

START_TEST(is_less_13) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val1.bits[0] = 255;
  val2.bits[0] = 256;
  ck_assert_int_eq(1, s21_is_less(val1, val2));
}
END_TEST

START_TEST(is_less_14) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val1.bits[0] = 256;
  val2.bits[0] = 256;
  ck_assert_int_eq(0, s21_is_less(val1, val2));
}
END_TEST

START_TEST(is_less_15) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val1.bits[0] = 257;
  val2.bits[0] = 256;
  ck_assert_int_eq(0, s21_is_less(val1, val2));
}
END_TEST

START_TEST(is_less_16) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_setbit(&val1, 127, 1);
  ck_assert_int_eq(0, s21_is_less(val1, val2));
}
END_TEST

START_TEST(is_less_17) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val1.bits[0] = 257;
  val2.bits[0] = 257;
  val1.bits[2] = 256;
  val2.bits[2] = 257;
  s21_setScale(&val1, 11);
  s21_setScale(&val2, 10);
  ck_assert_int_eq(1, s21_is_less(val1, val2));
}
END_TEST

START_TEST(is_less_18) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val1.bits[0] = 257;
  val2.bits[0] = 257;
  val1.bits[2] = 256;
  val2.bits[2] = 257;
  s21_setScale(&val1, 10);
  s21_setScale(&val2, 11);
  ck_assert_int_eq(0, s21_is_less(val1, val2));
}
END_TEST

START_TEST(is_less_19) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val2.bits[2] = 257;
  s21_setbit(&val1, 127, 1);
  s21_setbit(&val2, 127, 1);
  ck_assert_int_eq(0, s21_is_less(val1, val2));
}
END_TEST

START_TEST(is_less_20) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_setbit(&val1, 127, 1);
  s21_setbit(&val2, 127, 1);
  s21_setbit(&val1, 83, 1);
  s21_setScale(&val1, 12);
  s21_setScale(&val2, 11);
  ck_assert_int_eq(1, s21_is_less(val1, val2));
}
END_TEST

START_TEST(is_less_21) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_setbit(&val1, 127, 1);
  s21_setbit(&val2, 127, 1);
  s21_setbit(&val1, 83, 1);
  s21_setbit(&val2, 83, 1);
  s21_setScale(&val1, 10);
  s21_setScale(&val2, 11);
  ck_assert_int_eq(1, s21_is_less(val1, val2));
}
END_TEST

START_TEST(is_less_22) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_setbit(&val1, 127, 1);
  s21_setbit(&val2, 127, 1);
  s21_setbit(&val1, 83, 1);
  s21_setScale(&val1, 10);
  s21_setScale(&val2, 10);
  ck_assert_int_eq(1, s21_is_less(val1, val2));
}
END_TEST

START_TEST(is_less_23) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_setbit(&val1, 127, 1);
  s21_setbit(&val2, 127, 0);
  s21_setbit(&val1, 83, 1);
  ck_assert_int_eq(1, s21_is_less(val1, val2));
}
END_TEST

START_TEST(is_less_24) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_setbit(&val1, 127, 1);
  s21_setbit(&val2, 127, 0);
  ck_assert_int_eq(0, s21_is_less(val1, val2));
}
END_TEST

START_TEST(is_greater_1) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val1.bits[0] = 255;
  val2.bits[0] = 256;
  ck_assert_int_eq(0, s21_is_greater(val1, val2));
}
END_TEST

START_TEST(is_greater_2) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val1.bits[0] = 256;
  val2.bits[0] = 256;
  ck_assert_int_eq(0, s21_is_greater(val1, val2));
}
END_TEST

START_TEST(is_greater_3) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val1.bits[0] = 257;
  val2.bits[0] = 256;
  ck_assert_int_eq(1, s21_is_greater(val1, val2));
}
END_TEST

START_TEST(is_greater_4) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_setbit(&val1, 127, 1);
  ck_assert_int_eq(0, s21_is_greater(val1, val2));
}
END_TEST

START_TEST(is_greater_5) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val1.bits[0] = 257;
  val2.bits[0] = 257;
  val1.bits[2] = 256;
  val2.bits[2] = 257;
  s21_setScale(&val1, 11);
  s21_setScale(&val2, 10);
  ck_assert_int_eq(0, s21_is_greater(val1, val2));
}
END_TEST

START_TEST(is_greater_6) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val1.bits[0] = 257;
  val2.bits[0] = 257;
  val1.bits[2] = 256;
  val2.bits[2] = 257;
  s21_setScale(&val1, 10);
  s21_setScale(&val2, 11);
  ck_assert_int_eq(1, s21_is_greater(val1, val2));
}
END_TEST

START_TEST(is_greater_7) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val2.bits[2] = 257;
  s21_setbit(&val1, 127, 1);
  s21_setbit(&val2, 127, 1);
  ck_assert_int_eq(1, s21_is_greater(val1, val2));
}
END_TEST

START_TEST(is_greater_8) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val2.bits[2] = 257;
  s21_setbit(&val1, 127, 1);
  s21_setbit(&val2, 127, 0);
  ck_assert_int_eq(0, s21_is_greater(val1, val2));
}
END_TEST

START_TEST(is_greater_9) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  ck_assert_int_eq(0, s21_is_greater(val1, val2));
}
END_TEST

START_TEST(is_greater_or_equal_1) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val1.bits[0] = 255;
  val2.bits[0] = 256;
  ck_assert_int_eq(0, s21_is_greater_or_equal(val1, val2));
}
END_TEST

START_TEST(is_greater_or_equal_2) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val1.bits[0] = 256;
  val2.bits[0] = 256;
  ck_assert_int_eq(1, s21_is_greater_or_equal(val1, val2));
}
END_TEST

START_TEST(is_greater_or_equal_3) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val1.bits[0] = 257;
  val2.bits[0] = 256;
  ck_assert_int_eq(1, s21_is_greater_or_equal(val1, val2));
}
END_TEST

START_TEST(is_greater_or_equal_4) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_setbit(&val1, 127, 1);
  ck_assert_int_eq(1, s21_is_greater_or_equal(val1, val2));
}
END_TEST

START_TEST(is_greater_or_equal_5) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val1.bits[0] = 257;
  val2.bits[0] = 257;
  val1.bits[2] = 256;
  val2.bits[2] = 257;
  s21_setScale(&val1, 11);
  s21_setScale(&val2, 10);
  ck_assert_int_eq(0, s21_is_greater_or_equal(val1, val2));
}
END_TEST

START_TEST(is_greater_or_equal_6) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val1.bits[0] = 257;
  val2.bits[0] = 257;
  val1.bits[2] = 256;
  val2.bits[2] = 257;
  s21_setScale(&val1, 10);
  s21_setScale(&val2, 11);
  ck_assert_int_eq(1, s21_is_greater_or_equal(val1, val2));
}
END_TEST

START_TEST(is_greater_or_equal_7) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val2.bits[2] = 257;
  s21_setbit(&val1, 127, 1);
  s21_setbit(&val2, 127, 1);
  ck_assert_int_eq(1, s21_is_greater_or_equal(val1, val2));
}
END_TEST

START_TEST(is_greater_or_equal_8) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  ck_assert_int_eq(1, s21_is_greater_or_equal(val1, val2));
}
END_TEST

START_TEST(is_less_or_equal_1) {
  s21_decimal value1 = {{0, 0, 0, 0}};
  s21_decimal value2 = {{0, 0, 0, 0}};
  int state = s21_is_less_or_equal(value1, value2);
  int state2 = s21_is_less_or_equal(value2, value1);
  ck_assert_int_eq(state, TRUE);
  ck_assert_int_eq(state2, TRUE);
  ck_assert_int_eq(state, state2);
}
END_TEST

START_TEST(is_less_or_equal_2) {
  s21_decimal value1 = {{1, 0, 0, 0}};
  s21_decimal value2 = {{0, 0, 0, 0}};
  int state = s21_is_less_or_equal(value1, value2);
  int state2 = s21_is_less_or_equal(value2, value1);
  ck_assert_int_eq(state, FALSE);
  ck_assert_int_eq(state2, TRUE);
}
END_TEST

START_TEST(is_less_or_equal_3) {
  s21_decimal value1 = {{0, 0, 0, 0}};
  s21_decimal value2 = {{0, 0, 0, 0}};
  value1.bits[MID] = 1;
  value2.bits[LOW] = S21_MAX_UINT;
  int state = s21_is_less_or_equal(value1, value2);
  int state2 = s21_is_less_or_equal(value2, value1);
  ck_assert_int_eq(state, FALSE);
  ck_assert_int_eq(state2, TRUE);
}
END_TEST

START_TEST(is_less_or_equal_4) {
  s21_decimal dst1 = {{0, 1, 0, 0}}, dst2 = {{4294967295, 0, 0, 0}};
  float kek = 0;
  s21_from_decimal_to_float(dst1, &kek);
  float mem = 0;
  s21_from_decimal_to_float(dst2, &mem);
  ck_assert_int_eq(s21_is_less_or_equal(dst1, dst2), FALSE);
  ck_assert_int_eq(s21_is_less_or_equal(dst2, dst1), TRUE);
}
END_TEST

START_TEST(is_less_or_equal_5) {
  s21_decimal dst1, dst2;
  s21_from_float_to_decimal(-1.21, &dst1);
  s21_from_float_to_decimal(-1.2, &dst2);
  ck_assert_int_eq(s21_is_less_or_equal(dst1, dst2), TRUE);
  ck_assert_int_eq(s21_is_less_or_equal(dst2, dst1), FALSE);
}
END_TEST

START_TEST(is_less_or_equal_6) {
  s21_decimal dst1, dst2;
  s21_from_float_to_decimal(1.2345, &dst1);
  s21_from_float_to_decimal(-1.2, &dst2);
  ck_assert_int_eq(s21_is_less_or_equal(dst1, dst2), FALSE);
  ck_assert_int_eq(s21_is_less_or_equal(dst2, dst1), TRUE);
}
END_TEST

START_TEST(is_less_or_equal_7) {
  s21_decimal test_value_1 = {{5000, 0, 0, 0}};
  s21_decimal test_value_2 = {{5000, 0, 0, 2147483648}};
  int state1 = s21_is_less_or_equal(test_value_1, test_value_2);
  ck_assert_int_eq(state1, FALSE);
  int state2 = s21_is_less_or_equal(test_value_2, test_value_1);
  ck_assert_int_eq(state2, TRUE);
}
END_TEST

START_TEST(is_less_or_equal_8) {
  s21_decimal test_value_1 = {{0, 0, 0, 0}};
  s21_decimal test_value_2 = {{0, 0, 0, 0}};
  float fNum = 250.0;
  s21_from_float_to_decimal(fNum, &test_value_1);
  int iNum = 250;
  s21_from_int_to_decimal(iNum, &test_value_2);
  int state1 = s21_is_less_or_equal(test_value_1, test_value_2);
  ck_assert_int_eq(state1, TRUE);
  int state2 = s21_is_less_or_equal(test_value_2, test_value_1);
  ck_assert_int_eq(state2, TRUE);
}
END_TEST

START_TEST(is_less_or_equal_9) {
  s21_decimal test_value_1 = {{0, 0, 0, 0}};
  s21_decimal test_value_2 = {{0, 0, 0, 0}};
  float fNum = 250.001;
  s21_from_float_to_decimal(fNum, &test_value_1);
  int iNum = 250;
  s21_from_int_to_decimal(iNum, &test_value_2);
  int state1 = s21_is_less_or_equal(test_value_1, test_value_2);
  ck_assert_int_eq(state1, FALSE);
  int state2 = s21_is_less_or_equal(test_value_2, test_value_1);
  ck_assert_int_eq(state2, TRUE);
}
END_TEST

START_TEST(is_less_or_equal_10) {
  s21_decimal test_value_1 = {{0, 0, 0, 0}};
  s21_decimal test_value_2 = {{0, 0, 0, 0}};
  float fNum = -S21_MAX_INT;
  s21_from_float_to_decimal(fNum, &test_value_1);
  int iNum = S21_MAX_INT;
  s21_from_int_to_decimal(iNum, &test_value_2);
  int state1 = s21_is_less_or_equal(test_value_1, test_value_2);
  ck_assert_int_eq(state1, TRUE);
  int state2 = s21_is_less_or_equal(test_value_2, test_value_1);
  ck_assert_int_eq(state2, FALSE);
}
END_TEST

START_TEST(is_less_or_equal_11) {
  s21_decimal test_value_1 = {{0, 0, 0, 0}};
  s21_decimal test_value_2 = {{0, 0, 0, 0}};
  float fNum1 = -0.000011;
  s21_from_float_to_decimal(fNum1, &test_value_1);
  float fNum2 = -0.000012;
  s21_from_float_to_decimal(fNum2, &test_value_2);
  int state1 = s21_is_less_or_equal(test_value_1, test_value_2);
  ck_assert_int_eq(state1, FALSE);
  int state2 = s21_is_less_or_equal(test_value_2, test_value_1);
  ck_assert_int_eq(state2, TRUE);
}
END_TEST

START_TEST(is_less_or_equal_12) {
  s21_decimal test_value_1 = {{0, 0, 0, 0}};
  s21_decimal test_value_2 = {{0, 0, 0, 0}};
  float fNum1 = -0.000011;
  s21_from_float_to_decimal(fNum1, &test_value_1);
  float fNum2 = -0.000011;
  s21_from_float_to_decimal(fNum2, &test_value_2);
  int state1 = s21_is_less_or_equal(test_value_1, test_value_2);
  ck_assert_int_eq(state1, TRUE);
  int state2 = s21_is_less_or_equal(test_value_2, test_value_1);
  ck_assert_int_eq(state2, TRUE);
}
END_TEST

START_TEST(is_less_or_equal_13) {
  s21_decimal test_value_1 = {{0, 0, 0, 0}};
  s21_decimal test_value_2 = {{0, 0, 0, 0}};
  float fNum1 = -0.0;
  s21_from_float_to_decimal(fNum1, &test_value_1);
  float fNum2 = 0.0;
  s21_from_float_to_decimal(fNum2, &test_value_2);
  int state1 = s21_is_less_or_equal(test_value_1, test_value_2);
  ck_assert_int_eq(state1, TRUE);
  int state2 = s21_is_less_or_equal(test_value_2, test_value_1);
  ck_assert_int_eq(state2, TRUE);
}
END_TEST

START_TEST(is_less_or_equal_14) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  ck_assert_int_eq(1, s21_is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(is_less_or_equal_15) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val1.bits[0] = 255;
  val2.bits[0] = 256;
  ck_assert_int_eq(1, s21_is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(is_less_or_equal_16) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val1.bits[0] = 256;
  val2.bits[0] = 256;
  ck_assert_int_eq(1, s21_is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(is_less_or_equal_17) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val1.bits[0] = 257;
  val2.bits[0] = 256;
  ck_assert_int_eq(0, s21_is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(is_less_or_equal_18) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_setbit(&val1, 127, 1);
  ck_assert_int_eq(1, s21_is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(is_less_or_equal_19) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val1.bits[0] = 257;
  val2.bits[0] = 257;
  val1.bits[2] = 256;
  val2.bits[2] = 257;
  s21_setScale(&val1, 11);
  s21_setScale(&val2, 10);
  ck_assert_int_eq(1, s21_is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(is_less_or_equal_20) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val1.bits[0] = 257;
  val2.bits[0] = 257;
  val1.bits[2] = 256;
  val2.bits[2] = 257;
  s21_setScale(&val1, 10);
  s21_setScale(&val2, 11);
  ck_assert_int_eq(0, s21_is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(is_less_or_equal_21) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val2.bits[2] = 257;
  s21_setbit(&val1, 127, 1);
  s21_setbit(&val2, 127, 1);
  ck_assert_int_eq(0, s21_is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(is_equal_1) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_setbit(&val2, 3, 1);
  ck_assert_int_eq(0, s21_is_equal(val1, val2));
}
END_TEST

START_TEST(is_equal_2) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_setbit(&val2, 127, 1);
  s21_setbit(&val1, 33, 1);
  s21_setbit(&val2, 33, 1);
  ck_assert_int_eq(0, s21_is_equal(val1, val2));
}
END_TEST

START_TEST(is_equal_3) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_setbit(&val1, 3, 1);
  s21_setbit(&val2, 3, 1);
  ck_assert_int_eq(1, s21_is_equal(val1, val2));
}
END_TEST

START_TEST(is_equal_4) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_setbit(&val1, 3, 1);
  s21_setbit(&val2, 4, 1);
  ck_assert_int_eq(0, s21_is_equal(val1, val2));
}
END_TEST

START_TEST(is_equal_5) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_setScale(&val1, 3);
  s21_setScale(&val2, 3);
  ck_assert_int_eq(1, s21_is_equal(val1, val2));
}
END_TEST

START_TEST(is_equal_6) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_setbit(&val1, 3, 1);
  s21_setbit(&val2, 4, 1);
  s21_setScale(&val1, 3);
  s21_setScale(&val2, 3);
  ck_assert_int_eq(0, s21_is_equal(val1, val2));
}
END_TEST

START_TEST(is_equal_7) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_setScale(&val1, 3);
  s21_setScale(&val2, 2);
  ck_assert_int_eq(1, s21_is_equal(val1, val2));
}
END_TEST

START_TEST(is_equal_8) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  ck_assert_int_eq(1, s21_is_equal(val1, val2));
}
END_TEST

START_TEST(is_equal_9) {
  s21_decimal val1 = {{0, 0, 0, 0}};
  s21_decimal val2 = {{0, 0, 0, 0}};
  s21_setSign(&val2, 1);
  ck_assert_int_eq(1, s21_is_equal(val1, val2));
}
END_TEST

START_TEST(is_not_equal_1) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_setbit(&val2, 3, 1);
  ck_assert_int_eq(1, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(is_not_equal_2) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_setbit(&val2, 127, 1);
  s21_setbit(&val1, 33, 1);
  s21_setbit(&val2, 33, 1);
  ck_assert_int_eq(1, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(is_not_equal_3) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_setbit(&val1, 3, 1);
  s21_setbit(&val2, 3, 1);
  ck_assert_int_eq(0, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(is_not_equal_4) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_setbit(&val1, 3, 1);
  s21_setbit(&val2, 4, 1);
  ck_assert_int_eq(1, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(is_not_equal_5) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_setScale(&val1, 3);
  s21_setScale(&val2, 3);
  ck_assert_int_eq(0, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(is_not_equal_6) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_setbit(&val1, 3, 1);
  s21_setbit(&val2, 4, 1);
  s21_setScale(&val1, 3);
  s21_setScale(&val2, 3);
  ck_assert_int_eq(1, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(is_not_equal_7) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_setScale(&val1, 3);
  s21_setScale(&val2, 2);
  ck_assert_int_eq(0, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(is_not_equal_8) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  ck_assert_int_eq(0, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(is_not_equal_9) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_setbit(&val1, 127, 1);
  s21_setbit(&val2, 127, 0);
  ck_assert_int_eq(0, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(sub_1) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_2) {
  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_3) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_4) {
  s21_decimal val1 = {{8, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_5) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{8, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_6) {
  s21_decimal val1 = {{8, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_7) {
  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{8, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_8) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{8, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_9) {
  s21_decimal val1 = {{8, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_10) {
  s21_decimal val1 = {{8, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_11) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{4, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(2, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_12) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal val2 = {{4, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_13) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{4, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_14) {
  s21_decimal val1 = {{4, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal res;
  ck_assert_int_eq(2, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_15) {
  s21_decimal val1 = {{4, 0, 0, 0}};
  s21_decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_16) {
  s21_decimal val1 = {{4, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_17) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal val2 = {{4, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(1, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_18) {
  s21_decimal val1 = {{4, 0, 0, 0}};
  s21_decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(1, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_19) {
  s21_decimal val1 = {{4, 0, 0, 0}};
  s21_decimal val2 = {{4, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_20) {
  s21_decimal dec1;
  s21_decimal dec2;
  int tmp1 = 100;
  int tmp2 = 99999;
  int res_s21 = 0;
  int res = -99899;
  s21_decimal res1;
  s21_from_int_to_decimal(tmp1, &dec1);
  s21_from_int_to_decimal(tmp2, &dec2);
  s21_sub(dec1, dec2, &res1);
  s21_from_decimal_to_int(res1, &res_s21);
  ck_assert_int_eq(res_s21, res);
}
END_TEST

START_TEST(sub_21) {
  s21_decimal dec1;
  s21_decimal dec2;
  int tmp1 = -100;
  int tmp2 = -99999;
  int res_s21 = 0;
  s21_decimal res1;
  int res = 99899;
  s21_from_int_to_decimal(tmp1, &dec1);
  s21_from_int_to_decimal(tmp2, &dec2);
  s21_sub(dec1, dec2, &res1);
  s21_from_decimal_to_int(res1, &res_s21);
  ck_assert_int_eq(res_s21, res);
}
END_TEST

START_TEST(sub_22) {
  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(add_1) {
  s21_decimal val1 = {{15, 0, 0, 0}};
  s21_decimal val2 = {{15, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_2) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal val2 = {{1, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(1, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_3) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(2, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_4) {
  s21_decimal val1 = {{8, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_5) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{8, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_6) {
  s21_decimal val1 = {{8, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_7) {
  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{8, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_8) {
  s21_decimal val1 = {{0}};
  s21_decimal val2 = {{0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_9) {
  s21_decimal val1 = {{4, 0, 0, 0}};
  s21_decimal val2 = {{8, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_10) {
  s21_decimal val1 = {{8, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_11) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{4, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_12) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{4, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(2, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_13) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal val2 = {{4, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_14) {
  s21_decimal val1 = {{4, 0, 0, 0}};
  s21_decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_15) {
  s21_decimal val1 = {{4, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_16) {
  s21_decimal val1 = {{4, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(2, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_17) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_setScale(&val1, 5);
  s21_setScale(&val2, 3);
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_18) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_setScale(&val1, 5);
  s21_setScale(&val2, 3);
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_19) {
  s21_decimal value_1 = {{100, 0, 0, 0}};
  s21_decimal value_2 = {{100, 0, 0, 0}};
  s21_decimal res;

  int sum = s21_add(value_1, value_2, &res);
  ck_assert_int_eq(sum, 0);
  ck_assert_int_eq(res.bits[0], 200);
}
END_TEST

START_TEST(add_20) {
  s21_decimal value_1 = {{11, 0, 0, 0}};
  s21_decimal value_2 = {{999, 0, 0, 0}};
  s21_decimal res;

  int sum = s21_add(value_1, value_2, &res);
  ck_assert_int_eq(sum, 0);
  ck_assert_int_eq(res.bits[0], 1010);
}
END_TEST

START_TEST(add_21) {
  s21_decimal value_1 = {{0, 1, 0, 0}};
  s21_decimal value_2 = {{0, 1, 0, 0}};
  s21_decimal res;

  int sum = s21_add(value_1, value_2, &res);
  ck_assert_int_eq(sum, 0);
  ck_assert_int_eq(res.bits[1], 2);
}
END_TEST

START_TEST(add_22) {
  s21_decimal value_1 = {{1000, 0, 0, 32768 * 2}};
  s21_decimal value_2 = {{100, 0, 0, 0}};
  s21_decimal res;
  int sum = s21_add(value_1, value_2, &res);
  ck_assert_int_eq(sum, 0);
  ck_assert_int_eq(res.bits[0], 2000);
}
END_TEST

START_TEST(add_23) {
  s21_decimal value_1 = {{0, 0, 1, 0}};
  s21_decimal value_2 = {{0, 0, 1, 0}};
  s21_decimal res;

  int sum = s21_add(value_1, value_2, &res);
  ck_assert_int_eq(sum, 0);
  ck_assert_int_eq(res.bits[2], 2);
}
END_TEST

START_TEST(add_24) {
  s21_decimal value_1 = {{1, 1, 1, 0}};
  s21_decimal value_2 = {{1, 1, 1, 0}};
  s21_decimal res;

  int sum = s21_add(value_1, value_2, &res);
  ck_assert_int_eq(sum, 0);
  ck_assert_int_eq(res.bits[0], 2);
  ck_assert_int_eq(res.bits[1], 2);
  ck_assert_int_eq(res.bits[2], 2);
}
END_TEST

START_TEST(add_25) {
  s21_decimal value_1 = {{1111, 999, 1000, 0}};
  s21_decimal value_2 = {{1111, 11, 18, 0}};
  s21_decimal res;

  int sum = s21_add(value_1, value_2, &res);
  ck_assert_int_eq(sum, 0);
  ck_assert_int_eq(res.bits[0], 2222);
  ck_assert_int_eq(res.bits[1], 1010);
  ck_assert_int_eq(res.bits[2], 1018);
}
END_TEST

START_TEST(add_26) {
  s21_decimal value_1 = {{1, 1, 1, 0}};
  s21_decimal value_2 = {{1, 1, 0, 0}};
  s21_decimal res;

  int sum = s21_add(value_1, value_2, &res);
  ck_assert_int_eq(sum, 0);
  ck_assert_int_eq(res.bits[0], 2);
  ck_assert_int_eq(res.bits[1], 2);
  ck_assert_int_eq(res.bits[2], 1);
}
END_TEST

START_TEST(add_27) {
  s21_decimal val1 = {{15, 0, 0, ~(S21_MAX_UINT / 2)}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(mul_1) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_2) {
  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_3) {
  s21_decimal val1 = {{21, 21, 21, 21}};
  s21_decimal val2 = {{21, 21, 21, 21}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_4) {
  s21_decimal val1 = {{8, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_5) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{8, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_6) {
  s21_decimal val1 = {{8, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_7) {
  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{8, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_8) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(1, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_9) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(2, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_10) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0}};
  s21_setScale(&val1, 1);
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_11) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal val2 = {{200, 0, 0, 0}};
  s21_decimal res = {{0}};
  s21_setScale(&val2, 1);
  s21_setScale(&val2, 2);
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_12) {
  s21_decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal val1 = {{20, 0, 0, 0}};
  s21_decimal res = {{0}};
  s21_setScale(&val2, 1);
  s21_setScale(&val2, 2);
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_13) {
  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(div_1) {
  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_div(val1, val2, &res));
}
END_TEST

START_TEST(div_2) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_div(val1, val2, &res));
}
END_TEST

START_TEST(div_3) {
  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_div(val1, val2, &res));
}
END_TEST

START_TEST(div_4) {
  int num1 = 100;
  int num2 = 50;
  int res_origin = 2;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_div(a, b, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, res_origin);
}
END_TEST

START_TEST(div_5) {
  int num1 = -32768;
  int num2 = 2;
  int res_origin = -16384;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_div(a, b, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, res_origin);
}
END_TEST

START_TEST(div_6) {
  int num1 = 2;
  int num2 = 2;
  int res_origin = 1;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_div(a, b, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, res_origin);
}
END_TEST

START_TEST(div_7) {
  int num1 = 0;
  int num2 = 5;
  int res_origin = num1 / num2;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_div(a, b, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, res_origin);
}
END_TEST

START_TEST(div_8) {
  float num1 = 9403.0e2;
  int num2 = 202;
  float res_origin = num1 / num2;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_float_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  float res_float = 0;
  s21_div(a, b, &res_dec);
  s21_from_decimal_to_float(res_dec, &res_float);
  ck_assert_int_eq(res_float, res_origin);
}
END_TEST

START_TEST(div_9) {
  float num1 = -9403.0e2;
  float num2 = -2020.29;
  float res_origin = num1 / num2;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_float_to_decimal(num1, &a);
  s21_from_float_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  float res_float = 0;
  s21_div(a, b, &res_dec);
  s21_from_decimal_to_float(res_dec, &res_float);
  ck_assert_int_eq(res_float, res_origin);
}
END_TEST

START_TEST(div_10) {
  float num1 = -9403.0e2;
  float num2 = 2020.29;
  float res_origin = num1 / num2;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_float_to_decimal(num1, &a);
  s21_from_float_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  float res_float = 0;
  s21_div(a, b, &res_dec);
  s21_from_decimal_to_float(res_dec, &res_float);
  ck_assert_int_eq(res_float, res_origin);
}
END_TEST

START_TEST(div_11) {
  float num1 = -9403.0e2;
  float num2 = 2.28e17;
  float res_origin = num1 / num2;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_float_to_decimal(num1, &a);
  s21_from_float_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  float res_float = 0;
  s21_div(a, b, &res_dec);
  s21_from_decimal_to_float(res_dec, &res_float);
  ck_assert_int_eq(res_float, res_origin);
}
END_TEST

START_TEST(div_12) {
  float num1 = -0.9;
  float num2 = 30.323;
  float res_origin = num1 / num2;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_float_to_decimal(num1, &a);
  s21_from_float_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  float res_float = 0;
  s21_div(a, b, &res_dec);
  s21_from_decimal_to_float(res_dec, &res_float);
  ck_assert_int_eq(res_float, res_origin);
}
END_TEST

START_TEST(div_13) {
  float num1 = 100.0;
  float num2 = 99999.0;
  float res_origin = num1 / num2;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_float_to_decimal(num1, &a);
  s21_from_float_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  float res_float = 0;
  s21_div(a, b, &res_dec);
  s21_from_decimal_to_float(res_dec, &res_float);
  ck_assert_int_eq(res_float, res_origin);
}
END_TEST

START_TEST(div_14) {
  int num1 = 100;
  float num2 = 999.99;
  float res_origin = num1 / num2;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_float_to_decimal(num1, &a);
  s21_from_float_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  float res_float = 0;
  s21_div(a, b, &res_dec);
  s21_from_decimal_to_float(res_dec, &res_float);
  ck_assert_int_eq(res_float, res_origin);
}
END_TEST

START_TEST(div_15) {
  float num1 = -100.0;
  float num2 = -99999.0;
  float res_origin = num1 / num2;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_float_to_decimal(num1, &a);
  s21_from_float_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  float res_float = 0;
  s21_div(a, b, &res_dec);
  s21_from_decimal_to_float(res_dec, &res_float);
  ck_assert_int_eq(res_float, res_origin);
}
END_TEST

START_TEST(div_16) {
  float num1 = 10.0e3;
  float num2 = 2.00e2;
  float res_origin = num1 / num2;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_float_to_decimal(num1, &a);
  s21_from_float_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  float res_float = 0;
  s21_div(a, b, &res_dec);
  s21_from_decimal_to_float(res_dec, &res_float);
  ck_assert_int_eq(res_float, res_origin);
}
END_TEST

START_TEST(div_17) {
  float num1 = -0.9e3;
  float num2 = 30.32;
  float res_origin = num1 / num2;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_float_to_decimal(num1, &a);
  s21_from_float_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  float res_float = 0;
  s21_div(a, b, &res_dec);
  s21_from_decimal_to_float(res_dec, &res_float);
  ck_assert_int_eq(res_float, res_origin);
}
END_TEST

START_TEST(div_18) {
  float num1 = -100;
  float num2 = 30.1;
  float res_origin = num1 / num2;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_float_to_decimal(num1, &a);
  s21_from_float_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  float res_float = 0;
  s21_div(a, b, &res_dec);
  s21_from_decimal_to_float(res_dec, &res_float);
  ck_assert_int_eq(res_float, res_origin);
}
END_TEST

START_TEST(truncate_1) {
  s21_decimal val = {{7, 7, 7, 0}};
  s21_decimal res = {0};
  ck_assert_int_eq(0, s21_truncate(val, &res));
  float fres = 0;
  s21_from_decimal_to_float(res, &fres);
  float need = 129127208515966861312.0;
  ck_assert_float_eq(need, fres);
}
END_TEST

START_TEST(truncate_2) {
  s21_decimal val = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {0};
  ck_assert_int_eq(0, s21_truncate(val, &res));
  float fres = 0;
  s21_from_decimal_to_float(res, &fres);
  float need = -2.0;
  ck_assert_float_eq(need, fres);
}
END_TEST

START_TEST(truncate_3) {
  s21_decimal val = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {0};
  ck_assert_int_eq(0, s21_truncate(val, &res));
  float fres = 0;
  s21_from_decimal_to_float(res, &fres);
  float need = -2.0;
  ck_assert_float_eq(need, fres);
}
END_TEST

START_TEST(truncate_4) {
  s21_decimal val = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {0};
  s21_setScale(&val, 5);
  ck_assert_int_eq(0, s21_truncate(val, &res));
  float fres = 0;
  s21_from_decimal_to_float(res, &fres);
  float need = -0.0;
  ck_assert_float_eq(need, fres);
}

START_TEST(truncate_5) {
  s21_decimal val = {{128, 0, 0, 0}};
  s21_decimal res = {0};
  s21_setScale(&val, 1);
  ck_assert_int_eq(0, s21_truncate(val, &res));
  float fres = 0;
  s21_from_decimal_to_float(res, &fres);
  float need = 12;
  ck_assert_float_eq(need, fres);
}

START_TEST(negate_1) {
  s21_decimal val = {{2, 0, 0, 0}};
  s21_decimal res = {0};
  int sign_before = s21_getSign(val);
  s21_negate(val, &res);
  int sign_after = s21_getSign(res);

  ck_assert_int_ne(sign_before, sign_after);
}
END_TEST

START_TEST(negate_2) {
  s21_decimal val = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {0};
  int sign_before = s21_getSign(val);
  s21_negate(val, &res);
  int sign_after = s21_getSign(res);
  ck_assert_int_ne(sign_before, sign_after);
}
END_TEST

START_TEST(negate_3) {
  s21_decimal val = {{0, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {0};
  int sign_before = s21_getSign(val);
  s21_negate(val, &res);
  int sign_after = s21_getSign(res);
  ck_assert_int_ne(sign_before, sign_after);
}
END_TEST

START_TEST(negate_4) {
  s21_decimal val = {0};
  s21_decimal res = {0};
  int sign_before = s21_getSign(val);
  s21_negate(val, &res);
  int sign_after = s21_getSign(res);
  ck_assert_int_ne(sign_before, sign_after);
}
END_TEST

START_TEST(floor_1) {
  s21_decimal val = {{2, 0, 0, 0}};
  s21_decimal res = {0};
  ck_assert_int_eq(0, s21_floor(val, &res));
}
END_TEST

START_TEST(floor_2) {
  s21_decimal val = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {0};
  s21_floor(val, &res);
  float fres = 0;
  s21_from_decimal_to_float(res, &fres);
  ck_assert_float_eq(-2, fres);
}
END_TEST

START_TEST(floor_3) {
  s21_decimal val = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {0};
  s21_setScale(&val, 5);
  s21_floor(val, &res);
  float fres = 0;
  s21_from_decimal_to_float(res, &fres);
  ck_assert_float_eq(-1, fres);
}
END_TEST

START_TEST(floor_4) {
  s21_decimal val = {{2, 0, 0, 0}};
  s21_decimal res = {0};
  s21_setScale(&val, 5);
  s21_floor(val, &res);
  float fres = 0;
  s21_from_decimal_to_float(res, &fres);
  ck_assert_float_eq(0, fres);
}
END_TEST

START_TEST(round_1) {
  s21_decimal val = {{3, 3, 3, ~(UINT_MAX / 2)}};
  s21_decimal res = {0};
  ck_assert_int_eq(0, s21_round(val, &res));
}
END_TEST

START_TEST(round_2) {
  s21_decimal val = {{3, 3, 3, 0}};
  s21_decimal res = {0};
  s21_setScale(&val, 5);
  ck_assert_int_eq(0, s21_round(val, &res));
}
END_TEST

START_TEST(round_3) {
  s21_decimal val = {{7, 7, 7, ~(UINT_MAX / 2)}};
  s21_decimal res = {0};
  s21_setScale(&val, 5);
  ck_assert_int_eq(0, s21_round(val, &res));
}
END_TEST

START_TEST(round_4) {
  s21_decimal val = {{25, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {0};
  s21_setScale(&val, 1);
  ck_assert_int_eq(0, s21_round(val, &res));
}
END_TEST

START_TEST(round_5) {
  s21_decimal val = {{26, 0, 0, 0}};
  s21_decimal res = {0};
  s21_setScale(&val, 1);
  ck_assert_int_eq(0, s21_round(val, &res));
}
END_TEST

START_TEST(round_6) {
  s21_decimal val = {{115, 0, 0, 0}};
  s21_decimal res = {0};
  s21_setScale(&val, 1);
  ck_assert_int_eq(0, s21_round(val, &res));
}
END_TEST

START_TEST(round_7) {
  s21_decimal val = {{118, 0, 0, 0}};
  s21_decimal res = {0};
  s21_setScale(&val, 1);
  ck_assert_int_eq(0, s21_round(val, &res));
}
END_TEST

START_TEST(round_8) {
  s21_decimal val = {{125, 0, 0, 0}};
  s21_decimal res = {0};
  s21_setScale(&val, 1);
  ck_assert_int_eq(0, s21_round(val, &res));
}
END_TEST

START_TEST(round_9) {
  s21_decimal val = {{128, 0, 0, 0}};
  s21_decimal res = {0};
  s21_setScale(&val, 1);
  s21_round(val, &res);
  float fres = 0;
  s21_from_decimal_to_float(res, &fres);
  float need = 13;
  ck_assert_float_eq(need, fres);
}
END_TEST

START_TEST(round_10) {
  s21_decimal val = {{7, 7, 7, 0}};
  s21_decimal res = {0};
  s21_round(val, &res);
  float fres = 0;
  s21_from_decimal_to_float(res, &fres);
  float need = 129127208515966861312.0;
  ck_assert_float_eq(need, fres);
}
END_TEST

START_TEST(round_11) {
  s21_decimal value_1 = {{5, 0, 1, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_round(value_1, &result);
  ck_assert_float_eq(result.bits[0], 5);
  ck_assert_float_eq(result.bits[1], 0);
  ck_assert_float_eq(result.bits[2], 1);
  ck_assert_float_eq(result.bits[3], 0);
}
END_TEST

START_TEST(round_12) {
  s21_decimal value_1 = {{155, 1, 1, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_round(value_1, &result);
  ck_assert_float_eq(result.bits[0], 155);
  ck_assert_float_eq(result.bits[1], 1);
  ck_assert_float_eq(result.bits[2], 1);
  ck_assert_float_eq(result.bits[3], 0);
}
END_TEST

START_TEST(round_13) {
  s21_decimal value_1 = {{155, 1, 1, 2147483648}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_round(value_1, &result);
  ck_assert_float_eq(result.bits[0], 155);
  ck_assert_float_eq(result.bits[1], 1);
  ck_assert_float_eq(result.bits[2], 1);
  ck_assert_float_eq(result.bits[3], 2147483648);
}
END_TEST

START_TEST(round_14) {
  s21_decimal value_1 = {{0, 1, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_round(value_1, &result);
  ck_assert_float_eq(result.bits[0], 0);
  ck_assert_float_eq(result.bits[1], 1);
  ck_assert_float_eq(result.bits[2], 0);
  ck_assert_float_eq(result.bits[3], 0);
}
END_TEST

START_TEST(round_15) {
  s21_decimal value_1 = {{2555, 0, 0, 0}};
  s21_setScale(&value_1, 2);
  s21_decimal result = {{0, 0, 0, 0}};
  s21_round(value_1, &result);
  ck_assert_float_eq(result.bits[0], 26);
  ck_assert_float_eq(result.bits[1], 0);
  ck_assert_float_eq(result.bits[2], 0);
  ck_assert_float_eq(result.bits[3], 0);
}
END_TEST

START_TEST(round_16) {
  s21_decimal val = {{7, 7, 7, 0}};
  s21_decimal res = {0};
  s21_round(val, &res);
  float fres = 0;
  s21_from_decimal_to_float(res, &fres);
  float need = 129127208515966861312.0;
  ck_assert_float_eq(need, fres);
}
END_TEST

START_TEST(round_17) {
  s21_decimal val = {{3, 3, 3, ~(S21_MAX_UINT / 2)}};
  s21_decimal res = {0};
  ck_assert_int_eq(0, s21_round(val, &res));
}
END_TEST

START_TEST(round_18) {
  s21_decimal val = {{128, 0, 0, 0}};
  s21_decimal res = {0};
  s21_setScale(&val, 1);
  s21_round(val, &res);
  float fres = 0;
  s21_from_decimal_to_float(res, &fres);
  float need = 13;
  ck_assert_float_eq(need, fres);
}
END_TEST

START_TEST(round_19) {
  s21_decimal val = {{53455, 0, 0, 0}};
  s21_decimal res = {0};
  s21_setScale(&val, 1);
  s21_round(val, &res);
  float fres = 0;
  s21_from_decimal_to_float(res, &fres);
  float need = 5346.0;
  ck_assert_float_eq(need, fres);
}
END_TEST

START_TEST(round_20) {
  s21_decimal val = {{534593545, 0, 0, 0}};
  s21_decimal res = {0};
  s21_setScale(&val, 1);
  s21_round(val, &res);
  float fres = 0;
  s21_from_decimal_to_float(res, &fres);
  float need = 53459355.0;
  ck_assert_float_eq(need, fres);
}
END_TEST

START_TEST(from_decimal_to_float_1) {
  s21_decimal val = {{123456789, 0, 0, 0}};
  s21_setScale(&val, 5);
  float res = 1234.56789;
  float tmp = 0.;
  float *dst = &tmp;
  s21_from_decimal_to_float(val, dst);
  ck_assert_float_eq(*dst, res);
}
END_TEST

START_TEST(from_decimal_to_float_2) {
  s21_decimal val = {{123456789, 0, 0, 0}};
  s21_setbit(&val, 127, 1);
  s21_setScale(&val, 5);
  float res = -1234.56789;
  float tmp = 0.;
  float *dst = &tmp;
  s21_from_decimal_to_float(val, dst);
  ck_assert_float_eq(*dst, res);
}
END_TEST

START_TEST(from_float_to_decimal_1) {
  s21_decimal decimal = {0};
  float num = 92000108940.0;
  int state = s21_from_float_to_decimal(num, &decimal);
  ck_assert_int_eq(state, OK);
  float test = 0;
  int result = s21_from_decimal_to_float(decimal, &test);
  ck_assert_int_eq(result, OK);
  ck_assert_float_eq(test, num);
}
END_TEST

START_TEST(from_float_to_decimal_2) {
  s21_decimal decimal = {0};
  float num = 17.000000000000;
  int state = s21_from_float_to_decimal(num, &decimal);
  ck_assert_int_eq(state, OK);
  float test = 0;
  int result = s21_from_decimal_to_float(decimal, &test);
  ck_assert_int_eq(result, OK);
  ck_assert_float_eq(test, num);
}
END_TEST

START_TEST(from_float_to_decimal_3) {
  s21_decimal decimal = {0};
  float num = 1743839.0;
  int state = s21_from_float_to_decimal(num, &decimal);
  ck_assert_int_eq(state, OK);
  float test = 0;
  int result = s21_from_decimal_to_float(decimal, &test);
  ck_assert_int_eq(result, OK);
  ck_assert_float_eq(test, num);
}
END_TEST

START_TEST(from_float_to_decimal_4) {
  s21_decimal decimal = {0};
  float num = 3849 * 1090009.0;
  int state = s21_from_float_to_decimal(num, &decimal);
  ck_assert_int_eq(state, OK);
  float test = 0;
  int result = s21_from_decimal_to_float(decimal, &test);
  ck_assert_int_eq(result, OK);
  ck_assert_float_eq(test, num);
}
END_TEST

START_TEST(from_float_to_decimal_5) {
  s21_decimal decimal = {0};
  float num = -10.0;
  int state = s21_from_float_to_decimal(num, &decimal);
  ck_assert_int_eq(state, OK);
  float test = 0;
  int result = s21_from_decimal_to_float(decimal, &test);
  ck_assert_int_eq(result, OK);
  ck_assert_float_eq(test, num);
}
END_TEST

START_TEST(from_float_to_decimal_6) {
  s21_decimal decimal = {0};
  float num = -17.0;
  int state = s21_from_float_to_decimal(num, &decimal);
  ck_assert_int_eq(state, OK);
  float test = 0;
  int result = s21_from_decimal_to_float(decimal, &test);
  ck_assert_int_eq(result, OK);
  ck_assert_float_eq(test, num);
}
END_TEST

START_TEST(from_float_to_decimal_7) {
  s21_decimal decimal = {0};
  float num = -1743839.0;
  int state = s21_from_float_to_decimal(num, &decimal);
  ck_assert_int_eq(state, OK);
  float test = 0;
  int result = s21_from_decimal_to_float(decimal, &test);
  ck_assert_int_eq(result, OK);
  ck_assert_float_eq(test, num);
}
END_TEST

START_TEST(from_float_to_decimal_8) {
  s21_decimal decimal = {0};
  float num = -599999000.0;
  int state = s21_from_float_to_decimal(num, &decimal);
  ck_assert_int_eq(state, OK);
  float test = 0;
  int result = s21_from_decimal_to_float(decimal, &test);
  ck_assert_int_eq(result, OK);
  ck_assert_float_eq(test, num);
}
END_TEST

START_TEST(from_float_to_decimal_9) {
  s21_decimal decimal = {0};
  float num = 4.5;
  int state = s21_from_float_to_decimal(num, &decimal);
  ck_assert_int_eq(state, OK);
  float test = 0;
  int result = s21_from_decimal_to_float(decimal, &test);
  ck_assert_int_eq(result, OK);
  ck_assert_float_eq_tol(test, num, 1e-06);
}
END_TEST

START_TEST(from_float_to_decimal_10) {
  s21_decimal decimal = {0};
  float num = 443.5112;
  int state = s21_from_float_to_decimal(num, &decimal);
  ck_assert_int_eq(state, OK);
  float test = 0;
  int result = s21_from_decimal_to_float(decimal, &test);
  ck_assert_int_eq(result, OK);
  ck_assert_float_eq_tol(test, num, 1e-07);
}
END_TEST

START_TEST(from_float_to_decimal_11) {
  s21_decimal decimal = {0};
  float num = 449223.913294;
  int state = s21_from_float_to_decimal(num, &decimal);
  ck_assert_int_eq(state, OK);
  float test = 0;
  int result = s21_from_decimal_to_float(decimal, &test);
  ck_assert_int_eq(result, OK);
  ck_assert_float_eq_tol(test, num, 1e-07);
}
END_TEST

START_TEST(from_float_to_decimal_12) {
  s21_decimal decimal = {0};
  float num = 43348.91;
  int state = s21_from_float_to_decimal(num, &decimal);
  ck_assert_int_eq(state, OK);
  float test = 0;
  int result = s21_from_decimal_to_float(decimal, &test);
  ck_assert_int_eq(result, OK);
  ck_assert_float_eq_tol(test, num, 1e-02);
}
END_TEST

START_TEST(from_float_to_decimal_13) {
  s21_decimal decimal = {0};
  float num = 127.1234;
  int state = s21_from_float_to_decimal(num, &decimal);
  ck_assert_int_eq(state, OK);
  float test = 0;
  int result = s21_from_decimal_to_float(decimal, &test);
  ck_assert_int_eq(result, OK);
  ck_assert_float_eq(test, num);
}
END_TEST

START_TEST(from_float_to_decimal_14) {
  s21_decimal decimal = {0};
  float num = 127.1234;
  int state = s21_from_float_to_decimal(num, &decimal);
  ck_assert_int_eq(state, OK);
  float test = 0;
  int result = s21_from_decimal_to_float(decimal, &test);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(from_float_to_decimal_15) {
  s21_decimal *decimal = NULL;
  float num = 127.1234;
  int state = s21_from_float_to_decimal(num, decimal);
  ck_assert_int_eq(state, 1);
}
END_TEST

START_TEST(from_float_to_decimal_16) {
  float inp = 2;
  s21_decimal *out = NULL;
  int error = s21_from_float_to_decimal(inp, out);
  ck_assert_ptr_eq(out, NULL);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(from_float_to_decimal_17) {
  float inp = 2;
  s21_decimal out = {{0, 0, 0, 0}};
  int error = s21_from_float_to_decimal(inp, &out);
  s21_decimal res = {{0x00000002, 0, 0, 0}};
  for (int i = LOW; i <= HIGH; i++) ck_assert_int_eq(out.bits[i], res.bits[i]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(from_float_to_decimal_18) {
  float inp = -321.2;
  s21_decimal out = {{0, 0, 0, 0}};
  int error = s21_from_float_to_decimal(inp, &out);
  s21_decimal res = {{0x00000C8C, 0, 0, 0x80010000}};
  for (int i = LOW; i <= HIGH; i++) ck_assert_int_eq(out.bits[i], res.bits[i]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(from_float_to_decimal_19) {
  float inp = 321.2;
  s21_decimal out = {{0, 0, 0, 0}};
  int error = s21_from_float_to_decimal(inp, &out);
  s21_decimal res = {{0x00000C8C, 0, 0, 0x00010000}};
  for (int i = LOW; i <= HIGH; i++) ck_assert_int_eq(out.bits[i], res.bits[i]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(from_float_to_decimal_20) {
  s21_decimal decimal = {0};
  float num = 14433489223.913293843944;
  int state = s21_from_float_to_decimal(num, &decimal);
  ck_assert_int_eq(state, OK);
  float test = 0;
  int result = s21_from_decimal_to_float(decimal, &test);
  ck_assert_int_eq(result, OK);
  ck_assert_float_eq_tol(test, num, 1e-07);
}
END_TEST

START_TEST(from_float_to_decimal_21) {
  s21_decimal decimal = {0};
  float num = 1e12;
  int state = s21_from_float_to_decimal(num, &decimal);
  ck_assert_int_eq(state, OK);
  float test = 0;
  int result = s21_from_decimal_to_float(decimal, &test);
  ck_assert_int_eq(result, 0);
  ck_assert_float_eq(test, num);
}
END_TEST

START_TEST(from_float_to_decimal_22) {
  s21_decimal decimal = {0};
  float num = 0.000000899;
  int state = s21_from_float_to_decimal(num, &decimal);
  ck_assert_int_eq(state, OK);
  float test = 0;
  int result = s21_from_decimal_to_float(decimal, &test);
  ck_assert_int_eq(result, 0);
  ck_assert_float_eq(test, num);
}
END_TEST

START_TEST(from_float_to_decimal_23) {
  s21_decimal val = {{0, 0, 0, 0}};
  float res = 0.;
  float tmp = -1234.56789;
  s21_from_float_to_decimal(tmp, &val);
  printf(" ");
  s21_from_decimal_to_float(val, &res);
  ck_assert_float_eq(res, tmp);
}
END_TEST

START_TEST(from_float_to_decimal_24) {
  s21_decimal val = {{0, 0, 0, 0}};
  float res = 0.;
  float tmp = 1234.56789;
  s21_from_float_to_decimal(tmp, &val);
  printf(" ");
  s21_from_decimal_to_float(val, &res);
  ck_assert_float_eq(res, tmp);
}
END_TEST
//
START_TEST(from_float_to_decimal_25) {
  s21_decimal val = {{0, 0, 0, 0}};
  float res = 0.;
  float tmp = -1234.56789;
  s21_from_float_to_decimal(tmp, &val);
  printf(" ");
  s21_from_decimal_to_float(val, &res);
  ck_assert_float_eq(res, tmp);
}
END_TEST

START_TEST(from_float_to_decimal_26) {
  s21_decimal val = {{0, 0, 0, 0}};
  float res = 0.;
  float tmp = 1234.56789;
  s21_from_float_to_decimal(tmp, &val);
  printf(" ");
  s21_from_decimal_to_float(val, &res);
  ck_assert_float_eq(res, tmp);
}
END_TEST
//
START_TEST(from_decimal_to_int_1) {
  s21_decimal val = {{123456789, 0, 0, 0}};
  s21_setScale(&val, 5);
  int res = 1234;
  int tmp = 0;
  int *dst = &tmp;
  s21_from_decimal_to_int(val, dst);
  ck_assert_int_eq(*dst, res);
}
END_TEST

START_TEST(from_decimal_to_int_2) {
  s21_decimal val = {{123456789, 0, 0, 0}};
  s21_setbit(&val, 127, 1);
  s21_setScale(&val, 5);
  int res = -1234;
  int tmp = 0.;
  int *dst = &tmp;
  s21_from_decimal_to_int(val, dst);
  ck_assert_int_eq(*dst, res);
}
END_TEST

START_TEST(from_int_to_decimal_1) {
  s21_decimal val = {{0, 0, 0, 0}};
  int res = 0;
  int tmp = 123456789;
  s21_from_int_to_decimal(tmp, &val);
  s21_from_decimal_to_int(val, &res);
  ck_assert_int_eq(res, tmp);
}
END_TEST

START_TEST(from_int_to_decimal_2) {
  s21_decimal val = {{0, 0, 0, 0}};
  int res = 0;
  int tmp = -123456789;
  s21_from_int_to_decimal(tmp, &val);
  s21_from_decimal_to_int(val, &res);
  ck_assert_int_eq(res, tmp);
}
END_TEST

int main(void) {
  Suite *s1 = suite_create("Core");
  TCase *tc1_1 = tcase_create("Core");
  SRunner *sr = srunner_create(s1);
  int nf;

  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, is_less_1);  // s21_is_less
  tcase_add_test(tc1_1, is_less_2);
  tcase_add_test(tc1_1, is_less_3);
  tcase_add_test(tc1_1, is_less_4);
  tcase_add_test(tc1_1, is_less_5);
  tcase_add_test(tc1_1, is_less_6);
  tcase_add_test(tc1_1, is_less_7);
  tcase_add_test(tc1_1, is_less_8);
  tcase_add_test(tc1_1, is_less_9);
  tcase_add_test(tc1_1, is_less_10);
  tcase_add_test(tc1_1, is_less_11);
  tcase_add_test(tc1_1, is_less_12);
  tcase_add_test(tc1_1, is_less_13);
  tcase_add_test(tc1_1, is_less_14);
  tcase_add_test(tc1_1, is_less_15);
  tcase_add_test(tc1_1, is_less_16);
  tcase_add_test(tc1_1, is_less_17);
  tcase_add_test(tc1_1, is_less_18);
  tcase_add_test(tc1_1, is_less_19);
  tcase_add_test(tc1_1, is_less_20);
  tcase_add_test(tc1_1, is_less_21);
  tcase_add_test(tc1_1, is_less_22);
  tcase_add_test(tc1_1, is_less_23);
  tcase_add_test(tc1_1, is_less_24);
  tcase_add_test(tc1_1, is_greater_1);  // s21_is_greater
  tcase_add_test(tc1_1, is_greater_2);
  tcase_add_test(tc1_1, is_greater_3);
  tcase_add_test(tc1_1, is_greater_4);
  tcase_add_test(tc1_1, is_greater_5);
  tcase_add_test(tc1_1, is_greater_6);
  tcase_add_test(tc1_1, is_greater_7);
  tcase_add_test(tc1_1, is_greater_8);
  tcase_add_test(tc1_1, is_greater_9);
  tcase_add_test(tc1_1, is_greater_or_equal_1);  // s21_is_greater_or_equal
  tcase_add_test(tc1_1, is_greater_or_equal_2);
  tcase_add_test(tc1_1, is_greater_or_equal_3);
  tcase_add_test(tc1_1, is_greater_or_equal_4);
  tcase_add_test(tc1_1, is_greater_or_equal_5);
  tcase_add_test(tc1_1, is_greater_or_equal_6);
  tcase_add_test(tc1_1, is_greater_or_equal_7);
  tcase_add_test(tc1_1, is_greater_or_equal_8);
  tcase_add_test(tc1_1, is_less_or_equal_1);  // s21_is_less_or_equal
  tcase_add_test(tc1_1, is_less_or_equal_2);
  tcase_add_test(tc1_1, is_less_or_equal_3);
  tcase_add_test(tc1_1, is_less_or_equal_4);
  tcase_add_test(tc1_1, is_less_or_equal_5);
  tcase_add_test(tc1_1, is_less_or_equal_6);
  tcase_add_test(tc1_1, is_less_or_equal_7);
  tcase_add_test(tc1_1, is_less_or_equal_8);
  tcase_add_test(tc1_1, is_less_or_equal_9);
  tcase_add_test(tc1_1, is_less_or_equal_10);
  tcase_add_test(tc1_1, is_less_or_equal_11);
  tcase_add_test(tc1_1, is_less_or_equal_12);
  tcase_add_test(tc1_1, is_less_or_equal_13);
  tcase_add_test(tc1_1, is_less_or_equal_14);
  tcase_add_test(tc1_1, is_less_or_equal_15);
  tcase_add_test(tc1_1, is_less_or_equal_16);
  tcase_add_test(tc1_1, is_less_or_equal_17);
  tcase_add_test(tc1_1, is_less_or_equal_18);
  tcase_add_test(tc1_1, is_less_or_equal_19);
  tcase_add_test(tc1_1, is_less_or_equal_20);
  tcase_add_test(tc1_1, is_less_or_equal_21);
  tcase_add_test(tc1_1, is_equal_1);  // s21_is_equal
  tcase_add_test(tc1_1, is_equal_2);
  tcase_add_test(tc1_1, is_equal_3);
  tcase_add_test(tc1_1, is_equal_4);
  tcase_add_test(tc1_1, is_equal_5);
  tcase_add_test(tc1_1, is_equal_6);
  tcase_add_test(tc1_1, is_equal_7);
  tcase_add_test(tc1_1, is_equal_8);
  tcase_add_test(tc1_1, is_equal_9);
  tcase_add_test(tc1_1, is_not_equal_1);  // s21_is_not_equal
  tcase_add_test(tc1_1, is_not_equal_2);
  tcase_add_test(tc1_1, is_not_equal_3);
  tcase_add_test(tc1_1, is_not_equal_4);
  tcase_add_test(tc1_1, is_not_equal_5);
  tcase_add_test(tc1_1, is_not_equal_6);
  tcase_add_test(tc1_1, is_not_equal_7);
  tcase_add_test(tc1_1, is_not_equal_8);
  tcase_add_test(tc1_1, is_not_equal_9);
  tcase_add_test(tc1_1, sub_1);  // s21_sub
  tcase_add_test(tc1_1, sub_2);
  tcase_add_test(tc1_1, sub_3);
  tcase_add_test(tc1_1, sub_4);
  tcase_add_test(tc1_1, sub_5);
  tcase_add_test(tc1_1, sub_6);
  tcase_add_test(tc1_1, sub_7);
  tcase_add_test(tc1_1, sub_8);
  tcase_add_test(tc1_1, sub_9);
  tcase_add_test(tc1_1, sub_10);
  tcase_add_test(tc1_1, sub_11);
  tcase_add_test(tc1_1, sub_12);
  tcase_add_test(tc1_1, sub_13);
  tcase_add_test(tc1_1, sub_14);
  tcase_add_test(tc1_1, sub_15);
  tcase_add_test(tc1_1, sub_16);
  tcase_add_test(tc1_1, sub_17);
  tcase_add_test(tc1_1, sub_18);
  tcase_add_test(tc1_1, sub_19);
  tcase_add_test(tc1_1, sub_20);
  tcase_add_test(tc1_1, sub_21);
  tcase_add_test(tc1_1, sub_22);
  tcase_add_test(tc1_1, add_1);  // s21_add
  tcase_add_test(tc1_1, add_2);
  tcase_add_test(tc1_1, add_3);
  tcase_add_test(tc1_1, add_4);
  tcase_add_test(tc1_1, add_5);
  tcase_add_test(tc1_1, add_6);
  tcase_add_test(tc1_1, add_7);
  tcase_add_test(tc1_1, add_8);
  tcase_add_test(tc1_1, add_9);
  tcase_add_test(tc1_1, add_10);
  tcase_add_test(tc1_1, add_11);
  tcase_add_test(tc1_1, add_12);
  tcase_add_test(tc1_1, add_13);
  tcase_add_test(tc1_1, add_14);
  tcase_add_test(tc1_1, add_15);
  tcase_add_test(tc1_1, add_16);
  tcase_add_test(tc1_1, add_17);
  tcase_add_test(tc1_1, add_18);
  tcase_add_test(tc1_1, add_19);
  tcase_add_test(tc1_1, add_20);
  tcase_add_test(tc1_1, add_21);
  tcase_add_test(tc1_1, add_22);
  tcase_add_test(tc1_1, add_23);
  tcase_add_test(tc1_1, add_24);
  tcase_add_test(tc1_1, add_25);
  tcase_add_test(tc1_1, add_26);
  tcase_add_test(tc1_1, add_27);
  tcase_add_test(tc1_1, mul_1);  // s21_mul
  tcase_add_test(tc1_1, mul_2);
  tcase_add_test(tc1_1, mul_3);
  tcase_add_test(tc1_1, mul_4);
  tcase_add_test(tc1_1, mul_5);
  tcase_add_test(tc1_1, mul_6);
  tcase_add_test(tc1_1, mul_7);
  tcase_add_test(tc1_1, mul_8);
  tcase_add_test(tc1_1, mul_9);
  tcase_add_test(tc1_1, mul_10);
  tcase_add_test(tc1_1, mul_11);
  tcase_add_test(tc1_1, mul_12);
  tcase_add_test(tc1_1, mul_13);
  tcase_add_test(tc1_1, div_1);  // s21_div
  tcase_add_test(tc1_1, div_2);
  tcase_add_test(tc1_1, div_3);
  tcase_add_test(tc1_1, div_4);
  tcase_add_test(tc1_1, div_5);
  tcase_add_test(tc1_1, div_6);
  tcase_add_test(tc1_1, div_7);
  tcase_add_test(tc1_1, div_8);
  tcase_add_test(tc1_1, div_9);
  tcase_add_test(tc1_1, div_10);
  tcase_add_test(tc1_1, div_11);
  tcase_add_test(tc1_1, div_12);
  tcase_add_test(tc1_1, div_13);
  tcase_add_test(tc1_1, div_14);
  tcase_add_test(tc1_1, div_15);
  tcase_add_test(tc1_1, div_16);
  tcase_add_test(tc1_1, div_17);
  tcase_add_test(tc1_1, div_18);
  tcase_add_test(tc1_1, negate_1);  // negate
  tcase_add_test(tc1_1, negate_2);
  tcase_add_test(tc1_1, negate_3);
  tcase_add_test(tc1_1, negate_4);
  tcase_add_test(tc1_1, round_1);  // round
  tcase_add_test(tc1_1, round_2);
  tcase_add_test(tc1_1, round_3);
  tcase_add_test(tc1_1, round_4);
  tcase_add_test(tc1_1, round_5);
  tcase_add_test(tc1_1, round_6);
  tcase_add_test(tc1_1, round_7);
  tcase_add_test(tc1_1, round_8);
  tcase_add_test(tc1_1, round_9);
  tcase_add_test(tc1_1, round_10);
  tcase_add_test(tc1_1, round_11);
  tcase_add_test(tc1_1, round_12);
  tcase_add_test(tc1_1, round_13);
  tcase_add_test(tc1_1, round_14);
  tcase_add_test(tc1_1, round_15);
  tcase_add_test(tc1_1, round_16);
  tcase_add_test(tc1_1, round_17);
  tcase_add_test(tc1_1, round_18);
  tcase_add_test(tc1_1, round_19);
  tcase_add_test(tc1_1, round_20);
  tcase_add_test(tc1_1, truncate_1);  // truncate
  tcase_add_test(tc1_1, truncate_2);
  tcase_add_test(tc1_1, truncate_3);
  tcase_add_test(tc1_1, truncate_4);
  tcase_add_test(tc1_1, truncate_5);
  tcase_add_test(tc1_1, floor_1);  // floor
  tcase_add_test(tc1_1, floor_2);
  tcase_add_test(tc1_1, floor_3);
  tcase_add_test(tc1_1, floor_4);
  tcase_add_test(tc1_1, from_decimal_to_float_1);  // from_decimal_to_float
  tcase_add_test(tc1_1, from_decimal_to_float_2);
  tcase_add_test(tc1_1, from_float_to_decimal_1);  // from_float_to_decimal
  tcase_add_test(tc1_1, from_float_to_decimal_2);
  tcase_add_test(tc1_1, from_float_to_decimal_3);
  tcase_add_test(tc1_1, from_float_to_decimal_4);
  tcase_add_test(tc1_1, from_float_to_decimal_5);
  tcase_add_test(tc1_1, from_float_to_decimal_6);
  tcase_add_test(tc1_1, from_float_to_decimal_7);
  tcase_add_test(tc1_1, from_float_to_decimal_8);
  tcase_add_test(tc1_1, from_float_to_decimal_9);
  tcase_add_test(tc1_1, from_float_to_decimal_10);
  tcase_add_test(tc1_1, from_float_to_decimal_11);
  tcase_add_test(tc1_1, from_float_to_decimal_12);
  tcase_add_test(tc1_1, from_float_to_decimal_13);
  tcase_add_test(tc1_1, from_float_to_decimal_14);
  tcase_add_test(tc1_1, from_float_to_decimal_15);
  tcase_add_test(tc1_1, from_float_to_decimal_16);
  tcase_add_test(tc1_1, from_float_to_decimal_17);
  tcase_add_test(tc1_1, from_float_to_decimal_18);
  tcase_add_test(tc1_1, from_float_to_decimal_19);
  tcase_add_test(tc1_1, from_float_to_decimal_20);
  tcase_add_test(tc1_1, from_float_to_decimal_21);
  tcase_add_test(tc1_1, from_float_to_decimal_22);
  tcase_add_test(tc1_1, from_float_to_decimal_23);
  tcase_add_test(tc1_1, from_float_to_decimal_24);
  tcase_add_test(tc1_1, from_float_to_decimal_25);
  tcase_add_test(tc1_1, from_float_to_decimal_26);
  tcase_add_test(tc1_1, from_decimal_to_int_1);  // from_decimal_to_int
  tcase_add_test(tc1_1, from_decimal_to_int_2);
  tcase_add_test(tc1_1, from_int_to_decimal_1);  // from_int_to_decimal
  tcase_add_test(tc1_1, from_int_to_decimal_2);

  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf == 0 ? 0 : 1;
}
