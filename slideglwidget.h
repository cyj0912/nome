/**
 * @author Andy Wang, UC Berkeley.
 * Copyright 2016 reserve.
 * UC Berkeley, Slide_2016 project.
 * Advised by Prof. Sequin H. Carlos.
 */

#ifndef SLIDEGLWIDGET_H
#define SLIDEGLWIDGET_H

#include <QMainWindow>
#include <QtOpenGL>
#define ROTATION_SPEED (1.0)
#if __linux__
 #include <GL/glut.h>
 #include <GL/gl.h>
 #define ROTATION_SPEED (50.0)
#elif __APPLE__
 #include <GLUT/GLUT.h>
 #define ROTATION_SPEED (1.0)
#endif
#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
#endif
#include "mesh.h"
#include "makeMesh.h"
#include "polyline.h"
#include "myselection.h"
#include "subdivison.h"
#include "stl.h"
#include "offset.h"
#include "zipper.h"
#include <QMessageBox>
#include <QColor>
#include <QString>
class SlideGLWidget: public QGLWidget
{
    Q_OBJECT

public:
    explicit SlideGLWidget(QWidget *parent = 0);
    /**
     * @param name the path of the file.
     * @param i, i = 0 is the SIF file, i = 1 is the SLF file.
     */
    SlideGLWidget(string name, int i, QWidget *parent = 0);
    ~SlideGLWidget();
    /**
     * Save the current master_mesh in a STL file.
     */
    void saveMesh(string name);
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
private:
    /* Viewer variables.*/
    enum MODES { MODE_OBJECT, MODE_CAMERA, MODE_LIGHT, MODE_LAST } view_mode;
    mat4 transforms[MODE_LAST];
    float cameraDistance;
    /* Support arcball feature.*/
    int last_mx, last_my, cur_mx, cur_my;
    /* Support arcball feature. */
    int arcball_on;
    /* object2world matrix for arcball.*/
    mat4 object2world;
    /* control of the wireframe mode. */
    bool wireframe;
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
    void makeSIFMesh(string name);
    /**
     * @brief makeSLFMesh: Make a mesh by reading in a SLF file.
     * @param name: The path to the input file.
     */
    void makeSLFMesh(string name);
    /*
     * The master mesh. As a result of SIF parser.
     * Or as a result of merging the scene.
     */
    Mesh master_mesh;
    /*
     * The working mesh that the user modified.
     * Can be merged into the master mesh.
     */
    Mesh temp_mesh;
    /* A subdivider to handle subdivision.*/
    Subdivision *subdivider;
    /* An offseter to handle offsetting.*/
    Offset *offseter;
    /* A pointer to the subdivided mesh. */
    Mesh subdiv_mesh;
    /**
     * The cache of mesh that has been subdivided.
     * The index in this vector = subdivision level - 1.
     */
    vector<Mesh> cache_subdivided_meshes;
    /* A pointer to the offset mesh. */
    Mesh offset_mesh;
    /* A pointer to the subdivided offset mesh. */
    Mesh subdiv_offset_mesh;
    /* A pointer to the current view mesh. */
    Mesh *view_mesh;
    /* Selection object to handle mouse selection.*/
    MySelection mySelect;
    /**
     * Get a normalized vector from the center of the virtual ball O to a
     * point P on the virtual ball surface, such that P is aligned on
     * screen's (X,Y) coordinates.  If (X,Y) is too far away from the
     * sphere, return the nearest point on the virtual ball surface.
     */
    vec3 get_arcball_vector(int x, int y);
    /**
     * A wrapper function for selection with mouse
     * @param x, the x coordinate of the mouse clicked
     * @param y, the y coordinate of the mouse clicked
     * @param mode, the mode of selection.
     */
    void mouse_select(int x, int y);
    /**
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
     * The default foreground color.
     */
    QColor foreColor;
    /*
     * The default background color.
     */
    QColor backColor;
    /* Auto check if the newly added face can have
     * same orientation with master_mesh. */
    bool auto_check;
    /* Check if whole border selection is on.*/
    bool whole_border;
    /* The zipper.*/
    Zipper *zipper;
    /* The first border to zip.*/
    PolyLine border1;
    /* The second border to zip. */
    PolyLine border2;
    /**
     * @brief clearSubDivisionAndOffset: Clear the subdiv_mesh
     * and offset_mesh.
     */
    void clearSubDivisionAndOffset();
    /**
     * @brief clearSelection: clear the selected items.
     */
    void clearSelection();
    /* A flattened view of meshes in the current scene. */
    vector<Mesh*> global_mesh_list;
    /* Index list of where the name buffer start for every mesh.*/
    vector<int> global_name_index_list;
    /* Update the global name index list.*/
    void updateGlobalIndexList();
    /* A wrapper class to draw the whole scene. */
    void drawScene();
    /* The trianglePanelty for zipping function. */
    float trianglePanelty;
protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void mousePressEvent(QMouseEvent*);
    void mouseMoveEvent(QMouseEvent*);
    void keyPressEvent(QKeyEvent*);
    /**
     * @brief timerEvent: Timer Event for this MainWindow.
     * Similar to OnIdleFunc of GLUT.
     */
    void timerEvent(QTimerEvent *event);
    /**
     * @brief wheelEvent: Handles mouse wheel event.
     * Will zoom in or zoom out in the scene.
     * @param event: The qt wheel event.
     */
    void wheelEvent(QWheelEvent *event);
public slots:
    /**
     * @brief viewContentChanged: Change the current view mesh.
     * @param view_content:
     * 0 for hirachical scene
     * 1 for master mesh
     * 2 for subdivision mesh
     * 3 for offset mesh
     * 4 for subdivision on offset mesh
     */
    void viewContentChanged(int);
    /* Receive the signal from control panel to do subdivision.*/
    void levelChanged(int);
    /* Receive the signal to reset the viewing direction. */
    void resetViewDirection(bool);
    /* Receive the signal of offset value changed. */
    void offsetValueChanged(float);
    /* Recevie the signal of changing to add mode. */
    void addModeChecked(bool);
    /* Recevie the signal of changing to zip mode. */
    void zipModeChecked(bool);
    /* Receive the signal auto correct orientation in adding mode. */
    void autoCorrectChecked(bool);
    /* Receive the signal whole border selection in zipping mode. */
    void wholeBorderSelectionChecked(bool);
    /* Receive the signal to add a polygon to temp_mesh. */
    void addToTempCalled(bool);
    /* Receive the signal to zip two borders.
     * And add the result polygons to temp_mesh. */
    void zipToTempCalled(bool);
    /* Recieve signal to add the temp_mesh to master_mesh.*/
    void addTempToMasterCalled(bool);
    /* Add temp_mesh to master_mesh. */
    void addTempToMaster();
    /* Receive the signal to add a border. Add border1 first*/
    void addBorderCalled(bool);
    /* Receive the signal to clear all selections.
     * Including selected vertices and border. */
    void clearSelectionCalled(bool);
    /* Reset the triangle panelty of zipping function. */
    void resetTrianglePanelty(QString);
signals:
    /* A feedback signal send back to control panel statusBar.*/
    void feedback_status_bar(QString, int);
};

#endif // SLIDEGLWIDGET_H
