#ifndef BANKCALC_H
#define BANKCALC_H

#include <QWidget>

namespace Ui {
class bankcalc;
}

class bankcalc : public QWidget {
  Q_OBJECT

 public:
  explicit bankcalc(QWidget *parent = nullptr);
  ~bankcalc();

 private slots:
  void on_pushButton_calc_clicked();

 private:
  void annuit_pay();
  void different_pay();
  int check_values();
  Ui::bankcalc *ui;
};

#endif  // BANKCALC_H
