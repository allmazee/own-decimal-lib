#include "s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int res = 0;
  int tmp = 0;
  int sign1 = s21_sign(value_1), sign2 = s21_sign(value_2);
  for (int i = 0; i < 4; i++) {
    result->bits[i] = 0;
  }
  if (sign1 == sign2) {
    s21_align_scale(&value_1, &value_2);
    tmp = s21_addBit(value_1, value_2, result);
    if (tmp) {
      s21_set_scale(result, s21_get_scale(value_1));
      s21_set_bit(result, 127, sign1);
    } else {
      if (sign1) {
        res = 2;
      } else {
        res = 1;
      }
    }
  } else if (sign1 && !sign2) {
    s21_set_bit(&value_1, 127, 0);
    res = s21_sub(value_2, value_1, result);
  } else if (!sign1 && sign2) {
    s21_set_bit(&value_2, 127, s21_get_bit(value_1, 127));
    res = s21_sub(value_1, value_2, result);
  }
  return res;
}