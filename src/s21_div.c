#include "s21_decimal.h"

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int res = -1;
  s21_decimal zero = {{0, 0, 0, 0}};
  if (s21_is_equal(value_2, zero)) {
    res = 3;
  }
  if (result != NULL && res != 3) {
    for (int i = 0; i < 4; i++) {
      result->bits[i] = 0;
    }
    res = 0;
  }
  if (s21_is_equal(value_1, zero)) {
    res = 0;
  }
  return res;
}