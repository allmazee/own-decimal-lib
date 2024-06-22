#include "s21_decimal.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
  for (int i = 0; i < 4; i++) {
    result->bits[i] = 0;
  }
  *result = value;
  if (s21_sign(value)) {
    s21_set_bit(result, 127, 0);
  } else {
    s21_set_bit(result, 127, 1);
  }
  return 0;
}
