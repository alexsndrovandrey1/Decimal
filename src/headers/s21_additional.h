#ifndef SRC_S21_AUXILIARY_H_
#define SRC_S21_AUXILIARY_H_

int s21_getbit(s21_decimal value, int bit);
int s21_getLastbit(s21_decimal value);
int s21_getSign(s21_decimal value);
s21_decimal *s21_setbit(s21_decimal *value, int pos, int bit);
s21_decimal *s21_setSign(s21_decimal *value, int bit);
int s21_addBit(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_getScale(s21_decimal value);
s21_decimal *s21_setScale(s21_decimal *value, int scale);
s21_decimal *s21_increaseScale(s21_decimal *value, int shift);
s21_decimal *s21_decreaseScale(s21_decimal *value, int shift);


int get_bit(int number, int position);
int lshifts(s21_decimal *num, int pow);
s21_decimal _lshift(s21_decimal num);
int setBit(unsigned int num, int index, int bit);
int zero(s21_decimal value);
int test_bit(unsigned int value, int BitNumber);
void set_1_bit(unsigned int *value, int BitNumber);
void set_0_bit(unsigned int *value, int BitNumber);
int s21_shift(s21_decimal *number);
void s21_unshift(s21_decimal *number);

void s21_alignmentScale(s21_decimal *value_1, s21_decimal *value_2);
s21_decimal *s21_convert(s21_decimal *value);
int s21_isNull(s21_decimal value);
int s21_getFloatExp(float *value);
s21_decimal *s21_leftShift(s21_decimal *value, int shift);

#endif 