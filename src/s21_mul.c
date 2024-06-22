#include "s21_decimal.h"

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int res = 0;
  int bit1 = s21_getBitLast(value_1);
  for (int i = 0; i < bit1; i++) {
    s21_decimal tmp = {{0, 0, 0, 0}};
    if (s21_get_bit(value_1, i)) {
      tmp = value_2;
      s21_left_shift(&tmp, i);
      res = s21_addBit(*result, tmp, result);
    }
  }
  if (res && s21_sign(value_1) != s21_sign(value_2)) res = 2;
  return res;
}