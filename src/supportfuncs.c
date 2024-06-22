#include "s21_decimal.h"

int s21_get_bit(s21_decimal value, int bit) {
  int id_bits = bit / 32;
  int id_bit = bit % 32;
  int res = !!(value.bits[id_bits] & (1u << id_bit));
  return res;
}

int s21_getBitLast(s21_decimal value) {
  int bit = 95, f = 1;
  while (bit >= 0 && f) {
    if (s21_get_bit(value, bit)) {
      f = 0;
    } else {
      bit--;
    }
  }
  return bit;
}

s21_decimal *s21_set_bit(s21_decimal *value, int bit, int set) {
  int id_bits = bit / 32;
  int id_bit = bit % 32;
  if (set == 1) {
    value->bits[id_bits] = value->bits[id_bits] | (1u << id_bit);
  } else {
    if (s21_get_bit(*value, bit)) {
      value->bits[id_bits] = ~(~value->bits[id_bits] | (1u << id_bit));
    }
  }
  return value;
};

int s21_sign(s21_decimal value) { return s21_get_bit(value, 127); }

int s21_addBit(s21_decimal first, s21_decimal second, s21_decimal *result) {
  int add_1 = 0;
  // int max_f = 0;
  int res = 1;
  for (int i = 0; i < 96; i++) {
    int temp1 = s21_get_bit(first, i);
    int temp2 = s21_get_bit(second, i);
    if (!temp1 && !temp2) {
      if (add_1) {
        s21_set_bit(result, i, 1);
        add_1 = 0;
      } else {
        s21_set_bit(result, i, 0);
      }
    }
    if (temp1 && !temp2) {
      if (add_1) {
        s21_set_bit(result, i, 0);
        add_1 = 1;
      } else {
        s21_set_bit(result, i, 1);
      }
    }
    if (!temp1 && temp2) {
      if (add_1) {
        s21_set_bit(result, i, 0);
        add_1 = 1;
      } else {
        s21_set_bit(result, i, 1);
      }
    }
    if (temp1 && temp2) {
      if (add_1) {
        s21_set_bit(result, i, 1);
        add_1 = 1;
      } else {
        s21_set_bit(result, i, 0);
        add_1 = 1;
      }
    }
  }
  // if (!add_1 && !s21_get_bit(first, 97) && !s21_get_bit(second, 97)) {
  //   max_f = 1;
  // }
  if (add_1 && !s21_get_bit(*result, 95)) {
    res = 0;
  }
  return res;
}

int s21_get_scale(s21_decimal value) {
  int mask = 0b11111111;
  int scale = (value.bits[3] >> 16) & mask;
  return scale;
}

s21_decimal *s21_set_scale(s21_decimal *value, int scale) {
  if (scale >= 0 && scale <= 28) {
    int mask = 0b11111111;
    value->bits[3] &= ~(mask << 16);
    value->bits[3] |= scale << 16;
  }
  return value;
}

s21_decimal *s21_left_shift(s21_decimal *value, int shift) {
  if (s21_getBitLast(*value) + shift <= 95) {
    for (int i = shift; i > 0; i--) {
      value->bits[2] <<= 1;
      if (s21_get_bit(*value, 63)) {
        s21_set_bit(value, 64, 1);
      }
      value->bits[1] <<= 1;
      if (s21_get_bit(*value, 31)) {
        s21_set_bit(value, 32, 1);
      }
      value->bits[0] <<= 1;
    }
  }
  return value;
}

s21_decimal *s21_right_shift(s21_decimal *value, int shift) {
  if (s21_getBitLast(*value) - shift >= -1) {
    for (int i = shift; i > 0; i--) {
      value->bits[0] >>= 1;
      if (s21_get_bit(*value, 32)) {
        s21_set_bit(value, 31, 1);
      }
      value->bits[1] >>= 1;
      if (s21_get_bit(*value, 64)) {
        s21_set_bit(value, 63, 1);
      }
      value->bits[2] >>= 1;
    }
  }
  return value;
}

s21_decimal *s21_increase_scale(s21_decimal *value, int shift) {
  if (s21_get_scale(*value) + shift < 29) {
    s21_set_scale(value, s21_get_scale(*value) + shift);
    s21_left_shift(value, shift);
  }
  return value;
}

s21_decimal *s21_decrease_scale(s21_decimal *value, int shift) {
  int remain = 0;
  int sign = s21_sign(*value);
  s21_decimal tmp = {{0, 0, 0, 0}};
  for (int j = shift; j > 0; j--) {
    remain = 0;
    tmp.bits[0] = 0;
    tmp.bits[1] = 0;
    tmp.bits[2] = 0;
    tmp.bits[3] = 0;
    for (int i = 95; i > -1; i--) {
      remain = (remain << 1) + s21_get_bit(*value, i);
      if (remain >= 10) {
        remain -= 10;
        s21_set_bit(&tmp, i, 1);
      }
    }
    s21_set_bit(&tmp, 127, sign);
    *value = tmp;
  }
  return value;
}

void s21_align_scale(s21_decimal *value_1, s21_decimal *value_2) {
  int scale_1 = s21_get_scale(*value_1);
  int scale_2 = s21_get_scale(*value_2);
  int diff = scale_1 - scale_2;
  if (scale_1 != scale_2) {
    if (diff > 0) {  // 2.0
      if (scale_1 <= 28) {
        s21_increase_scale(value_2, diff);
      } else {
        s21_increase_scale(value_2, 28 - scale_2);
        s21_decrease_scale(value_1, scale_1 - 28);
      }
    } else {
      if (scale_2 <= 28) {
        s21_increase_scale(value_1, -diff);
      } else {
        s21_increase_scale(value_1, 28 - scale_1);
        s21_decrease_scale(value_2, scale_2 - 28);
      }
    }
  }
}

void s21_mul_10(s21_decimal *res, int exp) {
  for (int i = exp; i > 0; i--) {
    s21_decimal tmp_1 = *res;
    s21_decimal tmp_2 = *res;
    s21_left_shift(&tmp_1, 1);
    s21_left_shift(&tmp_2, 3);
    s21_addBit(tmp_1, tmp_2, res);
  }
}

s21_decimal s21_inverse_bits(s21_decimal value) {
  s21_decimal res = {{0, 0, 0, 0}};
  for (int i = 0; i < 3; i++) {
    res.bits[i] = ~value.bits[i];
  }
  return res;
}

int isNull(s21_decimal value) {
  int res = 0;
  if (!value.bits[0] && !value.bits[1] && !value.bits[2]) res = 1;
  return res;
}

void calc_mantiss(char *str_mantiss, int *dot, int len, int *mantiss,
                  int *zeros) {
  if (str_mantiss[0] == '-') {
    *dot = 2;
  } else {
    *dot = 1;
  }
  for (int i = *dot; i < len; i++) {
    if (i != len - 1) {
      str_mantiss[i] = str_mantiss[i + 1];
    } else {
      str_mantiss[i] = '\0';
    }
  }
  *mantiss = atoi(str_mantiss);
  while (*mantiss % 10 == 0) {
    *mantiss = *mantiss / 10;
    *zeros = *zeros + 1;
  }
}