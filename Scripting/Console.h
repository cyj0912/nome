#pragma once

#include <QPlainTextEdit>
#include <QPushButton>

class CConsole : public QWidget
{
	Q_OBJECT

public:
	explicit CConsole(QWidget *parent = nullptr);

protected:
    QPlainTextEdit* TextArea;
    QPlainTextEdit* TextEntry;
    QPushButton* EnterButton;
};

class Session;

class CPythonConsole : public CConsole
{
    Q_OBJECT
public:
    explicit CPythonConsole(QWidget *parent = nullptr);

    void SetSession(Session* s)
    {
        CurrSession = s;
    }

protected:
    void focusInEvent(QFocusEvent* event) override;

private slots:
    void enterButtonPressed();

private:
    Session* CurrSession;
};
