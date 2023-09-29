#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow       (parent)
  , ui                (new Ui::MainWindow)
  , m_converter       (new RomanNumeralsConverter)
{
  ui->setupUi(this);

  m_dialog          = new QDialog         (ui->centralwidget);
  m_dialogButtonBox = new QDialogButtonBox(m_dialog);

  m_dialog->setWindowTitle("Conversion error");

  m_dialogButtonBox->setGeometry(QRect(20, 20, 160, 30));
  m_dialogButtonBox->setStandardButtons(QDialogButtonBox::Cancel | QDialogButtonBox::Ok);

  connect(ui->convertDecToRomButton, &QPushButton::clicked,     this, &MainWindow::ConvertDecimalToRomanSlot);
  connect(ui->convertRomToDecButton, &QPushButton::clicked,     this, &MainWindow::ConvertRomanToDecimalSlot);
  connect(ui->errorButton,           &QPushButton::clicked,     this, &MainWindow::ErrorSlot);
  connect(ui->decimalNumberLineEdit, &QLineEdit::returnPressed, this, &MainWindow::ConvertDecimalToRomanSlot);
  connect(ui->romanNumberLineEdit,   &QLineEdit::returnPressed, this, &MainWindow::ConvertRomanToDecimalSlot);
}

MainWindow::~MainWindow(void)
{
  delete ui;
  delete m_converter;
}

/**
 * @brief Calls conversion from roman numeral to decimal, and changes case to all caps in QLineEdit
 **/
void MainWindow::ConvertRomanToDecimalSlot(void)
{
  QString romanNumeralTypedByUser       (ui->romanNumberLineEdit->text());
  size_t  convertedDecimalNumber        (m_converter->ConvertRomanToDecimal(romanNumeralTypedByUser));
  QString convertedDecimalNumberToString(QString::number(convertedDecimalNumber));

  ui->romToDecResultLabel->setText(convertedDecimalNumberToString);
  ui->romanNumberLineEdit->setText(romanNumeralTypedByUser.toUpper());
}

/**
 * @brief Calls conversion from decimal to roman numeral
 **/
void MainWindow::ConvertDecimalToRomanSlot(void)
{
  size_t  decimalNumberTypedByUser(ui->decimalNumberLineEdit->text().toULongLong());
  QString convertedRomanNumeral   (m_converter->ConvertDecimalToRoman(decimalNumberTypedByUser));

  ui->decToRomResultLabel->setText(convertedRomanNumeral);
}

void MainWindow::ErrorSlot(void)
{
  m_dialog->open();
}
