#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <QLabel>
#include <QDialogButtonBox>
#include "romannumeralsconverter.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
   MainWindow(QWidget *parent = nullptr);
  ~MainWindow(void);

private:
  Ui::MainWindow*         ui;
  QDialog*                m_errorDialog;
  QLabel*                 m_errorMessageLabel;
  QDialogButtonBox*       m_errorCloseButtonBox;
  RomanNumeralsConverter* m_converter;

public slots:
  void convertDecimalToRomanSlot(void);
  void convertRomanToDecimalSlot(void);
  void errorSlot(void);

signals:
  void conversionError(void);
};
#endif // MAINWINDOW_H
