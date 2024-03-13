#ifndef S21_DECIMAL_H
#define S21_DECIMAL_H

#include <limits.h>
#include <math.h>
#include <stdio.h>

typedef struct s21_decimal
{
    unsigned int bits[4];
} s21_decimal;

//  Используется в s21_from_float_to_decimal.
typedef union {
  int ui;
  float fl;
} fbits;


enum DIGIT { LOW, MID, HIGH, SCALE };
enum BOOLEAN { FALSE, TRUE };


#define S21_MAX_UINT 4294967295
#define S21_MAX_INT 2147483647
#define OK 0
#define POSITIVE_OVERFLOW 1
#define NEGATIVE_OVERFLOW 2
#define DIVISION_ERR 3

#include "./headers/s21_additional.h"
#include "./headers/s21_comparison.h"
#include "./headers/s21_arithmetic.h"
#include "./headers/s21_convertor.h"
#include "./headers/s21_other.h"

#endif