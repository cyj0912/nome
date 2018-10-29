//SliderWindow.cpp File

#include "SliderSubdivisionNew.h"
#include "SubdivisionNew.h"
#include <QtGui>
#include <QMainWindow>
#include <QHBoxLayout>
#include <QSlider>
#include <QLabel>
#include "Data.h"

SliderSubdivisionNew::SliderSubdivisionNew(SubdivisionNew* subdivision, SlideGLWidget * canvas)
{
    this->canvas = canvas;
    this->subdivision = subdivision;
    label = new QLabel((subdivision->name + ": ").c_str() + QString::number(subdivision->value));

    this->addWidget(label);
    QHBoxLayout *sliderLayout;
    this -> addLayout(sliderLayout = new QHBoxLayout);
    sliderLayout -> addWidget(new QLabel(QString::number(0)));

    //Initialize Slider and Label here
    slider = new QSlider(Qt::Horizontal);
    slider -> setPageStep(1);
    slider -> setMinimum(0);
    double maximum = (*subdivision->subdivisions - 0) / 1;
    slider -> setMaximum(int(round(maximum)));
    double currentValue = (subdivision -> value) / 1;
    slider -> setValue(int(round(currentValue)));


    sliderLayout->addWidget(slider);
    sliderLayout -> addWidget(new QLabel(QString::number(*subdivision->subdivisions)));

    connect(slider,SIGNAL(valueChanged(int)),this,SLOT(sliderValueChanged(int)));
};

void SliderSubdivisionNew::sliderValueChanged(int value)
{
    subdivision->value = value;
    label->setText((subdivision->name + ": ").c_str() + QString::number(value));
    canvas->currSession->recalculateSubdivision = true;

	canvas->update();
};


