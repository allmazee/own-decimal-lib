#include "s21_decimal.h"

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int res = -1;
  s21_decimal temp = {{0, 0, 0, 0}};
  s21_decimal one = {{1, 0, 0, 0}};
  s21_align_scale(&value_1, &value_2);
  int scale = s21_get_scale(value_1);
  int loc_1 = s21_getBitLast(value_1);
  int loc_2 = s21_getBitLast(value_2);
  int sign_1 = s21_sign(value_1);
  int sign_2 = s21_sign(value_2);
  for (int i = 0; i < 4; i++) {
    result->bits[i] = 0;
  }
  if (sign_1 && sign_2) {
    if (loc_1 > loc_2) {
      s21_addBit(s21_inverse_bits(value_2), one, &temp);
      s21_addBit(value_1, temp, result);
      s21_set_bit(result, 97, 0);
      s21_set_bit(result, 127, 1);
      s21_set_scale(result, scale);
    } else {
      s21_addBit(s21_inverse_bits(value_1), one, &temp);
      s21_addBit(value_2, temp, result);
      s21_set_bit(result, 97, 0);
      s21_set_bit(result, 127, 0);
      s21_set_scale(result, scale);
    }
    res = 0;
  }
  if (!sign_1 && !sign_2) {
    if (loc_1 >= loc_2) {
      s21_addBit(s21_inverse_bits(value_2), one, &temp);
      s21_addBit(value_1, temp, result);
      s21_set_bit(result, 97, 0);
      s21_set_bit(result, 127, 0);
      s21_set_scale(result, scale);
    } else {
      s21_addBit(s21_inverse_bits(value_1), one, &temp);
      s21_addBit(value_2, temp, result);
      s21_set_bit(result, 97, 0);
      s21_set_bit(result, 127, 1);
      s21_set_scale(result, scale);
    }
    res = 0;
  }
  if (sign_1 && !sign_2) {
    s21_set_bit(&value_2, 127, 1);
    res = s21_add(value_1, value_2, result);
    s21_set_bit(result, 127, 0);
  }
  if (!sign_1 && sign_2) {
    s21_set_bit(&value_2, 127, 0);
    res = s21_add(value_1, value_2, result);
    s21_set_bit(result, 127, 1);
  }
  return res;
}