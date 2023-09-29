#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
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
  QDialog*                m_dialog;
  QDialogButtonBox*       m_dialogButtonBox;
  RomanNumeralsConverter* m_converter;

public slots:
  void ConvertDecimalToRomanSlot(void);
  void ConvertRomanToDecimalSlot(void);
  void ErrorSlot(void);
};
#endif // MAINWINDOW_H
