#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "nomeglwidget.h"
#include "controlpanel.h"
#include "nomeparser.h"
#include "newNOME/Session.h"
#include "newNOME/SliderNew.h"
#include "newNOME/SliderSubdivisionNew.h"
#include "newNOME/SliderOffsetNew.h"

#include "Scripting/PythonModule.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QSettings>
#include <QDesktopWidget>

#include <vector>

//>>>>>>
#include "Scripting/Console.h"

class CPythonConsole : public QWidget
{
public:
	explicit CPythonConsole(QWidget* parent = nullptr);

	~CPythonConsole() override;

private:
	void WriteData(const QByteArray& data);

	std::string LineBuffer;
};

CPythonConsole::CPythonConsole(QWidget* parent) : QWidget(parent, Qt::Window)
{
	auto* layout = new QVBoxLayout(this);
	setLayout(layout);
	layout->setContentsMargins(0, 0, 0, 0);

	auto* console = new CConsole(this);
	layout->addWidget(console);

	connect(console, &CConsole::getData, this, &CPythonConsole::WriteData);

	setWindowTitle("Python Console");

	InitPython();
}

CPythonConsole::~CPythonConsole()
{
	FiniPythion();
}

void CPythonConsole::WriteData(const QByteArray& data)
{
	if (data.length() == 0)
		return;

	for (int i = 0; i < data.length(); i++)
	{
		char ch = data.at(i);
		if (ch == '\n' || ch == '\r')
		{
			if (LineBuffer.size() != 0)
			{
				std::cout << ">>> " << LineBuffer << std::endl;
				PythonRun(LineBuffer.c_str());
				LineBuffer.clear();
			}
		}
		else
		{
			LineBuffer.push_back(ch);
		}
	}
}
//<<<<<<

CMainWindow::CMainWindow() : ui(new Ui::CMainWindow)
{
	init();
	setCurrentFile(QString());
}

CMainWindow::CMainWindow(const QString& fileName) : ui(new Ui::CMainWindow)
{
	init();
	loadFile(fileName);
}

CMainWindow::~CMainWindow()
{
	delete ui;
}

void CMainWindow::closeEvent(QCloseEvent *event)
{
	if (maybeSave()) {
		writeSettings();
		event->accept();
	}
	else {
		event->ignore();
	}
}

void CMainWindow::newFile()
{
	CMainWindow *other = new CMainWindow;
	other->tile(this);
	other->show();
}

void CMainWindow::open()
{
	const QString fileName = QFileDialog::getOpenFileName(this);
	if (!fileName.isEmpty())
		openFile(fileName);
}

void CMainWindow::openFile(const QString& fileName)
{
	CMainWindow *existing = findMainWindow(fileName);
	if (existing) {
		existing->show();
		existing->raise();
		existing->activateWindow();
		return;
	}

	if (isUntitled && textEdit->document()->isEmpty() && !isWindowModified()) {
		loadFile(fileName);
		return;
	}

	CMainWindow *other = new CMainWindow(fileName);
	if (other->isUntitled) {
		delete other;
		return;
	}
	other->tile(this);
	other->show();
}

bool CMainWindow::save()
{
	return isUntitled ? saveAs() : saveFile(curFile);
}

bool CMainWindow::saveAs()
{
	QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"),
		curFile);
	if (fileName.isEmpty())
		return false;

	return saveFile(fileName);
}

void CMainWindow::about()
{
	QMessageBox::about(this, tr("About Nome"),
		"This is the Non-Orientable Manifold Editor project developed at Cal.\n"
		"\n"
		"Authors:\n"
		"Yu (Andy) Wang (c) 2016\n"
		"Gauthier Diepadelle (c) 2017-2018\n"
		"Toby Chen (c) 2018\n"
		"Henry Sun (c) 2018\n"
		"Marc Wudunn (c) 2018\n"
		"\n"
		"Version: 1.0\n");
}

void CMainWindow::documentWasModified()
{
	setWindowModified(true);
}

void CMainWindow::init()
{
	setAttribute(Qt::WA_DeleteOnClose);

	ui->setupUi(this);
	ui->sliderDock->hide();

	isUntitled = true;

	textEdit = new QTextEdit;
	setCentralWidget(textEdit);

	connect(ui->actionNew, &QAction::triggered, this, &CMainWindow::newFile);
	connect(ui->actionOpen, &QAction::triggered, this, &CMainWindow::open);
	connect(ui->actionSave, &QAction::triggered, this, &CMainWindow::save);
	connect(ui->actionSave_As, &QAction::triggered, this, &CMainWindow::saveAs);
	connect(ui->actionClose, &QAction::triggered, this, &QWidget::close);
	connect(ui->actionExit, &QAction::triggered, qApp, &QApplication::closeAllWindows);

	connect(ui->menuRecent_Files, &QMenu::aboutToShow, this, &CMainWindow::updateRecentFileActions);
	recentFileSubMenuAct = ui->menuRecent_Files->menuAction();

	for (int i = 0; i < MaxRecentFiles; ++i) {
		recentFileActs[i] = ui->menuRecent_Files->addAction(QString(), this, &CMainWindow::openRecentFile);
		recentFileActs[i]->setVisible(false);
	}

	setRecentFilesVisible(CMainWindow::hasRecentFiles());

	connect(ui->actionAbout, &QAction::triggered, this, &CMainWindow::about);
	connect(ui->actionAbout_Qt, &QAction::triggered, qApp, &QApplication::aboutQt);

	readSettings();

	connect(textEdit->document(), &QTextDocument::contentsChanged,
		this, &CMainWindow::documentWasModified);

	setUnifiedTitleAndToolBarOnMac(true);
}

void CMainWindow::tile(const QMainWindow *previous)
{
	if (!previous)
		return;
	int topFrameWidth = previous->geometry().top() - previous->pos().y();
	if (!topFrameWidth)
		topFrameWidth = 40;
	const QPoint pos = previous->pos() + 2 * QPoint(topFrameWidth, topFrameWidth);
	if (QApplication::desktop()->availableGeometry(this).contains(rect().bottomRight() + pos))
		move(pos);
}

void CMainWindow::readSettings()
{
	QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());
	const QByteArray geometry = settings.value("geometry", QByteArray()).toByteArray();
	if (geometry.isEmpty()) {
		const QRect availableGeometry = QApplication::desktop()->availableGeometry(this);
		resize(availableGeometry.width() / 3, availableGeometry.height() / 2);
		move((availableGeometry.width() - width()) / 2,
			(availableGeometry.height() - height()) / 2);
	}
	else {
		restoreGeometry(geometry);
	}
}

void CMainWindow::writeSettings()
{
	QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());
	settings.setValue("geometry", saveGeometry());
}

bool CMainWindow::maybeSave()
{
	if (!textEdit->document()->isModified())
		return true;
	const QMessageBox::StandardButton ret
		= QMessageBox::warning(this, tr("Nome"),
			tr("The document has been modified.\n"
				"Do you want to save your changes?"),
			QMessageBox::Save | QMessageBox::Discard
			| QMessageBox::Cancel);
	switch (ret) {
	case QMessageBox::Save:
		return save();
	case QMessageBox::Cancel:
		return false;
	default:
		break;
	}
	return true;
}

void CMainWindow::loadFile(const QString &fileName)
{
	QFile file(fileName);
	if (!file.open(QFile::ReadOnly | QFile::Text)) {
		QMessageBox::warning(this, tr("Nome"),
			tr("Cannot read file %1:\n%2.")
			.arg(QDir::toNativeSeparators(fileName), file.errorString()));
		return;
	}

	QTextStream in(&file);
	QApplication::setOverrideCursor(Qt::WaitCursor);
	textEdit->setPlainText(in.readAll());
	QApplication::restoreOverrideCursor();

	setCurrentFile(fileName);
	statusBar()->showMessage(tr("File loaded"), 2000);
}

void CMainWindow::setRecentFilesVisible(bool visible)
{
	recentFileSubMenuAct->setVisible(visible);
}

static inline QString recentFilesKey() { return QStringLiteral("recentFileList"); }
static inline QString fileKey() { return QStringLiteral("file"); }

static QStringList readRecentFiles(QSettings &settings)
{
	QStringList result;
	const int count = settings.beginReadArray(recentFilesKey());
	for (int i = 0; i < count; ++i) {
		settings.setArrayIndex(i);
		result.append(settings.value(fileKey()).toString());
	}
	settings.endArray();
	return result;
}

static void writeRecentFiles(const QStringList &files, QSettings &settings)
{
	const int count = files.size();
	settings.beginWriteArray(recentFilesKey());
	for (int i = 0; i < count; ++i) {
		settings.setArrayIndex(i);
		settings.setValue(fileKey(), files.at(i));
	}
	settings.endArray();
}

bool CMainWindow::hasRecentFiles()
{
	QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());
	const int count = settings.beginReadArray(recentFilesKey());
	settings.endArray();
	return count > 0;
}

void CMainWindow::prependToRecentFiles(const QString &fileName)
{
	QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());

	const QStringList oldRecentFiles = readRecentFiles(settings);
	QStringList recentFiles = oldRecentFiles;
	recentFiles.removeAll(fileName);
	recentFiles.prepend(fileName);
	if (oldRecentFiles != recentFiles)
		writeRecentFiles(recentFiles, settings);

	setRecentFilesVisible(!recentFiles.isEmpty());
}

void CMainWindow::updateRecentFileActions()
{
	QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());

	const QStringList recentFiles = readRecentFiles(settings);
	const int count = qMin(int(MaxRecentFiles), recentFiles.size());
	int i = 0;
	for (; i < count; ++i) {
		const QString fileName = CMainWindow::strippedName(recentFiles.at(i));
		recentFileActs[i]->setText(tr("&%1 %2").arg(i + 1).arg(fileName));
		recentFileActs[i]->setData(recentFiles.at(i));
		recentFileActs[i]->setVisible(true);
	}
	for (; i < MaxRecentFiles; ++i)
		recentFileActs[i]->setVisible(false);
}

void CMainWindow::openRecentFile()
{
	if (const QAction* action = qobject_cast<const QAction*>(sender()))
		openFile(action->data().toString());
}

bool CMainWindow::saveFile(const QString &fileName)
{
	QFile file(fileName);
	if (!file.open(QFile::WriteOnly | QFile::Text)) {
		QMessageBox::warning(this, tr("Nome"),
			tr("Cannot write file %1:\n%2.")
			.arg(QDir::toNativeSeparators(fileName), file.errorString()));
		return false;
	}

	QTextStream out(&file);
	QApplication::setOverrideCursor(Qt::WaitCursor);
	out << textEdit->toPlainText();
	QApplication::restoreOverrideCursor();

	setCurrentFile(fileName);
	statusBar()->showMessage(tr("File saved"), 2000);
	return true;
}

void CMainWindow::setCurrentFile(const QString &fileName)
{
	static int sequenceNumber = 1;

	isUntitled = fileName.isEmpty();
	if (isUntitled) {
		curFile = tr("document%1.txt").arg(sequenceNumber++);
	}
	else {
		curFile = QFileInfo(fileName).canonicalFilePath();
	}

	textEdit->document()->setModified(false);
	setWindowModified(false);

	if (!isUntitled && windowFilePath() != curFile)
		CMainWindow::prependToRecentFiles(curFile);

	setWindowFilePath(curFile);
}

QString CMainWindow::strippedName(const QString &fullFileName)
{
	return QFileInfo(fullFileName).fileName();
}

CMainWindow* CMainWindow::findMainWindow(const QString& fileName) const
{
	QString canonicalFilePath = QFileInfo(fileName).canonicalFilePath();

	foreach(QWidget* widget, QApplication::topLevelWidgets()) {
		CMainWindow* mainWin = qobject_cast<CMainWindow*>(widget);
		if (mainWin && mainWin->curFile == canonicalFilePath)
			return mainWin;
	}

	return 0;
}

#if 0
CMainWindow::CMainWindow() :
    QMainWindow(),
    ui(new Ui::CMainWindow)
{
	Init();
}

CMainWindow::CMainWindow(const QString& fileName) :
	QMainWindow(),
	ui(new Ui::CMainWindow)
{
	Init();
}

CMainWindow::~CMainWindow()
{
    delete ui;
}

void CMainWindow::Init()
{
	setAttribute(Qt::WA_DeleteOnClose);

	ui->setupUi(this);

	ui->sliderDock->hide();
	ui->centralHLayout->setContentsMargins(0, 0, 0, 0);

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

void CMainWindow::LoadFile(const QString& fileName)
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
		QWidget* window = new QWidget(this, Qt::Window);
		window->resize(400, 0);
		QVBoxLayout* layout = new QVBoxLayout(window);
		QLabel* label = new QLabel(b->name.c_str());
		layout->addWidget(label);
		for (auto s : b->sets) {
			layout->addLayout(new SliderNew(s, canvas));
		}
		window->setLayout(layout);
		window->show();
	}
}

void CMainWindow::CreateSubdivisionSliders(SlideGLWidget* canvas, Session* currSession)
{
	QWidget *window = new QWidget(this, Qt::Window);
	window->resize(400, 0);
	QVBoxLayout* layout = new QVBoxLayout(window);
	QLabel* label = new QLabel("SUBDIVISION");
	layout->addWidget(label);
	for (SubdivisionNew* sd : currSession->subdivisions) {
		layout->addLayout(new SliderSubdivisionNew(sd, canvas));
		window->setLayout(layout);
	}
	window->show();
}

void CMainWindow::CreateOffsetSliders(SlideGLWidget* canvas, Session* currSession)
{
	QWidget *window = new QWidget(this, Qt::Window);
	window->resize(400, 0);
	QVBoxLayout* layout = new QVBoxLayout(window);
	QLabel* label = new QLabel("OFFSET");
	layout->addWidget(label);
	for (OffsetNew* sd : currSession->offsets) {
		layout->addLayout(new SliderOffsetNew(sd, canvas));
		window->setLayout(layout);
	}
	window->show();
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

void CMainWindow::on_actionPython_Console_toggled(bool state)
{
	if (state)
	{
		auto* pyConsole = new CPythonConsole(this);
		pyConsole->setObjectName("pyConsole");
		pyConsole->show();
	}
	else
	{
		auto* pyConsole = findChild<CPythonConsole*>("pyConsole");
		delete pyConsole;
	}
}
#endif
