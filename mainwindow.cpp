#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "nomeglwidget.h"
#include "controlpanel.h"
#include "nomeparser.h"
#include "newNOME/Session.h"
#include "newNOME/SliderNew.h"
#include "newNOME/SliderSubdivisionNew.h"
#include "newNOME/SliderOffsetNew.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QSettings>

#include <vector>

CMainWindow::CMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CMainWindow)
{
    ui->setupUi(this);

	connect(ui->actionExit, &QAction::triggered, this, &QMainWindow::close);
	connect(ui->actionAbout, &QAction::triggered, [this]() {
		QMessageBox::about(this, "About NOME", "This is the Non-Orientable Manifold Editor project developed at Cal.\n"
			"Authors:\n"
			"Yu (Andy) Wang (c) 2016\n"
			"Gauthier Diepadelle (c) 2017-2018\n"
			"Toby Chen (c) 2018\n"
			"Henry Sun (c) 2018\n"
			"Marc Wudunn (c) 2018\n"
			"\n"
			"Version: 1.0\n");
	});
	connect(ui->actionAbout_Qt, &QAction::triggered, [this]() {
		QMessageBox::aboutQt(this);
	});
}

CMainWindow::~CMainWindow()
{
    delete ui;
}

void CMainWindow::LoadFile(QString fileName)
{
	if ((fileName.right(3).toLower() == "stl") || (fileName.right(3).toLower() == "nom") || (fileName.right(3).toLower() == "obj"))
	{
		DocSession = NomeParser::makeWithNome(fileName.toStdString());
		if (!DocSession)
		{
			std::cout << "ERR: Cannot parse file!" << std::endl;
			return;
		}

		Canvas = new SlideGLWidget(ui->centralwidget, DocSession);
		ui->centralHLayout->addWidget(Canvas);

		CreateSliders(Canvas, DocSession);
		CreateSubdivisionSliders(Canvas, DocSession);
		CreateOffsetSliders(Canvas, DocSession);

		Canvas->move(0, 50);
		Canvas->show();
		CreateControlPanel(Canvas, DocSession);
		Canvas->update();

	}
	else
	{
		std::cout << "File type not supported!" << std::endl;
	}
}

void CMainWindow::CreateSliders(SlideGLWidget* canvas, Session* currSession)
{
	for (auto b : currSession->banks)
	{
		QWidget* window = new QWidget;
		window->resize(400, 0);
		QVBoxLayout* layout = new QVBoxLayout(window);
		QLabel* label = new QLabel(b->name.c_str());
		layout->addWidget(label);
		for (auto s : b->sets) {
			layout->addLayout(new SliderNew(s, canvas));
		}
		window->setLayout(layout);
		window->show();

		SliderWindows.push_back(window);
	}
}

void CMainWindow::CreateSubdivisionSliders(SlideGLWidget* canvas, Session* currSession)
{
	QWidget *window = new QWidget;
	window->resize(400, 0);
	QVBoxLayout* layout = new QVBoxLayout(window);
	QLabel* label = new QLabel("SUBDIVISION");
	layout->addWidget(label);
	for (SubdivisionNew* sd : currSession->subdivisions) {
		layout->addLayout(new SliderSubdivisionNew(sd, canvas));
		window->setLayout(layout);
	}
	window->show();
	SliderWindows.push_back(window);
}

void CMainWindow::CreateOffsetSliders(SlideGLWidget* canvas, Session* currSession)
{
	QWidget *window = new QWidget;
	window->resize(400, 0);
	QVBoxLayout* layout = new QVBoxLayout(window);
	QLabel* label = new QLabel("OFFSET");
	layout->addWidget(label);
	for (OffsetNew* sd : currSession->offsets) {
		layout->addLayout(new SliderOffsetNew(sd, canvas));
		window->setLayout(layout);
	}
	window->show();
	SliderWindows.push_back(window);
}

void CMainWindow::CreateControlPanel(SlideGLWidget* canvas, Session* currSession)
{
	Controls = new ControlPanel(this, canvas, currSession);
	ui->controlPanelDock->setWidget(Controls);
}

void CMainWindow::on_actionNew_triggered()
{
	QMessageBox::information(this, "Info", "Not implemented", QMessageBox::Ok);
}

void CMainWindow::on_actionOpen_triggered()
{
	const QString DEFAULT_DIR_KEY("FilePickerLastDir");
	QSettings settings;

	QString fileName = QFileDialog::getOpenFileName(this, tr("Select Input File"),
		settings.value(DEFAULT_DIR_KEY).toString(), tr("Geometry Files (*.stl *.nom *.obj)"));

	if (!fileName.isEmpty())
	{
		settings.setValue(DEFAULT_DIR_KEY, fileName);
		LoadFile(fileName);
	}
}

void CMainWindow::on_actionSave_triggered()
{
	QMessageBox::information(this, "Info", "Not implemented", QMessageBox::Ok);
}

void CMainWindow::on_actionSave_As_triggered()
{
	const QString DEFAULT_DIR_KEY("FilePickerLastDir");
	QSettings settings;
	QString fileName = QFileDialog::getSaveFileName(this, tr("Save Output File"),
		settings.value(DEFAULT_DIR_KEY).toString(), tr("Output Files (*.stl *.nom)"));

	if (!IsFileOpen())
	{
		ui->statusbar->showMessage("File saving failed. No file is currently open.");
		return;
	}

	if (fileName.right(3).toLower() == "stl")
	{
		DocSession->SaveSessionStl(fileName.toStdString());
	}
	else if (fileName.right(3).toLower() == "nom")
	{
		DocSession->SaveSessionNom(fileName.toStdString());
	}
	else
	{
		ui->statusbar->showMessage("File saving failed. Unknown format chosen.");
	}
}

void CMainWindow::on_actionClose_triggered()
{
	QMessageBox::information(this, "Info", "Not implemented", QMessageBox::Ok);
}
