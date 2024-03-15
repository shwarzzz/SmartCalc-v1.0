#include "s21_convert_to_polish.h"

s21_stack* s21_convert_to_polish(s21_stack* input) {
  s21_stack* reverse_res = NULL;
  if (input != NULL) {
    s21_stack* result = s21_stack_init_elem(0, -6, 'h');
    s21_stack* support = s21_stack_init_elem(0, -6, 'h');
    s21_stack* elem = s21_get_tail_value(input);
    while (elem != input) {
      if (elem->symb == 'n' || elem->symb == 'x') {
        s21_stack_push(result, elem->value, elem->priority, elem->symb);
      } else {
        s21_priority_check(elem, support, result);
      }
      s21_stack_pop(input);
      elem = s21_get_tail_value(input);
    }
    s21_add_rest(result, support);
    s21_destroy_stack(input);
    support = NULL;
    reverse_res = s21_stack_reverse(result);
  }
  return reverse_res;
}

void s21_priority_check(s21_stack* elem, s21_stack* support,
                        s21_stack* result) {
  s21_stack* tmp = s21_get_tail_value(support);
  if (elem->symb != ')') {
    if (elem->priority <= tmp->priority && elem->symb != '(') {
      while (elem->priority <= tmp->priority) {
        s21_stack_push(result, tmp->value, tmp->priority, tmp->symb);
        s21_stack_pop(support);
        tmp = s21_get_tail_value(support);
      }
    }
    s21_stack_push(support, elem->value, elem->priority, elem->symb);
  } else {
    while (tmp->symb != '(') {
      s21_stack_push(result, tmp->value, tmp->priority, tmp->symb);
      s21_stack_pop(support);
      tmp = s21_get_tail_value(support);
    }
    s21_stack_pop(support);
  }
}

void s21_add_rest(s21_stack* result, s21_stack* support) {
  s21_stack* tmp = s21_get_tail_value(support);
  while (tmp != support) {
    s21_stack_push(result, tmp->value, tmp->priority, tmp->symb);
    s21_stack_pop(support);
    tmp = s21_get_tail_value(support);
  }
  s21_destroy_stack(support);
}
