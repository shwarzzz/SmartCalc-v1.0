#include "bankcalc.h"

#include <string>

#include "ui_bankcalc.h"

bankcalc::bankcalc(QWidget *parent) : QWidget(parent), ui(new Ui::bankcalc) {
  ui->setupUi(this);
}

bankcalc::~bankcalc() { delete ui; }

int bankcalc::check_values() {
  int ret = 1;
  if (ui->doubleSpinBox_percent->value() == 0) {
    ui->plainTextEdit_result->setPlainText(
        "Ошибка: Введите корректную процентную ставку!");
  } else if (ui->spinBox_month->value() == 0) {
    ui->plainTextEdit_result->setPlainText(
        "Ошибка: Введите корректный срок кредитования!");
  } else if (ui->doubleSpinBox_sum->value() == 0) {
    ui->plainTextEdit_result->setPlainText(
        "Ошибка: Введите корректную сумму кредита!");
  } else {
    ret = 0;
  }
  return ret;
}

void bankcalc::annuit_pay() {
  double sum = ui->doubleSpinBox_sum->value();
  double percent = ui->doubleSpinBox_percent->value();
  double month_percent = percent / 100.0 / 12.0;
  int month_count = ui->spinBox_month->value();
  ui->plainTextEdit_result->setPlainText("");
  double month_payment =
      sum * (month_percent +
             month_percent / (pow(1 + month_percent, month_count) - 1));
  month_payment = round(month_payment * 100) / 100;
  for (int i = 1; i <= month_count; i++) {
    double percent_rest = round(sum * month_percent * 100) / 100;
    double debt = round((month_payment - percent_rest) * 100) / 100;
    double sum_rest = sum - debt;
    char str[5000] = "";
    sprintf(str,
            "\nМесяц: %d\nОстаток долга: %.2lf руб.\nПлатеж: %.2lf "
            "руб.\nПроцентная часть: %.2lf руб.\nДолговая часть: %.2lf "
            "руб.\nОстаток долга на конец периода: %.2lf руб.\n",
            i, sum, month_payment, percent_rest, debt, sum_rest);
    ui->plainTextEdit_result->setPlainText(
        ui->plainTextEdit_result->toPlainText() + str);
    sum = sum_rest;
  }
  double total_sum = floor(month_payment * month_count * 100) / 100;
  char total_str[5000] = "";
  sprintf(total_str,
          "\nИтог:\nЕжемесячный платеж: %.2lf руб.\nОбщая сумма выплат: %.2lf "
          "руб.\nНачисленные проценты: %.2lf руб.",
          month_payment, total_sum, total_sum - ui->doubleSpinBox_sum->value());
  ui->plainTextEdit_result->setPlainText(
      ui->plainTextEdit_result->toPlainText() + total_str);
}

void bankcalc::different_pay() {
  double sum = ui->doubleSpinBox_sum->value();
  double percent = ui->doubleSpinBox_percent->value();
  double month_percent = (percent / 100.0) / 12.0;
  int month_count = ui->spinBox_month->value();
  ui->plainTextEdit_result->setPlainText("");
  double month_payment = 0;
  double max_payment = 0;
  double min_payment = 0;
  double total_sum = 0;
  double month_pay_debt = sum / month_count;
  for (int i = 1; i <= month_count; i++) {
    double percent_rest = round(sum * month_percent * 100) / 100;
    month_payment = month_pay_debt + percent_rest;
    month_payment = round(month_payment * 100) / 100;
    if (i == 1) {
      max_payment = month_payment;
    } else if (i == month_count) {
      min_payment = month_payment;
    }
    double sum_rest = sum - month_pay_debt;
    total_sum += month_payment;
    char str[5000] = "";
    sprintf(str,
            "\nМесяц: %d\nОстаток долга: %.2lf руб.\nПлатеж: %.2lf "
            "руб.\nПроцентная часть: %.2lf руб.\nДолговая часть: %.2lf "
            "руб.\nОстаток долга на конец периода: %.2lf руб.\n",
            i, sum, month_payment, percent_rest, month_pay_debt, sum_rest);
    ui->plainTextEdit_result->setPlainText(
        ui->plainTextEdit_result->toPlainText() + str);
    sum = sum_rest;
  }
  char total_str[5000] = "";
  sprintf(total_str,
          "\nИтог:\nЕжемесячный платеж: %.2lf руб., .., %.2lf руб.\nОбщая "
          "сумма выплат: %.2lf руб.\nНачисленные проценты: %.2lf руб.",
          max_payment, min_payment, total_sum,
          total_sum - ui->doubleSpinBox_sum->value());
  ui->plainTextEdit_result->setPlainText(
      ui->plainTextEdit_result->toPlainText() + total_str);
}

void bankcalc::on_pushButton_calc_clicked() {
  if (!check_values()) {
    if (ui->radioButton_an->isChecked()) {
      annuit_pay();
    } else if (ui->radioButton_dif->isChecked()) {
      different_pay();
    } else {
      ui->plainTextEdit_result->setPlainText("Ошибка: Выберите тип платежа!");
    }
  }
}
