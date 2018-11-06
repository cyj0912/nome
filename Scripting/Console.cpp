#include "Console.h"

#include "SceneBuilder.h"
#include "PythonModule.h"

#include <QScrollBar>
#include <QHBoxLayout>
#include <QVBoxLayout>

CConsole::CConsole(QWidget *parent) : QWidget(parent, Qt::Window)
{
	QPalette p = palette();
	p.setColor(QPalette::Base, Qt::black);
	p.setColor(QPalette::Text, Qt::lightGray);
	setPalette(p);

    QVBoxLayout* vLayout = new QVBoxLayout(this);
    TextArea = new QPlainTextEdit();
    vLayout->addWidget(TextArea);

    QHBoxLayout* btmLayout = new QHBoxLayout();
    vLayout->addLayout(btmLayout);
    TextEntry = new QPlainTextEdit();
    EnterButton = new QPushButton("Enter");
    btmLayout->addWidget(TextEntry);
    btmLayout->addWidget(EnterButton);
    this->setLayout(vLayout);
}

CPythonConsole::CPythonConsole(QWidget* parent) : CConsole(parent)
{
    setWindowTitle("Python Console");

    connect(EnterButton, &QPushButton::released, this, &CPythonConsole::enterButtonPressed);
}

void CPythonConsole::focusInEvent(QFocusEvent* event)
{
    QWidget::focusInEvent(event);
}

void CPythonConsole::enterButtonPressed()
{
    //When this console is focused, switch context to CurrSession
    CSceneBuilder::GetSingleton()->SetSession(CurrSession);

    auto text = TextEntry->toPlainText();
    TextArea->appendPlainText(text);
    PythonRun(text.toLocal8Bit().data());
    TextEntry->clear();
}
