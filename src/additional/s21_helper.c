#include "./../s21_decimal.h"

int s21_getbit(s21_decimal value, int bit) {
  return !!(value.bits[bit / 32] & (1u << (bit % 32)));
}

int s21_getLastbit(s21_decimal value) {
  int last = 95;
  for (; (last >= 0) && (!s21_getbit(value, last));) last -= 1;
  return last;
}

int s21_getSign(s21_decimal value) {
  int result = !!(value.bits[3] & (1u << 31));
  return result;
}

s21_decimal *s21_setbit(s21_decimal *value, int pos, int bit) {
  if (pos / 32 < 4 && bit)
    value->bits[pos / 32] |= (1u << (pos % 32));
  else if (pos / 32 < 4 && !bit)
    value->bits[pos / 32] &= ~(1u << (pos % 32));
  return value;
}

s21_decimal *s21_setSign(s21_decimal *value, int bit) {
  value->bits[3] =
      (bit) ? (value->bits[3] | (1u << 31)) : (value->bits[3] & ~(1u << 31));
  return value;
}

int s21_addBit(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int fres = 0, exp = 0;
  for (int i = 0; i < 96; i += 1) {
    int bit_1 = s21_getbit(value_1, i), bit_2 = s21_getbit(value_2, i);
    if (!bit_1 && !bit_2)
      exp ? s21_setbit(result, i, (exp = 0) + 1) : s21_setbit(result, i, 0);
    else if (bit_1 != bit_2)
      exp ? s21_setbit(result, i, (exp = 1) - 1) : s21_setbit(result, i, 1);
    else
      exp ? s21_setbit(result, i, (exp = 1))
          : s21_setbit(result, i, (exp = 1) - 1);
    if (i == 95 && exp == 1 && !s21_getbit(value_1, 97) &&
        !s21_getbit(value_2, 97))
      fres = 1;
  }
  return fres;
}

int s21_getScale(s21_decimal value) {
  int result = (char)(value.bits[3] >> 16);
  return result;
}

s21_decimal *s21_setScale(s21_decimal *value, int scale) {
  if (scale >= 0 && scale <= 28) {
    int sign = s21_getSign(*value);
    value->bits[3] &= ~(0xFF << 16);
    value->bits[3] |= scale << 16;
    sign ? s21_setSign(value, 1) : value;
  }
  return value;
}

s21_decimal *s21_increaseScale(s21_decimal *value, int shift) {
  if (s21_getScale(*value) + shift < 29) {
    s21_setScale(value, s21_getScale(*value) + shift);
    s21_decimal auxValue_1 = *value, auxValue_2 = *value;
    if (s21_addBit(*s21_leftShift(&auxValue_1, 1),
                   *s21_leftShift(&auxValue_2, 3), value))
      s21_setbit(value, 96, 1);
  }
  return value;
}

s21_decimal *s21_decreaseScale(s21_decimal *value, int shift) {
  for (int i = 0; i < shift; i += 1) {
    unsigned long long overflow = value->bits[2];
    for (int j = 2; j >= 0; j -= 1) {
      value->bits[j] = overflow / 10;
      overflow =
          (overflow % 10) * (S21_MAX_UINT + 1) + value->bits[j ? j - 1 : j];
    }
  }
  s21_setScale(value, (s21_getScale(*value) - shift));
  return value;
}

void s21_alignmentScale(s21_decimal *value_1, s21_decimal *value_2) {
  if (s21_getScale(*value_1) != s21_getScale(*value_2)) {
    if (s21_getScale(*value_1) < s21_getScale(*value_2)) {
      s21_alignmentScale(value_2, value_1);
    } else {
      int scaleLow = s21_getScale(*value_2), scaleHigh = s21_getScale(*value_1);
      for (; (scaleHigh - scaleLow) && !s21_getbit(*value_2, 96); scaleLow += 1)
        s21_increaseScale(value_2, 1);
      for (; scaleHigh - scaleLow; scaleHigh -= 1) {
        s21_decreaseScale(value_1, scaleHigh - scaleLow);
        s21_setScale(value_1, scaleLow);
      }
    }
  }
}

s21_decimal *s21_convert(s21_decimal *value) {
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal add = {{1, 0, 0, 0}};
  for (int x = 0; x < 3; x += 1) value->bits[x] = ~value->bits[x];
  s21_addBit(*value, add, &result);
  for (int x = 0; x < 3; x += 1) value->bits[x] = result.bits[x];
  s21_setbit(value, 97, 1);
  return value;
}

int zero(s21_decimal value) {
  int error = 3;
  if (value.bits[0] == 0 && value.bits[1] == 0 && value.bits[2] == 0 &&
      value.bits[3] == 0)
    error = 3;
  else
    error = 0;
  return error;
}

int test_bit(unsigned int value, int BitNumber) {
  return value & (1 << BitNumber);
}

void set_1_bit(unsigned int *value, int BitNumber) {
  *value |= (1 << BitNumber);
}

void set_0_bit(unsigned int *value, int BitNumber) {
  *value &= ~(1 << BitNumber);
}

int s21_shift(s21_decimal *number) {
  int vault_1 = 0;
  int vault_2 = 0;
  int error = test_bit(number->bits[2], 31);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 32; j++) {
      vault_2 = test_bit((number->bits[i]), j);
      if (vault_1)
        set_1_bit(&number->bits[i], j);
      else
        set_0_bit(&number->bits[i], j);
      vault_1 = vault_2;
    }
  }
  return error;
}

void s21_unshift(s21_decimal *number) {
  int vault_1 = 0;
  int vault_2 = 0;
  for (int i = 2; i >= 0; i--) {
    for (int j = 31; j >= 0; j--) {
      vault_2 = test_bit((number->bits[i]), j);
      if (vault_1)
        set_1_bit(&number->bits[i], j);
      else
        set_0_bit(&number->bits[i], j);
      vault_1 = vault_2;
    }
  }
}

int get_bit(int number, int position) {
  number = number >> position;
  number = number & 1;
  return number;
}

int lshifts(s21_decimal *num, int pow) {
  int res = 0;

  for (int i = 0; i < pow; i++) {
    if (get_bit(num->bits[2], 31)) {
      res = 1;
      break;
    }
    *num = _lshift(*num);
  }

  return res;
}

s21_decimal _lshift(s21_decimal num) {
  int res = 0;
  int res1 = 0;
  if (get_bit(num.bits[0], 31)) {
    res = 1;
  }
  num.bits[0] = num.bits[0] << 1;
  if (get_bit(num.bits[1], 31)) {
    res1 = 1;
  }
  num.bits[1] = num.bits[1] << 1;
  num.bits[1] = setBit(num.bits[1], 0, res);

  num.bits[2] = num.bits[2] << 1;
  num.bits[2] = setBit(num.bits[2], 0, res1);
  return num;
}

int setBit(unsigned int num, int index, int bit) {
  int r = 1 << index;
  if (bit == 1) {
    num |= r;
  } else {
    r = ~r;
    num = num & r;
  }
  return (num);
}

int s21_isNull(s21_decimal value) {
  return !value.bits[0] && !value.bits[1] && !value.bits[2];
}

int s21_getFloatExp(float *value) {
  return ((*((int *)value) & ~(1u << 31)) >> 23) - 127;
}

s21_decimal *s21_leftShift(s21_decimal *value, int shift) {
  if (!(s21_getLastbit(*value) + shift > 95)) {
    for (int y = 0; y < shift; y += 1) {
      int bitTransfer_1 = s21_getbit(*value, 31);
      int bitTransfer_2 = s21_getbit(*value, 63);
      for (int x = 0; x < 3; x += 1) value->bits[x] <<= 1;
      if (bitTransfer_1) s21_setbit(value, 32, 1);
      if (bitTransfer_2) s21_setbit(value, 64, 1);
    }
  }
  return value;
}