//ConsolidateWindow.h File

#ifndef CONSOLIDATEWINDOW_H
#define CONSOLIDATEWINDOW_H

#include <QtGui>
#include <QMainWindow>
#include <QHBoxLayout>
#include <QSlider>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

class ConsolidateWindow: public QObject
{
  Q_OBJECT
  public:
    ConsolidateWindow();
    ConsolidateWindow(QWidget * hello);
    ~ ConsolidateWindow(){};

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
