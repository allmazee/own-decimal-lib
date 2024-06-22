#ifndef S_21_DECIMAL_H
#define S_21_DECIMAL_H

#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  unsigned int bits[4];
} s21_decimal;

int s21_get_bit(s21_decimal value, int bit);
int s21_getBitLast(s21_decimal value);
s21_decimal *s21_set_bit(s21_decimal *value, int bit, int set);
int s21_addBit(s21_decimal first, s21_decimal second, s21_decimal *result);

int s21_sign(s21_decimal value);

int s21_get_scale(s21_decimal value);
s21_decimal *s21_set_scale(s21_decimal *value, int scale);
s21_decimal *s21_increase_scale(s21_decimal *value, int shift);
s21_decimal *s21_decrease_scale(s21_decimal *value, int shift);
void s21_align_scale(s21_decimal *value_1, s21_decimal *value_2);

s21_decimal *s21_left_shift(s21_decimal *value, int shift);
s21_decimal *s21_right_shift(s21_decimal *value, int shift);

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

int s21_is_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_less(s21_decimal value_1, s21_decimal value_2);
int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2);

int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

void s21_mul_10(s21_decimal *res, int exp);
s21_decimal s21_inverse_bits(s21_decimal value);
int isNull(s21_decimal value);
void calc_mantiss(char *str_mantiss, int *dot, int len, int *mantiss,
                  int *zeros);

#endif  // S_21_DECIMAL_H