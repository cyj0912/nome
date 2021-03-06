//ConsolidateWindow.h File

#ifndef CONSOLIDATEWINDOW_H
#define CONSOLIDATEWINDOW_H

#include <QtGui>
#include <QMainWindow>
#include <QHBoxLayout>
#include <QSlider>
#include <QLabel>
#include <QGLWidget>
#include <QLineEdit>
#include <QPushButton>

class ConsolidateWindow: public QObject
{
  Q_OBJECT
  public:
    ConsolidateWindow();
    ConsolidateWindow(QGLWidget * hello);
    ~ ConsolidateWindow(){};

  public:
  QWidget *window;
  QGLWidget * currWidget;
  QVBoxLayout* layout;
  QLabel* instanceLabel;
  QLineEdit* textboxInstanceName;
  QLabel* meshLabel;
  QLineEdit* textboxMeshName;
  QPushButton * consolidateButton;
};

#endif
