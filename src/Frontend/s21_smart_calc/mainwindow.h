#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>

#include "bankcalc.h"
extern "C" {
#include "../../Backend/s21_calc.h"
#include "../../Backend/s21_convert_to_polish.h"
#include "../../Backend/s21_parser.h"
#include "../../Backend/s21_stack.h"
}

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private:
  Ui::MainWindow *ui;
  bankcalc *bankCalcForm;

 private slots:
  void symb_to_lineEdit();
  void func_to_lineEdit();

  void on_pushButton_eq_clicked();
  void on_pushButton_clean_clicked();
  void on_pushButton_x_clicked();
  void on_pushButton_div_clicked();
  void on_pushButton_mul_clicked();
  void on_pushButton_mod_clicked();
  void on_pushButton_plot_clicked();
  void on_pushButton_openCreditCalc_clicked();
};

#endif  // MAINWINDOW_H
