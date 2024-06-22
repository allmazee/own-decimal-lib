#include "s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  int res = 1;
  if (result != NULL) {
    if (!s21_sign(value)) {
      s21_truncate(value, result);
      res = 0;
    } else {
      if (s21_get_scale(value) != 0) {
        s21_decrease_scale(&value, s21_get_scale(value) - 1);
        int remain = 0;
        s21_decimal one = {{1, 0, 0, 0}};
        s21_decimal tmp = {{0, 0, 0, 0}};
        for (int i = 95; i > -1; i--) {
          remain = (remain << 1) + s21_get_bit(value, i);
          if (remain >= 10) {
            remain -= 10;
            s21_set_bit(&tmp, i, 1);
          }
        }
        if (remain >= 1) {
          s21_addBit(one, tmp, result);
          s21_set_bit(result, 127, s21_sign(value));
        } else {
          *result = tmp;
          s21_set_bit(result, 127, s21_sign(value));
        }
      } else {
        *result = value;
      }
      res = 0;
    }
  }
  return res;
}