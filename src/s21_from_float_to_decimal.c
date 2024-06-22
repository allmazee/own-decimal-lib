#include "s21_decimal.h"

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int res = 1;
  if (dst != NULL) {
    if (src == src && src <= 79228162514264337593543950336.0 &&
        src >= -79228162514264337593543950336.0 && !(src < 1e-28 && src > 0) &&
        !(src > -1e-28 && src < 0)) {
      for (int i = 0; i < 4; i++) {
        dst->bits[i] = 0;
      }
      res = 0;
    }
    if (!res && src != 0) {
      char str[14] = "", str_mantiss[9] = "";
      char delim[] = "e", *token = NULL;
      int mantiss = 0, exp_f = 6, exp = 0, zeros = 0, dot = 0, len = 0;
      sprintf(str, "%e", src);
      token = strtok(str, delim);
      sprintf(str_mantiss, "%s", token);
      len = strlen(str_mantiss);

      calc_mantiss(str_mantiss, &dot, len, &mantiss, &zeros);

      token = strtok(NULL, delim);
      exp = atoi(token);  // после "e"
      exp_f = exp_f - zeros;  // в научной нотации до "e", исключая нули
      exp = exp - exp_f;  // результирующая степень
      if (exp < 0) {
        if (-exp <= 28) {
          s21_from_int_to_decimal(mantiss, dst);
          s21_set_scale(dst, -exp);
        } else {
          for (int i = 28 + exp; i < 0; i++) {
            if (mantiss % 10 >= 5 && i == -1) {
              mantiss += 10;
            }
            if (mantiss % 10 <= -5 && i == -1) {
              mantiss -= 10;
            }
            mantiss = mantiss / 10;
          }
          s21_from_int_to_decimal(mantiss, dst);
          s21_set_scale(dst, 28);
        }
      }
      if (exp > 0) {
        s21_from_int_to_decimal(mantiss, dst);
        s21_mul_10(dst, exp);
        s21_set_scale(dst, 0);
      }
      if (exp == 0) {
        s21_from_int_to_decimal(mantiss, dst);
        s21_set_scale(dst, 0);
      }
    }
  }
  return res;
}
