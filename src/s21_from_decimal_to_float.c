#include "s21_decimal.h"

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int res = 1;
  if (dst != NULL) {
    double tmp = 0;
    int exp = 0;
    *dst = 0;
    for (int i = 0; i < 96; i++) {
      if (src.bits[i / 32] & (1 << (i % 32))) {
        tmp += pow(2, i);
      }
    }
    if (s21_sign(src)) {
      tmp *= -1;
    }
    for (exp = s21_get_scale(src); exp > 0; exp--) {
      tmp /= 10;
    }
    *dst = (float)tmp;
    res = 0;
  }
  return res;
}
