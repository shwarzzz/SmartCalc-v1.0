#ifndef S21_STACK_H

#define S21_STACK_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct stack {
  double value;
  int priority;
  char symb;
  struct stack* next;
} s21_stack;

s21_stack* s21_stack_init_elem(double value, int pr, char symb);
int s21_stack_push(s21_stack* head, double v, int p, char s);
int s21_stack_pop(s21_stack* head);
void s21_destroy_stack(s21_stack* head);
s21_stack* s21_get_tail_value(s21_stack* head);
s21_stack* s21_stack_reverse(s21_stack* src);
s21_stack* s21_stack_copy(s21_stack* src);
#endif
