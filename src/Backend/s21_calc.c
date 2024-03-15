#include "s21_calc.h"

int s21_calc(s21_stack* input, double* res, double x) {
  *res = 0;
  int ret = -1;
  if (input != NULL) {
    double numb[MAX_NUMB_COUNT] = {0};
    ret = 0;
    int index = -1;
    s21_x_change_value(input, x);
    s21_stack* tail = s21_get_tail_value(input);
    while (tail != input && ret != 3 && ret != 2) {
      if (tail->symb == 'x' || tail->symb == 'n') {
        index++;
        numb[index] = tail->value;
      } else {
        ret = s21_do_simple_arithm(tail, numb, &index);
        if (!ret) {
          ret = s21_do_hard_arithm(tail, numb, &index);
        }
      }
      s21_stack_pop(input);
      tail = s21_get_tail_value(input);
    }
    if (ret != 3 && ret != 2 && !isfinite(numb[index])) {
      ret = CALCULATION_ERROR;
    }
    if (ret != 3 && ret != 2) {
      *res = numb[index];
    }
    s21_destroy_stack(input);
  }
  return ret;
}

void s21_x_change_value(s21_stack* dst, double x) {
  s21_stack* ptr = dst;
  while (ptr->next != NULL) {
    if (ptr->symb == 'x') {
      ptr->value = x;
    }
    ptr = ptr->next;
  }
  if (ptr->symb == 'x') {
    ptr->value = x;
  }
}

int s21_do_simple_arithm(s21_stack* elem, double* numb, int* index) {
  int res = 1;
  if (elem->symb == '+') {
    numb[*index - 1] += numb[*index];
    (*index)--;
  } else if (elem->symb == '-') {
    numb[*index - 1] -= numb[*index];
    (*index)--;
  } else if (elem->symb == 'M') {
    numb[*index] *= -1;
  } else if (elem->symb == 'P') {
    numb[*index] *= 1;
  } else if (elem->symb == '*') {
    numb[*index - 1] *= numb[*index];
    (*index)--;
  } else if (elem->symb == '/') {
    if (numb[*index] == 0) {
      res = DIV_BY_ZERO;
    } else {
      numb[*index - 1] /= numb[*index];
      (*index)--;
    }
  } else if (elem->symb == '%') {
    if (numb[*index] != 0) {
      numb[*index - 1] = fmod(numb[*index - 1], numb[*index]);
      (*index)--;
    } else {
      res = DIV_BY_ZERO;
    }
  } else if (elem->symb == '^') {
    numb[*index - 1] = pow(numb[*index - 1], numb[*index]);
    (*index)--;
  } else {
    res = 0;
  }
  return res;
}

int s21_do_hard_arithm(s21_stack* elem, double* numb, int* index) {
  int res = 1;
  if (elem->symb == 's') {
    numb[*index] = sin(numb[*index]);
  } else if (elem->symb == 'c') {
    numb[*index] = cos(numb[*index]);
  } else if (elem->symb == 't') {
    numb[*index] = tan(numb[*index]);
  } else if (elem->symb == 'S') {
    if (fabs(numb[*index]) <= 1) {
      numb[*index] = asin(numb[*index]);
    } else {
      res = CALCULATION_ERROR;
    }
  } else if (elem->symb == 'C') {
    if (fabs(numb[*index]) <= 1) {
      numb[*index] = acos(numb[*index]);
    } else {
      res = CALCULATION_ERROR;
    }
  } else if (elem->symb == 'T') {
    numb[*index] = atan(numb[*index]);
  } else if (elem->symb == 'l') {
    if (numb[*index] > 0) {
      numb[*index] = log10(numb[*index]);
    } else {
      res = CALCULATION_ERROR;
    }
  } else if (elem->symb == 'L') {
    if (numb[*index] > 0) {
      numb[*index] = log(numb[*index]);
    } else {
      res = CALCULATION_ERROR;
    }
  } else if (elem->symb == 'q') {
    if (numb[*index] < 0) {
      res = CALCULATION_ERROR;
    } else {
      numb[*index] = sqrt(numb[*index]);
    }
  } else {
    res = 0;
  }
  return res;
}
