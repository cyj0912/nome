//GroupWindow.cpp File

#include "GroupWindow.h"
#include <QtGui>
#include <QMainWindow>
#include <QHBoxLayout>
#include <QSlider>
#include <QLabel>
#include "Data.h"

GroupWindow::GroupWindow(){

}

GroupWindow::GroupWindow(QWidget * currWidget)
{
    this -> currWidget = currWidget;

    window = new QWidget;
    window->resize(400,0);
    layout = new QVBoxLayout(window);
    instanceLabel = new QLabel("Enter the name of instance created:");
    textboxInstanceName = new QLineEdit;
    textboxInstanceName->setPlaceholderText("Instance Name");

    meshLabel = new QLabel("Enter the name of object created:");
    textboxMeshName = new QLineEdit;
    textboxMeshName->setPlaceholderText("Object Name");
    consolidateButton = new QPushButton("Group Faces");

    layout->addWidget(instanceLabel);
    layout->addWidget(textboxInstanceName);
    layout->addWidget(meshLabel);
    layout->addWidget(textboxMeshName);
    layout->addWidget(consolidateButton);

    window->setLayout(layout);
    window->show();
    connect(textboxInstanceName, SIGNAL(textChanged(QString)), currWidget, SLOT(readConsolidateInstanceName(QString)));
    connect(textboxMeshName, SIGNAL(textChanged(QString)), currWidget, SLOT(readConsolidateMeshName(QString)));
    connect(consolidateButton, SIGNAL(clicked(bool)), currWidget, SLOT(groupFacesMsg(bool)));
};

