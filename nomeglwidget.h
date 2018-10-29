/**
 * @author Andy Wang, UC Berkeley.
 * Copyright 2016 reserve.
 * UC Berkeley, Slide_2016 project.
 * Advised by Prof. Sequin H. Carlos.
 */

#pragma once

#include "newNOME/Session.h"
#include "newNOME/ConsolidateWindow.h"
#include "newNOME/GroupWindow.h"

#include <glm/glm.hpp>

#include <QMainWindow>
#include <QOpenGLWidget>
#include <QMessageBox>
#include <QColor>
#include <QString>

class SlideGLWidget: public QOpenGLWidget
{
    Q_OBJECT

public:
    explicit SlideGLWidget(QWidget *parent = 0);
    SlideGLWidget(std::string name, QWidget *parent = 0);
	SlideGLWidget(QWidget* parent, Session* session);
    ~SlideGLWidget();
    ConsolidateWindow *conWindow;
    GroupWindow *groupWindow;

    /**
     * Save the current master_mesh in a STL file.
     */
    void saveMesh(std::string name);
    /**
     * @brief subdivide: for certain level.
     * @param level, level of subdivision.
     */
    void subdivide(int level);
    /**
     * @brief offset: create offset mesh with given value.
     * @param value: the value of this offset.
     */
    void offset(float value);
    /**
     * @brief setForeColor, set default foreground color.
     * @param color, the color to be set.
     */
    void setForeColor(QColor color);
    /**
     * @brief setBackColor, set default background color.
     * @param color, the color to be set.
     */
    void setBackColor(QColor color);

    void setOutsideColor(QColor color);
    void setInsideColor(QColor color);
    void setOffsetColor(QColor color);

    /* Update the canvas after reading in the aslf file. */
    void updateFromSavedMesh();
    /* Set the in_editing_mode of scene shown and all leave meshes.*/
    void set_to_editing_mode(bool in_editing_mode);
    /* Record the list of the name of faces deleted by the user.
     * (Not including the consolidated mesh or temprary mesh. */
	std::vector<std::string> deletedFaces;
public:
    std::string consolidateMeshName;
    std::string consolidateInstanceName;
    Session *currSession;
    /* Viewer variables.*/
    enum MODES { MODE_OBJECT, MODE_CAMERA, MODE_LIGHT, MODE_LAST } view_mode;
    glm::mat4 transforms[MODE_LAST];
    float cameraDistance;
    float centerX, centerY, centerZ;
    /* Support arcball feature.*/
    int last_mx, last_my, cur_mx, cur_my;
    /* Support arcball feature. */
    int arcball_on;
    /* object2world matrix for arcball.*/
	glm::mat4 object2world;
    /* control of the wireframe mode. */
    bool wireframe;
    /* control of the backface illuminiation. */
    bool backface;
    /* control of the shading mode. */
    bool smoothshading;
    /**
     * @brief makeDefaultMesh: Make a default mesh of a cube.
     */
    void makeDefaultMesh();
    /**
     * @brief makeSIFMesh: Make a mesh by reading in a SIF file.
     * @param name: The path to the input file.
     */
    void makeSIFMesh(std::string name);
    /**
     * @brief makeSLFMesh: Make a mesh by the output of SLF file parser.
     */
    void makeSLFMesh();

    /**
     * Get a normalized vector from the center of the virtual ball O to a
     * point P on the virtual ball surface, such that P is aligned on
     * screen's (X,Y) coordinates.  If (X,Y) is too far away from the
     * sphere, return the nearest point on the virtual ball surface.
     */
    glm::vec3 get_arcball_vector(int x, int y);
    /**
     * A wrapper function for selection with mouse
     * @param x, the x coordinate of the mouse clicked
     * @param y, the y coordinate of the mouse clicked
     * @param mode, the mode of selection.
     */
    void mouse_select(int x, int y);
    /**
     * selection_mode = 0: face selection;
     * selection_mode = 1: vertex selection
     * selection_mode = 2: whole border selection (line loop)
     * selection_mode = 3: partial border selection (line strip)
     */
    int selection_mode;
    /* Called by constructor to setup general background parameters. */
    void generalSetup();
    /* A message box that deliver error message.*/
    QMessageBox *errorMsg;
    /* Zoom in in the current view. */
    void zoom_in();
    /* Zoom out in the current view. */
    void zoom_out();
    /*
     * The foreground color.
     */
    QColor foreColor;
    /*
     * The background color.
     */
    QColor backColor;
    QColor outsideColor;
    QColor insideColor;
    QColor offsetColor;
    /*
     * The temp mesh color.
     */
    QColor tempColor;
    /* Auto check if the newly added face can have
     * same orientation with master_mesh. */
    bool auto_check;
    /* Check if whole border selection is on.*/
    bool whole_border;

    /**
     * @brief clearSubDivisionAndOffset: Clear the subdiv_mesh
     * and offset_mesh.
     */
    void clearSubDivisionAndOffset();
    /**
     * @brief clearSelection: clear the selected items.
     */
    void clearSelection();

    /* Index list of where the name buffer start for every mesh.*/
    vector<int> global_name_index_list;
    /* Index list of where the name buffer start for every polyline.*/
    vector<int> global_polyline_name_index_list;
    /* Update the global name index list.*/
    void updateGlobalIndexList();
    /* The trianglePanelty for zipping function. */
    float trianglePanelty;
    /* Create the hierarchical_scene_transformed. */
    void transform_meshes_in_scene();
    /* The current mode of view.
     * 1: Hierarchical Scene.
     * SLF will read in the scene with parameters set up.
     * SIF will read in just one mesh.
     * This is the interactive editing mode.
     * 2: Merged Modified Mesh
     * This is the merged result of the modified mesh. It is a perfect
     * 2-manifold to serve as the input of the subdivision.
     * 3: Subdivied Mesh
     * 4: Offseted Mesh
     */
    int viewer_mode;

    /* Current work phase. */
    int work_phase;
    /* The current subdivision level.*/
    int subdiv_level;
    /* The current offset value. */
    float offset_value;
    /* Merge all meshes from global_mesh_list into master_mesh.*/
    void mergeAll();
    /* Update the temprary mesh.*/
    void updateTempMesh();
    /* Update the consolidate mesh.*/
    void updateConsolidateMesh();
    /* Update the saved consolidated mesh. */
    void updateSavedConsolidatedMesh();
protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    void paintGLImpl();
    void mousePressEvent(QMouseEvent*) override;
    void mouseMoveEvent(QMouseEvent*) override;
    void keyPressEvent(QKeyEvent*) override;
    /**
     * @brief timerEvent: Timer Event for this MainWindow.
     * Similar to OnIdleFunc of GLUT.
     */
    void timerEvent(QTimerEvent *event) override;
    /**
     * @brief wheelEvent: Handles mouse wheel event.
     * Will zoom in or zoom out in the scene.
     * @param event: The qt wheel event.
     */
    void wheelEvent(QWheelEvent *event) override;
public slots:
    /**
     * @brief viewContentChanged: Change the current view mesh.
     * @param viewer_mode, the mode for the viewer.
     */

    void createConsolidated(bool);
    void readConsolidateMeshName(QString text);
    void readConsolidateInstanceName(QString text);
    void viewContentChanged(int viewer_mode);
    /* Receive the signal from control panel to do subdivision.*/
    void levelChanged(int);
    /* Receive the signal to reset the viewing direction. */
    void resetViewDirection(bool);
    /* Receive the signal of offset value changed. */
    void offsetValueChanged(float);
    /* Recevie the signal of changing to vertex selection mode. */
    void vertexModeChecked(bool);
    /* Recevie the signal of changing to border selection mode. */
    void borderModeChecked(bool);
    /* Recevie the signal of changing to face selection mode. */
    void faceModeChecked(bool);
    /* Receive the signal auto correct orientation in adding mode. */
    void autoCorrectChecked(bool);
    void repaintCanvas();
    /* Receive the signal whole border selection in zipping mode. */
    void wholeBorderSelectionChecked(bool);
    /* Receive the signal to add a polygon to temp_mesh. */
    void addToTempCalled(bool);
    void groupFacesMsg(bool);
    void undoFaceCalled(bool);
    void addToPolylineCalled(bool);
    /* Receive the signal to zip two borders.
     * And add the result polygons to temp_mesh. */
    void zipToTempCalled(bool);
    /* Recieve signal to add the temp_mesh to master_mesh.*/
    void addTempToMasterCalled(bool);
    /* Recieve signal to add the temp_mesh to consolidated_mesh. */
    void popUpConsolidateWindow(bool);

    void popUpGroupWindow(bool);
    /* Add temp_mesh to master_mesh. */
    void addTempToMaster();
    /* Receive the signal to add a border. Add border1 first*/
    void addBorderCalled(bool);
    /* Receive the signal to clear all selections.
     * Including selected vertices and border. */
    void clearSelectionCalled(bool);
    /* Reset the triangle panelty of zipping function. */
    void resetTrianglePanelty(QString);
    /* @brief mergeCalled: Recieve the signal from control panel to merge. */
    void mergeCalled(bool);
    /* Slider value changed.*/
    void paramValueChanged(float);
    /* Delete the selected faces called. */
    void deleteFaceCalled(bool);
signals:
    /* A feedback signal send back to control panel statusBar.*/
    void feedback_status_bar(QString, int);
};
