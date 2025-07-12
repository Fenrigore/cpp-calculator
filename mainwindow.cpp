#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    SetText("0");
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::SetText(const QString& text) {
    QString text_to_normalize = RemoveTrailingZeroes(text);
    text_to_normalize = NormalizeNumber(text_to_normalize);
    input_number_ = text_to_normalize;
    ui->l_result->setText(input_number_);
    active_number_ = input_number_.toDouble();
}

void MainWindow::AddText(const QString& suffix) {
    //допишет к input_number_ нужный текст и вызовет SetText.
    QString text_to_add = input_number_ + suffix;
    SetText(text_to_add);
}

QString MainWindow::RemoveTrailingZeroes(const QString& text) {
    for (qsizetype i = 0; i < text.size(); ++i) {
        if (text[i] != '0') {
            return text.mid(i);
        }
    }
    return "";
}

QString MainWindow::NormalizeNumber(const QString& text) {
    if (text.isEmpty()) {
        return "0";
    }
    if (text.startsWith('.')) {
        // Рекурсивный вызов.
        return NormalizeNumber("0" + text);
    }
    if (text.startsWith('-')) {
        // Рекурсивный вызов.
        return "-" + NormalizeNumber(text.mid(1));
    }
    if (text.startsWith('0') && !text.startsWith("0.")) {
        return NormalizeNumber(RemoveTrailingZeroes(text));
    }
    return text;
}

void MainWindow::SetOperation(Operation op) {
    if (current_operation_ == Operation::NO_OPERATION) {
        calculator_.Set(active_number_);
        input_number_ = "";
    }
    current_operation_ = op;
    QString op_to_string = OpToString(op);
    ui->l_formula->setText(QString::number(calculator_.GetNumber()) + " " + op_to_string);
}

QString MainWindow::OpToString(Operation op) {
    switch (op) {
    case Operation::NO_OPERATION: return "";
    case Operation::ADDITION: return "+";
    case Operation::DIVISION: return "÷";
    case Operation::MULTIPLICATION: return "×";
    case Operation::SUBTRACTION: return "−";
    case Operation::POWER: return "^";
    }
}

void MainWindow::on_btn_0_clicked() {
    AddText(ui->btn_0->text());
}

void MainWindow::on_btn_1_clicked() {
    AddText(ui->btn_1->text());
}

void MainWindow::on_btn_2_clicked() {
    AddText(ui->btn_2->text());
}

void MainWindow::on_btn_3_clicked() {
    AddText(ui->btn_3->text());
}

void MainWindow::on_btn_4_clicked() {
    AddText(ui->btn_4->text());
}

void MainWindow::on_btn_5_clicked() {
    AddText(ui->btn_5->text());
}

void MainWindow::on_btn_6_clicked() {
    AddText(ui->btn_6->text());
}

void MainWindow::on_btn_7_clicked() {
    AddText(ui->btn_7->text());
}

void MainWindow::on_btn_8_clicked() {
    AddText(ui->btn_8->text());
}

void MainWindow::on_btn_9_clicked() {
    AddText(ui->btn_9->text());
}

void MainWindow::on_btn_dot_clicked() {
    std::string need_to_find_dot = input_number_.toStdString();
    if (need_to_find_dot.find_first_of('.') == std::string::npos) {
        AddText(".");
    }
}

void MainWindow::on_dtn_del_clicked() {
    if (input_number_.size() > 0) {
        input_number_.chop(1);
        //чтоб при удалении отрицательного числа не оставался минус
        if (input_number_ == "-") {
            input_number_ = "";
        }
        SetText(input_number_);
    }
}

void MainWindow::on_btm_plus_minus_clicked() {
    if (input_number_.startsWith('-')) {
        input_number_ = input_number_.mid(1);
    }
    else {
        input_number_ = "-" + input_number_;
    }
    SetText(input_number_);
}

void MainWindow::on_btn_pow_clicked() {
    SetOperation(Operation::POWER);
}

void MainWindow::on_btn_div_clicked() {
    SetOperation(Operation::DIVISION);
}

void MainWindow::on_btn_mul_clicked() {
    SetOperation(Operation::MULTIPLICATION);
}

void MainWindow::on_btn_min_clicked() {
    SetOperation(Operation::SUBTRACTION);
}

void MainWindow::on_btn_plus_clicked() {
    SetOperation(Operation::ADDITION);
}

void MainWindow::on_btn_equal_clicked() {
    QString calc_number = QString::number(calculator_.GetNumber());

    switch (current_operation_) {
    case Operation::ADDITION:
        calculator_.Add(active_number_);
        break;
    case Operation::SUBTRACTION:
        calculator_.Sub(active_number_);
        break;
    case Operation::MULTIPLICATION:
        calculator_.Mul(active_number_);
        break;
    case Operation::DIVISION:
        calculator_.Div(active_number_);
        break;
    case Operation::POWER:
        calculator_.Pow(active_number_);
        break;
    case Operation::NO_OPERATION:
        return;
    default:
        break;
    }

    ui->l_formula->setText(calc_number + " "
        + OpToString(current_operation_) + " "
        + QString::number(active_number_) + " =");

    active_number_ = calculator_.GetNumber();
    ui->l_result->setText(QString::number(active_number_));
    input_number_ = "";
    current_operation_ = Operation::NO_OPERATION;
}

void MainWindow::on_btn_clear_clicked() {
    ui->l_formula->setText("");
    SetText("");
    calculator_.Set(0);
    current_operation_ = Operation::NO_OPERATION;
}

void MainWindow::on_btn_ms_clicked() {
    memory_ = QString::number(active_number_);
    ui->l_memory->setText("M");
}

void MainWindow::on_btn_mr_clicked() {
    if (memory_.size() > 0) {
        SetText(memory_);
    }
}

void MainWindow::on_btn_mc_clicked() {
    memory_ = "";
    ui->l_memory->setText("");
}

