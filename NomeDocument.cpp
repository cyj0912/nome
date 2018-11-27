#include "NomeDocument.h"

#include "nomeglwidget.h"
#include "controlpanel.h"
#include "nomeparser.h"
#include "newNOME/Session.h"
#include "newNOME/SliderNew.h"
#include "newNOME/SliderSubdivisionNew.h"
#include "newNOME/SliderOffsetNew.h"

CNomeDocument::CNomeDocument()
{
}

CNomeDocument::CNomeDocument(const QString& fileName)
{
    if ((fileName.right(3).toLower() == "stl") || (fileName.right(3).toLower() == "nom") || (fileName.right(3).toLower() == "obj"))
    {
        CurrSession = NomeParser::makeWithNome(fileName.toStdString());
        if (!CurrSession)
        {
            std::cout << "ERR: Cannot parse file!" << std::endl;
            return;
        }

        Canvas = new SlideGLWidget(nullptr, CurrSession);
        Canvas->show();
        Canvas->update();
    }
    else
    {
        std::cout << "File type not supported!" << std::endl;
    }
}

CNomeDocument::~CNomeDocument()
{
}

void CNomeDocument::CreateSliders(QWidget* mainWindow)
{
    for (auto b : CurrSession->banks)
    {
        QWidget* window = new QWidget(mainWindow, Qt::Window);
        window->resize(400, 0);
        QVBoxLayout* layout = new QVBoxLayout(window);
        QLabel* label = new QLabel(b->name.c_str());
        layout->addWidget(label);
        for (auto s : b->sets) {
            layout->addLayout(new SliderNew(s, Canvas));
        }
        window->setLayout(layout);
        window->show();
    }
}

void CNomeDocument::CreateSubdivisionSliders(QWidget* mainWindow)
{
    QWidget *window = new QWidget(mainWindow, Qt::Window);
    window->resize(400, 0);
    QVBoxLayout* layout = new QVBoxLayout(window);
    QLabel* label = new QLabel("SUBDIVISION");
    layout->addWidget(label);
    for (SubdivisionNew* sd : CurrSession->subdivisions) {
        layout->addLayout(new SliderSubdivisionNew(sd, Canvas));
        window->setLayout(layout);
    }
    window->show();
}

void CNomeDocument::CreateOffsetSliders(QWidget* mainWindow)
{
    QWidget *window = new QWidget(mainWindow, Qt::Window);
    window->resize(400, 0);
    QVBoxLayout* layout = new QVBoxLayout(window);
    QLabel* label = new QLabel("OFFSET");
    layout->addWidget(label);
    for (OffsetNew* sd : CurrSession->offsets) {
        layout->addLayout(new SliderOffsetNew(sd, Canvas));
        window->setLayout(layout);
    }
    window->show();
}

void CNomeDocument::CreateControlPanel(CMainWindow* mainWindow)
{
    Controls = new ControlPanel(mainWindow, Canvas, CurrSession);

    //Be sure to do this in the main window:
    //ui->controlPanelDock->setWidget(Controls);
}

bool CNomeDocument::SaveFile(const QString& fileName)
{
    if (fileName.right(3).toLower() == "stl")
    {
        CurrSession->SaveSessionStl(fileName.toStdString());
		return true;
    }
    if (fileName.right(3).toLower() == "nom")
    {
        CurrSession->SaveSessionNom(fileName.toStdString());
		return true;
    }
	return false;
}
