//
//  Mesh.cpp
//  model
//
//  Created by L on 26/08/2017.
//  Copyright © 2017 L. All rights reserved.
//

#include "MeshNew.h"
#include "Data.h"
#include "Session.h"
#include <unordered_map>

static int mIndex = 0;

///Mesh class methods, see header file for more details
bool MeshNew::hasVert(Vert* v0)
{
    return getVert(v0) != NULL;
}

bool MeshNew::hasEdge(EdgeNew* e0)
{
    return getEdge(e0) != NULL;
}

bool MeshNew::hasFace(FaceNew* f0)
{
    return getFace(f0) != NULL;
}
    
Vert* MeshNew::getVert(Vert* v0)
{
    for( Vert* v1 : this->verts )
    {
        if( v0->index == v1->index )
            return v1;
    }
    return NULL;
}

EdgeNew* MeshNew::getEdge(EdgeNew* e0)
{
    for( EdgeNew* e1 : this->edges )
    {
        if( e0->index == e1->index )
            return e1;
    }
    return NULL;
}

EdgeNew* MeshNew::getEdge(int i0, int i1)
{
    for( EdgeNew* e1 : this->edges )
    {
        if( ((e1->v0->index == i0) && (e1->v1->index == i1)) || ((e1->v1->index == i0) && (e1->v0->index == i1)) )
            return e1;
    }
    return NULL;
}

FaceNew* MeshNew::getFace(FaceNew* f0)
{
    for( FaceNew* f1 : this->faces )
    {
        if( f0->index == f1->index )
            return f1;
    }
    return NULL;
}
    
bool MeshNew::deleteVert(Vert* v0)
{
    deleteVert(v0);
    this->verts.remove(v0);
    return true;
}

bool MeshNew::deleteEdge(EdgeNew* e0)
{
    deleteEdge(e0);
    this->edges.remove(e0);
    return true;
}

bool MeshNew::deleteFace(FaceNew* f0)
{
    deleteFace(f0);
    this->faces.remove(f0);
    return true;
}

bool MeshNew::setName(std::string n)
{
    if(n.find(".") != std::string::npos && n.find(":") != std::string::npos)
        return false;
    name = n;
    bool error = updateNames();
    return error;
}

bool MeshNew::updateNames()
{
    for(Vert* v0 : verts)
    {
        v0->setPrefix(getFullName());
    }
    for(EdgeNew* e0 : edges)
    {
        e0->setPrefix(getFullName());
    }
    for(FaceNew* f0 : faces)
    {
        f0->setPrefix(getFullName());
    }
    return true;
}


///Instance functions
MeshNew* createMesh()
{
    MeshNew* m0 = new MeshNew();
    //std::list<Vert*> verts; std::list<EdgeNew*> edges; std::list<FaceNew*> faces;
    //m0->verts = verts; m0->edges = edges; m0->faces = faces;
    //This behaviour depends on the parser
    m0->verts = {};
    m0->edges = {};
    m0->faces = {};

    m0->setName("mesh" + std::to_string(mIndex));
    mIndex++;
    //std::cout << m0->getFullName() << std::endl;
    return m0;
}

Node* MeshNew::vert(std::string name)
{
    std::string str = findSubstring(name, 'v', ".");
    if(str.compare("") == 0)
        return NULL;
    std::string id = str.substr(3);
    for(Vert* v0 : verts)
    {
        if(v0->name.compare(id) == 0)
            return v0;
    }
    return NULL;
}

Node* MeshNew::edge(std::string name)
{
    std::string str = findSubstring(name, 'e', ".");
    if(str.compare("") == 0)
        return NULL;
    std::string id = str.substr(3);
    for(EdgeNew* e0 : edges)
    {
        if(e0->name.compare(id) == 0)
            return e0;
    }
    return NULL;
}

Node* MeshNew::face(std::string name)
{
    std::string str = findSubstring(name, 'f', ".");
    if(str.compare("") == 0)
        return NULL;
    std::string id = str.substr(3);
    for(FaceNew* f0 : faces)
    {
        if(f0->name.compare(id) == 0)
            return f0;
    }
    return NULL;
}

Node* MeshNew::vert(int i)
{
    for(Vert* v0 : verts)
    {
        if(v0->index == i)
            return v0;
    }
    return NULL;
}

Node* MeshNew::getVertByIndex(int i) {

    int counter = 0;
    for(Vert* v0 : verts)
    {
        if(counter == i)
            return v0;
        counter++;
    }
    return nullptr;
}

Node* MeshNew::edge(int i)
{
    for(EdgeNew* e0 : edges)
    {
        if(e0->index == i)
            return e0;
    }
    return NULL;
}

Node* MeshNew::face(int i)
{
    for(FaceNew* f0 : faces)
    {
        if(f0->index == i)
            return f0;
    }
    return NULL;
}

bool MeshNew::drawFaces()
{
    /*for(FaceNew* f : faces) {
      drawFace(f, NULL);
    }*/

    return true;
}

double dotProductNormal(std::vector<double> v1, std::vector<double> v2){
    return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}

bool MeshNew::draw(double offset, bool computeOffset, Surface* outsideColor, Surface* insideColor, Surface* offsetColor, Session* currSession)
{
    //std::cout << "DRAW" << std::endl;
    /*double *rIn = (double*) malloc(sizeof(double));
    double *gIn = (double*) malloc(sizeof(double));
    double *bIn = (double*) malloc(sizeof(double));
    *rIn = currSession->insideColor.red() / 255.0;
    *gIn = currSession->insideColor.green() / 255.0;
    *bIn = currSession->insideColor.blue() / 255.0;

    double *rOut = (double*) malloc(sizeof(double));
    double *gOut = (double*) malloc(sizeof(double));
    double *bOut = (double*) malloc(sizeof(double));
    *rOut = currSession->outsideColor.red() / 255.0;
    *gOut = currSession->outsideColor.green() / 255.0;
    *bOut = currSession->outsideColor.blue() / 255.0;

    double *rOffset = (double*) malloc(sizeof(double));
    double *gOffset = (double*) malloc(sizeof(double));
    double *bOffset = (double*) malloc(sizeof(double));
    *rOffset = currSession->offsetColor.red() / 255.0;
    *gOffset = currSession->offsetColor.green() / 255.0;
    *bOffset = currSession->offsetColor.blue() / 255.0;

    Surface* inSurf = createSurface(rIn, gIn, bIn, "inSurf");
    Surface* outSurf = createSurface(rOut, gOut, bOut, "outSurf");
    Surface* offsetSurf = createSurface(rOffset, gOffset, bOffset, "offsetSurf");*/

    Surface* inSurf = currSession->insideColor;
    Surface* outSurf = currSession->outsideColor;
    Surface* offsetSurf = currSession->offsetColor;

    if (offset == 0){
        if (currSession->normalVectShow){
            for (Vert* currVert : this->verts){
                drawNormal(currVert, NULL);
            }
        }
    }
    if (computeOffset == false){
        if (offset == 0){
            for (FaceNew* f0: faces){
                drawFace(f0, NULL, currSession);
            }
        } else{
            for (FaceNew* f0: inFaces){
                drawFace(f0, NULL, currSession);
            }
            for (FaceNew* f0: outFaces){
                drawFace(f0, NULL, currSession);
            }
        }
    } else{
        inFaces.clear();
        outFaces.clear();

        std::list<Vert*> listOutVert;
        std::list<Vert*> listInVert;
        Vert* lastVertSeen;

        /*double *r = (double*) malloc(sizeof(double));
        double *g = (double*) malloc(sizeof(double));
        double *b = (double*) malloc(sizeof(double));
        *r = 1.0;
        *g = 0.64;
        *b = 0.0;
        Surface* s = createSurface(r, g, b, "orange");*/

        for(FaceNew* f : faces) {
            listOutVert.clear();
            listInVert.clear();
            //std::cout << "DONE" << std::endl;
            for(Vert* v : f->verts) {
                v->updateOutOffsetVertex(offset);
                v->updateInOffsetVertex(offset);
                //std::cout << v->mobius << std::endl;


                //if (dotProductNormal(f->getNormal(), v->normal)>= 0){
                //if (v->mobius == true && f->mobius){
                //if (v->mobius == true && (std::find(v->mobiusFaces.begin(), v->mobiusFaces.end(), f) != v->mobiusFaces.end())){
                if (v->mobius == true && (std::find(v->facesReversed.begin(), v->facesReversed.end(), f) != v->facesReversed.end())){
                    //std::cout << v->facesReversed.size() << std::endl;
                    listOutVert.push_back(v->normalOutVert);
                    listInVert.push_back(v->normalInVert);
                }
                else{
                    listOutVert.push_back(v->normalInVert);
                    listInVert.push_back(v->normalOutVert);
                }


            }
            bool wasReversed = false;

            /*if (f->mobius){
                listInVert.swap(listOutVert);
                std::reverse(listInVert.begin(), listInVert.end());
                std::reverse(listOutVert.begin(), listOutVert.end());
                wasReversed = true;
            }*/
            std::reverse(listOutVert.begin(), listOutVert.end());


            if (offset != 0){
                //listInVert.reverse();
                FaceNew* newFace = createOffsetFace(listOutVert);
                outFaces.push_back(newFace);

                FaceNew* newInFace = createOffsetFace(listInVert);
                inFaces.push_back(newInFace);

                /*double *r = (double*) malloc(sizeof(double));
                double *g = (double*) malloc(sizeof(double));
                double *b = (double*) malloc(sizeof(double));
                *r = 0.0;
                *g = 0.0;
                *b = 1.0;*/
                //newInFace->surface = createSurface(r, g, b, "HELLO");
                newInFace->surface = outSurf;
                newFace->surface = inSurf;
                drawFace(newFace, NULL, currSession);
                drawFace(newInFace, NULL, currSession);

                Vert* startInVert;
                Vert* endInVert;
                Vert* startOutVert;
                Vert* endOutVert;
                int posStartIn = -1;
                int posEndIn = -1;
                int posStartOut = -1;
                int posEndOut = -1;

                // CREATE EDGE FACE
                for (EdgeNew* e : f->edges){
                    if (e->isBorder()){
                        std::list<Vert*> listEdgeVert;

                        if (e->v1->mobius == true
                                && (((e->f0 != NULL) && (std::find(e->v1->facesReversed.begin(), e->v1->facesReversed.end(), e->f0) != e->v1->facesReversed.end())) ||
                                ((e->f1 != NULL) && (std::find(e->v1->facesReversed.begin(), e->v1->facesReversed.end(), e->f1) != e->v1->facesReversed.end())))){

                            listEdgeVert.push_back(e->v1->normalOutVert);
                            listEdgeVert.push_back(e->v1->normalInVert);
                        } else{
                            listEdgeVert.push_back(e->v1->normalInVert);
                            listEdgeVert.push_back(e->v1->normalOutVert);
                        }

                        if ((e->v0->mobius == true)
                                && (((e->f0 != NULL) && (std::find(e->v0->facesReversed.begin(), e->v0->facesReversed.end(), e->f0) != e->v0->facesReversed.end())) ||
                                ((e->f1 != NULL) && (std::find(e->v0->facesReversed.begin(), e->v0->facesReversed.end(), e->f1) != e->v0->facesReversed.end())))){

                            listEdgeVert.push_back(e->v0->normalInVert);
                            listEdgeVert.push_back(e->v0->normalOutVert);
                        } else{
                            listEdgeVert.push_back(e->v0->normalOutVert);
                            listEdgeVert.push_back(e->v0->normalInVert);
                        }

                        FaceNew* testFace = createOffsetFace(listEdgeVert);
                        testFace->surface = offsetSurf;
                        outFaces.push_back(testFace);

                        drawFace(testFace, NULL, currSession);
                        /*startInVert = e->v0->normalInVert;
                        endInVert = e->v1->normalInVert;
                        startOutVert = e->v0->normalOutVert;
                        endOutVert = e->v1->normalOutVert;
                        int index = 0;
                        for (Vert* vIn : listInVert){
                            if (startInVert->index==vIn->index){
                                posStartIn = index;
                            }
                            if (endInVert->index==vIn->index){
                                posEndIn = index;
                            }
                            if (startOutVert->index==vIn->index){
                                posStartOut = index;
                            }
                            if (endOutVert->index==vIn->index){
                                posEndOut = index;
                            }
                            index++;
                        }

                        for (Vert* vIn : listOutVert){
                            if (startInVert->index==vIn->index){
                                posStartIn = index;
                            }
                            if (endInVert->index==vIn->index){
                                posEndIn = index;
                            }
                            if (startOutVert->index==vIn->index){
                                posStartOut = index;
                            }
                            if (endOutVert->index==vIn->index){
                                posEndOut = index;
                            }
                            index++;
                        }

                    std::list<Vert*> listEdgeVert;

                    if (posStartIn != -1 || posEndIn != -1 || posStartOut != -1 || posEndOut != -1){
                        //std::cout << "TEST" << std::endl;
                        if (wasReversed == true){
                            // MAYBE BUG WITH THIS PART NEED TO CHECK
                            // THIS PART IS FOR MOBIUS EDGES
                            if (posStartIn < posEndIn){
                                listEdgeVert.push_back(startInVert);
                                listEdgeVert.push_back(endOutVert);
                                listEdgeVert.push_back(endInVert);
                                listEdgeVert.push_back(startOutVert);
                            } else{
                                listEdgeVert.push_back(startInVert);
                                listEdgeVert.push_back(startOutVert);
                                listEdgeVert.push_back(endInVert);
                                listEdgeVert.push_back(endOutVert);
                            }
                        } else{
                            Vert* firstV;
                            if (posStartIn < posEndIn){
                                listEdgeVert.push_back(endInVert);
                                listEdgeVert.push_back(startInVert);
                            } else{
                                listEdgeVert.push_back(startInVert);
                                listEdgeVert.push_back(endInVert);
                            }

                            if (posStartOut < posEndOut){
                                listEdgeVert.push_back(endOutVert);
                                listEdgeVert.push_back(startOutVert);
                            } else{
                                listEdgeVert.push_back(startOutVert);
                                listEdgeVert.push_back(endOutVert);
                            }

                        }
                        FaceNew* testFace = createOffsetFace(listEdgeVert);
                        testFace->surface = offsetSurf;
                        outFaces.push_back(testFace);

                        drawFace(testFace, NULL, currSession);

                        }*/
                    }
                }


            } else {
                drawFace(f, NULL, currSession);
            }

        }



    }


    return true;
}

bool isInList(Vert* vert, std::list<Vert*> listOfStrs){
    std::list<Vert*>::iterator it;
    it = std::find(listOfStrs.begin(), listOfStrs.end(), vert);

    // Check if iterator points to end or not
    if(it != listOfStrs.end())
        return true;
    return false;
}

MeshNew* MeshNew::subdivideMesh(){
    MeshNew* newMesh = createMesh();
    // Iterating over all faces.
    for (FaceNew* currFace: this->faces){
        std::list<Vert*>::iterator vertIt = currFace->verts.begin();
        Vert * previousEdgePoint = NULL;
        // Iterating over all edges.
        for (EdgeNew* currEdge: currFace->edges){
            if (previousEdgePoint == NULL){
                previousEdgePoint = currEdge->edgePoint;
            }
            else{
                std::list<Vert*> listFace;
                listFace.clear();

                listFace.push_back(previousEdgePoint);
                listFace.push_back((*vertIt)->vertPoint);
                listFace.push_back(currEdge->edgePoint);
                listFace.push_back(currFace->facePoint);

                FaceNew* f0 = createFace(listFace, &(newMesh->edges), NULL, true);

                if(previousEdgePoint->inList == false){
                    newMesh->verts.push_back(previousEdgePoint);
                }
                if((*vertIt)->vertPoint->inList == false){
                    newMesh->verts.push_back((*vertIt)->vertPoint);
                }
                if(currEdge->edgePoint->inList == false){
                    newMesh->verts.push_back(currEdge->edgePoint);
                }
                if(currFace->facePoint->inList == false){
                    newMesh->verts.push_back(currFace->facePoint);
                }

                previousEdgePoint->inList = true;
                (*vertIt)->vertPoint->inList = true;
                currEdge->edgePoint->inList = true;
                currFace->facePoint->inList = true;

                newMesh->faces.push_back(f0);

                previousEdgePoint = currEdge->edgePoint;
            }

            vertIt++;
        }
        vertIt = currFace->verts.begin();
        std::list<EdgeNew*>::iterator edgeIt = currFace->edges.begin();
        std::list<Vert*> listFace;
        listFace.clear();
        listFace.push_back(previousEdgePoint);
        listFace.push_back((*vertIt)->vertPoint);
        listFace.push_back((*edgeIt)->edgePoint);
        listFace.push_back(currFace->facePoint);

        if (previousEdgePoint->inList == false){
            newMesh->verts.push_back(previousEdgePoint);
        }
        if((*vertIt)->vertPoint->inList == false){
            newMesh->verts.push_back((*vertIt)->vertPoint);
        }
        if((*edgeIt)->edgePoint->inList == false){
            newMesh->verts.push_back((*edgeIt)->edgePoint);
        }
        if(currFace->facePoint->inList == false){
            newMesh->verts.push_back(currFace->facePoint);
        }

        previousEdgePoint->inList = true;
        (*vertIt)->vertPoint->inList = true;
        (*edgeIt)->edgePoint->inList = true;
        currFace->facePoint->inList = true;

        FaceNew* f0 = createFace(listFace, &(newMesh->edges), NULL, true);

        newMesh->faces.push_back(f0);
    }
    return newMesh;
}

void MeshNew::calculateNormal(Session* currSession){
    for (Vert* currVert : this->verts){
        currVert->normal = {0, 0, 0};
        currVert->edgesSeen.clear();
        currVert->mobiusFaces.clear();
    }
    //std::cout <<"NN" << std::endl;

    // Calculate Face Normal
    for (FaceNew* currFace : this->faces){
        currFace->normal = {0, 0, 0};
        std::list<Vert*>::iterator it = currFace->verts.begin();
        std::vector<Vert*> firstVerts;


        int i = -1;
        while (it != currFace->verts.end()){

            if (i == 3){
                break;
            }

            if (firstVerts.size() == 3){

                // FOUND TWO EDGES
                // 0 not found
                // 1 good
                // 2 wrong order
                int foundE0 = 0;
                int foundE1 = 0;

                for (std::tuple<Vert*,Vert*> vertTuple : firstVerts[1]->edgesSeen){
                    if  (std::get<0>(vertTuple) == firstVerts[0] && std::get<1>(vertTuple) == firstVerts[1]){
                        // EDGE IS FOUND WE ARE GOOD
                        for (EdgeNew* e : currFace->edges){
                            if ((e->v0->index == firstVerts[0]->index && e->v1->index == firstVerts[1]->index) || (e->v1->index == firstVerts[0]->index && e->v0->index == firstVerts[1]->index)){
                                e->mobius = true;
                            }
                        }
                        foundE0 = 2;
                    } else if  (std::get<0>(vertTuple) == firstVerts[1] && std::get<1>(vertTuple) == firstVerts[0]){
                        // WRONG ORDER BUT GOOD AS CLOCKWISE
                        foundE0 = 1;
                    }

                    if  (std::get<0>(vertTuple) == firstVerts[1] && std::get<1>(vertTuple) == firstVerts[2]){
                        // EDGE IS FOUND WRONG ORDER
                        for (EdgeNew* e : currFace->edges){
                            if ((e->v0->index == firstVerts[1]->index && e->v1->index == firstVerts[2]->index) || (e->v1->index == firstVerts[1]->index && e->v0->index == firstVerts[2]->index)){
                                e->mobius = true;
                            }
                        }

                        foundE1 = 2;
                    } else if  (std::get<0>(vertTuple) == firstVerts[2] && std::get<1>(vertTuple) == firstVerts[1]){
                        // WRONG ORDER BUT GOOD AS CLOCKWISE


                        foundE1 = 1;
                    }
                }
                if (foundE0 == 0){
                    firstVerts[1]->edgesSeen.push_back(std::make_tuple (firstVerts[0], firstVerts[1]));
                }
                if (foundE1 == 0){
                    firstVerts[1]->edgesSeen.push_back(std::make_tuple (firstVerts[1], firstVerts[2]));
                }
                std::vector<Vert*> firstVertsOrder;
                for (Vert* v : firstVerts){
                    firstVertsOrder.push_back(v);
                }
                if (foundE0 == 2 || foundE1 == 2){
                    //std::reverse(firstVertsOrder.begin(), firstVertsOrder.end());
                    firstVerts[1]->mobius = true;
                    currFace->mobius = true;
                    firstVerts[1]->mobiusFaces.push_back(currFace);
                }

                std::vector<double> normalVector;
                normalVector = getNormalFromVertsForOffset(firstVertsOrder, this);

                /*if (firstVertsOrder[1]->name.compare("v:26") == 0){
                    std::cout << "============================" << std::endl;
                    std::cout << normalVector[0] << std::endl;
                    std::cout << normalVector[1] << std::endl;
                    std::cout << normalVector[2] << std::endl;
                }*/

                if (currSession->offsetType == 1){
                    currFace->normal[0] += normalVector[0];
                    currFace->normal[1] += normalVector[1];
                    currFace->normal[2] += normalVector[2];
                } else if (currSession->offsetType == 0){
                    double magnitude = sqrt(normalVector[0] * normalVector[0] + normalVector[1] * normalVector[1] + normalVector[2] * normalVector[2]);
                    double new_magnitude = abs(getAngleFromVerts(firstVertsOrder));

                    /*if (firstVertsOrder[1]->name.compare("v:26") == 0){
                        std::cout << "============================" << std::endl;
                        std::cout << magnitude << std::endl;
                        std::cout << new_magnitude << std::endl;
                        std::cout << normalVector[0] << std::endl;
                        std::cout << normalVector[1] << std::endl;
                        std::cout << normalVector[2] << std::endl;
                    }*/

                    normalVector[0] = normalVector[0] * (new_magnitude / magnitude);
                    normalVector[1] = normalVector[1] * (new_magnitude / magnitude);
                    normalVector[2] = normalVector[2] * (new_magnitude / magnitude);

                    firstVertsOrder[1] -> normal[0] += normalVector[0];
                    firstVertsOrder[1] -> normal[1] += normalVector[1];
                    firstVertsOrder[1] -> normal[2] += normalVector[2];
                }

                firstVerts.erase(firstVerts.begin());
            }
            firstVerts.push_back((*it));

            it++;

            if (i != -1){
                i++;
            }

            if ((i == -1) && (it == currFace->verts.end())){
                it = currFace->verts.begin();
                i++;
            }

        }

        currFace->normal[0] /= currFace->verts.size();
        currFace->normal[1] /= currFace->verts.size();
        currFace->normal[2] /= currFace->verts.size();
    }



    for (Vert* v : this->verts){
        std::vector<EdgeNew*> edgesToSee = std::vector<EdgeNew*>();
        std::vector<FaceNew*> faceToReverse = std::vector<FaceNew*>();

        if (v->mobius){
            int numMobius = 0;
            for (EdgeNew* e : v->edges){
                if (e->mobius){
                    if (!(std::find(faceToReverse.begin(), faceToReverse.end(), e->f0) != faceToReverse.end())
                        && !(std::find(faceToReverse.begin(), faceToReverse.end(), e->f1) != faceToReverse.end())){
                        // Red
                        bool didAddFace = false;
                        if (e->f0 != NULL){
                            if (!(std::find(faceToReverse.begin(), faceToReverse.end(), e->f0) != faceToReverse.end())){
                                faceToReverse.push_back(e->f0);
                                didAddFace = true;
                            }
                        } else if (e->f1 != NULL){
                            if (!(std::find(faceToReverse.begin(), faceToReverse.end(), e->f1) != faceToReverse.end())){
                                faceToReverse.push_back(e->f1);
                                didAddFace = true;
                            }
                        }

                        // Green
                        if (didAddFace == true){

                            for (EdgeNew* e1 : faceToReverse.back()->edges){
                                if ((e1->v0->index == v->index || e1->v1->index == v->index) && e->index != e1->index){
                                    edgesToSee.push_back(e1);
                                }
                            }

                            // Blue If it is a mobius then stop or if the face has already been reversed then stop
                            while (didAddFace && edgesToSee.back()->mobius != true
                                   && (!(std::find(faceToReverse.begin(), faceToReverse.end(), edgesToSee.back()->f0) != faceToReverse.end())
                                   || !(std::find(faceToReverse.begin(), faceToReverse.end(), edgesToSee.back()->f1) != faceToReverse.end()))){

                                didAddFace = false;
                                if (edgesToSee.back()->f0 != NULL && !(std::find(faceToReverse.begin(), faceToReverse.end(), edgesToSee.back()->f0) != faceToReverse.end())){
                                    //if (!(std::find(faceToReverse.begin(), faceToReverse.end(), e->f0) != faceToReverse.end())){
                                        faceToReverse.push_back(edgesToSee.back()->f0);
                                        didAddFace = true;
                                    //}
                                } else if (edgesToSee.back()->f1 != NULL && !(std::find(faceToReverse.begin(), faceToReverse.end(), edgesToSee.back()->f1) != faceToReverse.end())){
                                    //if (!(std::find(faceToReverse.begin(), faceToReverse.end(), e->f1) != faceToReverse.end())){
                                        faceToReverse.push_back(edgesToSee.back()->f1);
                                        didAddFace = true;
                                    //}
                                }

                                if (didAddFace == true){
                                    for (EdgeNew* e1 : faceToReverse.back()->edges){
                                        if (((e1->v0->index == v->index || e1->v1->index == v->index) && e->index != e1->index) && (std::find(edgesToSee.begin(), edgesToSee.end(), e1) == edgesToSee.end())){
                                            edgesToSee.push_back(e1);
                                        }
                                    }
                                }
                            }
                        }


                    }

                }
            }

            v->facesReversed = faceToReverse;

            v->normal = {0, 0, 0};

            for (FaceNew* f : v->faces){
                std::vector<Vert*> vv = std::vector<Vert*>();
                for (std::list<Vert*>::iterator it=f->verts.begin(); it != f->verts.end(); ++it){
                    if ((*f->verts.begin())->index == v->index){
                        vv.push_back(f->verts.back());
                        vv.push_back(*f->verts.begin());
                        vv.push_back(*(std::next(it, 1)));
                        break;
                    }

                    if (std::next(it, 1) != f->verts.end() && (*(std::next(it, 1)))->index == v->index){
                        vv.push_back(*it);
                        vv.push_back(*(std::next(it, 1)));
                        if (std::next(it, 2) != f->verts.end()){
                            vv.push_back(*(std::next(it, 2)));
                        } else{
                            vv.push_back(*(f->verts.begin()));
                        }
                    }

                }

                if ((std::find(faceToReverse.begin(), faceToReverse.end(), f) != faceToReverse.end())){
                    std::reverse(vv.begin(), vv.end());
                }

                std::vector<double> normalVector;
                normalVector = getNormalFromVertsForOffset(vv, this);

                if (currSession->offsetType == 0){
                    double magnitude = sqrt(normalVector[0] * normalVector[0] + normalVector[1] * normalVector[1] + normalVector[2] * normalVector[2]);
                    double new_magnitude = abs(getAngleFromVerts(vv));

                    normalVector[0] = normalVector[0] * (new_magnitude / magnitude);
                    normalVector[1] = normalVector[1] * (new_magnitude / magnitude);
                    normalVector[2] = normalVector[2] * (new_magnitude / magnitude);

                    v -> normal[0] += normalVector[0];
                    v -> normal[1] += normalVector[1];
                    v -> normal[2] += normalVector[2];
                }
            }

            //std::cout << edgesToSee.size() << std::endl;
            //std::cout << faceToReverse.size() << std::endl;

            //std::cout << numMobius << std::endl;
            //std::cout << v->edges.size() << std::endl;
        } else{
            v->facesReversed = faceToReverse;
        }

    }

    /*for (Vert* v : this->verts){
        if (v->mobius){
            std::unordered_map<FaceNew*, std::vector<std::tuple<Vert*, Vert*>>> mymap;

            for (FaceNew* f : v->faces){
                std::vector<std::tuple<Vert*, Vert*>> vv = std::vector<std::tuple<Vert*, Vert*>>();
                for (std::list<Vert*>::iterator it=f->verts.begin(); it != f->verts.end(); ++it){
                    if ((*f->verts.begin())->index == v->index){
                        vv.push_back(std::make_tuple(*(f->verts.end()), *(f->verts.begin())));
                        vv.push_back(std::make_tuple(*(f->verts.begin()), *(std::next(it, 1))));
                        break;
                    }

                    if (std::next(it, 1) != f->verts.end() && (*(std::next(it, 1)))->index == v->index){
                        vv.push_back(std::make_tuple(*it, *(std::next(it, 1))));
                        if (std::next(it, 2) != f->verts.end()){
                            vv.push_back(std::make_tuple(*(std::next(it, 1)), *(std::next(it, 2))));
                        } else{
                            vv.push_back(std::make_tuple(*(std::next(it, 1)), *(f->verts.begin())));
                        }
                    }
                }
                mymap[f] = vv;
            }
            std::cout << "mymap.size()" << std::endl;
            for ( auto it = mymap.begin(); it != mymap.end(); ++it ){

                std::cout << " " << it->first->index << ":" << it->second.size() << "\n";
            }
            std::cout << "DONE" << std::endl;
        }
    }*/


    if (currSession->offsetType == 1){
        for (FaceNew* currFace : this->faces){
            for (Vert* v : currFace->verts){
                v->edgesSeen.clear();
            }
        }

        // Calulcate Vertex Normal
        for (FaceNew* currFace : this->faces){
            std::list<Vert*>::iterator it = currFace->verts.begin();
            std::vector<Vert*> firstVerts;


            int i = -1;
            while (it != currFace->verts.end()){

                if (i == 3){
                    break;
                }

                if (firstVerts.size() == 3){

                    // FOUND TWO EDGES
                    // 0 not found
                    // 1 good
                    // 2 wrong order
                    int foundE0 = 0;
                    int foundE1 = 0;

                    for (std::tuple<Vert*,Vert*> vertTuple : firstVerts[1]->edgesSeen){
                        if  (std::get<0>(vertTuple) == firstVerts[0] && std::get<1>(vertTuple) == firstVerts[1]){
                            // EDGE IS FOUND WE ARE GOOD
                            foundE0 = 2;
                        } else if  (std::get<0>(vertTuple) == firstVerts[1] && std::get<1>(vertTuple) == firstVerts[0]){
                            // WRONG ORDER BUT GOOD AS CLOCKWISE
                            foundE0 = 1;
                        }

                        if  (std::get<0>(vertTuple) == firstVerts[1] && std::get<1>(vertTuple) == firstVerts[2]){
                            // EDGE IS FOUND WRONG ORDER
                            foundE1 = 2;
                        } else if  (std::get<0>(vertTuple) == firstVerts[2] && std::get<1>(vertTuple) == firstVerts[1]){
                            // WRONG ORDER BUT GOOD AS CLOCKWISE
                            foundE1 = 1;
                        }
                    }
                    if (foundE0 == 0){
                        firstVerts[1]->edgesSeen.push_back(std::make_tuple (firstVerts[0], firstVerts[1]));
                    }
                    if (foundE1 == 0){
                        firstVerts[1]->edgesSeen.push_back(std::make_tuple (firstVerts[1], firstVerts[2]));
                    }
                    std::vector<Vert*> firstVertsOrder;
                    for (Vert* v : firstVerts){
                        firstVertsOrder.push_back(v);
                    }
                    if (foundE0 == 2 || foundE1 == 2){
                        std::reverse(firstVertsOrder.begin(), firstVertsOrder.end());
                        firstVerts[1]->mobius = true;
                        currFace->mobius = true;
                        firstVerts[1]->mobiusFaces.push_back(currFace);
                    }

                    std::vector<double> normalVector;

                    normalVector = currFace->normal;

                    double magnitude = sqrt(normalVector[0] * normalVector[0] + normalVector[1] * normalVector[1] + normalVector[2] * normalVector[2]);
                    double new_magnitude = abs(getAngleFromVerts(firstVertsOrder));

                    int sign = 1;
                    if ((std::find(firstVertsOrder[1]->facesReversed.begin(), firstVertsOrder[1]->facesReversed.end(), currFace) != firstVertsOrder[1]->facesReversed.end())){
                        sign = -1;
                    }

                    normalVector[0] = normalVector[0] * (new_magnitude / magnitude);
                    normalVector[1] = normalVector[1] * (new_magnitude / magnitude);
                    normalVector[2] = normalVector[2] * (new_magnitude / magnitude);


                    firstVertsOrder[1] -> normal[0] += sign * normalVector[0];
                    firstVertsOrder[1] -> normal[1] += sign * normalVector[1];
                    firstVertsOrder[1] -> normal[2] += sign * normalVector[2];

                    firstVerts.erase(firstVerts.begin());
                }
                firstVerts.push_back((*it));

                it++;

                if (i != -1){
                    i++;
                }

                if ((i == -1) && (it == currFace->verts.end())){
                    it = currFace->verts.begin();
                    i++;
                }
            }
        }
    }
    for (Vert* currVert : this->verts){
        double magnitude = sqrt(currVert->normal[0] * currVert->normal[0] + currVert->normal[1] * currVert->normal[1] + currVert->normal[2] * currVert->normal[2]);
        if (magnitude == 0){
            currVert->normal[0] = 0.0;
            currVert->normal[1] = 0.0;
            currVert->normal[2] = 0.0;
        } else{
            currVert->normal[0] = currVert->normal[0] / magnitude;
            currVert->normal[1] = currVert->normal[1] / magnitude;
            currVert->normal[2] = currVert->normal[2] / magnitude;
        }
    }


}

bool MeshNew::setSurface(Surface* surface){
    this->surface = surface;
    return true;
}
