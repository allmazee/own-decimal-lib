#include "s21_decimal.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  *dst = 0;
  int res = 1;
  unsigned int min = 2147483648;
  s21_decrease_scale(&src, s21_get_scale(src));
  if (src.bits[0] == min && src.bits[1] == 0 && src.bits[2] == 0) {
    *dst = min;
    res = 0;
  }
  if (!s21_get_bit(src, 31) && src.bits[1] == 0 && src.bits[2] == 0) {
    if (!s21_get_bit(src, 127)) {
      *dst = src.bits[0];
    } else {
      *dst = src.bits[0] * -1;
    }
    res = 0;
  }
  return res;
}