#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow       (parent)
  , ui                (new Ui::MainWindow)
  , m_converter       (new RomanNumeralsConverter)
{
  ui->setupUi(this);

  m_errorDialog         = new QDialog         (ui->centralwidget);
  m_errorMessageLabel   = new QLabel          ("Please, check your input.", m_errorDialog);
  m_errorCloseButtonBox = new QDialogButtonBox(m_errorDialog);

  m_errorDialog->setWindowTitle("Conversion error");

  m_errorCloseButtonBox->setGeometry(QRect(20, 20, 160, 30));
  m_errorCloseButtonBox->setStandardButtons(QDialogButtonBox::Close);

  connect(ui->convertDecToRomButton, &QPushButton::clicked,        this,          &MainWindow::convertDecimalToRomanSlot);
  connect(ui->convertRomToDecButton, &QPushButton::clicked,        this,          &MainWindow::convertRomanToDecimalSlot);
  connect(ui->decimalNumberLineEdit, &QLineEdit::returnPressed,    this,          &MainWindow::convertDecimalToRomanSlot);
  connect(ui->romanNumberLineEdit,   &QLineEdit::returnPressed,    this,          &MainWindow::convertRomanToDecimalSlot);
  connect(this,                      &MainWindow::conversionError, this,          &MainWindow::errorSlot);
  connect(m_errorCloseButtonBox,     &QDialogButtonBox::rejected,  m_errorDialog, &QDialog::reject);
}

MainWindow::~MainWindow(void)
{
  delete ui;
  delete m_converter;
}

/**
 * @brief Calls conversion from roman numeral to decimal, and changes case to all caps in QLineEdit
 **/
void MainWindow::convertRomanToDecimalSlot(void)
{
  QString romanNumeralTypedByUser(ui->romanNumberLineEdit->text());
  size_t  convertedDecimalNumber (m_converter->ConvertRomanToDecimal(romanNumeralTypedByUser));

  if ( convertedDecimalNumber )
  {
    QString convertedDecimalNumberToString(QString::number(convertedDecimalNumber));

    ui->romToDecResultLabel->setText(convertedDecimalNumberToString);
    ui->romanNumberLineEdit->setText(romanNumeralTypedByUser.toUpper());
  }
  else
  {
    emit conversionError();
  }
}

/**
 * @brief Calls conversion from decimal to roman numeral
 **/
void MainWindow::convertDecimalToRomanSlot(void)
{
  size_t  decimalNumberTypedByUser(ui->decimalNumberLineEdit->text().toULongLong());
  QString convertedRomanNumeral   (m_converter->ConvertDecimalToRoman(decimalNumberTypedByUser));

  if ( !convertedRomanNumeral.isEmpty() )
  {
    ui->decToRomResultLabel->setText(convertedRomanNumeral);
  }
  else
  {
    emit conversionError();
  }
}

void MainWindow::errorSlot(void)
{
  m_errorDialog->open(); // Meglio rispetto a exec perché non apre un altro event loop
}