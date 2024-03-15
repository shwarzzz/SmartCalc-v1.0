#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  bankCalcForm = new bankcalc();
  // numbers
  connect(ui->pushButton_n_0, SIGNAL(clicked()), this,
          SLOT(symb_to_lineEdit()));
  connect(ui->pushButton_n_1, SIGNAL(clicked()), this,
          SLOT(symb_to_lineEdit()));
  connect(ui->pushButton_n_2, SIGNAL(clicked()), this,
          SLOT(symb_to_lineEdit()));
  connect(ui->pushButton_n_3, SIGNAL(clicked()), this,
          SLOT(symb_to_lineEdit()));
  connect(ui->pushButton_n_4, SIGNAL(clicked()), this,
          SLOT(symb_to_lineEdit()));
  connect(ui->pushButton_n_5, SIGNAL(clicked()), this,
          SLOT(symb_to_lineEdit()));
  connect(ui->pushButton_n_6, SIGNAL(clicked()), this,
          SLOT(symb_to_lineEdit()));
  connect(ui->pushButton_n_7, SIGNAL(clicked()), this,
          SLOT(symb_to_lineEdit()));
  connect(ui->pushButton_n_8, SIGNAL(clicked()), this,
          SLOT(symb_to_lineEdit()));
  connect(ui->pushButton_n_9, SIGNAL(clicked()), this,
          SLOT(symb_to_lineEdit()));

  // special symbols
  connect(ui->pushButton_dot, SIGNAL(clicked()), this,
          SLOT(symb_to_lineEdit()));
  connect(ui->pushButton_lbracket, SIGNAL(clicked()), this,
          SLOT(symb_to_lineEdit()));
  connect(ui->pushButton_rbracket, SIGNAL(clicked()), this,
          SLOT(symb_to_lineEdit()));

  // simple operations
  connect(ui->pushButton_pow, SIGNAL(clicked()), this,
          SLOT(symb_to_lineEdit()));
  connect(ui->pushButton_minus, SIGNAL(clicked()), this,
          SLOT(symb_to_lineEdit()));
  connect(ui->pushButton_plus, SIGNAL(clicked()), this,
          SLOT(symb_to_lineEdit()));

  // functions
  connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(func_to_lineEdit()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this,
          SLOT(func_to_lineEdit()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this,
          SLOT(func_to_lineEdit()));
  connect(ui->pushButton_sin, SIGNAL(clicked()), this,
          SLOT(func_to_lineEdit()));
  connect(ui->pushButton_cos, SIGNAL(clicked()), this,
          SLOT(func_to_lineEdit()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this,
          SLOT(func_to_lineEdit()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this,
          SLOT(func_to_lineEdit()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this,
          SLOT(func_to_lineEdit()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this,
          SLOT(func_to_lineEdit()));
}

MainWindow::~MainWindow() {
  delete ui;
  delete bankCalcForm;
}

void MainWindow::symb_to_lineEdit() {
  QPushButton* current_button = (QPushButton*)sender();
  ui->lineEdit->setText(ui->lineEdit->text() + current_button->text());
}

void MainWindow::func_to_lineEdit() {
  QPushButton* current = (QPushButton*)sender();
  ui->lineEdit->setText(ui->lineEdit->text() + current->text() + "(");
}

void MainWindow::on_pushButton_eq_clicked() {
  QString str = ui->lineEdit->text();
  char input[260];
  strcpy(input, str.toLatin1().constData());
  s21_stack* stack;
  stack = s21_parse_string(input);
  if (stack != NULL) {
    s21_stack* polish = s21_convert_to_polish(stack);
    double result = 0;
    double x = ui->doubleSpinBox_xvalue->value();
    int ret = s21_calc(polish, &result, x);
    if (ret == 3) {
      ui->lineEdit->setText("Error: Div by zero!");
    } else if (ret == 2) {
      ui->lineEdit->setText("Error: Calculation error!");
    } else {
      QString res = res.number(result, 'f', 7);
      ui->lineEdit->setText(res);
    }
  } else {
    ui->lineEdit->setText("Error: Wrong Input Data!");
  }
}

void MainWindow::on_pushButton_clean_clicked() { ui->lineEdit->setText(""); }

void MainWindow::on_pushButton_x_clicked() {
  ui->lineEdit->setText(ui->lineEdit->text() + "x");
}

void MainWindow::on_pushButton_div_clicked() {
  ui->lineEdit->setText(ui->lineEdit->text() + "/");
}

void MainWindow::on_pushButton_mul_clicked() {
  ui->lineEdit->setText(ui->lineEdit->text() + "*");
}

void MainWindow::on_pushButton_mod_clicked() {
  ui->lineEdit->setText(ui->lineEdit->text() + "mod");
}

void MainWindow::on_pushButton_plot_clicked() {
  QVector<double> x, y;
  double xBegin = ui->doubleSpinBox_xbegin->value();
  double xEnd = ui->doubleSpinBox_xend->value();
  double yBegin = ui->doubleSpinBox_ybegin->value();
  double yEnd = ui->doubleSpinBox_yend->value();
  ui->s21_graph->clearGraphs();
  ui->s21_graph->replot();
  if (xBegin >= xEnd || yBegin >= yEnd) {
    ui->s21_graph->clearGraphs();
    ui->s21_graph->replot();
    ui->labelPlotStatus->setText("Plot Status: Incorrect x or y value!");
  } else {
    double step = fabs((xEnd - xBegin) / 100.0);
    QString str = ui->lineEdit->text();
    char input[260];
    strcpy(input, str.toLatin1().constData());
    s21_stack* stack;
    stack = s21_parse_string(input);
    if (stack != NULL) {
      s21_stack* polish = s21_convert_to_polish(stack);
      double value = ui->doubleSpinBox_xvalue->value();
      s21_stack* polish_copy = s21_stack_copy(polish);
      value = xBegin;
      int ret = 0;
      for (int i = 0; i < 101 && ret != 2 && ret != 3; i++, value += step) {
        double tmp = 0;
        ret = s21_calc(polish, &tmp, value);
        polish = s21_stack_copy(polish_copy);
        y.push_back(tmp);
        x.push_back(value);
      }
      s21_destroy_stack(polish);
      s21_destroy_stack(polish_copy);
      if (ret == 2) {
        ui->labelPlotStatus->setText("Plot Status: Calculation error!");
      } else if (ret == 3) {
        ui->labelPlotStatus->setText("Plot Status: Div by zero!");
      } else {
        ui->s21_graph->clearGraphs();
        ui->s21_graph->xAxis->setRange(xBegin, xEnd);
        ui->s21_graph->yAxis->setRange(yBegin, yEnd);
        ui->s21_graph->addGraph();
        ui->s21_graph->graph(0)->addData(x, y);
        ui->s21_graph->replot();
        ui->labelPlotStatus->setText("Plot Status: Success!");
      }
    } else {
      ui->labelPlotStatus->setText("Plot Status: Wrong Input Data!");
    }
  }
}

void MainWindow::on_pushButton_openCreditCalc_clicked() {
  bankCalcForm->show();
}
