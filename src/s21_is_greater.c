#include "s21_decimal.h"

int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
  int res = 0, flag = 0;
  if (!(isNull(value_1) && isNull(value_2))) {
    if (s21_sign(value_1) == s21_sign(value_2)) {
      s21_align_scale(&value_1, &value_2);
      for (int i = 95; i >= 0 && flag != 1; i--) {
        int bit1 = s21_get_bit(value_1, i), bit2 = s21_get_bit(value_2, i);
        if (bit1 != bit2) {
          if (bit1 == 1) {
            res = (s21_sign(value_1)) ? 0 : 1;
            flag = 1;
          } else {
            res = (s21_sign(value_1)) ? 1 : 0;
            flag = 1;
          }
        }
      }
    } else {
      if (s21_sign(value_1) == 0) res = 1;
    }
  }
  return res;
}