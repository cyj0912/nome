#pragma once

#include <QMainWindow>

class CMainWindowPriv;
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
    explicit CMainWindow(QWidget *parent = nullptr);
    ~CMainWindow();

private:
	void LoadFile(QString fileName);
	void CreateSliders(SlideGLWidget* canvas, Session* currSession);
	void CreateSubdivisionSliders(SlideGLWidget* canvas, Session* currSession);
	void CreateOffsetSliders(SlideGLWidget* canvas, Session* currSession);
	void CreateControlPanel(SlideGLWidget* canvas, Session* currSession);

	bool IsFileOpen() const
	{
		return Canvas && DocSession;
	}

private slots:
	void on_actionNew_triggered();
	void on_actionOpen_triggered();
	void on_actionSave_triggered();
	void on_actionSave_As_triggered();
	void on_actionClose_triggered();

private:
    Ui::CMainWindow *ui;

	SlideGLWidget* Canvas = nullptr;
	ControlPanel* Controls = nullptr;
	Session* DocSession = nullptr;

	std::vector<QWidget*> SliderWindows;
};
