#ifndef S21_CALC_H

#define S21_CALC_H

#include "s21_convert_to_polish.h"

#define DIV_BY_ZERO 3
#define MAX_NUMB_COUNT 255
#define CALCULATION_ERROR 2

int s21_calc(s21_stack* input, double* d, double x);
void s21_x_change_value(s21_stack* dst, double x);
int s21_do_simple_arithm(s21_stack* elem, double* numb, int* index);
int s21_do_hard_arithm(s21_stack* elem, double* numb, int* index);
#endif