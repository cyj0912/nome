#include "commonDialogs.h"

#include <QLayout>
#include <QPushButton>

VertListDialog::VertListDialog(QWidget* parent, Reader& reader, std::set<Vert*> candidates)
	: QDialog(parent), Candidates(candidates)
{
	List = new QListWidget();
	for (Vert* v : Candidates)
	{
		List->addItem(reader.getVertName(v->index).c_str());
	}
	connect(List, &QListWidget::currentRowChanged, [&](int row) {
		auto iter = Candidates.begin();
		std::advance(iter, row);
		Selection = *iter;
	});
	List->setCurrentRow(0);
	connect(List, &QListWidget::itemDoubleClicked, this, &QDialog::close);

	auto* okButton = new QPushButton("OK");
	connect(okButton, &QPushButton::clicked, this, &QDialog::close);

	QVBoxLayout* layout = new QVBoxLayout(this);
	layout->addWidget(List);
	layout->addWidget(okButton);

	adjustSize();
}
