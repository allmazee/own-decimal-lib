#include "s21_decimal.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
  int res = 1;
  if (result != NULL) {
    for (int i = 0; i < 4; i++) {
      result->bits[i] = 0;
    }
    s21_decimal tmp = value;
    s21_decrease_scale(&tmp, s21_get_scale(tmp));
    *result = tmp;
    res = 0;
  }
  return res;
}