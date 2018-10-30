#include "Console.h"
#include <QScrollBar>

CConsole::CConsole(QWidget *parent) :
	QPlainTextEdit(parent)
{
	document()->setMaximumBlockCount(1000);
	QPalette p = palette();
	p.setColor(QPalette::Base, Qt::black);
	p.setColor(QPalette::Text, Qt::lightGray);
	setPalette(p);
}

void CConsole::putData(const QByteArray &data)
{
	insertPlainText(data);

	QScrollBar *bar = verticalScrollBar();
	bar->setValue(bar->maximum());
}

void CConsole::setLocalEchoEnabled(bool set)
{
	m_localEchoEnabled = set;
}

void CConsole::keyPressEvent(QKeyEvent *e)
{
	switch (e->key()) {
	case Qt::Key_Backspace:
	case Qt::Key_Left:
	case Qt::Key_Right:
	case Qt::Key_Up:
	case Qt::Key_Down:
		break;
	default:
		if (m_localEchoEnabled)
			QPlainTextEdit::keyPressEvent(e);
		emit getData(e->text().toLocal8Bit());
	}
}

void CConsole::mousePressEvent(QMouseEvent *e)
{
	Q_UNUSED(e)
	setFocus();
}

void CConsole::mouseDoubleClickEvent(QMouseEvent *e)
{
	Q_UNUSED(e)
}

void CConsole::contextMenuEvent(QContextMenuEvent *e)
{
	Q_UNUSED(e)
}
