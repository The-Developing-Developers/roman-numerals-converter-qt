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
    std::cout << "Converted Number: " << converter->ConvertDecimalToRoman(ui->decimalNumberLineEdit->text().toULongLong()) << std::endl;
}

void MainWindow::ConvertRomanToDecimalSlot()
{
    std::cout << "Converted Number: " << converter->ConvertRomanToDecimal(ui->romanNumberLineEdit->text().toStdString()) << std::endl;
}
