#include "s21_parser.h"

s21_stack* s21_parse_string(char* str) {
  int error = 0;
  s21_stack* head = s21_stack_init_elem(0, -6, 'h');
  s21_stack* input = NULL;
  for (int i = 0; !error && str[i] != '\0'; i++) {
    if (s21_isdigit(str[i]) != 0) {
      int start = i;
      if (s21_convert_num_to_str(head, str, &i) == 2 ||
          (start > 0 && (str[start - 1] == 'x' || str[start - 1] == ')'))) {
        error = INPUT_ERROR;
      }
    } else if (str[i] == 'x') {
      if (i == 0 || (i > 0 && (s21_isdigit(str[i - 1]) == 0 &&
                               str[i - 1] != ')' && str[i - 1] != 'x'))) {
        s21_stack_push(head, 0, 0, 'x');
      } else {
        error = INPUT_ERROR;
      }
    } else if (!s21_algebraic_signs_check(head, str, i, &error)) {
      if (!s21_bracket_search(head, str, &error, i, str[i])) {
        if (!s21_math_lexeme_check(head, str, &i, &error)) {
          if (!s21_triganom_lexeme_check(head, str, &i, &error)) {
            if (str[i] != '\0') {
              error = INPUT_ERROR;
            }
          }
        }
      }
    }
  }
  if (error == 2) {
    s21_destroy_stack(head);
    head = NULL;
  } else {
    input = s21_stack_reverse(head);
    head = NULL;
  }
  return input;
}

int s21_convert_num_to_str(s21_stack* head, char* str, int* index) {
  char num[1000] = "";
  int i = 0;
  int dot_count = 0;
  int flag = 0;
  for (; !flag; (*index)++) {
    if ((s21_isdigit(str[*index]) != 0 || str[*index] == '.') &&
        str[*index] != '\0') {
      num[i] = str[*index];
      if (str[*index] == '.') {
        dot_count++;
      }
      i++;
    } else {
      if ((i > 0 && num[i - 1] == '.') || dot_count > 1 ||
          (i > 1 && num[0] == '0' && num[1] != '.')) {
        flag = INPUT_ERROR;
        (*index) = 0;
      } else {
        (*index)--;
        flag++;
      }
    }
  }
  if (flag == 1) {
    (*index)--;
    num[i] = '\0';
    double res = s21_convert_to_double(num);
    s21_stack_push(head, res, 0, 'n');
  }
  return flag;
}

double s21_convert_to_double(char* str) {
  int dot_check = 0;
  double count = 1;
  double res = 0;
  for (int i = 0; str[i] != '\0'; i++) {
    if (str[i] == '.') {
      dot_check++;
      count = 0;
    } else {
      res = res * 10 + (str[i] - '0');
      count++;
    }
  }
  if (dot_check) {
    res /= pow(10, count);
  }
  return res;
}

int s21_algebraic_signs_check(s21_stack* head, char* str, int index, int* err) {
  int res = 1;
  if (str[index] == '+' || str[index] == '-') {
    if (index == 0 || (index > 0 && str[index - 1] == '(')) {
      if (s21_next_symb_check(str, index + 1)) {
        if (str[index] == '+') {
          s21_stack_push(head, 0, 1, 'P');
        } else {
          s21_stack_push(head, 0, 1, 'M');
        }
      } else {
        *err = INPUT_ERROR;
      }
    } else if (index > 0 &&
               (str[index - 1] == ')' || str[index - 1] == 'x' ||
                s21_isdigit(str[index - 1]) != 0) &&
               s21_next_symb_check(str, index + 1)) {
      s21_stack_push(head, 0, 1, str[index]);
    } else {
      *err = INPUT_ERROR;
    }
  } else if (str[index] == '*' || str[index] == '/') {
    if (index == 0 ||
        (index > 0 && (s21_isdigit(str[index - 1]) == 0 &&
                       str[index - 1] != 'x' && str[index - 1] != ')')) ||
        !s21_next_symb_check(str, index + 1)) {
      *err = INPUT_ERROR;
    } else {
      s21_stack_push(head, 0, 2, str[index]);
    }
  } else if (str[index] == '^') {
    if (index == 0 ||
        (index > 0 && (s21_isdigit(str[index - 1]) == 0 &&
                       str[index - 1] != 'x' && str[index - 1] != ')')) ||
        !s21_next_symb_check(str, index + 1)) {
      *err = INPUT_ERROR;
    } else {
      s21_stack_push(head, 0, 3, str[index]);
    }
  } else {
    res = 0;
  }
  return res;
}

int s21_bracket_search(s21_stack* head, char* str, int* err, int i, char c) {
  int res = 0;
  int find_check = 0;
  if (c == '(') {
    res++;
    if (i - 1 >= 0 && (str[i - 1] == 'x' || s21_isdigit(str[i - 1]))) {
      *err = INPUT_ERROR;
    } else {
      i++;
      for (; str[i] != '\0' && find_check != 1; i++) {
        if (str[i] == '(') {
          find_check--;
        } else if (str[i] == ')') {
          find_check++;
          if (str[i - 1] == '(') {
            *err = INPUT_ERROR;
          }
        }
      }
      if (find_check != 1) {
        *err = INPUT_ERROR;
      }
    }
  } else if (c == ')') {
    res++;
    i--;
    for (; i >= 0 && find_check != 1; i--) {
      if (str[i] == ')') {
        find_check--;
      } else if (str[i] == '(') {
        find_check++;
        if (str[i + 1] == ')') {
          *err = INPUT_ERROR;
        }
      }
    }
    if (find_check != 1) {
      *err = INPUT_ERROR;
    }
  }
  if (find_check) {
    s21_stack_push(head, 0, -1, c);
  }
  return res;
}

int s21_math_lexeme_check(s21_stack* head, char* str, int* index, int* err) {
  int flag = 0;
  if (str[*index] == 'm') {
    flag = s21_mode_check(head, str, index, err);
  } else if (str[*index] == 'l') {
    if (str[*index + 1] == 'n') {
      flag = s21_lexeme_eq_check(head, str, index, S21_LN, 3, err, 4, 'L');
    } else if (str[*index + 1] == 'o') {
      flag = s21_lexeme_eq_check(head, str, index, S21_LOG, 4, err, 4, 'l');
    } else {
      *err = INPUT_ERROR;
      flag++;
    }
  } else if (str[*index] == 's' && str[*index + 1] != 'i') {
    flag = s21_lexeme_eq_check(head, str, index, S21_SQRT, 5, err, 4, 'q');
  }
  return flag;
}

int s21_triganom_lexeme_check(s21_stack* head, char* str, int* index,
                              int* err) {
  int flag = 0;
  if (str[*index] == 'a') {
    if (str[*index + 1] == 's') {
      flag = s21_lexeme_eq_check(head, str, index, S21_ASIN, 5, err, 4, 'S');
    } else if (str[*index + 1] == 'c') {
      flag = s21_lexeme_eq_check(head, str, index, S21_ACOS, 5, err, 4, 'C');
    } else if (str[*index + 1] == 't') {
      flag = s21_lexeme_eq_check(head, str, index, S21_ATAN, 5, err, 4, 'T');
    } else {
      *err = INPUT_ERROR;
      flag++;
    }
  } else if (str[*index] == 's' && str[*index + 1] != 'q') {
    flag = s21_lexeme_eq_check(head, str, index, S21_SIN, 4, err, 4, 's');
  } else if (str[*index] == 'c') {
    flag = s21_lexeme_eq_check(head, str, index, S21_COS, 4, err, 4, 'c');
  } else if (str[*index] == 't') {
    flag = s21_lexeme_eq_check(head, str, index, S21_TAN, 4, err, 4, 't');
  }
  return flag;
}

int s21_lexeme_eq_check(s21_stack* head, char* str, int* index,
                        const char* check, int length, int* err, int p,
                        char s) {
  int flag = 0;
  for (int i = 0; i < length && !flag; i++, (*index)++) {
    if (str[*index] == '\0' || str[*index] != check[i]) {
      *err = INPUT_ERROR;
      flag++;
      (*index) = 0;
    }
  }
  if (!flag) {
    flag++;
    s21_stack_push(head, 0, p, s);
    (*index) -= 2;
  }
  return flag;
}

int s21_isdigit(char c) {
  int res = 0;
  if (c >= 48 && c <= 57) {
    res = 1;
  }
  return res;
}

int s21_next_symb_check(char* str, int index) {
  int res = 0;
  if (str[index] == '(' || str[index] == 'a' || str[index] == 's' ||
      str[index] == 'c' || str[index] == 't' || str[index] == 'l' ||
      str[index] == 'x' || s21_isdigit(str[index])) {
    res = 1;
  }
  return res;
}

int s21_mode_check(s21_stack* head, char* str, int* index, int* err) {
  int flag = 1;
  if (*index > 0 && (str[*index - 1] == ')' || str[*index - 1] == 'x' ||
                     s21_isdigit(str[*index - 1]))) {
    for (int i = 0; i < 3 && *err == 0; i++, (*index)++) {
      if (str[*index] != S21_MOD[i]) {
        *err = INPUT_ERROR;
      }
    }
    if (*err == 0) {
      if (s21_next_symb_check(str, *index)) {
        s21_stack_push(head, 0, 2, '%');
        (*index)--;
      } else {
        *err = INPUT_ERROR;
      }
    }
  } else {
    *err = INPUT_ERROR;
  }
  return flag;
}
