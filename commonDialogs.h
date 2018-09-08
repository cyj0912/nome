#pragma once

#include <newNOME/Reader.h>

#include <QDialog>
#include <QListWidget>

class VertListDialog : public QDialog
{
	Q_OBJECT

public:
	VertListDialog(QWidget* parent, Reader& reader, std::set<Vert*> candidates);

	Vert* GetSelection() const
	{
		return Selection;
	}

private:
	QListWidget* List;
	Vert* Selection = nullptr;
	std::set<Vert*> Candidates;
};
