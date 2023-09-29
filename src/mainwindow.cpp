#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , converter(new RomanNumeralsConverter)
{
    ui->setupUi(this);
    connect(ui->convertDecToRomButton, &QPushButton::clicked, this, &MainWindow::ConvertDecimalToRomanSlot);
    connect(ui->convertRomToDecButton, &QPushButton::clicked, this, &MainWindow::ConvertRomanToDecimalSlot);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ConvertDecimalToRomanSlot()
{
    auto result = converter->ConvertDecimalToRoman(ui->decimalNumberLineEdit->text().toULongLong());
    ui->decToRomResultLabel->setText(result);
}

void MainWindow::ConvertRomanToDecimalSlot()
{
    auto res = converter->ConvertRomanToDecimal(ui->romanNumberLineEdit->text());
    QString result = QString::number(res);
    ui->romToDecResultLabel->setText(result);
}
