#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <calculator.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public:
    enum class Operation{
        NO_OPERATION,
        ADDITION,
        SUBTRACTION,
        MULTIPLICATION,
        DIVISION,
        POWER
    };

private slots:
    void on_btn_0_clicked();
    void on_btn_1_clicked();
    void on_btn_2_clicked();
    void on_btn_3_clicked();
    void on_btn_4_clicked();
    void on_btn_5_clicked();
    void on_btn_6_clicked();
    void on_btn_7_clicked();
    void on_btn_8_clicked();
    void on_btn_9_clicked();
    void on_btn_dot_clicked();
    void on_dtn_del_clicked();
    void on_btm_plus_minus_clicked();
    void on_btn_pow_clicked();
    void on_btn_div_clicked();
    void on_btn_mul_clicked();
    void on_btn_min_clicked();
    void on_btn_plus_clicked();
    void on_btn_equal_clicked();
    void on_btn_clear_clicked();
    void on_btn_ms_clicked();
    void on_btn_mr_clicked();
    void on_btn_mc_clicked();

private:
    void SetText(const QString& text);
    void AddText(const QString& suffix);
    QString RemoveTrailingZeroes(const QString &text);
    QString NormalizeNumber(const QString &text);
    void SetOperation(Operation op);
    QString OpToString(Operation op);

private:
    Ui::MainWindow *ui;
    Calculator calculator_;
    QString input_number_;
    double active_number_;
    Operation current_operation_ = Operation::NO_OPERATION;
    QString memory_;
};
#endif // MAINWINDOW_H
