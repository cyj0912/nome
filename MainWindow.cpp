#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "nomeglwidget.h"
#include "controlpanel.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QSettings>
#include <QDesktopWidget>
#include <QCloseEvent>

CMainWindow::CMainWindow()
    : ui(new Ui::CMainWindow)
{
    init();
    setCurrentFile(QString());
}

CMainWindow::CMainWindow(const QString& fileName)
    : ui(new Ui::CMainWindow)
{
    init();
    loadFile(fileName);
}

CMainWindow::~CMainWindow()
{
    delete ui;
}

void CMainWindow::closeEvent(QCloseEvent* event)
{
    if (maybeSave())
    {
        writeSettings();
        event->accept();
    }
    else
    {
        event->ignore();
    }
}

void CMainWindow::newFile()
{
    CMainWindow* other = new CMainWindow;
    other->tile(this);
    other->show();
}

void CMainWindow::open()
{
    const QString DEFAULT_DIR_KEY("FilePickerLastDir");
    QSettings settings;

    QString fileName = QFileDialog::getOpenFileName(this, tr("Select Input File"),
                                                    settings.value(DEFAULT_DIR_KEY).toString(),
                                                    tr("Geometry Files (*.stl *.nom *.obj)"));

    if (!fileName.isEmpty())
    {
        settings.setValue(DEFAULT_DIR_KEY, fileName);
        openFile(fileName);
    }
}

void CMainWindow::openFile(const QString& fileName)
{
    CMainWindow* existing = findMainWindow(fileName);
    if (existing)
    {
        existing->show();
        existing->raise();
        existing->activateWindow();
        return;
    }

    if (!document)
    {
        loadFile(fileName);
        return;
    }

    CMainWindow* other = new CMainWindow(fileName);
    if (other->isUntitled)
    {
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

    connect(ui->actionNew, &QAction::triggered, this, &CMainWindow::newFile);
    connect(ui->actionOpen, &QAction::triggered, this, &CMainWindow::open);
    connect(ui->actionSave, &QAction::triggered, this, &CMainWindow::save);
    connect(ui->actionSave_As, &QAction::triggered, this, &CMainWindow::saveAs);
    connect(ui->actionClose, &QAction::triggered, this, &QWidget::close);
    connect(ui->actionExit, &QAction::triggered, qApp, &QApplication::closeAllWindows);

    connect(ui->menuRecent_Files, &QMenu::aboutToShow, this, &CMainWindow::updateRecentFileActions);
    recentFileSubMenuAct = ui->menuRecent_Files->menuAction();

    for (int i = 0; i < MaxRecentFiles; ++i)
    {
        recentFileActs[i] = ui->menuRecent_Files->addAction(QString(), this, &CMainWindow::openRecentFile);
        recentFileActs[i]->setVisible(false);
    }

    setRecentFilesVisible(CMainWindow::hasRecentFiles());

    connect(ui->actionAbout, &QAction::triggered, this, &CMainWindow::about);
    connect(ui->actionAbout_Qt, &QAction::triggered, qApp, &QApplication::aboutQt);

    readSettings();

    //connect(textEdit->document(), &QTextDocument::contentsChanged,
    //        this, &CMainWindow::documentWasModified);

    setUnifiedTitleAndToolBarOnMac(true);
}

void CMainWindow::tile(const QMainWindow* previous)
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
    if (geometry.isEmpty())
    {
        const QRect availableGeometry = QApplication::desktop()->availableGeometry(this);
        resize(availableGeometry.width() / 3, availableGeometry.height() / 2);
        move((availableGeometry.width() - width()) / 2,
             (availableGeometry.height() - height()) / 2);
    }
    else
    {
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
    if (!document || !document->IsModified())
        return true;
    const QMessageBox::StandardButton ret
        = QMessageBox::warning(this, tr("Nome"),
                               tr("The document has been modified.\n"
                                  "Do you want to save your changes?"),
                               QMessageBox::Save | QMessageBox::Discard
                                   | QMessageBox::Cancel);
    switch (ret)
    {
        case QMessageBox::Save:
            return save();
        case QMessageBox::Cancel:
            return false;
        default:
            break;
    }
    return true;
}

void CMainWindow::loadFile(const QString& fileName)
{
    QApplication::setOverrideCursor(Qt::WaitCursor);

    if (document)
    {
        delete document;
    }
    document = new CNomeDocument(fileName);
    document->CreateSliders(this);
    document->CreateOffsetSliders(this);
    document->CreateSubdivisionSliders(this);
    document->CreateControlPanel(this);
    ui->controlPanelDock->setWidget(document->GetControls());
    ui->centralHLayout->addWidget(document->GetCanvas());

    pyConsole = new CPythonConsole(this);
    pyConsole->SetSession(document->GetSession());
    pyConsole->show();
	connect(pyConsole, &CConsole::OnCommandSent, [&]() {
		document->GetCanvas()->update();
	});

    QApplication::restoreOverrideCursor();

    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File loaded"), 2000);
}

void CMainWindow::setRecentFilesVisible(bool visible)
{
    recentFileSubMenuAct->setVisible(visible);
}

static inline QString recentFilesKey()
{ return QStringLiteral("recentFileList"); }
static inline QString fileKey()
{ return QStringLiteral("file"); }

static QStringList readRecentFiles(QSettings& settings)
{
    QStringList result;
    const int count = settings.beginReadArray(recentFilesKey());
    for (int i = 0; i < count; ++i)
    {
        settings.setArrayIndex(i);
        result.append(settings.value(fileKey()).toString());
    }
    settings.endArray();
    return result;
}

static void writeRecentFiles(const QStringList& files, QSettings& settings)
{
    const int count = files.size();
    settings.beginWriteArray(recentFilesKey());
    for (int i = 0; i < count; ++i)
    {
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

void CMainWindow::prependToRecentFiles(const QString& fileName)
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
    for (; i < count; ++i)
    {
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

bool CMainWindow::saveFile(const QString& fileName)
{
    QApplication::setOverrideCursor(Qt::WaitCursor);

    if (document)
        document->SaveFile(fileName);

    QApplication::restoreOverrideCursor();

    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File saved"), 2000);
    return true;
}

void CMainWindow::setCurrentFile(const QString& fileName)
{
    static int sequenceNumber = 1;

    isUntitled = fileName.isEmpty();
    if (isUntitled)
    {
        curFile = tr("document%1.txt").arg(sequenceNumber++);
    }
    else
    {
        curFile = QFileInfo(fileName).canonicalFilePath();
    }

    //textEdit->document()->setModified(false);
    setWindowModified(false);

    if (!isUntitled && windowFilePath() != curFile)
        CMainWindow::prependToRecentFiles(curFile);

    setWindowFilePath(curFile);
}

QString CMainWindow::strippedName(const QString& fullFileName)
{
    return QFileInfo(fullFileName).fileName();
}

CMainWindow* CMainWindow::findMainWindow(const QString& fileName) const
{
    QString canonicalFilePath = QFileInfo(fileName).canonicalFilePath();

        foreach(QWidget* widget, QApplication::topLevelWidgets())
        {
            CMainWindow* mainWin = qobject_cast<CMainWindow*>(widget);
            if (mainWin && mainWin->curFile == canonicalFilePath)
                return mainWin;
        }

    return 0;
}
