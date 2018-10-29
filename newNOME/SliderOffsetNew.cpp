//SliderWindow.cpp File

#include "SliderOffsetNew.h"
#include <QtGui>
#include <QMainWindow>
#include <QHBoxLayout>
#include <QSlider>
#include <QLabel>
#include "Data.h"
#include "OffsetNew.h"

SliderOffsetNew::SliderOffsetNew(OffsetNew* offset, SlideGLWidget * canvas)
{
    this->canvas = canvas;
    this->offset = offset;
    label = new QLabel((offset->name + ": ").c_str() + QString::number(offset->value));

    this->addWidget(label);
    QHBoxLayout *sliderLayout;
    this -> addLayout(sliderLayout = new QHBoxLayout);
    sliderLayout -> addWidget(new QLabel(QString::number(*offset->min)));

    //Initialize Slider and Label here
    slider = new QSlider(Qt::Horizontal);
    slider -> setPageStep(1);
    slider -> setMinimum(0);
    double maximum = (*offset->max - *offset->min) / *offset->step;
    slider -> setMaximum(int(round(maximum)));
    double currentValue = (*offset -> min - *offset -> min) / *offset -> step;
    slider -> setValue(int(round(currentValue)));


    sliderLayout->addWidget(slider);
	sliderLayout->addWidget(new QLabel(QString::number(*offset->max)));

    connect(slider,SIGNAL(valueChanged(int)),this,SLOT(sliderValueChanged(int)));
};

void SliderOffsetNew::sliderValueChanged(int value)
{
    offset->value = value * (*offset -> step) + *offset -> min;
    label->setText((offset->name + ": ").c_str() + QString::number(value * (*offset -> step) + *offset -> min));
    canvas->currSession->recalculateOffset = true;

	canvas->update();
};


