/**
 * @author Andy Wang, UC Berkeley.
 * Copyright 2016 reserve.
 * UC Berkeley, Slide_2016 project.
 * Advised by Prof. Sequin H. Carlos.
 */

#include "nomeparser.h"

#include "nomeglwidget.h"
#include "newNOME/ConsolidateWindow.h"
#include "newNOME/GroupWindow.h"
#include "newNOME/Reader.h"
#include "newNOME/Data.h"
#include "newNOME/MeshNew.h"
#include "newNOME/GroupNew.h"
#include "newNOME/BankNew.h"
#include "newNOME/PolylineNew.h"
#include "newNOME/BSplineNew.h"
#include "newNOME/BezierCurveNew.h"
#include "newNOME/CircleNew.h"
#include "newNOME/FunnelNew.h"
#include "newNOME/TunnelNew.h"
#include "newNOME/SubdivisionNew.h"
#include "newNOME/OffsetNew.h"

SlideGLWidget::SlideGLWidget(QWidget *parent) :
    QGLWidget(parent)
{
    generalSetup();
    makeDefaultMesh();
    updateGlobalIndexList();
}

SlideGLWidget::SlideGLWidget(string name, QWidget *parent) :
    QGLWidget(parent)
{
    generalSetup();
    makeSIFMesh(name);
    updateGlobalIndexList();
}

SlideGLWidget::SlideGLWidget(Group &group, Session *currSession, QWidget *parent) :
    QGLWidget(parent)
{
    this->currSession = currSession;
    generalSetup();
    //makeDefaultMesh();
    //hierarchical_scene = &group;
    //makeSLFMesh();
    //updateGlobalIndexList();
}

void SlideGLWidget::generalSetup()
{
    startTimer(0);
    cameraDistance = 4;
    centerX = centerY = centerZ = 0;
    last_mx = last_my = cur_mx = cur_my = 0;
    arcball_on = false;
    wireframe = false;
    backface = true;
    smoothshading = false;
    selection_mode = 1;
    object2world = mat4(1);
    /*foreColor = QColor(255,0,0);
    backColor = QColor(0,0,0);
    outsideColor = QColor(255,0,0);
    insideColor = QColor(0,0,255);*/
    //currSession->outsideColor = outsideColor;
    //currSession->insideColor = insideColor;
    tempColor = QColor(255, 255, 0);
    whole_border = true;
    errorMsg = new QMessageBox();
    resize(600, 480);
    viewer_mode = 0;
    work_phase = 0;
    temp_mesh.color = Qt::yellow;
    temp_mesh.clear();
    temp_mesh.type = 99;
    consolidate_mesh.color = QColor(255, 69, 0);
    consolidate_mesh.clear();
    consolidate_mesh.isConsolidateMesh = true;
    consolidate_mesh.type = 99;
    group_from_consolidate_mesh = NULL;
    trianglePanelty = 1.3;
}

void SlideGLWidget::makeDefaultMesh()
{
    makeCube(master_mesh,0.5,0.5,0.5);
    master_mesh.computeNormals();
    master_mesh.color = foreColor;
    global_mesh_list.push_back(&master_mesh);
    global_mesh_list.push_back(&consolidate_mesh);
    global_mesh_list.push_back(&temp_mesh);
}

void SlideGLWidget::makeSIFMesh(string name)
{
    /* Figure out the QuadSIF or SIF later.*/
    makeWithSIF(master_mesh,name);
    //makeWithQuadSIF(master_mesh,name);
    master_mesh.computeNormals();
    master_mesh.color = foreColor;
    global_mesh_list.push_back(&master_mesh);
    global_mesh_list.push_back(&consolidate_mesh);
    global_mesh_list.push_back(&temp_mesh);
}

void SlideGLWidget::makeSLFMesh()
{
    hierarchical_scene_transformed.clearAndDelete();
    hierarchical_scene_transformed = hierarchical_scene->makeCopyForTransform();
    transform_meshes_in_scene();
    hierarchical_scene_transformed.setColor(foreColor);
    hierarchical_scene_transformed.assignColor();
    hierarchical_scene_transformed.updateGroupElementName();
}

void SlideGLWidget::transform_meshes_in_scene()
{
    hierarchical_scene_transformed.updateCopyForTransform();
    global_mesh_list = hierarchical_scene_transformed.flattenedMeshes();
    global_polyline_list = hierarchical_scene_transformed.flattenedPolylines();

    global_mesh_list.push_back(&consolidate_mesh);
    global_mesh_list.push_back(&temp_mesh);
}

void SlideGLWidget::mergeAll()
{
    work_phase = glm::max(work_phase, 1);
    global_mesh_list.pop_back();
    merged_mesh.clearAndDelete();
    merged_mesh = merge(global_mesh_list);
    global_mesh_list.push_back(&temp_mesh);
    merged_mesh.color = foreColor;
    merged_mesh.computeNormals();
}

void SlideGLWidget::mergeCalled(bool)
{
    viewer_mode = 1;
    currSession->recalculateOffset = true;
    currSession->recalculateSubdivision = true;
    currSession->recalculateSlider = true;

    //std::cout << "HELLO" << std::endl;
    //mergeAll();
    repaint();
}

void SlideGLWidget::saveMesh(string name)
{
    // Figure out the QuadSIF or SIF later/
    STL *stl = new STL;
    if(!offset_mesh.isEmpty()) {
        stl -> STLOutput(offset_mesh, name);
    } else {
        emit feedback_status_bar(tr("Offset is empty, can't save file!"),0);
    }
}

vec3 SlideGLWidget::get_arcball_vector(int x, int y)
{
    vec3 p = vec3(1.0 * x / this->width() * 2 - 1.0,
      1.0 * y / this->height() * 2 - 1.0, 0);
    p.y = - p.y;
    float op_squared = p.x * p.x + p.y * p.y;
    if (op_squared <= 1 * 1) {
        p.z = sqrt(1 * 1 - op_squared);
    } else {
        p = normalize(p);  // nearest point
    }
    return p;
}

void SlideGLWidget::set_to_editing_mode(bool in_editing_mode)
{
    hierarchical_scene_transformed.in_editing_mode = in_editing_mode;
    for(Mesh*& mesh : global_mesh_list)
    {
        mesh->in_editing_mode = in_editing_mode;
    }
}

void SlideGLWidget::mouse_select(int x, int y)
{
    if(viewer_mode != 0) {
        return;
    }

    GLuint buff[64] = {0};
    GLint hits, view[4];
    GLdouble modelview[16];
    GLdouble projection[16];
    GLfloat winX, winY, winZ;
    GLdouble posX, posY, posZ;
    GLdouble camX, camY, camZ;

    set_to_editing_mode(true);
    glGetIntegerv(GL_VIEWPORT, view);
    // Find the 3D points of the current clicked point
    glGetDoublev(GL_MODELVIEW_MATRIX, modelview );
    glGetDoublev(GL_PROJECTION_MATRIX, projection );
    winX = (double) x;
    winY = (double) view[3] - (double)y;
    glReadPixels( x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ );
    gluUnProject( winX, winY, winZ, modelview, projection,
                  view, &posX, &posY, &posZ);
    gluUnProject(winX, winY, -1.0f, modelview, projection, view, &camX, &camY, &camZ);

    if (selection_mode == 1)
    {
        Vector3 camPos = Vector3(camX, camY, camZ);
        Vector3 targetPos = Vector3(posX, posY, posZ);
        Vector3 dir = targetPos - camPos;
        dir.Normalize();

        float distMax = FLT_MAX;
        Vert* selectedVertex = nullptr;

        Ray mouseRay = Ray(camPos, dir);
        vector<OctreeProxy*> rayIntersectResults;
        currSession->getOctreeRoot()->findNodes(mouseRay, rayIntersectResults);
        for (OctreeProxy* proxy : rayIntersectResults)
        {
            auto* vertProxy = dynamic_cast<VertOctreeProxy*>(proxy);
            if (vertProxy)
            {
                float hitDistance = mouseRay.HitDistance(vertProxy->getWorldAABB());
                if (hitDistance < distMax)
                {
                    distMax = hitDistance;
                    selectedVertex = vertProxy->getOwner();
                }
            }
        }
        if (selectedVertex)
        {
            Reader* currReader = createReader(currSession);
            //std::cout << "hello" << std::endl;
            //std::cout << distMax << std::endl;
            //std::cout << selectedVertex->index << std::endl;
            std::cout << currReader->getVertName(selectedVertex->index) << std::endl;
            //std::cout << "bye" << std::endl;
            selectedVertex->selected = !selectedVertex->selected;
            if (selectedVertex -> selected == true) {
                currSession->selectedVerts.push_back(selectedVertex);
            }
            else {
                currSession->selectedVerts.remove(selectedVertex);
            }
            update();
        }
        return;
    } else if(selection_mode == 2){
        // Select Border
        Vector3 camPos = Vector3(camX, camY, camZ);
        Vector3 targetPos = Vector3(posX, posY, posZ);
        Vector3 dir = targetPos - camPos;
        dir.Normalize();

        float distMax = FLT_MAX;
        Vert* selectedVertex = nullptr;

        Ray mouseRay = Ray(camPos, dir);
        vector<OctreeProxy*> rayIntersectResults;
        currSession->getOctreeRoot()->findNodes(mouseRay, rayIntersectResults);
        for (OctreeProxy* proxy : rayIntersectResults)
        {
            //cout << proxy->toString() << endl;
            auto* vertProxy = dynamic_cast<VertOctreeProxy*>(proxy);
            if (vertProxy)
            {
                float hitDistance = mouseRay.HitDistance(vertProxy->getWorldAABB());
                if (hitDistance < distMax)
                {
                    distMax = hitDistance;
                    selectedVertex = vertProxy->getOwner();
                }
            }
        }

        if (selectedVertex)
        {
            std::tuple<std::vector<Vert*>, std::vector<EdgeNew*>> loopInfo = currSession->findBorder(selectedVertex);
            std::vector<Vert*> loop = std::get<0>(loopInfo);

            //set<Vert*> s( loop.begin(), loop.end() );
            //loop.assign( s.begin(), s.end() );

            std::vector<EdgeNew*> eloop = std::get<1>(loopInfo);
            //set<EdgeNew*> es( eloop.begin(), eloop.end() );
            //eloop.assign( es.begin(), es.end() );

            if (currSession->isBorderSelected == true){
                for (Vert* v : std::get<0>(currSession->tmpBorder)){
                    v->selected = false;
                }
                for (EdgeNew* e : std::get<1>(currSession->tmpBorder)){
                    e->selected = false;
                }
            }

            for (Vert* v : loop){
                v->selected = true;
                /*if (v -> selected == true) {
                    currSession->selectedVerts.push_back(v);
                }*/
            }
            for (EdgeNew* e : eloop){
                e->selected = true;
            }



            currSession->tmpBorder = std::make_tuple(loop, eloop);
            currSession->isBorderSelected = true;
            update();
        }

        return;
    }

    glSelectBuffer(64, buff);
    // Find the face selected.
    glRenderMode(GL_SELECT);
    //glClearColor(0, 0, 0, 1);
    glInitNames();
    glPushName(0);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluPickMatrix(x, view[3] - y, 1.0, 1.0, view);
    gluPerspective(45, (float) this -> width() / this -> height(), 0.1, 100);
    glMatrixMode(GL_MODELVIEW);
    paintGLImpl();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    hits = glRenderMode(GL_RENDER);

    if(selection_mode == 0)
    {
        currSession->selectFace(hits, buff, posX, posY, posZ);
    }
    else if(selection_mode == 1)
    {
        currSession->selectVert(hits, buff, posX, posY, posZ);
    }
    else if(selection_mode == 2)
    {
        currSession->selectBorder(hits, buff, posX, posY, posZ);
        mySelect.selectWholeBorder(global_mesh_list,
                                   global_polyline_list,
                                   global_name_index_list,
                                   global_polyline_name_index_list,
                                   hits, buff, posX, posY, posZ);
    }
    else if(selection_mode == 3)
    {
        /*mySelect.selectPartialBorder(global_mesh_list,
                                     global_polyline_list,
                                     global_name_index_list,
                                     global_polyline_name_index_list,
                                     hits, buff, posX, posY, posZ);*/
    }
    glMatrixMode(GL_MODELVIEW);
    repaint();
}

SlideGLWidget::~SlideGLWidget()
{

}

void SlideGLWidget::initializeGL()
{
    //Smooth Shading
    glShadeModel(GL_SMOOTH);
    // Two sided pr ones side;
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    //glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    //glEnable(GL_LIGHT1);

    GLfloat light_ambient0[] = { 0.3f, 0.3f, 0.3f, 0.0f };
    GLfloat light_diffuse0[] = { 0.6f, 0.6f, 0.6f, 0.0f };
    GLfloat light_specular0[] = { 0.0f, 0.0f, 0.0f, 0.0f };
    GLfloat light_position0[] = { 1, 1, 1, 0.0 };

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse0);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position0);

    GLfloat light_ambient1[] = { 0.0f, 0.0f, 0.0f, 0.0f };
    GLfloat light_diffuse1[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    GLfloat light_specular1[] = { 0.0f, 0.0f, 0.0f, 0.0f };
    GLfloat light_position1[] = { -1, -1, -1, 0.0 };

    glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse1);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular1);
    glLightfv(GL_LIGHT1, GL_POSITION, light_position1);

    transforms[MODE_CAMERA] = lookAt(vec3(0.0,  0.0, 10.0),
                                     vec3(0.0,  0.0, 0.0),
                                     vec3(0.0,  1.0, 0.0));
}

void SlideGLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, (float) w / h, 0.1, 100);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void SlideGLWidget::draw_mesh(int start_index, Mesh *mesh)
{
    mesh -> drawMesh(start_index, smoothshading);
}

void SlideGLWidget::draw_polyline(int start_index, PolyLine *polyline)
{
    QColor color = polyline -> color;
    GLfloat fcolor[] = {1.0f * color.red() / 255,
                        1.0f * color.green() / 255,
                        1.0f * color.blue() / 255,
                        1.0f * color.alpha() /255};
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, fcolor);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, fcolor);
    polyline -> drawLineWithCubes(start_index);
}

void SlideGLWidget::draw_scene()
{
    vector<PolyLine*>::iterator pIt;
    vector<Mesh*>::iterator mIt;
    vector<int>::iterator nIt;
    for(mIt = global_mesh_list.begin(), nIt = global_name_index_list.begin();
        nIt < global_name_index_list.end(); nIt++, mIt++)
    {
        draw_mesh(*nIt, *mIt);
    }
    for(pIt = global_polyline_list.begin(),  nIt = global_polyline_name_index_list.begin();
        pIt != global_polyline_list.end(); nIt++, pIt++)
    {
        draw_polyline(*nIt, *pIt);
    }
    GLfloat afcolor[] = {0.0f, 1.0f, 1.0f, 1.0f};
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, afcolor);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, afcolor);
    for(mIt = global_mesh_list.begin(); mIt != global_mesh_list.end(); mIt++)
    {
        Mesh * currentMesh = (*mIt);
        currentMesh -> drawVertices();
    }
    for(pIt = global_polyline_list.begin(); pIt != global_polyline_list.end(); pIt++)
    {
        PolyLine * currentPolyline = (*pIt);
        currentPolyline -> drawVertices();
    }
    if(!border1.isEmpty() || !border2.isEmpty())
    {
        glLineWidth(4.0);
        border1.drawLine();
        if(!border2.isEmpty()) {
            border2.drawLine();
        }
        glLineWidth(1.0);
    }
}

void SlideGLWidget::paintGL()
{
    paintGLImpl();
}

void SlideGLWidget::paintGLImpl()
{
    glClearColor(1.0f * *currSession->backColor->r,
                 1.0f * *currSession->backColor->g,
                 1.0f * *currSession->backColor->b,
                 1.0f * 255 / 255);
    glClearDepth(1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0, 0, cameraDistance, centerX, centerY, centerZ, 0, 1, 0);
    glMultMatrixf(&object2world[0][0]);

    if (currSession->recalculateSlider == true){
        // Update Epsilon value of merging.
        double *currentValNum = (double*) malloc(sizeof(double));
        parseGetBankVal(currSession->epsilonStr.c_str(), this->currSession, currentValNum, 0);
        currSession->epsilon = *currentValNum;

        for (Surface* s : currSession->surfaces){
            s->update();
        }

        for (InstanceNew* i : currSession->instances){
            i->updateTransformations();
        }

        for (Vert* p : currSession->verts){
            p->update();
        }

        for (BSplineNew* bs : currSession->bsplines){
            bs->updateBSpline();
            for (std::list<InstanceNew*>::iterator iterator = currSession->instances.begin(), end = currSession->instances.end(); iterator != end; ++iterator) {
                if ((*iterator)->mesh == bs){
                    if ((*iterator)->edges.size() != (*iterator)->mesh->edges.size()){
                        Reader* currReader = createReader(currSession);
                        InstanceNew * newInstance = createInstance((*iterator)->mesh, currSession->verts, currReader, true, false, false, currSession, true);
                        newInstance->surface = (*iterator)->surface;
                        newInstance->setName((*iterator)->name);
                        newInstance->transformations = (*iterator)->transformations;
                        (*iterator) = newInstance;
                    }
                    else{
                        (*iterator)->update();
                    }
                }
            }
        }

        for (BezierCurveNew* bc : currSession->bezierCurves){
            bc->updateBezierCurve();
            for (std::list<InstanceNew*>::iterator iterator = currSession->instances.begin(), end = currSession->instances.end(); iterator != end; ++iterator) {
                if ((*iterator)->mesh == bc){
                    if ((*iterator)->edges.size() != (*iterator)->mesh->edges.size()){
                        Reader* currReader = createReader(currSession);
                        InstanceNew * newInstance = createInstance((*iterator)->mesh, currSession->verts, currReader, true, false, false, currSession, true);
                        newInstance->surface = (*iterator)->surface;
                        newInstance->setName((*iterator)->name);
                        newInstance->transformations = (*iterator)->transformations;
                        (*iterator) = newInstance;
                    }
                    else{
                        (*iterator)->update();
                    }
                }
            }
        }

        for(CircleNew* c : currSession->circles){
            if (c->updateCircle() == 1){
                for (std::list<InstanceNew*>::iterator iterator = currSession->instances.begin(), end = currSession->instances.end(); iterator != end; ++iterator) {
                    if ((*iterator)->mesh == c){
                        if ((*iterator)->edges.size() != (*iterator)->mesh->edges.size()){
                            Reader* currReader = createReader(currSession);
                            InstanceNew * newInstance = createInstance((*iterator)->mesh, currSession->verts, currReader, true, false, false, currSession, true);
                            newInstance->surface = (*iterator)->surface;
                            newInstance->setName((*iterator)->name);
                            newInstance->transformations = (*iterator)->transformations;
                            (*iterator) = newInstance;
                        }
                        else{
                            (*iterator)->update();
                        }
                    }
                }
            }
        }

        for(FunnelNew* f : currSession->funnels){
            if (f->updateFunnel() == 1){
                for (std::list<InstanceNew*>::iterator iterator = currSession->instances.begin(), end = currSession->instances.end(); iterator != end; ++iterator) {
                    if ((*iterator)->mesh == f){
                        if ((*iterator)->edges.size() != (*iterator)->mesh->edges.size()){
                            Reader* currReader = createReader(currSession);
                            InstanceNew * newInstance = createInstance((*iterator)->mesh, currSession->verts, currReader, true, false, false, currSession, true);
                            newInstance->surface = (*iterator)->surface;
                            newInstance->setName((*iterator)->name);
                            newInstance->transformations = (*iterator)->transformations;
                            (*iterator) = newInstance;
                        }
                        else{
                            (*iterator)->update();
                        }
                    }
                }
            }
        }
        for(TunnelNew* t : currSession->tunnels){
            if (t->updateTunnel() == 1){
                for (std::list<InstanceNew*>::iterator iterator = currSession->instances.begin(), end = currSession->instances.end(); iterator != end; ++iterator) {
                    if ((*iterator)->mesh == t){
                        if ((*iterator)->edges.size() != (*iterator)->mesh->edges.size()){
                            Reader* currReader = createReader(currSession);
                            InstanceNew * newInstance = createInstance((*iterator)->mesh, currSession->verts, currReader, true, false, false, currSession, true);
                            newInstance->surface = (*iterator)->surface;
                            newInstance->setName((*iterator)->name);
                            newInstance->transformations = (*iterator)->transformations;
                            (*iterator) = newInstance;
                        }
                        else{
                            (*iterator)->update();
                        }
                    }
                }
            }
        }

        /*for(PolylineNew* p : currSession->polylines){
            for (std::list<InstanceNew*>::iterator iterator = currSession->instances.begin(), end = currSession->instances.end(); iterator != end; ++iterator) {
                if ((*iterator)->mesh == p){
                    auto pIt = p->verts.begin();
                    auto iIt = (*iterator)->verts.begin();

                    for (int i = 0; i < p->verts.size() ; i++){
                        std::cout << *(*iIt)->xTransformed << std::endl;
                        (*iIt)->xTransformed = (*pIt)->xTransformed;
                        (*iIt)->yTransformed = (*pIt)->yTransformed;
                        (*iIt)->zTransformed = (*pIt)->zTransformed;

                        std::advance(pIt, 1);
                        std::advance(iIt, 1);
                    }
                }
            }
        }*/

        for (InstanceNew * newInstance: currSession->instances){
            newInstance->updateVerts();
        }
        std::list<Vert*> appliedVertTransformation = std::list<Vert*>();
        for (InstanceNew * newInstance: currSession->instances){

            for (Vert * v : newInstance->verts){
                if (v->transformations.size() > 0 && !(std::find(appliedVertTransformation.begin(), appliedVertTransformation.end(), v) != appliedVertTransformation.end())){
                    appliedVertTransformation.push_back(v);
                    for (TransformationNew * t : v->transformations){
                        v->applyTransformation(t);
                    }
                }
            }
        }


        for (InstanceNew * newInstance: currSession->instances){
            newInstance->applyTransformationGroup();
            for (TransformationNew * t : newInstance->transformations){
                newInstance->applyTransformation(t);
            }
        }
    }


    //std::cout << currSession->recompute << std::endl;
    if (viewer_mode == 0){
        currSession->draw();
    } else if (viewer_mode == 1){
        if (currSession->subdivisions.size() != 0 && currSession->offsets.size() != 0){
            // Subdivision and offset.
            currSession->drawSubdivide(currSession->subdivisions.front()->value, currSession->subdivisions.front()->previousSubdivisionLevel, currSession->offsets.front()->value, currSession->recalculateOffset, currSession->recalculateSubdivision, currSession->recalculateSlider);
            currSession->subdivisions.front()->previousSubdivisionLevel = currSession->subdivisions.front()->value;
        }
        else if (currSession->subdivisions.size() == 0 && currSession->offsets.size() != 0){
            // No subdivision but there is offset.
            currSession->drawSubdivide(0, 0, currSession->offsets.front()->value, currSession->recalculateOffset, currSession->recalculateSubdivision, currSession->recalculateSlider);
        }
        else if (currSession->subdivisions.size() != 0 && currSession->offsets.size() == 0){
            // Suvidvision but no offset
            currSession->drawSubdivide(currSession->subdivisions.front()->value, currSession->subdivisions.front()->previousSubdivisionLevel, 0, currSession->recalculateOffset, currSession->recalculateSubdivision, currSession->recalculateSlider);
            currSession->subdivisions.front()->previousSubdivisionLevel = currSession->subdivisions.front()->value;
        }
        else if (currSession->subdivisions.size() == 0 && currSession->offsets.size() == 0){
            // No subdivision and no offset
            currSession->drawSubdivide(0, 0, 0, currSession->recalculateOffset, currSession->recalculateSubdivision, currSession->recalculateSlider);
        }
    }

    currSession->recalculateOffset = false;
    currSession->recalculateSubdivision = false;
    currSession->recalculateSlider = false;
}

void SlideGLWidget::mousePressEvent(QMouseEvent* event)
{
    int pixelRatio = this->devicePixelRatio();
    if (event->buttons() & Qt::LeftButton)
    {
        arcball_on = true;
        last_mx = cur_mx = event -> x();
        last_my = cur_my = event -> y();
    }
    else
    {
        arcball_on = false;
    }
    if (event->buttons() & Qt::RightButton)
    {
        mouse_select(event -> x() * pixelRatio, event -> y() * pixelRatio);
    }
}

void SlideGLWidget::mouseMoveEvent(QMouseEvent* event)
{
    if(arcball_on)
    {
      cur_mx = event -> x();
      cur_my = event -> y();
    }
}

void SlideGLWidget::timerEvent(QTimerEvent *event) {
    if(last_mx != cur_mx || last_my != cur_my) {
        vec3 va = get_arcball_vector(last_mx, last_my);
        vec3 vb = get_arcball_vector( cur_mx,  cur_my);
        float angle = acos(glm::min(1.0f, dot(va, vb)));
        vec3 axis_in_camera_coord = cross(va, vb);
        mat3 camera2object = inverse(mat3(transforms[MODE_CAMERA]) * mat3(object2world));
        vec3 axis_in_object_coord = camera2object * axis_in_camera_coord;
        object2world = rotate(object2world, (float) ROTATION_SPEED * angle, axis_in_object_coord);
        last_mx = cur_mx;
        last_my = cur_my;
        repaint();
    }
}
void SlideGLWidget::keyPressEvent(QKeyEvent* event)
{
    switch(event->key())
    {
    case Qt::Key_Escape:
        mySelect.clearSelection();
        break;
    case Qt::Key_W:
        wireframe = !wireframe;
        if (wireframe)
        {
            glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
        }
        else
        {
            glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
        }
        break;
    case Qt::Key_X:
        backface = !backface;

        if (backface)
        {
            glPolygonMode( GL_BACK, GL_FILL );
        }
        else
        {
            glPolygonMode( GL_BACK, GL_LINE );
        }
        break;
    case Qt::Key_I:
        zoom_in();
        break;
    case Qt::Key_O:
        zoom_out();
        break;
    case Qt::Key_Left:
        centerX -= 1;
        break;
    case Qt::Key_Right:
        centerX += 1;
        break;
    case Qt::Key_Down:
        centerY -= 1;
        break;
    case Qt::Key_Up:
        centerY += 1;
        break;
    case Qt::Key_S:
        if (smoothshading)
        {
            glShadeModel(GL_FLAT);
        }
        else
        {
            glShadeModel(GL_SMOOTH);
        }
        smoothshading = !smoothshading;
        break;
    default:
        event->ignore();
        break;
    }

    repaint();
}

void SlideGLWidget::subdivide(int level)
{
    if(level <= 0) {
        subdiv_mesh = merged_mesh.makeCopy();
        return;
    }
    //int cachedLevel = cache_subdivided_meshes.size();
    //if(cachedLevel >= level)
    //{
    //    subdiv_mesh = cache_subdivided_meshes[level - 1];
    //}
    //else
    //{
    //    if(cachedLevel == 0)
    //    {
    //        subdiv_mesh = merged_mesh;
    //    }
    //    else
    //    {
    //        subdiv_mesh = cache_subdivided_meshes[cachedLevel - 1];
    //    }
    //    while(cachedLevel <= level)
    //    {
    //        subdiv_mesh = subdiv_mesh.makeCopy();
    //        subdivider = new Subdivision(subdiv_mesh);
    //        subdiv_mesh = subdivider->ccSubdivision(1);
    //        subdiv_mesh.computeNormals();
    //        cache_subdivided_meshes.push_back(subdiv_mesh);
    //        cachedLevel++;
    //    }
    //}
    subdivider = new Subdivision(merged_mesh);
    subdiv_mesh.clearAndDelete();
    subdiv_mesh = subdivider->ccSubdivision(level);
    subdiv_mesh.computeNormals();
    subdiv_mesh.color = foreColor;
}

void SlideGLWidget::offset(float value)
{
    work_phase = glm::max(work_phase, 3);
    if(value == 0)
    {
        offset_mesh = merged_mesh.makeCopy();
        return;
    }
    if(subdiv_mesh.isEmpty())
    {
        subdiv_mesh = merged_mesh.makeCopy();
    }
    offseter = new Offset(subdiv_mesh, value);
    offseter -> makeFullOffset();
    offset_mesh.clearAndDelete();
    offset_mesh = offseter->offsetMesh;
}

void SlideGLWidget::viewContentChanged(int viewer_mode)
{
    this -> viewer_mode = viewer_mode;
    repaint();
}

void SlideGLWidget::levelChanged(int new_level)
{
    work_phase = glm::max(work_phase, 2);
    subdiv_level = new_level;
    subdivide(new_level);
    offset_mesh.clearAndDelete();
    subdiv_offset_mesh.clearAndDelete();
    viewer_mode = 2;
    repaint();
    //emit feedback_status_bar(tr("Subdivision Finished. Level: ")
    //                         + QString::number(new_level), 0);
}

void SlideGLWidget::offsetValueChanged(float new_offset_value)
{
    viewer_mode = 3;
    offset_value = new_offset_value;
    offset(new_offset_value);
    subdiv_offset_mesh.clearAndDelete();
    repaint();
}

void SlideGLWidget::resetViewDirection(bool)
{
    object2world = mat4(1);
    repaint();
}

void SlideGLWidget::zoom_in()
{
    if(cameraDistance > 0.001)
    {
        cameraDistance *= 0.9;
    }
}

void SlideGLWidget::zoom_out()
{
    if(cameraDistance < 200)
    {
        cameraDistance *= 1.1;
    }
}

void SlideGLWidget::wheelEvent(QWheelEvent *event)
{
    QPoint numDegrees = event->angleDelta() / 8;
    int numZoomIn = numDegrees.y() / 15;
    if(numZoomIn >= 1) {
        for(int i = 0; i < numZoomIn; i++) {
            zoom_in();
        }
    } else if(numZoomIn <= -1) {
        for(int i = 0; i < -numZoomIn; i++) {
            zoom_out();
        }
    }
    event->accept();
    repaint();
}

void SlideGLWidget::setForeColor(QColor color)
{
    foreColor = color;
    master_mesh.color = foreColor;
    merged_mesh.color = foreColor;
    subdiv_mesh.color = foreColor;
    offset_mesh.color = foreColor;

    double *r = (double*) malloc(sizeof(double));
    double *g = (double*) malloc(sizeof(double));
    double *b = (double*) malloc(sizeof(double));

    *r = color.red() / 255.0;
    *g = color.green() / 255.0;
    *b = color.blue() / 255.0;

    currSession->foreColor = createSurface(r, g, b, "foreColor");

    hierarchical_scene_transformed.setColor(foreColor);
    hierarchical_scene_transformed.assignColor();


    repaint();
}

void SlideGLWidget::setBackColor(QColor color)
{


    double *r = (double*) malloc(sizeof(double));
    double *g = (double*) malloc(sizeof(double));
    double *b = (double*) malloc(sizeof(double));

    *r = color.red() / 255.0;
    *g = color.green() / 255.0;
    *b = color.blue() / 255.0;

    currSession->backColor = createSurface(r, g, b, "backColor");

    repaint();
}

void SlideGLWidget::setInsideColor(QColor color)
{
    insideColor = color;
    currSession->recalculateOffset = true;

    double *r = (double*) malloc(sizeof(double));
    double *g = (double*) malloc(sizeof(double));
    double *b = (double*) malloc(sizeof(double));

    *r = color.red() / 255.0;
    *g = color.green() / 255.0;
    *b = color.blue() / 255.0;

    currSession->insideColor = createSurface(r, g, b, "insideColor");
    repaint();
}

void SlideGLWidget::setOffsetColor(QColor color)
{
    offsetColor = color;
    currSession->recalculateOffset = true;

    double *r = (double*) malloc(sizeof(double));
    double *g = (double*) malloc(sizeof(double));
    double *b = (double*) malloc(sizeof(double));

    *r = color.red() / 255.0;
    *g = color.green() / 255.0;
    *b = color.blue() / 255.0;

    currSession->offsetColor = createSurface(r, g, b, "offsetColor");
    repaint();
}

void SlideGLWidget::setOutsideColor(QColor color)
{
    outsideColor = color;
    currSession->recalculateOffset = true;

    double *r = (double*) malloc(sizeof(double));
    double *g = (double*) malloc(sizeof(double));
    double *b = (double*) malloc(sizeof(double));

    *r = color.red() / 255.0;
    *g = color.green() / 255.0;
    *b = color.blue() / 255.0;

    currSession->outsideColor = createSurface(r, g, b, "outsideColor");

    repaint();
}

void SlideGLWidget::repaintCanvas()
{
    repaint();
}

void SlideGLWidget::vertexModeChecked(bool checked)
{
    if(checked)
    {
        selection_mode = 1;
    }
}

void SlideGLWidget::borderModeChecked(bool checked)
{
    if(checked)
    {
        if(whole_border)
        {
            selection_mode = 2;
        }
        else
        {
            selection_mode = 3;
        }
    }
}

void SlideGLWidget::faceModeChecked(bool checked)
{
    if(checked)
    {
        selection_mode = 0;
    }
}

void SlideGLWidget::autoCorrectChecked(bool checked)
{
    auto_check = checked;
}

void SlideGLWidget::wholeBorderSelectionChecked(bool checked)
{
    whole_border = checked;
    if(checked)
    {
        selection_mode = 2;
    } else
    {
        selection_mode = 3;
    }
    clearSelection();
}

void SlideGLWidget::addToPolylineCalled(bool)
{
    /*if (currSession->tmpPolyline != NULL || currSession->tmpMesh != NULL){
        QMessageBox msgBox;
        msgBox.setWindowTitle("Add Polyline");
        msgBox.setText("Are you sure you want to overwrite the faces or polyline and create a new polyline?");
        msgBox.setStandardButtons(QMessageBox::Yes);
        msgBox.addButton(QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::No);
        if(msgBox.exec() == QMessageBox::Yes){
            currSession->tmpMesh = NULL;
            currSession->tmpPolyline = NULL;
            currSession->tmpInstance =  NULL;
            currSession->addTmpPolyline();
        }
    }
    else{
        currSession->tmpMesh = NULL;
        currSession->tmpPolyline = NULL;
        currSession->tmpInstance =  NULL;
        currSession->addTmpPolyline();
    }*/

    currSession->addTmpPolyline();

    repaint();
}

void SlideGLWidget::undoFaceCalled(bool){
    currSession->deleteTmpFace();
    repaint();
}

void SlideGLWidget::groupFacesMsg(bool)
{
    if (consolidateMeshName.length() == 0){
        std::cout << "Enter a mesh name." << std::endl;
    }
    else if (consolidateInstanceName.length() == 0){
        std::cout << "Enter an instance name." << std::endl;
    }
    else{
        currSession->groupFaces(consolidateInstanceName, consolidateMeshName);

        groupWindow->window->close();
    }

    repaint();
}

void SlideGLWidget::addToTempCalled(bool)
{
    /*if (currSession->tmpPolyline != NULL){
        QMessageBox msgBox;
        msgBox.setWindowTitle("Add Polygon");
        msgBox.setText("Are you sure you want to overwrite the polyline and create a new face?");
        msgBox.setStandardButtons(QMessageBox::Yes);
        msgBox.addButton(QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::No);
        if(msgBox.exec() == QMessageBox::Yes){
            currSession->tmpMesh = NULL;
            currSession->tmpPolyline = NULL;
            currSession->tmpInstance =  NULL;
            currSession->addTmpFace();
        }
    }
    else{
        currSession->addTmpFace();
    }*/
    currSession->addTmpFace();

    repaint();
}

void SlideGLWidget::zipToTempCalled(bool)
{

    currSession->zipBorders();

    repaint();
}

void SlideGLWidget::popUpConsolidateWindow(bool){
    conWindow = new ConsolidateWindow(this);
}

void SlideGLWidget::popUpGroupWindow(bool){
    groupWindow = new GroupWindow(this);
}


void SlideGLWidget::addTempToMaster()
{
    Mesh newMesh;
    vector<Vertex*>::iterator vIt;
    for(vIt = master_mesh.vertList.begin();
        vIt < master_mesh.vertList.end(); vIt ++)
    {
        Vertex * vertCopy = new Vertex;
        vertCopy -> ID = (*vIt) -> ID;
        vertCopy -> position = (*vIt) -> position;
        newMesh.addVertex(vertCopy);
    }
    vector<Face*>::iterator fIt;
    for(fIt = master_mesh.faceList.begin();
     fIt < master_mesh.faceList.end(); fIt ++)
    {
        Face * tempFace = *fIt;
        Edge * firstEdge = tempFace -> oneEdge;
        Edge * currEdge = firstEdge;
        Edge * nextEdge;
        vector<Vertex*> vertices;
        Vertex * tempv;
        vertices.clear();
        do {
            if(tempFace == currEdge -> fa) {
                tempv = currEdge -> vb;
                nextEdge = currEdge -> nextVbFa;
            } else {
                if(currEdge -> mobius) {
                    tempv = currEdge -> vb;
                    nextEdge = currEdge -> nextVbFb;
                } else {
                    tempv = currEdge -> va;
                    nextEdge = currEdge -> nextVaFb;
                }
            }
            vertices.push_back(newMesh.vertList[tempv -> ID]);
            currEdge = nextEdge;
        } while (currEdge != firstEdge);
        newMesh.addPolygonFace(vertices);
    }
    for(fIt = temp_mesh.faceList.begin();
     fIt < temp_mesh.faceList.end(); fIt ++)
    {
        Face * tempFace = *fIt;
        Edge * firstEdge = tempFace -> oneEdge;
        Edge * currEdge = firstEdge;
        Edge * nextEdge;
        vector<Vertex*> vertices;
        Vertex * tempv;
        vertices.clear();
        do {
            if(tempFace == currEdge -> fa) {
                tempv = currEdge -> vb;
                nextEdge = currEdge -> nextVbFa;
            } else {
                if(currEdge -> mobius) {
                    tempv = currEdge -> vb;
                    nextEdge = currEdge -> nextVbFb;
                } else {
                    tempv = currEdge -> va;
                    nextEdge = currEdge -> nextVaFb;
                }
            }
            vertices.push_back(newMesh.vertList[tempv -> ID]);
            currEdge = nextEdge;
        } while (currEdge != firstEdge);
        newMesh.addPolygonFace(vertices);
    }
    newMesh.color = master_mesh.color;
    master_mesh = newMesh;
    master_mesh.buildBoundary();
    master_mesh.computeNormals();
    repaint();
}

void SlideGLWidget::addTempToMasterCalled(bool) {
    if(temp_mesh.isEmpty())
    {
        emit feedback_status_bar(tr("Current temp mesh is empty."), 0);
        return;
    }
    addTempToMaster();
    clearSubDivisionAndOffset();
    clearSelectionCalled(true);
    updateGlobalIndexList();
    emit feedback_status_bar(tr("Joining temp mesh into initial mesh"), 0);
    repaint();
}

void SlideGLWidget::addBorderCalled(bool)
{
    if (currSession->isBorderSelected == true){
        currSession->borders.push_back(currSession->tmpBorder);
        for (Vert* v : std::get<0>(currSession->tmpBorder)){
            v->selected = false;
        }
    }

    currSession->isBorderSelected = false;
    repaint();
}

void SlideGLWidget::clearSubDivisionAndOffset() {
    subdiv_mesh.clearAndDelete();
    offset_mesh.clearAndDelete();
    subdiv_offset_mesh.clearAndDelete();
    //cache_subdivided_meshes.clear();
}

void SlideGLWidget::clearSelection()
{
    mySelect.clearSelection();
    border1.clear();
    border2.clear();
    temp_mesh.clearAndDelete();
    if(temp_mesh.isEmpty() && consolidate_mesh.isEmpty())
    {
        set_to_editing_mode(false);
    }
    repaint();
}

void SlideGLWidget::clearSelectionCalled(bool)
{
    currSession->clearSelection();
    currSession->tmpMesh = NULL;
    currSession->tmpInstance = NULL;
    currSession->tmpPolyline = NULL;
    repaint();
}

void SlideGLWidget::updateGlobalIndexList()
{
    int count = 0;
    vector<Mesh*>::iterator mIt;
    vector<PolyLine*>::iterator pIt;
    global_name_index_list.clear();
    global_polyline_name_index_list.clear();
    for(mIt = global_mesh_list.begin(); mIt < global_mesh_list.end(); mIt++)
    {
        global_name_index_list.push_back(count);
        count += (*mIt) -> faceList.size();
    }
    for(pIt = global_polyline_list.begin(); pIt < global_polyline_list.end(); pIt++)
    {
        global_polyline_name_index_list.push_back(count);
        count += (*pIt) -> vertices.size();
    }
}

void SlideGLWidget::resetTrianglePanelty(QString new_value)
{
    trianglePanelty = new_value.toFloat();
}

void SlideGLWidget::paramValueChanged(float)
{
    if(hierarchical_scene_transformed.in_editing_mode)
    {
        transform_meshes_in_scene();
    }
    else
    {
        makeSLFMesh();
    }

    updateTempMesh();
    updateConsolidateMesh();
    updateSavedConsolidatedMesh();
    updateGlobalIndexList();
    if(work_phase >= 1)
    {
        mergeAll();
    }
    if(work_phase >= 2)
    {
        //cache_subdivided_meshes.clear();
        subdivide(subdiv_level);
    }
    if(work_phase >= 3)
    {
        offset(offset_value);
    }
    repaint();
}

void SlideGLWidget::updateSavedConsolidatedMesh()
{
    if(group_from_consolidate_mesh != NULL && group_from_consolidate_mesh->myMeshes.size() != 0)
    {
        for(Mesh& mesh : group_from_consolidate_mesh->myMeshes)
        {
            for(Vertex*& v: mesh.vertList)
            {
                v -> position = v -> source_vertex -> position;
            }
        }
        vector<Mesh*> append_list = group_from_consolidate_mesh -> flattenedMeshes();
        global_mesh_list.pop_back();
        global_mesh_list.insert(global_mesh_list.end(), append_list.begin(), append_list.end());
        global_mesh_list.push_back(&temp_mesh);
    }
}

void SlideGLWidget::updateFromSavedMesh()
{
    //cout << "HELLO" << endl;
    consolidate_mesh.computeNormals();

    vector<Mesh*> append_list = group_from_consolidate_mesh -> flattenedMeshesTemp();

    global_mesh_list.pop_back();
    global_mesh_list.insert(global_mesh_list.end(), append_list.begin(), append_list.end());
    global_mesh_list.push_back(&temp_mesh);
    updateGlobalIndexList();
    if(group_from_consolidate_mesh != NULL && group_from_consolidate_mesh->myMeshes.size() > 0)
    {
        set_to_editing_mode(true);
    }

    repaint();
}

void SlideGLWidget::deleteFaceCalled(bool)
{
    currSession->deleteFace();
    //mySelect.deleteSelectedFaces(deletedFaces);
    //updateGlobalIndexList();
    repaint();
}

void SlideGLWidget::updateTempMesh()
{
    for(Vertex * v : temp_mesh.vertList)
    {
        if(v -> source_vertex != NULL)
        {
            v -> position = v -> source_vertex -> position;
        }
    }
}

void SlideGLWidget::updateConsolidateMesh()
{
    for(Vertex * v : consolidate_mesh.vertList)
    {
        if(v -> source_vertex != NULL)
        {
            v -> position = v -> source_vertex -> position;
        }
    }
}

void SlideGLWidget::createConsolidated(bool){
    if (consolidateMeshName.length() == 0){
        std::cout << "Enter a mesh name." << std::endl;
    }
    else if (consolidateInstanceName.length() == 0){
        std::cout << "Enter an instance name." << std::endl;
    }
    else{
        currSession->consolidateTmpMesh(consolidateInstanceName, consolidateMeshName);

        conWindow->window->close();
    }
    repaint();
}

void SlideGLWidget::readConsolidateMeshName(QString text){
    consolidateMeshName = text.toUtf8().constData();
}

void SlideGLWidget::readConsolidateInstanceName(QString text){
    consolidateInstanceName = text.toUtf8().constData();
}
