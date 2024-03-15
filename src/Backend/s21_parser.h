#ifndef S21_PARSER_H

#define S21_PARSER_H
#define INPUT_ERROR 2

#define S21_MOD "mod"
#define S21_SQRT "sqrt("
#define S21_LN "ln("
#define S21_LOG "log("

#define S21_SIN "sin("
#define S21_COS "cos("
#define S21_TAN "tan("
#define S21_ASIN "asin("
#define S21_ACOS "acos("
#define S21_ATAN "atan("

#include <ctype.h>

#include "s21_stack.h"

s21_stack* s21_parse_string(char* str);
int s21_isdigit(char c);
int s21_convert_num_to_str(s21_stack* head, char* str, int* index);
int s21_algebraic_signs_check(s21_stack* head, char* str, int index, int* err);
int s21_bracket_search(s21_stack* head, char* str, int* err, int i, char c);
int s21_math_lexeme_check(s21_stack* head, char* str, int* index, int* err);
int s21_triganom_lexeme_check(s21_stack* head, char* str, int* index, int* err);
int s21_lexeme_eq_check(s21_stack* head, char* str, int* index,
                        const char* check, int length, int* err, int p, char s);
int s21_next_symb_check(char* str, int index);
int s21_mode_check(s21_stack* head, char* str, int* index, int* err);
double s21_convert_to_double(char* str);
#endif
