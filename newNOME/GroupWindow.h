//GroupWindow.h File

#ifndef GROUPWINDOW_H
#define GROUPWINDOW_H

#include <QtGui>
#include "BankNew.h"
#include <QMainWindow>
#include <QHBoxLayout>
#include <QSlider>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

class GroupWindow: public QObject
{
  Q_OBJECT
  public:
    GroupWindow();
    GroupWindow(QWidget * hello);
    ~ GroupWindow(){};

  public:
  QWidget *window;
  QWidget * currWidget;
  QVBoxLayout* layout;
  QLabel* instanceLabel;
  QLineEdit* textboxInstanceName;
  QLabel* meshLabel;
  QLineEdit* textboxMeshName;
  QPushButton * consolidateButton;
};

#endif
