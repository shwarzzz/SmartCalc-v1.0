#include <check.h>
#include <math.h>
#include <string.h>

#include "../Backend/s21_calc.h"
#include "../Backend/s21_convert_to_polish.h"
#include "../Backend/s21_parser.h"
#include "../Backend/s21_stack.h"

START_TEST(s21_polish_check_test_1) {
  char str[] = "cos(12)/sqrt(9)-atan(x)*(-sin(-x))+23*ln(5.23)^2";
  s21_stack* string = s21_parse_string(str);
  s21_stack* polish = s21_convert_to_polish(string);
  s21_stack* check = s21_stack_init_elem(0, -6, 'h');
  s21_stack_push(check, 12, 0, 'n');
  s21_stack_push(check, 0, 4, 'c');
  s21_stack_push(check, 9, 0, 'n');
  s21_stack_push(check, 0, 4, 'q');
  s21_stack_push(check, 0, 2, '/');
  s21_stack_push(check, 0, 0, 'x');
  s21_stack_push(check, 0, 4, 'T');
  s21_stack_push(check, 0, 0, 'x');
  s21_stack_push(check, 0, 1, 'M');
  s21_stack_push(check, 0, 4, 's');
  s21_stack_push(check, 0, 1, 'M');
  s21_stack_push(check, 0, 2, '*');
  s21_stack_push(check, 0, 1, '-');
  s21_stack_push(check, 23, 0, 'n');
  s21_stack_push(check, 5.23, 0, 'n');
  s21_stack_push(check, 0, 4, 'L');
  s21_stack_push(check, 2, 0, 'n');
  s21_stack_push(check, 0, 3, '^');
  s21_stack_push(check, 0, 2, '*');
  s21_stack_push(check, 0, 1, '+');
  s21_stack* check_reverse = s21_stack_reverse(check);
  double res = 0;
  s21_stack* calcs = s21_stack_copy(polish);
  s21_calc(calcs, &res, 3.15);
  for (int i = 0; i < 20; i++) {
    s21_stack* val_1 = s21_get_tail_value(polish);
    s21_stack* val_2 = s21_get_tail_value(check_reverse);
    ck_assert_double_eq(val_1->value, val_2->value);
    ck_assert_int_eq(val_1->priority, val_2->priority);
    ck_assert_int_eq(val_1->symb, val_2->symb);
    s21_stack_pop(polish);
    s21_stack_pop(check_reverse);
  }
  ck_assert_double_eq_tol(res, 63.2446699, 0.0000001);
  s21_destroy_stack(check_reverse);
  s21_destroy_stack(polish);
}
END_TEST

START_TEST(s21_polish_check_test_2) {
  char str[] = "-xmod2*6.35";
  s21_stack* string = s21_parse_string(str);
  s21_stack* polish = s21_convert_to_polish(string);
  s21_stack* check = s21_stack_init_elem(0, -6, 'h');
  s21_stack_push(check, 0, 0, 'x');
  s21_stack_push(check, 2, 0, 'n');
  s21_stack_push(check, 0, 2, '%');
  s21_stack_push(check, 6.35, 0, 'n');
  s21_stack_push(check, 0, 2, '*');
  s21_stack_push(check, 0, 1, 'M');
  s21_stack* check_reverse = s21_stack_reverse(check);
  double res = 0;
  s21_stack* calcs = s21_stack_copy(polish);
  s21_calc(calcs, &res, 103.9898);
  for (int i = 0; i < 6; i++) {
    s21_stack* val_1 = s21_get_tail_value(polish);
    s21_stack* val_2 = s21_get_tail_value(check_reverse);
    ck_assert_double_eq(val_1->value, val_2->value);
    ck_assert_int_eq(val_1->priority, val_2->priority);
    ck_assert_int_eq(val_1->symb, val_2->symb);
    s21_stack_pop(polish);
    s21_stack_pop(check_reverse);
  }
  ck_assert_double_eq_tol(res, -12.63523, 0.0000001);
  s21_destroy_stack(check_reverse);
  s21_destroy_stack(polish);
}
END_TEST

START_TEST(s21_polish_check_test_3) {
  char str[] = "x/0";
  s21_stack* string = s21_parse_string(str);
  s21_stack* polish = s21_convert_to_polish(string);
  double res = 0;
  int ret = s21_calc(polish, &res, 103.9898);
  ck_assert_int_eq(ret, DIV_BY_ZERO);
  ck_assert_double_eq_tol(res, 0, 0.0000001);
}
END_TEST

START_TEST(s21_polish_check_test_4) {
  char str[] = "log(0)";
  s21_stack* string = s21_parse_string(str);
  s21_stack* polish = s21_convert_to_polish(string);
  double res = 0;
  int ret = s21_calc(polish, &res, 103.9898);
  ck_assert_int_eq(ret, CALCULATION_ERROR);
  ck_assert_double_eq_tol(res, 0, 0.0000001);
}
END_TEST

START_TEST(s21_polish_check_test_5) {
  char str[] = "2+asin(1.01)*2.53";
  s21_stack* string = s21_parse_string(str);
  s21_stack* polish = s21_convert_to_polish(string);
  double res = 0;
  int ret = s21_calc(polish, &res, 103.9898);
  ck_assert_int_eq(ret, CALCULATION_ERROR);
  ck_assert_double_eq_tol(res, 0, 0.0000001);
}
END_TEST

START_TEST(s21_polish_check_test_6) {
  char str[] = "-acos(1.0001)";
  s21_stack* string = s21_parse_string(str);
  s21_stack* polish = s21_convert_to_polish(string);
  double res = 0;
  int ret = s21_calc(polish, &res, 103.9898);
  ck_assert_int_eq(ret, CALCULATION_ERROR);
  ck_assert_double_eq_tol(res, 0, 0.0000001);
}
END_TEST

START_TEST(s21_polish_check_test_7) {
  char str[] = "1.02355667653";
  s21_stack* string = s21_parse_string(str);
  s21_stack* polish = s21_convert_to_polish(string);
  double res = 0;
  s21_calc(polish, &res, 103.9898);
  ck_assert_double_eq_tol(res, 1.02355667653, 0.0000001);
}
END_TEST

START_TEST(s21_polish_check_test_8) {
  char str[] = "1.023.55667653";
  s21_stack* string = s21_parse_string(str);
  s21_stack* polish = s21_convert_to_polish(string);
  double res = 0;
  s21_calc(polish, &res, 103.9898);
  ck_assert_ptr_null(string);
  ck_assert_ptr_null(polish);
  s21_destroy_stack(polish);
}
END_TEST

START_TEST(s21_polish_check_test_9) {
  char str[] = "00102355667653";
  s21_stack* string = s21_parse_string(str);
  s21_stack* polish = s21_convert_to_polish(string);
  double res = 0;
  s21_calc(polish, &res, 103.9898);
  ck_assert_ptr_null(string);
  ck_assert_ptr_null(polish);
}
END_TEST

START_TEST(s21_polish_check_test_10) {
  char str[] = "sin(2)xx";
  s21_stack* string = s21_parse_string(str);
  s21_stack* polish = s21_convert_to_polish(string);
  double res = 0;
  s21_calc(polish, &res, 103.9898);
  ck_assert_ptr_null(string);
  ck_assert_ptr_null(polish);
}
END_TEST

START_TEST(s21_polish_check_test_11) {
  char str[] = "sik(2)";
  s21_stack* string = s21_parse_string(str);
  s21_stack* polish = s21_convert_to_polish(string);
  double res = 0;
  s21_calc(polish, &res, 103.9898);
  ck_assert_ptr_null(string);
  ck_assert_ptr_null(polish);
}
END_TEST

START_TEST(s21_polish_check_test_12) {
  char str[] = "mob(2)";
  s21_stack* string = s21_parse_string(str);
  s21_stack* polish = s21_convert_to_polish(string);
  double res = 0;
  s21_calc(polish, &res, 103.9898);
  ck_assert_ptr_null(string);
  ck_assert_ptr_null(polish);
}
END_TEST

START_TEST(s21_polish_check_test_13) {
  char str[] = "sin(";
  s21_stack* string = s21_parse_string(str);
  s21_stack* polish = s21_convert_to_polish(string);
  double res = 0;
  s21_calc(polish, &res, 103.9898);
  ck_assert_ptr_null(string);
  ck_assert_ptr_null(polish);
}
END_TEST

START_TEST(s21_polish_check_test_14) {
  char str[] = "sin()";
  s21_stack* string = s21_parse_string(str);
  s21_stack* polish = s21_convert_to_polish(string);
  double res = 0;
  s21_calc(polish, &res, 103.9898);
  ck_assert_ptr_null(string);
  ck_assert_ptr_null(polish);
}
END_TEST

START_TEST(s21_polish_check_test_15) {
  char str[] = "tan(asin(acos(0.98)))+log(2)+ln(0.5)";
  s21_stack* string = s21_parse_string(str);
  s21_stack* polish = s21_convert_to_polish(string);
  s21_stack* check = s21_stack_init_elem(0, -6, 'h');
  s21_stack_push(check, 0.98, 0, 'n');
  s21_stack_push(check, 0, 4, 'C');
  s21_stack_push(check, 0, 4, 'S');
  s21_stack_push(check, 0, 4, 't');
  s21_stack_push(check, 2, 0, 'n');
  s21_stack_push(check, 0, 4, 'l');
  s21_stack_push(check, 0, 1, '+');
  s21_stack_push(check, 0.5, 0, 'n');
  s21_stack_push(check, 0, 4, 'L');
  s21_stack_push(check, 0, 1, '+');
  s21_stack* check_reverse = s21_stack_reverse(check);
  double res = 0;
  s21_stack* calcs = s21_stack_copy(polish);
  s21_calc(calcs, &res, 0);
  for (int i = 0; i < 10; i++) {
    s21_stack* val_1 = s21_get_tail_value(polish);
    s21_stack* val_2 = s21_get_tail_value(check_reverse);
    ck_assert_double_eq(val_1->value, val_2->value);
    ck_assert_int_eq(val_1->priority, val_2->priority);
    ck_assert_int_eq(val_1->symb, val_2->symb);
    s21_stack_pop(polish);
    s21_stack_pop(check_reverse);
  }
  ck_assert_double_eq_tol(res, -0.1876370, 0.0000001);
  s21_destroy_stack(check_reverse);
  s21_destroy_stack(polish);
}
END_TEST

START_TEST(s21_polish_check_test_16) {
  char str[] = "+1modsqrt(-0.5)";
  s21_stack* string = s21_parse_string(str);
  s21_stack* polish = s21_convert_to_polish(string);
  double res = 0;
  int ret = s21_calc(polish, &res, 103.9898);
  ck_assert_int_eq(ret, CALCULATION_ERROR);
}
END_TEST

Suite* s21_polish_check_suite(void) {
  TCase* tc = tcase_create("s21_polish_check_core");
  Suite* s = suite_create("s21_polish_check_tests");

  tcase_add_test(tc, s21_polish_check_test_1);
  tcase_add_test(tc, s21_polish_check_test_2);
  tcase_add_test(tc, s21_polish_check_test_3);
  tcase_add_test(tc, s21_polish_check_test_4);
  tcase_add_test(tc, s21_polish_check_test_5);
  tcase_add_test(tc, s21_polish_check_test_6);
  tcase_add_test(tc, s21_polish_check_test_7);
  tcase_add_test(tc, s21_polish_check_test_8);
  tcase_add_test(tc, s21_polish_check_test_9);
  tcase_add_test(tc, s21_polish_check_test_10);
  tcase_add_test(tc, s21_polish_check_test_11);
  tcase_add_test(tc, s21_polish_check_test_12);
  tcase_add_test(tc, s21_polish_check_test_13);
  tcase_add_test(tc, s21_polish_check_test_14);
  tcase_add_test(tc, s21_polish_check_test_15);
  tcase_add_test(tc, s21_polish_check_test_16);

  suite_add_tcase(s, tc);

  return s;
}

int main() {
  int failed = 0;
  SRunner* sr;

  sr = srunner_create(s21_polish_check_suite());

  srunner_run_all(sr, CK_NORMAL);
  failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (failed == 0) ? 1 : 0;
}