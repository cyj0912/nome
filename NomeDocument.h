#pragma once

#include <QString>

class QWidget;

class SlideGLWidget;
class ControlPanel;
class Session;

//CNomeDocument serves as a portion of CMainWindow
class CMainWindow;

class CNomeDocument
{
public:
    CNomeDocument();
    CNomeDocument(const QString& fileName);
    ~CNomeDocument();

    bool IsEmpty() const
    {
        return false;
    }

    bool IsModified() const
    {
        return true;
    }

    Session* GetSession() const
    {
        return CurrSession;
    }

    SlideGLWidget* GetCanvas() const
    {
        return Canvas;
    }

    ControlPanel* GetControls() const
    {
        return Controls;
    }

    void CreateSliders(QWidget* mainWindow);
    void CreateSubdivisionSliders(QWidget* mainWindow);
    void CreateOffsetSliders(QWidget* mainWindow);
    void CreateControlPanel(CMainWindow* mainWindow);

    bool SaveFile(const QString& fileName);

private:
    Session* CurrSession = nullptr;
    SlideGLWidget* Canvas = nullptr;
    ControlPanel* Controls = nullptr;
};
