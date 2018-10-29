/**
 * @author Andy Wang, UC Berkeley.
 * Copyright 2016 reserve.
 * UC Berkeley, Slide_2016 project.
 * Advised by Prof. Sequin H. Carlos.
 */

#include "controlpanel.h"
#include "mainwindow.h"
#include "nomeglwidget.h"

ControlPanel::ControlPanel()
{
    setupLayout();
    //buildConnection();
}

ControlPanel::ControlPanel(CMainWindow* parentWindow, SlideGLWidget * canvas, Session* currSession)
{
	mainWindow = parentWindow;
    this -> currSession = currSession;
    setupLayout();
    this -> canvas = canvas;
    buildConnection();
    resize(700, 600);
}


void ControlPanel::buildConnection()
{
    /* Build our connections. */
    connect(viewContent, SIGNAL(activated(int)), canvas, SLOT(viewContentChanged(int)));
    connect(mergeButton, SIGNAL(clicked(bool)), canvas, SLOT(mergeCalled(bool)));
    connect(mergeButton, SIGNAL(clicked(bool)), this, SLOT(pushMerge(bool)));
    //connect(subdivLevelSlider,SIGNAL(valueChanged(int)), canvas, SLOT(levelChanged(int)));
    //connect(subdivLevelSlider, SIGNAL(valueChanged(int)), this, SLOT(viewContentSetToSubdiv(int)));
    connect(resetViewButton, SIGNAL(clicked(bool)), canvas, SLOT(resetViewDirection(bool)));
    //connect(minOffsetBox, SIGNAL(textChanged(QString)), this, SLOT(resetMinOffset(QString)));
    //connect(maxOffsetBox, SIGNAL(textChanged(QString)), this, SLOT(resetMaxOffset(QString)));
    //connect(offsetStepBox, SIGNAL(textChanged(QString)), this, SLOT(resetOffsetStep(QString)));
    //connect(offsetValueSlider, SIGNAL(sliderReleased()), this, SLOT(offSetSliderMoved()));
    connect(this, SIGNAL(makeOffsetMesh(float)), canvas, SLOT(offsetValueChanged(float)));
    connect(foreColorButton, SIGNAL(clicked(bool)), this, SLOT(resetForeColor(bool)));
    connect(backColorButton, SIGNAL(clicked(bool)), this, SLOT(resetBackColor(bool)));
    connect(outsideFacesColorButton, SIGNAL(clicked(bool)), this, SLOT(resetOutsideFacesColor(bool)));
    connect(insideFacesColorButton, SIGNAL(clicked(bool)), this, SLOT(resetInsideFacesColor(bool)));
    connect(offsetFacesColorButton, SIGNAL(clicked(bool)), this, SLOT(resetOffsetFacesColor(bool)));
    connect(vertexModeButton, SIGNAL(clicked(bool)), this, SLOT(vertexModeChecked(bool)));
    connect(borderModeButton, SIGNAL(clicked(bool)), this, SLOT(borderModeChecked(bool)));
    connect(normalVect, SIGNAL(clicked(bool)), this, SLOT(normalVectChecked(bool)));
    connect(faceModeButton, SIGNAL(clicked(bool)), this, SLOT(faceModeChecked(bool)));
    connect(canvas, SIGNAL(feedback_status_bar(QString, int)), statusBar, SLOT(showMessage(QString,int)));
    connect(vertexModeButton, SIGNAL(clicked(bool)), canvas, SLOT(vertexModeChecked(bool)));
    connect(borderModeButton, SIGNAL(clicked(bool)), canvas, SLOT(borderModeChecked(bool)));
    connect(faceModeButton, SIGNAL(clicked(bool)), canvas, SLOT(faceModeChecked(bool)));
    connect(addFaceButton, SIGNAL(clicked(bool)), canvas, SLOT(addToTempCalled(bool)));
    connect(groupFacesButton, SIGNAL(clicked(bool)), canvas, SLOT(popUpGroupWindow(bool)));
    connect(undoAddButton, SIGNAL(clicked(bool)), canvas, SLOT(undoFaceCalled(bool)));
    connect(addPolylineButton, SIGNAL(clicked(bool)), canvas, SLOT(addToPolylineCalled(bool)));
    connect(deleteFaceButton, SIGNAL(clicked(bool)), canvas, SLOT(deleteFaceCalled(bool)));
    connect(addBorderButton, SIGNAL(clicked(bool)), canvas, SLOT(addBorderCalled(bool)));
    connect(zipButton, SIGNAL(clicked(bool)), canvas, SLOT(zipToTempCalled(bool)));
    connect(clearSelectionButton,SIGNAL(clicked(bool)), canvas, SLOT(clearSelectionCalled(bool)));
    //connect(addTempToMasterButton, SIGNAL(clicked(bool)), canvas, SLOT(addTempToMasterCalled(bool)));
    connect(wholeBorderCheck,SIGNAL(clicked(bool)), canvas, SLOT(wholeBorderSelectionChecked(bool)));
    connect(trianglePaneltyEdit, SIGNAL(textChanged(QString)), canvas, SLOT(resetTrianglePanelty(QString)));
    connect(consolidateButton, SIGNAL(clicked(bool)), canvas, SLOT(popUpConsolidateWindow(bool)));
	connect(sceneRegenButton, &QPushButton::clicked, this, &ControlPanel::regenerateScene);
}

void ControlPanel::setupLayout()
{
    /* Main Layout.
     * Contains view, mode, subdivision, offset, color, status.*/
    setLayout(mainLayout = new QVBoxLayout);
    mainLayout -> setMargin(10);
    mainLayout->setSpacing(5);
    mainLayout -> addWidget(new QLabel("VIEW MODE"));
    mainLayout -> addLayout(viewLayout = new QVBoxLayout);
    mainLayout -> addWidget(new QLabel("EDIT MODE"));
    mainLayout -> addLayout(modeLayout = new QVBoxLayout);
    //mainLayout -> addWidget(new QLabel("SUBDIVISION"));
    mainLayout -> addLayout(subdivLayout = new QVBoxLayout);
    //mainLayout -> addWidget(new QLabel("OFFSET"));
    //mainLayout -> addLayout(offsetLayout = new QVBoxLayout);
    mainLayout -> addWidget(new QLabel("COLOR"));
    mainLayout -> addLayout(colorLayout = new QVBoxLayout);

	sceneRegenButton = new QPushButton("Reload Scene", this);
	mainLayout->addWidget(sceneRegenButton);

    /* View layout. */
    viewLayout -> addWidget(viewContent = new QComboBox);
    viewContent -> addItem("Hirachical Scene");
    viewContent -> addItem("Merged Mesh");
    viewContent -> addItem("Subdivision Mesh");
    viewContent -> addItem("Offset Mesh");
    viewContent -> addItem("Subdivision on Offset Mesh");
    viewContent -> setCurrentIndex(0);
    viewLayout -> addWidget(resetViewButton = new QPushButton(tr("Reset Arcball View")));

    /* Mode layout.*/
    modeLayout -> addLayout(selectionLayout = new QHBoxLayout);
    modeLayout -> addLayout(editLayout = new QHBoxLayout);
    modeLayout -> addLayout(editLayout2 = new QHBoxLayout);
    modeLayout -> addLayout(undoLayout = new QHBoxLayout);
    modeLayout -> addLayout(editLayout3 = new QHBoxLayout);
    modeLayout -> addLayout(zipOptionsLayout = new QHBoxLayout);
    selectionLayout -> addWidget(vertexModeButton = new QRadioButton(tr("Select Vertex")));
    selectionLayout -> addWidget(borderModeButton = new QRadioButton(tr("Select Border")));
    selectionLayout -> addWidget(faceModeButton = new QRadioButton(tr("Select Face")));
    vertexModeButton -> setChecked(true);

    editLayout -> addWidget(addPolylineButton = new QPushButton(tr("Add Polyline")));
    editLayout -> addWidget(addBorderButton = new QPushButton(tr("Add One Border")));
    editLayout -> addWidget(deleteFaceButton = new QPushButton(tr("Delete Face")));
    editLayout2 -> addWidget(addFaceButton = new QPushButton(tr("Add Polygon")));
    editLayout2 -> addWidget(zipButton = new QPushButton(tr("Zip 2 Mesh Borders")));
    editLayout2 -> addWidget(groupFacesButton = new QPushButton(tr("Group Faces")));
    undoLayout -> addWidget(undoAddButton = new QPushButton(tr("Undo Last Addition")));
    editLayout3 -> addWidget(groupFacesEdit = new QLineEdit(tr("meshName")));
    zipOptionsLayout -> addWidget(new QLabel(tr("Triangle Penalty")));
    zipOptionsLayout -> addWidget(trianglePaneltyEdit = new QLineEdit(tr("1.3")));

    modeLayout -> addLayout(addOrClearLayout = new QHBoxLayout);
    modeLayout-> addWidget(autoCorrectCheck = new QCheckBox(tr("Auto Correct Adding Face Oreinataion")));
    modeLayout-> addWidget(normalVect = new QCheckBox(tr("Show Normal Vector")));
    autoCorrectCheck -> setChecked(true);
    normalVect->setChecked(true);
    modeLayout-> addWidget(wholeBorderCheck = new QCheckBox(tr("Zip Whole Border Loop")));
    wholeBorderCheck -> setChecked(true);
    wholeBorderCheck -> setEnabled(false);
    //addOrClearLayout->addWidget(addTempToMasterButton = new QPushButton(tr("Add to Initial Mesh")));
    addOrClearLayout->addWidget(clearSelectionButton = new QPushButton(tr("Clear Selection")));
    modeLayout -> addWidget(consolidateButton = new QPushButton(tr("Consolidate Temp Mesh")));
    modeLayout -> addWidget(mergeButton = new QPushButton(tr("Merge All")));
    /* Subdivision layout. */
    //subdivLayout -> addLayout(subdivLevelLayout = new QHBoxLayout);
    //subdivLevelLayout -> addWidget(new QLabel("Level 0"));
    //subdivLevelLayout -> addWidget(subdivLevelSlider = new QSlider(Qt::Horizontal));
    //subdivLevelLayout -> addWidget(new QLabel("Level 5"));
    //subdivLayout -> addWidget(currentLevelLabel = new QLabel(tr("Current Subdivision Level:    0")));
    //subdivLevelSlider -> setMinimum(0);
    //subdivLevelSlider -> setMaximum(5);
    //subdivLevelSlider -> setValue(0);
    /* Offset Layout. */
    maxOffset = 0.005f;
    minOffset = 0.001f;
    offsetStep = 4;
    /*offsetLayout -> addLayout(offsetMinMaxLayout = new QHBoxLayout);
    offsetMinMaxLayout -> addWidget((new QLabel(tr("Min"))));
    offsetMinMaxLayout -> addWidget(minOffsetBox = new QLineEdit(QString::number(minOffset)));
    offsetMinMaxLayout -> addWidget((new QLabel(tr("Max"))));
    offsetMinMaxLayout -> addWidget(maxOffsetBox = new QLineEdit(QString::number(maxOffset)));
    offsetMinMaxLayout -> addWidget((new QLabel(tr("Step"))));
    offsetMinMaxLayout -> addWidget(offsetStepBox = new QLineEdit(QString::number(offsetStep)));
    offsetLayout -> addLayout(offsetValueLayout = new QHBoxLayout);
    offsetValueLayout -> addWidget(offsetValueSlider = new QSlider(Qt::Horizontal));
    offsetValueSlider -> setMinimum(0);
    offsetValueSlider -> setMaximum(offsetStep);
    offsetValueSlider -> setValue(0);
    offsetLayout -> addWidget(currentOffsetValueLabel = new QLabel(tr("Current Offset Value:    ")));*/
    /* Color Layout. */
    colorLayout -> addLayout(foreColorLayout = new QHBoxLayout);
    colorLayout -> addLayout(backColorLayout = new QHBoxLayout);
    colorLayout -> addLayout(outsideFacesColorLayout = new QHBoxLayout);
    colorLayout -> addLayout(insideFacesColorLayout = new QHBoxLayout);
    colorLayout -> addLayout(offsetFacesColorLayout = new QHBoxLayout);
    colorLayout -> setSpacing(2);
    foreColorLayout -> addWidget(foreColorButton = new QPushButton(tr("Foreground Color")));
    foreColorLayout -> addWidget(foreColorBox = new QWidget());
    foreColorBox -> resize(5,5);
    QPalette forePal = foreColorBox->palette();
    forePal.setColor(foreColorBox->backgroundRole(), QColor(*currSession->foreColor->r * 255.0,*currSession->foreColor->g * 255.0,*currSession->foreColor->b * 255.0));
    foreColorBox->setPalette(forePal);
    foreColorBox -> setAutoFillBackground(true);
    backColorLayout -> addWidget(backColorButton = new QPushButton(tr("Background Color")));
    backColorLayout -> addWidget(backColorBox = new QWidget());
    QPalette backPal = foreColorBox->palette();
    backPal.setColor(backColorBox->backgroundRole(), QColor(*currSession->backColor->r * 255.0,*currSession->backColor->g * 255.0,*currSession->backColor->b * 255.0));
    backColorBox->setPalette(backPal);
    backColorBox -> setAutoFillBackground(true);
    backColorBox -> resize(5,5);
    //
    outsideFacesColorLayout -> addWidget(outsideFacesColorButton = new QPushButton(tr("Outside Faces Color")));
    outsideFacesColorLayout -> addWidget(outsideFacesColorBox = new QWidget());
    QPalette outsideFacesPal = foreColorBox->palette();
    backPal.setColor(outsideFacesColorBox->backgroundRole(), QColor(*currSession->outsideColor->r * 255.0,*currSession->outsideColor->g * 255.0,*currSession->outsideColor->b * 255.0));
    outsideFacesColorBox->setPalette(backPal);
    outsideFacesColorBox -> setAutoFillBackground(true);
    outsideFacesColorBox -> resize(5,5);
    //
    insideFacesColorLayout -> addWidget(insideFacesColorButton = new QPushButton(tr("Inside Faces Color")));
    insideFacesColorLayout -> addWidget(insideFacesColorBox = new QWidget());
    QPalette insideFacesPal = foreColorBox->palette();
    backPal.setColor(insideFacesColorBox->backgroundRole(), QColor(*currSession->insideColor->r * 255.0,*currSession->insideColor->g * 255.0,*currSession->insideColor->b * 255.0));
    insideFacesColorBox->setPalette(backPal);
    insideFacesColorBox -> setAutoFillBackground(true);
    insideFacesColorBox -> resize(5,5);
    //
    offsetFacesColorLayout -> addWidget(offsetFacesColorButton = new QPushButton(tr("Offset Faces Color")));
    offsetFacesColorLayout -> addWidget(offsetFacesColorBox = new QWidget());
    QPalette offsetFacesPal = foreColorBox->palette();
    backPal.setColor(offsetFacesColorBox->backgroundRole(), QColor(*currSession->offsetColor->r * 255.0,*currSession->offsetColor->g * 255.0,*currSession->offsetColor->b * 255.0));
    offsetFacesColorBox->setPalette(backPal);
    offsetFacesColorBox -> setAutoFillBackground(true);
    offsetFacesColorBox -> resize(5,5);

    mainLayout -> addWidget(statusBar = new QStatusBar);
}

void ControlPanel::test(QString test)
{
	std::cout << test.toStdString() << std::endl;
}

void ControlPanel::test(bool checked)
{
	std::cout << "Hello!" << std::endl;
}

void ControlPanel::viewContentReset()
{
    viewContent ->setCurrentIndex(1);
}

void ControlPanel::viewContentSetToSubdiv(int level)
{
    viewContent -> setCurrentIndex(2);
    currentLevelLabel -> setText(tr("Current Subdivision Level:    "
                                    ) + QString::number(level));
}

void ControlPanel::resetMinOffset(QString minOffset)
{
    this->minOffset = minOffset.toFloat();
}

void ControlPanel::resetMaxOffset(QString maxOffset)
{
    this->maxOffset = maxOffset.toFloat();
}

void ControlPanel::resetOffsetStep(QString offsetStep)
{
    this->offsetStep = offsetStep.toInt();
    offsetValueSlider->setMaximum(this->offsetStep);
}

void ControlPanel::offSetSliderMoved()
{
    int value = offsetValueSlider ->value();
    float realOffsetValue = minOffset + (maxOffset - minOffset) / offsetStep * value;
    emit makeOffsetMesh(realOffsetValue);
    viewContent -> setCurrentIndex(3);
    currentOffsetValueLabel -> setText(tr("Current Offset Value:    "
                                          ) + QString::number(realOffsetValue));
}

void ControlPanel::viewContentSetToSubdivOffset()
{
    viewContent -> setCurrentIndex(4);
}

void ControlPanel::resetForeColor(bool)
{
    QColor newColor = QColorDialog::getColor();
    QPalette forePal = foreColorBox->palette();
    forePal.setColor(foreColorBox->backgroundRole(), newColor);
    foreColorBox->setPalette(forePal);
    canvas -> setForeColor(newColor);
}

void ControlPanel::resetBackColor(bool)
{
    QColor newColor = QColorDialog::getColor();
    QPalette backPal = backColorBox->palette();
    backPal.setColor(backColorBox->backgroundRole(), newColor);
    backColorBox->setPalette(backPal);
    canvas -> setBackColor(newColor);
}

void ControlPanel::resetInsideFacesColor(bool)
{
    QColor newColor = QColorDialog::getColor();
    QPalette insideFacesPal = insideFacesColorBox->palette();
    insideFacesPal.setColor(insideFacesColorBox->backgroundRole(), newColor);
    insideFacesColorBox->setPalette(insideFacesPal);
    canvas -> setInsideColor(newColor);
}

void ControlPanel::resetOffsetFacesColor(bool)
{
    QColor newColor = QColorDialog::getColor();
    QPalette offsetFacesPal = offsetFacesColorBox->palette();
    offsetFacesPal.setColor(offsetFacesColorBox->backgroundRole(), newColor);
    offsetFacesColorBox->setPalette(offsetFacesPal);
    canvas -> setOffsetColor(newColor);
}


void ControlPanel::resetOutsideFacesColor(bool)
{
    QColor newColor = QColorDialog::getColor();
    QPalette outsideFacesPal = outsideFacesColorBox->palette();
    outsideFacesPal.setColor(outsideFacesColorBox->backgroundRole(), newColor);
    outsideFacesColorBox->setPalette(outsideFacesPal);
    canvas -> setOutsideColor(newColor);
}

void ControlPanel::vertexModeChecked(bool checked)
{
    autoCorrectCheck->setEnabled(checked);
    wholeBorderCheck->setEnabled(!checked);
    statusBar -> showMessage(tr("Switch to Vertex Selection Mode"));
}

void ControlPanel::normalVectChecked(bool checked)
{
    currSession->normalVectShow = checked;
    canvas->repaintCanvas();
    //autoCorrectCheck->setEnabled(checked);
    //wholeBorderCheck->setEnabled(!checked);
    //statusBar -> showMessage(tr("Switch to Vertex Selection Mode"));
}


void ControlPanel::borderModeChecked(bool checked)
{
    autoCorrectCheck->setEnabled(!checked);
    wholeBorderCheck->setEnabled(checked);
    statusBar -> showMessage(tr("Switch to Border Selection Mode"));
}

void ControlPanel::faceModeChecked(bool checked)
{
    autoCorrectCheck->setEnabled(!checked);
    wholeBorderCheck->setEnabled(!checked);
    statusBar -> showMessage(tr("Switch to Face Selection Mode"));
}

void ControlPanel::pushMerge(bool)
{
    viewContent -> setCurrentIndex(1);
}

void ControlPanel::regenerateScene()
{
	currSession->updateFileContentSliders();

    //std::cout << "***Debug*** Here is the updated file content:" << std::endl;
    //std::cout << currSession->fileContent << std::endl;

	currSession->reset();
	currSession->parseSavedStr();
	//TODO: Urgent
	//mainWindow->recreateSliders();

	canvas->update();
}
