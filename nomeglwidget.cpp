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
#include "commonDialogs.h"

#ifdef __APPLE__
#include <OpenGL/GLU.h>
#else
#include <GL/glu.h>
#endif

#include <glm/gtx/transform.hpp>

SlideGLWidget::SlideGLWidget(QWidget *parent) :
	QOpenGLWidget(parent)
{
    generalSetup();
    makeDefaultMesh();
    updateGlobalIndexList();
}

SlideGLWidget::SlideGLWidget(std::string name, QWidget *parent) :
	QOpenGLWidget(parent)
{
    generalSetup();
    makeSIFMesh(name);
    updateGlobalIndexList();
}

SlideGLWidget::SlideGLWidget(QWidget* parent, Session* session)
{
	this->currSession = session;
	generalSetup();
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
    object2world = glm::mat4(1);
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
    trianglePanelty = 1.3f;
}

void SlideGLWidget::makeDefaultMesh()
{
}

void SlideGLWidget::makeSIFMesh(std::string name)
{
}

void SlideGLWidget::makeSLFMesh()
{
}

void SlideGLWidget::transform_meshes_in_scene()
{
}

void SlideGLWidget::mergeAll()
{
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

void SlideGLWidget::saveMesh(std::string name)
{
}

glm::vec3 SlideGLWidget::get_arcball_vector(int x, int y)
{
    glm::vec3 p = glm::vec3(1.0 * x / this->width() * 2 - 1.0,
      1.0 * y / this->height() * 2 - 1.0, 0);
    p.y = - p.y;
    float op_squared = p.x * p.x + p.y * p.y;
    if (op_squared <= 1 * 1) {
        p.z = sqrt(1 * 1 - op_squared);
    } else {
        p = glm::normalize(p);  // nearest point
    }
    return p;
}

void SlideGLWidget::set_to_editing_mode(bool in_editing_mode)
{
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
		std::set<Vert*> selectionCandidates;

        Ray mouseRay = Ray(camPos, dir);
        vector<OctreeProxy*> rayIntersectResults;
        currSession->getOctreeRoot()->findNodes(mouseRay, rayIntersectResults);
        for (OctreeProxy* proxy : rayIntersectResults)
        {
            auto* vertProxy = dynamic_cast<VertOctreeProxy*>(proxy);
            if (vertProxy)
            {
                float hitDistance = mouseRay.HitDistance(vertProxy->getWorldAABB());
				if (abs(hitDistance - distMax) < 0.01f)
				{
					//The vertex is just as close as current selection
					selectionCandidates.insert(vertProxy->getOwner());
				}
                else if (hitDistance < distMax)
                {
					selectionCandidates.clear();
                    distMax = hitDistance;
					selectionCandidates.insert(vertProxy->getOwner());
                }
            }
        }

		Vert* selectedVertex = nullptr;
		Reader* currReader = createReader(currSession);
		if (selectionCandidates.size() == 1)
		{
			selectedVertex = *selectionCandidates.begin();
		}
		else if (selectionCandidates.size() > 1)
		{
			//Show a list of vertices to choose from
			VertListDialog selectionList(this, *currReader, selectionCandidates);
			selectionList.exec();
			selectedVertex = selectionList.GetSelection();
		}

        if (selectedVertex)
        {
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

	transforms[MODE_CAMERA] = glm::lookAt(glm::vec3(0.0, 0.0, 10.0),
		glm::vec3(0.0, 0.0, 0.0),
		glm::vec3(0.0, 1.0, 0.0));
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

        //std::list<Vert*> appliedVertTransformation = std::list<Vert*>();
        //for (InstanceNew * newInstance: currSession->instances){

        //    for (Vert * v : newInstance->verts){
        //        if (v->transformations.size() > 0 && !(std::find(appliedVertTransformation.begin(), appliedVertTransformation.end(), v) != appliedVertTransformation.end())){
        //            appliedVertTransformation.push_back(v);
        //            for (TransformationNew * t : v->transformations){
        //                v->applyTransformation(t);
        //            }
        //        }
        //    }
        //}


		for (InstanceNew* newInstance : currSession->instances) {
			newInstance->updateVerts();
		}

        for (InstanceNew* newInstance: currSession->instances) {
            newInstance->applyTransformGroupChildren();
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
	const float ROTATION_SPEED = 0.6f;

    if(last_mx != cur_mx || last_my != cur_my) {
        glm::vec3 va = get_arcball_vector(last_mx, last_my);
		glm::vec3 vb = get_arcball_vector( cur_mx,  cur_my);
        float angle = acos(glm::min(1.0f, dot(va, vb)));
		glm::vec3 axis_in_camera_coord = cross(va, vb);
		glm::mat3 camera2object = glm::inverse(glm::mat3(transforms[MODE_CAMERA]) * glm::mat3(object2world));
		glm::vec3 axis_in_object_coord = camera2object * axis_in_camera_coord;
        object2world = glm::rotate(object2world, (float) ROTATION_SPEED * angle, axis_in_object_coord);
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
}

void SlideGLWidget::offset(float value)
{
}

void SlideGLWidget::viewContentChanged(int viewer_mode)
{
    this -> viewer_mode = viewer_mode;
    repaint();
}

void SlideGLWidget::levelChanged(int new_level)
{
}

void SlideGLWidget::offsetValueChanged(float new_offset_value)
{
    viewer_mode = 3;
    offset_value = new_offset_value;
    offset(new_offset_value);
    repaint();
}

void SlideGLWidget::resetViewDirection(bool)
{
    object2world = glm::mat4(1);
    repaint();
}

void SlideGLWidget::zoom_in()
{
    if(cameraDistance > 0.001)
    {
        cameraDistance *= 0.9f;
    }
}

void SlideGLWidget::zoom_out()
{
    if(cameraDistance < 200)
    {
        cameraDistance *= 1.1f;
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

    double *r = (double*) malloc(sizeof(double));
    double *g = (double*) malloc(sizeof(double));
    double *b = (double*) malloc(sizeof(double));

    *r = color.red() / 255.0;
    *g = color.green() / 255.0;
    *b = color.blue() / 255.0;

    currSession->foreColor = createSurface(r, g, b, "foreColor");

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
}

void SlideGLWidget::addTempToMasterCalled(bool)
{
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

void SlideGLWidget::clearSubDivisionAndOffset()
{
}

void SlideGLWidget::clearSelection()
{
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
}

void SlideGLWidget::resetTrianglePanelty(QString new_value)
{
    trianglePanelty = new_value.toFloat();
}

void SlideGLWidget::paramValueChanged(float)
{
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
}

void SlideGLWidget::updateFromSavedMesh()
{
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
}

void SlideGLWidget::updateConsolidateMesh()
{
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
