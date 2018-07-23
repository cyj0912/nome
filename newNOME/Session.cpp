//
//  Session.cpp
//  model
//
//  Created by L on 26/08/2017.
//  Copyright © 2017 L. All rights reserved.
//

#include "Session.h"
#include "Reader.h"
#include "Data.h"
#include "MeshNew.h"
#include "GroupNew.h"
#include "BankNew.h"
#include "PolylineNew.h"
#include "BSplineNew.h"
#include "BezierCurveNew.h"
#include "CircleNew.h"
#include "FunnelNew.h"
#include "TunnelNew.h"
#include "SubdivisionNew.h"
#include "OffsetNew.h"
#include <fstream>
#include <sstream>
#include <glm/glm.hpp>

#include "bankFlexBison.cpp"
#include "compilerNome/parser.hpp"

static Session* singletonPtr = nullptr;
static int sIndex = 0;

Session::Session()
{
    OctreeRoot = new OctantNew();
    OctreeRoot->setExtent(BoundingBox(-100.0f, 100.0f));

	singletonPtr = this;

	this->setName(std::to_string(sIndex));

	double *rF = (double*)malloc(sizeof(double));
	double *gF = (double*)malloc(sizeof(double));
	double *bF = (double*)malloc(sizeof(double));

	*rF = 255.0 / 255.0;
	*gF = 0.0;
	*bF = 0.0;

	this->foreColor = createSurface(rF, gF, bF, "foreColor");

	double *rB = (double*)malloc(sizeof(double));
	double *gB = (double*)malloc(sizeof(double));
	double *bB = (double*)malloc(sizeof(double));

	*rB = 0.0;
	*gB = 0.0;
	*bB = 0.0;

	this->backColor = createSurface(rB, gB, bB, "backColor");

	double *rOut = (double*)malloc(sizeof(double));
	double *gOut = (double*)malloc(sizeof(double));
	double *bOut = (double*)malloc(sizeof(double));

	*rOut = 255.0 / 255.0;
	*gOut = 0.0;
	*bOut = 0.0;

	this->outsideColor = createSurface(rOut, gOut, bOut, "outsideColor");

	double *rIn = (double*)malloc(sizeof(double));
	double *gIn = (double*)malloc(sizeof(double));
	double *bIn = (double*)malloc(sizeof(double));

	*rIn = 0.0;
	*gIn = 0.0;
	*bIn = 255.0 / 255.0;

	this->insideColor = createSurface(rIn, gIn, bIn, "insideColor");

	double *rOff = (double*)malloc(sizeof(double));
	double *gOff = (double*)malloc(sizeof(double));
	double *bOff = (double*)malloc(sizeof(double));

	*rOff = 255.0 / 255.0;
	*gOff = 163.0 / 255.0;
	*bOff = 0.0;

	this->offsetColor = createSurface(rOff, gOff, bOff, "offsetColor");

	sIndex++;
}

Session::~Session()
{
    delete OctreeRoot;
}

void Session::reset()
{
	delete OctreeRoot;

	OctreeRoot = new OctantNew();
	OctreeRoot->setExtent(BoundingBox(-100.0f, 100.0f));

	verts.clear();
	edges.clear();
	faces.clear();
	meshes.clear();
	surfaces.clear();
	groups.clear();
	instances.clear();
	polylines.clear();
	bsplines.clear();
	bezierCurves.clear();
	circles.clear();
	funnels.clear();
	tunnels.clear();
	banks.clear();
	subdivisions.clear();
	offsets.clear();

	selectedEdges.clear();
	selectedVerts.clear();
	selectedFaces.clear();

	tmpFaceIndex = 0;
	tmpPolylineIndex = 0;
	tmpMesh = nullptr;
	tmpPolyline = nullptr;
	tmpInstance = nullptr;

	recalculateSlider = true;
	recalculateSubdivision = true;
	recalculateOffset = true;
	flattenMeshList.clear();
}

Session& Session::getSingleton()
{
    return *singletonPtr;
}

bool Session::setName(std::string n)
{
    name = n;
    return updateNames();
}

std::string Session::getName()
{
    return name;
}

bool Session::updateNames()
{
    for(Vert* v0 : verts)
    {
        v0->setPrefix(name);
    }
    for(EdgeNew* e0 : edges)
    {
        e0->setPrefix(name);
    }
    for(FaceNew* f0 : faces)
    {
        f0->setPrefix(name);
    }
    for(GroupNew* g0 : groups)
    {
        g0->setPrefix(name);
        g0->updateNames();
    }
    for(MeshNew* m0 : meshes)
    {
        m0->setPrefix(name);
        m0->updateNames();
    }
    return true;
}

void Session::selectVert(int hits, unsigned int *names, double posX, double posY, double posZ){
    if(hits > 0) {
        glm::vec3 hit_position = glm::vec3(posX, posY, posZ);
        float min_distance = std::numeric_limits<float>::max();
        Vert * selectedVertex = NULL;
        Reader* currReader = createReader(this);

        for (int i = 0; i < hits; i++) {
            int currentID = names[i * 4 + 3];
            Vert * currentVertex = currReader->getVert(currentID);

            //std::cout << "+++" << std::endl;
            //std::cout << currentVertex << std::endl;
            if (currentVertex != NULL){
                //std::cout << "HELLO" << std::endl;
                //std::cout << currentVertex->name << std::endl;
                glm::vec3 vertex_position = glm::vec3(*(currentVertex->x), *(currentVertex->y), *(currentVertex->z));

                float new_distance = distance(vertex_position, hit_position);

                if(new_distance < min_distance) {
                    min_distance = new_distance;
                    selectedVertex = currentVertex;
                }
            }
        }

        if (selectedVertex != NULL){
            /*std::cout << "GGGGG" << std::endl;*/
            std::cout << selectedVertex->index << std::endl;
            //std::cout << currReader->getVertName(selectedVertex->index) << std::endl;
            //std::cout << selectedVertex->faces.size() << std::endl;
            std::cout << currReader->getVertName(selectedVertex->index) << std::endl;
            //std::cout << selectedVertex->index << std::endl;
            /*std::cout << selectedVertex->faces.size() << std::endl;
            std::cout << selectedVertex->edges.size() << std::endl;*/

            selectedVertex -> selected = !selectedVertex -> selected;

            if (selectedVertex -> selected == true){
                selectedVerts.push_back(selectedVertex);
            }
            else{
                selectedVerts.remove(selectedVertex);
            }
        }

    }
    std::cout << "CLICKED ON SCREEN!" << std::endl;
}

void Session::selectEdge(int hits, unsigned int *names, double posX, double posY, double posZ){
    if(hits > 0) {
        glm::vec3 hit_position = glm::vec3(posX, posY, posZ);
        float min_distance = std::numeric_limits<float>::max();
        Reader* currReader = createReader(this);
        EdgeNew * currentEdge;
        EdgeNew * selectedEdge;

        for (int i = 0; i < hits; i++) {
            int currentID = names[i * 4 + 3];
            currentEdge = currReader->edge(currentID);
            if (currentEdge != NULL){
                std::cout << currentEdge->name << std::endl;
                currentEdge->v0->selected = false;
                currentEdge->v1->selected = false;
                selectedEdges.push_back(currentEdge);
                //selectedFace = currentFace;
            }
        }

        //selectedFace -> selected = !selectedFace -> selected;
    }
}

void Session::selectBorder(int hits, unsigned int *names, double posX, double posY, double posZ){
    std::cout << "CLICKED" << std::endl;
    std::cout << hits << std::endl;
    vector<Vert*> selectedVertsLoop = vector<Vert*>();

    if(hits > 0) {
        glm::vec3 hit_position = glm::vec3(posX, posY, posZ);
        float min_distance = std::numeric_limits<float>::max();
        Reader* currReader = createReader(this);
        Vert * startVert;
        Vert * selectedEdge;

        for (int i = 0; i < hits; i++) {
            int currentID = names[i * 4 + 3];
            startVert = currReader->getVert(currentID);
            //std::cout << "currentEdge->name" << std::endl;
            if (startVert != NULL){
                selectedVertsLoop = findLoop(startVert, selectedVertsLoop);
                //selectedFace = currentFace;
            }
        }
        //selectedFace -> selected = !selectedFace -> selected;
    }
}

std::vector<Vert*> Session::findLoop(Vert* startVert, std::vector<Vert*> selectedVertsLoop){
    for (EdgeNew* currEdge : startVert->edges){
        if (currEdge->isBorder()){
            currEdge->v0->selected = true;
            currEdge->v1->selected = true;
            selectedVertsLoop.push_back(startVert);
            selectedEdges.push_back(currEdge);
        }

    }
    return selectedVertsLoop;
}

void Session::selectFace(int hits, unsigned int *names, double posX, double posY, double posZ){
    if(hits > 0) {
        glm::vec3 hit_position = glm::vec3(posX, posY, posZ);
        float min_distance = std::numeric_limits<float>::max();
        Reader* currReader = createReader(this);
        FaceNew * currentFace;
        FaceNew * selectedFace;

        for (int i = 0; i < hits; i++) {
            int currentID = names[i * 4 + 3];
            currentFace = currReader->getFace(currentID);
            if (currentFace != NULL){
                selectedFace = currentFace;
                break;
            }
        }

        if (selectedFace != NULL){
            selectedFace -> selected = !selectedFace -> selected;
            if (selectedFace -> selected == true){
                std::cout << currReader->getFaceName(selectedFace->index) << std::endl;
                selectedFaces.push_back(selectedFace);
            }
            else{
                selectedFaces.remove(selectedFace);
            }
        }
    }
}

static std::string dbl2str(double d)
{
    size_t len = std::snprintf(0, 0, "%.10f", d);
    std::string s(len+1, 0);
    // technically non-portable, see below
    std::snprintf(&s[0], len+1, "%.10f", d);
    // remove nul terminator
    s.pop_back();
    // remove trailing zeros
    s.erase(s.find_last_not_of('0') + 1, std::string::npos);
    // remove trailing point
    if(s.back() == '.') {
        s.pop_back();
    }
    return s;
}

void Session::updateFileContentSliders()
{
	int offset = 0;
	for (BankNew * b0 : banks) {
		for (SetNew * s0 : b0->sets) {
			this->fileContent.replace(s0->begValPosFile + offset, s0->lengthValChar, dbl2str(s0->value));
			offset += dbl2str(s0->value).length() - s0->lengthValChar;
		}
	}
}

void Session::SaveSessionNom(std::string outputFile)
{
	updateFileContentSliders();

	ofstream file(outputFile);
    if (!file.is_open())
    {
        cout <<"Error: COULD NOT OPEN THE FILE.\n";
    }

    file<< this->fileContent;
}

void Session::deleteTmpFace(){
    if (tmpMesh != NULL){
        tmpMesh->faces.pop_back();
        tmpMesh->edges.clear();
        for (FaceNew* f: tmpMesh->faces){
            for (EdgeNew* e : f->edges){
                bool found = (std::find(tmpMesh->edges.begin(), tmpMesh->edges.end(), e) != tmpMesh->edges.end());
                if (!found){
                    tmpMesh->edges.push_back(e);
                }
            }
        }
        Reader* currReader = createReader(this);
        tmpInstance = createInstance(tmpMesh, this->verts, currReader, false, false, false, this, true);
        tmpInstance->setName("tmpInstance");
        tmpFaceIndex -= 1;
    }
}

void Session::groupFaces(std::string consolidateInstanceName, std::string consolidateMeshName){
    if (selectedFaces.size() != 0){
        Reader* currReader = createReader(this);
        tmpMesh = createMesh();
        tmpMesh->setName(consolidateMeshName);
        for (FaceNew* f : selectedFaces){
            tmpMesh->faces.push_back(f);
            for (EdgeNew* e : f->edges){
                if (!(std::find(tmpMesh->edges.begin(), tmpMesh->edges.end(), e) != tmpMesh->edges.end())){
                    tmpMesh->edges.push_back(e);
                }
            }
            for (Vert* v : f->verts){
                if (!(std::find(tmpMesh->verts.begin(), tmpMesh->verts.end(), v) != tmpMesh->verts.end())){
                    tmpMesh->verts.push_back(v);
                }
            }
        }

        meshes.push_back(tmpMesh);

        InstanceNew* newInstance;
        newInstance = createInstance(tmpMesh, this->verts, currReader, true, false, true, this, true);
        newInstance->setName(consolidateInstanceName);
        instances.push_back(newInstance);

        this->fileContent += "object ";
        this->fileContent += consolidateMeshName;
        this->fileContent += " (";
        for (FaceNew * currFace : selectedFaces){
            this->fileContent += currReader->getFaceName(currFace->index) + " ";
        }
        this->fileContent += ") endobject\n";
        this->fileContent += "instance " + consolidateInstanceName + " " + consolidateMeshName + " endinstance\n\n";

    }
}

void Session::addTmpFace(){
    if (selectedVerts.size() != 0){
        if (tmpMesh == NULL){
            tmpMesh = createMesh();
            tmpFaceIndex = 0;
            tmpPolylineIndex = 0;
        }
        Reader* currReader = createReader(this);
        FaceNew * newFace = createFace(selectedVerts, &(tmpMesh->edges), currReader, false);

        setTmpSurface(newFace);

        newFace->setName("f" + std::to_string(tmpFaceIndex));

        tmpMesh->faces.push_back(newFace);
        for (Vert * selectedVert: selectedVerts){
            tmpMesh->verts.push_back(selectedVert);
        }
        tmpMesh->setName("tmpMesh");

        tmpInstance = createInstance(tmpMesh, this->verts, currReader, false, false, false, this, true);
        tmpInstance->setName("tmpInstance");
        clearSelection();
        tmpFaceIndex += 1;
    }

    /*if (tmpMesh == NULL){
        tmpMesh = createMesh();
        tmpFaceIndex = 0;
    }
    Reader* currReader = createReader(this);
    FaceNew * newFace = createFace(selectedVerts, &(tmpMesh->edges), currReader, false);

    setTmpSurface(newFace);
    newFace->setName("f" + std::to_string(tmpFaceIndex));
    tmpMesh->faces.push_back(newFace);

    for (Vert * selectedVert: selectedVerts){
        tmpMesh->verts.push_back(selectedVert);
    }
    tmpMesh->setName("tmpMesh");
    tmpInstance = createInstance(tmpMesh, this->verts, currReader, false, true, false, this);
    tmpInstance->setName("tmpInstance");
    clearSelection();
    tmpFaceIndex += 1;*/
}

void Session::addTmpPolyline(){
    /*Reader* currReader = createReader(this);
    tmpPolyline = createPolylineNew(selectedVerts);
    tmpPolyline->setName("tmpPolyline");
    tmpInstance = createInstance(tmpPolyline, this->verts, currReader, false, true, false, this);
    tmpInstance->setName("tmpInstance");
    clearSelection();*/
    if (selectedVerts.size() != 0){
        if (tmpMesh == NULL){
            tmpMesh = createMesh();
            tmpFaceIndex = 0;
            tmpPolylineIndex = 0;
        }


        Reader* currReader = createReader(this);
        tmpPolyline = createPolylineNew(selectedVerts, &tmpMesh->edges);
        tmpPolyline->setName("poly" + std::to_string(tmpPolylineIndex));

        for (Vert * v: tmpPolyline->verts){
            tmpMesh->verts.push_back(v);
        }

        tmpMesh->polylines.push_back(tmpPolyline);

        tmpInstance = createInstance(tmpMesh, this->verts, currReader, false, false, false, this, true);
        tmpInstance->setName("tmpInstance");
        tmpPolylineIndex += 1;
        clearSelection();
    }
}

void Session::consolidateTmpMesh(std::string consolidateInstanceName, std::string consolidateMeshName){
    Reader* currReader = createReader(this);
    if (tmpInstance != NULL){
        for (FaceNew * tmpFace: tmpInstance->faces){
            setSurface(tmpFace, NULL);
        }
    }
    /*if (tmpPolyline != NULL){
        tmpPolyline->setName(consolidateMeshName);
        polylines.push_back(tmpPolyline);
        this->fileContent += "\npolyline " + consolidateMeshName + " (";

        for (Vert* currVert : tmpPolyline->verts){
            this->fileContent += currReader->getVertName(currVert->index) + " ";
        }

        this->fileContent += ") endpolyline\n";
    }*/
    if (tmpMesh != NULL){
        tmpMesh->setName(consolidateMeshName);
        meshes.push_back(tmpMesh);
        this->fileContent += "\nmesh " + consolidateMeshName + "\n";
        for (FaceNew * currFace : tmpMesh->faces){
            this->fileContent += "face " + currFace->name + " (";
            for (Vert* currVert : currFace->verts){
                this->fileContent += currReader->getVertName(currVert->index) + " ";
            }
            this->fileContent += ") endface\n";
        }

        for (PolylineNew * currPoly : tmpMesh->polylines){
            this->fileContent += "polyline " + (currPoly->name.substr(5)) + " (";
            for (Vert* currVert : tmpPolyline->verts){
                this->fileContent += currReader->getVertName(currVert->index) + " ";
            }

            this->fileContent += ") endpolyline\n";
        }

        this->fileContent += "endmesh\n";
    }
    if (tmpInstance != NULL){
        tmpInstance->setName(consolidateInstanceName);

        InstanceNew* newInstance;
        if (tmpMesh != NULL){
            newInstance = createInstance(tmpMesh, this->verts, currReader, true, false, true, this, true);
        }

        newInstance->setName(consolidateInstanceName);
        for (FaceNew * tmpFace: newInstance->faces){
            setSurface(tmpFace, NULL);
        }

        instances.push_back(newInstance);

        //instances.push_back(tmpInstance);
        this->fileContent += "instance " + consolidateInstanceName + " " + consolidateMeshName + " endinstance\n";
        for (Vert * v : newInstance->verts){
            for (TransformationNew * t : v->transformations){
                v->applyTransformation(t);
            }
        }

    }

    tmpMesh = NULL;
    tmpInstance = NULL;
    tmpPolyline = NULL;



    clearSelection();
}


void Session::clearSelection(){
    for (Vert * selectedVert: selectedVerts){
        selectedVert->selected = !selectedVert->selected;
    }

    for (EdgeNew * selectedEdge: selectedEdges){
        selectedEdge->v0->selected = false;
        selectedEdge->v1->selected = false;
    }


    for (FaceNew * selectedFace: selectedFaces){
        selectedFace->selected = !selectedFace->selected;
    }

    selectedFaces.clear();
    selectedVerts.clear();
    selectedEdges.clear();

    for (Vert * selectedVert: std::get<0>(tmpBorder)){
        selectedVert->selected = false;
    }
    for (EdgeNew * selectedEdge: std::get<1>(tmpBorder)){
        selectedEdge->selected = false;
    }
    isBorderSelected = false;

    for (std::tuple<std::vector<Vert*>, std::vector<EdgeNew*>> border : borders){
        for (EdgeNew * selectedEdge: std::get<1>(border)){
            selectedEdge->selected = false;
        }
    }
    borders.clear();

}

void Session::saveFileToStr(string fileName){
    ifstream inFile;
    inFile.open(fileName.c_str());//open the input file

    stringstream strStream;
    strStream << inFile.rdbuf();//read the file
    string str = strStream.str();
    this->fileContent = str;
}

void Session::parseSavedStr()
{
	extern int scanFromSessionFileContent(Session* s);
	scanFromSessionFileContent(this);
}

void Session::deleteFace(){
    Reader* currReader = createReader(this);
    this->fileContent += "\ndelete\n";
    for (FaceNew* selectedFace : selectedFaces){
        this->fileContent += "face " + currReader->getFaceName(selectedFace->index) + " endface\n";
        currReader->deleteFace(selectedFace);
    }
    this->fileContent += "enddelete\n";
    clearSelection();
}

void Session::draw(){
    //std::cout << "DRAW" << std::endl;
    for (std::list<InstanceNew*>::iterator itMesh = instances.begin(); itMesh != instances.end(); itMesh++){
        //std::cout << "TRUE INSTANCE" << std::endl;
        //std::cout << (*itMesh)->name << std::endl;
        (*itMesh)->draw(NULL);
    }

    if (tmpInstance != NULL){
        //std::cout << "TMP INSTANCE" << std::endl;
        tmpInstance->draw(NULL);
    }
}

void Session::zipBorders(){
    if (this->borders.size() == 2){
        std::cout << "Zippering borders." << std::endl;
        std::tuple<std::vector<Vert*>, std::vector<EdgeNew*>> border0;
        std::tuple<std::vector<Vert*>, std::vector<EdgeNew*>> border1;

        if (std::get<0>(borders[0]).size() <= std::get<0>(borders[1]).size()){
            border0 = borders[1];
            border1 = borders[0];
        } else{
            border0 = borders[0];
            border1 = borders[1];
        }

        std::vector<std::tuple<Vert*, Vert*>> closeVertices;

        double minDistance = DBL_MAX;
        Vert* closestVert = NULL;
        std::tuple<Vert*, Vert*> tupleList;
        for (Vert* vB0 : std::get<0>(border0)){
            minDistance = DBL_MAX;
            for (Vert* vB1 : std::get<0>(border1)){
                double distance = sqrt(pow((vB1->xTransformed - vB0->xTransformed), 2) + pow((vB1->yTransformed - vB0->yTransformed), 2) + pow((vB1->zTransformed - vB0->zTransformed), 2));
                if (distance < minDistance){
                    minDistance = distance;
                    //closestVert = vB1;
                    tupleList = std::make_tuple(vB0, vB1);
                }
            }
            closeVertices.push_back(tupleList);
        }
        if (tmpMesh == NULL){
            tmpMesh = createMesh();
            tmpFaceIndex = 0;
            tmpPolylineIndex = 0;
        }

        Reader* currReader = createReader(this);
        std::vector<std::tuple<Vert*, Vert*>>::iterator vv = closeVertices.begin();

        while (vv+1 != closeVertices.end()){
            //std::cout <<
            Vert* vert0a = std::get<0>(*vv);
            Vert* vert0b;
            if (vv+1 != closeVertices.end()){
                vert0b = std::get<0>(*(vv+1));
            } else{
                vert0b = std::get<0>(*(closeVertices.begin()));
            }
            Vert* vert1 = std::get<1>(*vv);

            std::list<Vert*> currentVertsList;
            currentVertsList.push_back(vert0a);
            currentVertsList.push_back(vert0b);
            currentVertsList.push_back(vert1);

            FaceNew * newFace = createFace(currentVertsList, &(tmpMesh->edges), currReader, false);
            setTmpSurface(newFace);
            newFace->setName("f" + std::to_string(tmpFaceIndex));
            tmpMesh->faces.push_back(newFace);

            for (Vert * selectedVert: currentVertsList){
                tmpMesh->verts.push_back(selectedVert);
            }
            tmpFaceIndex+=1;
            //==============

            Vert* vert2a = std::get<1>(*vv);
            Vert* vert2b;
            Vert* vert3;
            if (vv+1 != closeVertices.end()){
                vert2b = std::get<1>(*(vv+1));
                vert3 = std::get<0>(*(vv+1));
            } else{
                vert2b = std::get<1>(*(closeVertices.begin()));
                vert3 = std::get<0>(*(closeVertices.begin()));
            }
            //std::cout << std::get<1>(*(vv+1))->name << std::endl;
            //std::cout << std::get<0>(*(vv+1))->name << std::endl;

            if (!((vert2a->index == vert2b->index) || (vert2a->index == vert3->index))){
                std::list<Vert*> currentVertsList2;
                currentVertsList2.push_back(vert3);
                currentVertsList2.push_back(vert2b);
                currentVertsList2.push_back(vert2a);

                FaceNew * newFace2 = createFace(currentVertsList2, &(tmpMesh->edges), currReader, false);

                setTmpSurface(newFace2);

                newFace2->setName("f" + std::to_string(tmpFaceIndex));

                tmpMesh->faces.push_back(newFace2);
                for (Vert * selectedVert: currentVertsList2){
                    tmpMesh->verts.push_back(selectedVert);
                }

                tmpFaceIndex += 1;
            }

            vv++;
        }
        tmpMesh->setName("tmpMesh");
        tmpInstance = createInstance(tmpMesh, this->verts, currReader, false, false, false, this, true);
        tmpInstance->setName("tmpInstance");
        clearSelection();

    } else{
        std::cout << "2 borders must be selected to zip." << std::endl;
    }
}

void Session::mergeEdges(MeshNew* flattenMesh){

    // NEED TO MERGE EDGES NOW
    std::vector<std::tuple<EdgeNew*, EdgeNew*>> toBeMerged = std::vector<std::tuple<EdgeNew*, EdgeNew*>>();
    toBeMerged.clear();

    std::list<EdgeNew*>::iterator i = flattenMesh->edges.begin();
    int position = 0;
    while (i != flattenMesh->edges.end())
    {
        std::list<EdgeNew*>::iterator checkD = flattenMesh->edges.begin();
        std::advance(checkD, position + 1);
        while (checkD != flattenMesh->edges.end()){

            //std::cout << abs(*((*i)->v0->xTransformed) - *((*checkD)->v1->xTransformed)) + abs(*((*i)->v0->yTransformed) - *((*checkD)->v1->yTransformed)) + abs(*((*i)->v0->zTransformed) - *((*checkD)->v1->zTransformed)) << std::endl;
            //std::cout << abs(*((*i)->v1->xTransformed) - *((*checkD)->v0->xTransformed)) + abs(*((*i)->v1->yTransformed) - *((*checkD)->v0->yTransformed)) + abs(*((*i)->v1->zTransformed) - *((*checkD)->v0->zTransformed)) << std::endl;
            if ((abs(((*i)->v0->xTransformed) - ((*checkD)->v0->xTransformed)) < epsilon
                && abs(((*i)->v0->yTransformed) - ((*checkD)->v0->yTransformed)) < epsilon
                && abs(((*i)->v0->zTransformed) - ((*checkD)->v0->zTransformed)) < epsilon
                && abs(((*i)->v1->xTransformed) - ((*checkD)->v1->xTransformed)) < epsilon
                && abs(((*i)->v1->yTransformed) - ((*checkD)->v1->yTransformed)) < epsilon
                && abs(((*i)->v1->zTransformed) - ((*checkD)->v1->zTransformed)) < epsilon)
                || (abs(((*i)->v0->xTransformed) - ((*checkD)->v1->xTransformed)) < epsilon
                    && abs(((*i)->v0->yTransformed) - ((*checkD)->v1->yTransformed)) < epsilon
                    && abs(((*i)->v0->zTransformed) - ((*checkD)->v1->zTransformed)) < epsilon
                    && abs(((*i)->v1->xTransformed) - ((*checkD)->v0->xTransformed)) < epsilon
                    && abs(((*i)->v1->yTransformed) - ((*checkD)->v0->yTransformed)) < epsilon
                    && abs(((*i)->v1->zTransformed) - ((*checkD)->v0->zTransformed)) < epsilon)){
                //std::cout << "MERGED EDGES" << std::endl;
                /*std::cout << (*i)->index << std::endl;
                std::cout << (*checkD)->index << std::endl;
                std::cout << (*checkD)->f0 << std::endl;
                std::cout << (*checkD)->f1 << std::endl;
                std::cout << (*i)->v0->index << std::endl;
                std::cout << (*i)->v1->index << std::endl;
                std::cout << (*checkD)->v0->index << std::endl;
                std::cout << (*checkD)->v1->index << std::endl;*/
                toBeMerged.push_back(std::make_tuple(*i, *checkD));
                //if (ef->f)
            }

            checkD++;
        }

        position++;
        i++;
    }
    //std::cout << "DONE" << std::endl;
    /*for (EdgeNew* e : flattenMesh->edges){
        std::cout << "e->f0" << std::endl;
        std::cout << e->f0 << std::endl;
        std::cout << e->f1 << std::endl;
    }*/
    /*for (EdgeNew* e : flattenMesh->edges){
        std::cout << e->index << std::endl;
    }*/
    /*for (EdgeNew* e : flattenMesh->edges){
        std::cout << e->v0->index << std::endl;
        std::cout << e->v1->index << std::endl;
    }*/

    int count = 1;
    for (std::vector<std::tuple<EdgeNew*, EdgeNew*>>::iterator it = toBeMerged.begin() ; it != toBeMerged.end(); ++it){
        // a map where the keys are integers and the values are strings
        std::map<Vert*, Vert*> newVertexDict;
        newVertexDict.clear();


        if (abs((std::get<0>((*it))->v0->xTransformed) - (std::get<1>((*it))->v0->xTransformed)) < epsilon
                        && abs((std::get<0>((*it))->v0->yTransformed) - (std::get<1>((*it))->v0->yTransformed)) < epsilon
                        && abs((std::get<0>((*it))->v0->zTransformed) - (std::get<1>((*it))->v0->zTransformed)) < epsilon
                        && abs((std::get<0>((*it))->v1->xTransformed) - (std::get<1>((*it))->v1->xTransformed)) < epsilon
                        && abs((std::get<0>((*it))->v1->yTransformed) - (std::get<1>((*it))->v1->yTransformed)) < epsilon
                        && abs((std::get<0>((*it))->v1->zTransformed) - (std::get<1>((*it))->v1->zTransformed)) < epsilon){
            newVertexDict[std::get<1>((*it))->v0] = std::get<0>((*it))->v0;
            newVertexDict[std::get<1>((*it))->v1] = std::get<0>((*it))->v1;
        } else{
            //std::cout << "HI" << std::endl;
            newVertexDict[std::get<1>((*it))->v1] = std::get<0>((*it))->v0;
            newVertexDict[std::get<1>((*it))->v0] = std::get<0>((*it))->v1;
        }

        for (EdgeNew* e : std::get<1>((*it))->v1->edges){
            if (!(std::find(newVertexDict[std::get<1>((*it))->v1]->edges.begin(), newVertexDict[std::get<1>((*it))->v1]->edges.end(), e) != newVertexDict[std::get<1>((*it))->v1]->edges.end())){
                newVertexDict[std::get<1>((*it))->v1]->edges.push_back(e);
            }
        }

        for (FaceNew* f : std::get<1>((*it))->v1->faces){
            if (!(std::find(newVertexDict[std::get<1>((*it))->v1]->faces.begin(), newVertexDict[std::get<1>((*it))->v1]->faces.end(), f) != newVertexDict[std::get<1>((*it))->v1]->faces.end())){
                newVertexDict[std::get<1>((*it))->v1]->faces.push_back(f);
            }
        }

        for (EdgeNew* e : std::get<1>((*it))->v0->edges){
            if (!(std::find(newVertexDict[std::get<1>((*it))->v0]->edges.begin(), newVertexDict[std::get<1>((*it))->v0]->edges.end(), e) != newVertexDict[std::get<1>((*it))->v0]->edges.end())){
                newVertexDict[std::get<1>((*it))->v0]->edges.push_back(e);
            }
        }

        for (FaceNew* f : std::get<1>((*it))->v0->faces){
            if (!(std::find(newVertexDict[std::get<1>((*it))->v0]->faces.begin(), newVertexDict[std::get<1>((*it))->v0]->faces.end(), f) != newVertexDict[std::get<1>((*it))->v0]->faces.end())){
                newVertexDict[std::get<1>((*it))->v0]->faces.push_back(f);
            }
        }
        // Remove second edge from edge list
        //std::cout << newVertexDict.size() <<  std::endl;
        /*std::cout << "||||||||" << std::endl;
        std::cout << std::get<0>((*it))->v0->index << std::endl;
        std::cout << std::get<0>((*it))->v1->index << std::endl;
        std::cout << std::get<1>((*it))->v0->index << std::endl;
        std::cout << std::get<1>((*it))->v1->index << std::endl;*/

        // UPDATE THE VERTICES FOR NEIGHBOR EDGES
        /*for (EdgeNew* edgeM : std::get<1>(e)->v1->edges){
            std::cout << "LLL" << std::endl;
            newVertexDict[std::get<1>(e)->v1]->edges.push_back(edgeM);
        }*/

        //newVertexDict[std::get<1>(e)->v1]->edges.remove(std::get<1>(e));

        /*for (EdgeNew* edgeM : std::get<1>(e)->v0->edges){
            newVertexDict[std::get<1>(e)->v0]->edges.push_back(edgeM);
        }
        std::cout << "++++" << std::endl;*/
        //newVertexDict[std::get<1>(e)->v0]->edges.remove(std::get<1>(e));

        // UPDATE THE EDGES FOR NEIGHBOR FACES.
        FaceNew* faceToAppend0;
        if (std::get<1>((*it))->f0 != NULL){
            //std::cout << "HELLO" << std::endl;
            faceToAppend0 = std::get<1>((*it))->f0;
        } else{
            //std::cout << "BYE" << std::endl;
            faceToAppend0 = std::get<1>((*it))->f1;
        }

        if (std::get<0>((*it))->f0 == NULL){
            std::get<0>((*it))->f0 = faceToAppend0;
        } else if (std::get<0>((*it))->f1 == NULL){
            std::get<0>((*it))->f1 = faceToAppend0;
        } else{
            continue;
        }

        /*for (FaceNew* f0 : flattenMesh->edges){

        }*/
        //flattenMesh->edges.remove(std::get<1>(e));

        /*for (EdgeNew* ff : flattenMesh->edges){
            if (ff->v0->index == std::get<1>(e)->v1->index){
                ff->v0 = newVertexDict[std::get<1>(e)->v1];
            } else if (ff->v0->index == std::get<1>(e)->v0->index){
                ff->v0 = newVertexDict[std::get<1>(e)->v0];
            } else if (ff->v1->index == std::get<1>(e)->v1->index){
                ff->v1 = newVertexDict[std::get<1>(e)->v1];
            } else if (ff->v1->index == std::get<1>(e)->v0->index){
                ff->v1 = newVertexDict[std::get<1>(e)->v0];
            }
        }*/
        /*for (FaceNew* f0 : flattenMesh->faces){
            std::cout << f0->verts.size() << std::endl;
        }*/

        // NOW NEED TO UPDATE THE FACE DATA STRUCTURE
        for (FaceNew* f0 : flattenMesh->faces){
            if (!(std::find(f0->edges.begin(), f0->edges.end(), std::get<0>((*it))) != f0->edges.end())){
                std::replace (f0->edges.begin(), f0->edges.end(), std::get<1>((*it)), std::get<0>((*it)));
            } else{
                //std::cout << "std::get<1>((*it))->index" << std::endl;
                //std::cout << std::get<0>((*it))->index << std::endl;
                //std::cout << std::get<1>((*it))->index << std::endl;
                f0->edges.remove(std::get<1>((*it)));
            }
            if (!(std::find(f0->verts.begin(), f0->verts.end(), newVertexDict[std::get<1>((*it))->v0]) != f0->verts.end())){
                std::replace (f0->verts.begin(), f0->verts.end(), std::get<1>((*it))->v0, newVertexDict[std::get<1>((*it))->v0]);
            } else if (std::get<1>((*it))->v0->index != newVertexDict[std::get<1>((*it))->v0]->index){
                /*std::cout << "NNN" << std::endl;
                std::cout << std::get<1>((*it))->v0->index << std::endl;
                std::cout << newVertexDict[std::get<1>((*it))->v0]->index << std::endl;*/
                f0->verts.remove(std::get<1>((*it))->v0);
            }
            if (!(std::find(f0->verts.begin(), f0->verts.end(), newVertexDict[std::get<1>((*it))->v1]) != f0->verts.end())){
                std::replace (f0->verts.begin(), f0->verts.end(), std::get<1>((*it))->v1, newVertexDict[std::get<1>((*it))->v1]);
            } else if (std::get<1>((*it))->v1->index != newVertexDict[std::get<1>((*it))->v1]->index){
                /*std::cout << "OOO" << std::endl;
                std::cout << std::get<1>((*it))->v1->index << std::endl;
                std::cout << newVertexDict[std::get<1>((*it))->v1]->index << std::endl;*/
                f0->verts.remove(std::get<1>((*it))->v1);
            }
        }

        /*for (FaceNew* f0 : flattenMesh->faces){
            std::cout << f0->verts.size() << std::endl;
        }
        std::cout << "====" << std::endl;*/



        if (std::get<1>((*it))->v1->index != newVertexDict[std::get<1>((*it))->v1]->index){
            flattenMesh->verts.remove(std::get<1>((*it))->v1);
        }

        if (std::get<1>((*it))->v0->index != newVertexDict[std::get<1>((*it))->v0]->index){
            flattenMesh->verts.remove(std::get<1>((*it))->v0);
        }



        for (Vert* f0 : flattenMesh->verts){
            if (!(std::find(f0->edges.begin(), f0->edges.end(), std::get<0>((*it))) != f0->edges.end())){
                std::replace (f0->edges.begin(), f0->edges.end(), std::get<1>((*it)), std::get<0>((*it)));
            } else{
                f0->edges.remove(std::get<1>((*it)));
            }
        }


        flattenMesh->edges.remove(std::get<1>((*it)));
        for (EdgeNew* ff : flattenMesh->edges){
            //if (ff->index != std::get<1>(*it)->index){
            if (ff->v0->index == std::get<1>((*it))->v1->index){
                ff->v0 = newVertexDict[std::get<1>((*it))->v1];
            } else if (ff->v0->index == std::get<1>((*it))->v0->index){
                ff->v0 = newVertexDict[std::get<1>((*it))->v0];
            } else if (ff->v1->index == std::get<1>((*it))->v1->index){
                ff->v1 = newVertexDict[std::get<1>((*it))->v1];
            } else if (ff->v1->index == std::get<1>((*it))->v0->index){
                ff->v1 = newVertexDict[std::get<1>((*it))->v0];
            }
        }
        /*std::cout << newVertexDict[std::get<1>((*it))->v0] << std::endl;
        std::cout << newVertexDict[std::get<1>((*it))->v1] << std::endl;
        std::cout << "TEST" << std::endl;*/

        //std::cout << "DONE" << std::endl;
    }
    //std::cout << "DONE" << std::endl;

    /*for (EdgeNew* e : flattenMesh->edges){
        std::cout << e->v0->index << std::endl;
        std::cout << e->v1->index << std::endl;
    }
    std::cout << "DONE" << std::endl;*/
}

void Session::createFlattenMesh(bool instance){
    MeshNew* tmpflattenMesh = createMesh();
    if (instance){
        //std::cout << "INSTANCE" << std::endl;
        for (std::list<InstanceNew*>::iterator itMesh = instances.begin(); itMesh != instances.end(); itMesh++){
            (*itMesh)->flattenInstance(tmpflattenMesh);
        }
        //
        mergeEdges(tmpflattenMesh);
    }
    else{
        tmpflattenMesh = flattenMesh;
    }

    // http://www.rorydriscoll.com/2008/08/01/catmull-clark-subdivision-the-basics/
    // STEP 1: Calculate face points.
    if (this->subdivisionType == 0){
        for (FaceNew* currFace : tmpflattenMesh->faces){
            currFace->calculateFacePoint();
        }
    } else if (this->subdivisionType == 1){
        for (FaceNew* currFace : tmpflattenMesh->faces){
            currFace->calculateWeightedFacePoint();
        }
    }

    for (EdgeNew* currEdge : tmpflattenMesh->edges){
        currEdge->calculateEdgePoint();
    }

    for (Vert* currVert : tmpflattenMesh->verts){
        currVert->calculateVertPoint();
    }

    flattenMesh = tmpflattenMesh;
}

std::tuple<std::vector<Vert*>, std::vector<EdgeNew*>> Session::findBorder(Vert* startVert){
    std::vector<Vert*> borderVerts = std::vector<Vert*>();
    std::vector<EdgeNew*> seenEdges = std::vector<EdgeNew*>();

    borderVerts.push_back(startVert);

    return findBorderRec(startVert, borderVerts, seenEdges);
}

std::tuple<std::vector<Vert*>, std::vector<EdgeNew*>> Session::findBorderRec(Vert* startVert, std::vector<Vert*> borderVerts, std::vector<EdgeNew*> seenEdges){
    if ((startVert->index == borderVerts.front()->index) && (borderVerts.size() != 1)){
        return std::make_tuple(borderVerts, seenEdges);
    }

    for (EdgeNew* edge : startVert->edges){
        if (std::find(seenEdges.begin(), seenEdges.end(), edge) == seenEdges.end()){
            if ((edge->f0 == NULL) || (edge->f1 == NULL)){
                seenEdges.push_back(edge);
                std::tuple<std::vector<Vert*>, std::vector<EdgeNew*>> borderRet;
                if (startVert->index == edge->v0->index){
                    borderVerts.push_back(edge->v1);
                    borderRet = findBorderRec(edge->v1, borderVerts, seenEdges);
                } else {
                    borderVerts.push_back(edge->v0);
                    borderRet = findBorderRec(edge->v0, borderVerts, seenEdges);
                }

                if (std::get<0>(borderRet).size() != 0){
                    return borderRet;
                }

            }
        }
    }
    return std::make_tuple(std::vector<Vert*>(), std::vector<EdgeNew*>());
}

void Session::drawSubdivide(int subdivision, int previousSubdivisionLevel, double offset, bool calculateOffset, bool calculateSubdivide, bool calculateSlider){


    bool computeOffset = false;
    if (calculateSubdivide){
        if ((flattenMeshList.size() != 0) && (flattenMeshList.size() >= subdivision + 1)){
            computeOffset = true;
            flattenMesh = flattenMeshList[subdivision];
        } else{
            computeOffset = true;
            int startIndex = 0;
            if ((flattenMeshList.size() != 0)){
                startIndex = flattenMeshList.size() - 1;
            } else{
                createFlattenMesh(true);
                flattenMeshList.push_back(flattenMesh);
            }

            for (int i = startIndex; i < subdivision; i++){
                createFlattenMesh(false);
                flattenMesh = flattenMesh->subdivideMesh();
                flattenMeshList.push_back(flattenMesh);
            }
            flattenMesh->calculateNormal(this);

            /*std::cout << "+++++" << std::endl;
            for (FaceNew* f : flattenMesh->faces){
                if (f->mobius){
                    std::cout << "MOBIUS" << std::endl;
                    std::cout << f->verts.size() << std::endl;
                }
            }
            for (Vert* v : flattenMesh->verts){
                std::cout << v->mobiusFaces.size() << std::endl;
            }*/
        }

        subdivisionLevel = subdivision;
    }

    flattenMesh->draw(offset, (computeOffset || calculateOffset), outsideColor, insideColor, offsetColor, this);

    /*for (Vert* hello : flattenMesh->verts){
        drawVert(hello->vertPoint, NULL);
    }*/
    /*for (EdgeNew* hello : flattenMesh->edges){
        drawVert(hello->edgePoint, NULL);
    }*/
    /*for (FaceNew* hello : flattenMesh->faces){
        drawVert(hello->facePoint, NULL);
    }*/
}

void saveFaceSTL(FaceNew* currFace, std::ofstream& file){
    std::vector<double> normalVector = currFace->getNormal();
    std::list<Vert*>::iterator itVert = currFace->verts.begin();

    Vert* initVertex = *itVert;
    itVert++;
    Vert* currVertex = *itVert;
    itVert++;
    Vert* lastVert = *itVert;

    while (itVert != currFace->verts.end()){

        lastVert = *itVert;
        std::vector<Vert *> vL;
        vL.push_back(initVertex);
        vL.push_back(currVertex);
        vL.push_back(lastVert);
        std::vector<double> nV = getNormalFromVerts(vL);
        file << "  facet normal " + dbl2str(nV[0]) + " " + dbl2str(nV[1]) + " " + dbl2str(nV[2]) + "\n";
        file << "    outer loop\n";
        file << "      vertex " + dbl2str(roundf((initVertex->xTransformed) * 10000) / 10000) + " " + dbl2str(roundf((initVertex->yTransformed) * 10000) / 10000) + " " + dbl2str(roundf((initVertex->zTransformed) * 10000) / 10000) + "\n";
        file << "      vertex " + dbl2str(roundf((currVertex->xTransformed) * 10000) / 10000) + " " + dbl2str(roundf((currVertex->yTransformed) * 10000) / 10000) + " " + dbl2str(roundf((currVertex->zTransformed) * 10000) / 10000) + "\n";
        file << "      vertex " + dbl2str(roundf((lastVert->xTransformed) * 10000) / 10000) + " " + dbl2str(roundf((lastVert->yTransformed) * 10000) / 10000) + " " + dbl2str(roundf((lastVert->zTransformed) * 10000) / 10000) + "\n";
        file << "    endloop\n";
        file << "  endfacet\n";

        currVertex = lastVert;
        itVert++;
    }
}

void Session::SaveSessionStl(std::string outputFile){
    ofstream file(outputFile);
    if (!file.is_open())
    {
        cout <<"Error: COULD NOT OPEN THE FILE.\n";
    }

    if (flattenMesh == NULL){
        createFlattenMesh(true);
    }

    file << "solid convertedFile\n";
    if (flattenMesh->inFaces.size() == 0){
        for (FaceNew * currFace : flattenMesh->faces){
            saveFaceSTL(currFace, file);
        }
    }
    else{
        for (FaceNew * currFace : flattenMesh->inFaces){
            saveFaceSTL(currFace, file);
        }

        for (FaceNew * currFace : flattenMesh->outFaces){
            saveFaceSTL(currFace, file);
        }
    }

    file<< "endsolid convertedFile";
}

void parseGetBankVal(const char* input, Session* sessionParse, double* output, int lineNumber){
    //std::cout << "AAA" << std::endl;
    BankCompiler* bankCompilerSession = new BankCompiler (input, sessionParse, output, lineNumber);
    //std::cout << "BBB" << std::endl;
    //*output = bankCompilerSession->getResult();
}
