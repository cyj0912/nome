#pragma once

#include <QMainWindow>
#include <QTextEdit>

#include <string>

class SlideGLWidget;
class ControlPanel;
class Session;

namespace Ui {
class CMainWindow;
}

class CMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	CMainWindow();
	explicit CMainWindow(const QString& fileName);
	~CMainWindow();

	void tile(const QMainWindow* previous);

protected:
	void closeEvent(QCloseEvent* event) override;

private slots:
	void newFile();
	void open();
	bool save();
	bool saveAs();
	void updateRecentFileActions();
	void openRecentFile();
	void about();
	void documentWasModified();

private:
	enum { MaxRecentFiles = 5 };

	Ui::CMainWindow* ui;

	void init();
	void readSettings();
	void writeSettings();
	bool maybeSave();
	void openFile(const QString& fileName);
	void loadFile(const QString& fileName);
	static bool hasRecentFiles();
	void prependToRecentFiles(const QString& fileName);
	void setRecentFilesVisible(bool visible);
	bool saveFile(const QString& fileName);
	void setCurrentFile(const QString& fileName);
	static QString strippedName(const QString& fullFileName);
	CMainWindow* findMainWindow(const QString& fileName) const;

	QAction* recentFileActs[MaxRecentFiles];
	QAction* recentFileSubMenuAct;

	QString curFile;
	bool isUntitled;
};
