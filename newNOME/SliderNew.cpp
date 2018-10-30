//SliderWindow.cpp File

#include "SliderNew.h"
#include <QtGui>
#include <QMainWindow>
#include <QHBoxLayout>
#include <QSlider>
#include <QLabel>
#include "Data.h"

SliderNew::SliderNew(SetNew* set, SlideGLWidget* canvas)
{
	this->canvas = canvas;
	this->set = set;
	label = new QLabel((set->name + ": ").c_str() + QString::number(set->value));

	this->addWidget(label);
	QHBoxLayout *sliderLayout;
	this->addLayout(sliderLayout = new QHBoxLayout);
	sliderLayout->addWidget(new QLabel(QString::number(set->start)));

	//Initialize Slider and Label here
	slider = new QSlider(Qt::Horizontal);
	slider->setPageStep(1);
	slider->setMinimum(0);
	double maximum = (set->end - set->start) / set->stepSize;
	slider->setMaximum(int(round(maximum)));
	double currentValue = (set->value - set->start) / set->stepSize;
	slider->setValue(int(round(currentValue)));


	sliderLayout->addWidget(slider);
	sliderLayout->addWidget(new QLabel(QString::number(set->end)));

	connect(slider, SIGNAL(valueChanged(int)), this, SLOT(sliderValueChanged(int)));
};

void SliderNew::sliderValueChanged(int value)
{
	set->value = value * (set->stepSize) + set->start;
	label->setText((set->name + ": ").c_str() + QString::number(value * (set->stepSize) + set->start));

	canvas->currSession->recalculateSlider = true;
	canvas->currSession->recalculateSubdivision = true;
	canvas->currSession->recalculateOffset = true;
	canvas->currSession->flattenMeshList.clear();

	canvas->update();
};


