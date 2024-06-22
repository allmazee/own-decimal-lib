#include "s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int res = 1;
  for (int i = 0; i < 4; i++) {
    dst->bits[i] = 0;
  }
  if (dst != NULL) {
    if (src == 0) {
      for (int i = 0; i < 4; i++) {
        dst->bits[i] = 0;
      }
      res = 0;
    }
    if (src > 0) {
      s21_set_bit(dst, 127, 0);
      dst->bits[0] = src;
      res = 0;
    }
    if (src < 0) {
      unsigned int tmp = src * -1;
      s21_set_bit(dst, 127, 1);
      dst->bits[0] = tmp;
      res = 0;
    }
  }
  return res;
}