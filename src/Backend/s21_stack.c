#include "s21_stack.h"

s21_stack* s21_stack_init_elem(double value, int pr, char symb) {
  s21_stack* new = (s21_stack*)calloc(1, sizeof(s21_stack));
  new->value = value;
  new->priority = pr;
  new->symb = symb;
  new->next = NULL;
  return new;
}

void s21_destroy_stack(s21_stack* head) {
  while (s21_stack_pop(head)) {
  };
  if (head != NULL) {
    free(head);
    head = NULL;
  }
}

int s21_stack_pop(s21_stack* head) {
  int ret = 1;
  if (head != NULL) {
    s21_stack* ptr = head;
    s21_stack* tmp = head;
    while (ptr->next != NULL) {
      tmp = ptr;
      ptr = ptr->next;
    }
    int h_check = 0;
    if (ptr == head) {
      h_check++;
    }
    if (!h_check) {
      free(ptr);
      ptr = NULL;
      tmp->next = NULL;
    } else {
      ret = 0;
    }
  } else {
    ret = 0;
  }
  return ret;
}

int s21_stack_push(s21_stack* head, double v, int p, char s) {
  s21_stack* new_elem = s21_stack_init_elem(v, p, s);
  s21_stack* ptr = head;
  while (ptr->next != NULL) {
    ptr = ptr->next;
  }
  ptr->next = new_elem;
  return 0;
}

s21_stack* s21_get_tail_value(s21_stack* head) {
  s21_stack* ptr = NULL;
  if (head != NULL) {
    ptr = head;
    while (ptr->next != NULL) {
      ptr = ptr->next;
    }
  }
  return ptr;
}

s21_stack* s21_stack_reverse(s21_stack* src) {
  s21_stack* new = s21_stack_init_elem(0, -6, 'h');
  s21_stack* tmp = NULL;
  while (tmp != src) {
    tmp = s21_get_tail_value(src);
    if (tmp != src) {
      s21_stack_push(new, tmp->value, tmp->priority, tmp->symb);
      s21_stack_pop(src);
    }
  }
  s21_destroy_stack(src);
  return new;
}

s21_stack* s21_stack_copy(s21_stack* src) {
  s21_stack* res = s21_stack_init_elem(0, -6, 'h');
  s21_stack* tmp = src;
  while (tmp->next != NULL) {
    tmp = tmp->next;
    s21_stack_push(res, tmp->value, tmp->priority, tmp->symb);
  }
  return res;
}
