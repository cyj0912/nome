/**
 * @author Andy Wang, UC Berkeley.
 * Copyright 2016 reserve.
 * UC Berkeley, NOME project.
 * Advised by Prof. Sequin H. Carlos.
 */

#pragma once

#include <QWidget>
#include <iostream>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QSlider>
#include <QGroupBox>
#include <QRadioButton>
#include <QPushButton>
#include <QComboBox>
#include <QColorDialog>
#include <QLineEdit>
#include <QStatusBar>
#include <QCheckBox>

class SlideGLWidget;
class Session;
class CMainWindow;

class ControlPanel : public QWidget
{
    Q_OBJECT

public:
    ControlPanel();
    /* @param canvas, the canvas that this panel control.*/
    ControlPanel(CMainWindow* parentWindow, SlideGLWidget * canvas, Session* currSession);
    /* Set up the layout and widgets.*/
    void setupLayout();
    /* Build the connections. */
    void buildConnection();
    /* The selection mode of current program.
     * 1: vertex selection.
     * 2: whole border secletion.
     * 3: partial border selection.
     */
    int selectionMode;
    /* The subdivision level.*/
    int subdivLevel;
    /* Offset value. */
    float offsetValue;
    Session* currSession;
private:
	CMainWindow * mainWindow;
    SlideGLWidget *canvas;
    /* Widgets and Layout in this Control Panel.*/
    QVBoxLayout *mainLayout;
    QVBoxLayout *viewLayout;
    QGroupBox *modeGroupBox;
    QVBoxLayout *modeLayout;
    QHBoxLayout *modeSelectLayout;
    QHBoxLayout *selectionLayout;
    QHBoxLayout *editLayout;
    QHBoxLayout *editLayout2;
    QHBoxLayout *editLayout3;
    QHBoxLayout *undoLayout;
    QRadioButton *vertexModeButton;
    QRadioButton *faceModeButton;
    QRadioButton *borderModeButton;
    QPushButton *addFaceButton;
    QPushButton *deleteFaceButton;
    QPushButton *addBorderButton;
    QPushButton *addPolylineButton;
    QPushButton *groupFacesButton;
    QPushButton *undoAddButton;
    QPushButton *zipButton;
    QCheckBox *autoCorrectCheck;
    QCheckBox *normalVect;
    QCheckBox *wholeBorderCheck;
    QHBoxLayout *zipOptionsLayout;
    QLineEdit *trianglePaneltyEdit;
    QLineEdit *groupFacesEdit;
    QHBoxLayout *addOrClearLayout;
    //QPushButton *addTempToMasterButton;
    QPushButton *clearSelectionButton;
    QVBoxLayout *subdivLayout;
    QVBoxLayout *offsetLayout;
    QVBoxLayout *colorLayout;
    QComboBox *viewContent;
    QPushButton *resetViewButton;
    QPushButton *consolidateButton;
    QPushButton *mergeButton;
    QHBoxLayout *subdivLevelLayout;
    QLabel *currentLevelLabel;
    QSlider *subdivLevelSlider;
    QHBoxLayout *offsetMinMaxLayout;
    QHBoxLayout *offsetValueLayout;
    QSlider *offsetValueSlider;
    QLabel *currentOffsetValueLabel;
    QHBoxLayout *foreColorLayout;
    QHBoxLayout *backColorLayout;
    QHBoxLayout *outsideFacesColorLayout;
    QHBoxLayout *insideFacesColorLayout;
    QHBoxLayout *offsetFacesColorLayout;
    QPushButton *foreColorButton;
    QWidget *foreColorBox;
    QPushButton *backColorButton;
    QPushButton *outsideFacesColorButton;
    QWidget *outsideFacesColorBox;
    QPushButton *insideFacesColorButton;
    QWidget *insideFacesColorBox;
    QPushButton *offsetFacesColorButton;
    QWidget *offsetFacesColorBox;
    QWidget *backColorBox;
    float minOffset;
    float maxOffset;
    int offsetStep;
    QLineEdit *minOffsetBox;
    QLineEdit *maxOffsetBox;
    QLineEdit *offsetStepBox;
    QStatusBar *statusBar;

	QPushButton *sceneRegenButton;
public slots:
    void test(QString test);
    void test(bool);
    void viewContentReset();
    void viewContentSetToSubdiv(int level);
    void viewContentSetToSubdivOffset();
    void resetMinOffset(QString minOffset);
    void resetMaxOffset(QString maxOffset);
    void resetOffsetStep(QString offsetStep);
    void offSetSliderMoved();
    void resetForeColor(bool);
    void resetBackColor(bool);
    void resetInsideFacesColor(bool);
    void resetOutsideFacesColor(bool);
    void resetOffsetFacesColor(bool);
    void vertexModeChecked(bool);
    void normalVectChecked(bool);
    void borderModeChecked(bool);
    void faceModeChecked(bool);
    void pushMerge(bool);
	void regenerateScene();
signals:
    void makeOffsetMesh(float);
};
