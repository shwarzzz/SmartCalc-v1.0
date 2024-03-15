#ifndef S21_CONVERT_TO_POLISH_H
#define S21_CONVERT_TO_POLISH_H
#include "s21_parser.h"

s21_stack* s21_convert_to_polish(s21_stack* input);
void s21_priority_check(s21_stack* elem, s21_stack* support, s21_stack* result);
void s21_add_rest(s21_stack* result, s21_stack* support);

#endif