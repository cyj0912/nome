//
//  Data.cpp
//  model
//
//  Created by L on 26/08/2017.
//  Copyright © 2017 L. All rights reserved.
//


#include "Data.h"
#include "BankNew.h"
#include "Reader.h"
#include <QColor>
#include <QtOpenGL>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/glm.hpp>
#ifdef __APPLE__
#include <OpenGL/glu.h>
#else
#include <gl/glu.h>
#endif

#include <math.h>
#define PI 3.14159265

QColor defaultColor = QColor(255, 0, 0);
QColor tmpColor = QColor(255, 255, 0);



///Indices for data instantiation
static int vIndex = 0;
static int eIndex = 0;
static int fIndex = 0;

///Global locks for instancing - in case one day want to multithread
static std::mutex vertLock;
static std::mutex edgeLock;
static std::mutex faceLock;

double *getBankValue(std::string str, Session* currSession){
    //std::cout << "START BANK" << std::endl;
    auto first = str.find("$") + 1;
    auto last = str.find(".");
    string strNew = str.substr (first,last-first);

    for(auto b : currSession->banks) {
        if (b->name == strNew){
            for(auto s : b->sets) {
                if (s->name == str.substr(last + 1)){
                    //std::cout << s->value << std::endl;
                    return &s->value;
                }
            }
        }
    }

	std::cout << "Could not locate bank value: " << str << std::endl;

    //std::cout << "END BANK" << std::endl;
    return NULL;
}

///Surfaces
Surface* createSurface(double *r, double *g, double *b, std::string name)
{
    Surface * surface0 = new Surface();
    surface0->r = r;
    surface0->g = g;
    surface0->b = b;
    surface0->color = QColor(255 * *r, 255 * *g, 255 * *b);
    surface0->name = name;
    return surface0;
}

QColor Surface::getColor(){
    color = QColor(255 * *r, 255 * *g, 255 * *b);
    return color;
}

///Vertex functions
///Create a default vert, will be at the origin with weight of 1.0
Vert* createVert()
{
    double *x = (double*) malloc(sizeof(double));
    double *y = (double*) malloc(sizeof(double));
    double *z = (double*) malloc(sizeof(double));

    *x = 0.0;
    *y = 0.0;
    *z = 0.0;

    return createVert(x, y, z, 1.0);
}

///Create a vert with specified x, y, z values without having to specify a weight
Vert* createVert(double *x, double *y, double *z)
{
    return createVert(x, y, z, 1.0);
}

///Create a weighted vert at x, y, z value
Vert* createVert(double *x, double *y, double *z, double w)
{
    Vert* v0 = new Vert();
    v0->selected = false;
    vertLock.lock();
    int index = vIndex;
    vIndex++;
    vertLock.unlock();

    v0->index = index;
    v0->setName(std::to_string(index));
    v0->x = x;
    v0->y = y;
    v0->z = z;
    v0->mobius = false;
    v0->mobiusFaces = std::vector<FaceNew*>();

    double *xTr = (double*) malloc(sizeof(double));
    double *yTr = (double*) malloc(sizeof(double));
    double *zTr = (double*) malloc(sizeof(double));
    *xTr = *x;
    *yTr = *y;
    *zTr = *z;
    v0->setWorldPos(*xTr, *yTr, *zTr);

    v0->normalInVert = NULL;
    v0->normalOutVert = NULL;

    v0->weight = w;
    std::list<EdgeNew*> edges; std::list<FaceNew*> faces;
    v0->edges = edges; v0->faces = faces;
    v0->transformations = list<TransformationNew*>();
    
    return v0;
}

Vert* createVert(Vert* toBeCopied){
    double *x = (double*) malloc(sizeof(double));
    double *y = (double*) malloc(sizeof(double));
    double *z = (double*) malloc(sizeof(double));

    x = toBeCopied->x;
    y = toBeCopied->y;
    z = toBeCopied->z;

    return createVert(x, y, z, 1.0);
}

Vert* createDupVert(Vert* toBeCopied){
    double *x = (double*) malloc(sizeof(double));
    double *y = (double*) malloc(sizeof(double));
    double *z = (double*) malloc(sizeof(double));

    x = toBeCopied->x;
    y = toBeCopied->y;
    z = toBeCopied->z;

    Vert* dupVert = createVert(x, y, z, 1.0);
    dupVert->xStr = toBeCopied->xStr;
    dupVert->yStr = toBeCopied->yStr;
    dupVert->zStr = toBeCopied->zStr;
    for (TransformationNew* t : toBeCopied->transformations){
        dupVert->transformations.push_back(t);
    }
    //dupVert->transformations = std::list();
    //dupVert->transformations = std::list(toBeCopied->transformations);
    dupVert->x = toBeCopied->x;
    dupVert->y = toBeCopied->y;
    dupVert->z = toBeCopied->z;

    dupVert->xTransformed = toBeCopied->xTransformed;
    dupVert->yTransformed = toBeCopied->yTransformed;
    dupVert->zTransformed = toBeCopied->zTransformed;

    dupVert->weight = toBeCopied->weight;
    dupVert->selected = toBeCopied->selected;
    dupVert->mobius = toBeCopied->mobius;
    dupVert->inList = toBeCopied->inList;
    dupVert->edgesSeen = toBeCopied->edgesSeen;

    dupVert->index = toBeCopied->index;
    for (EdgeNew* t : toBeCopied->edges){
        dupVert->edges.push_back(t);
    }
    //dupVert->edges = std::list(toBeCopied->edges);
    for (FaceNew* t : toBeCopied->faces){
        dupVert->faces.push_back(t);
    }
    //dupVert->faces = std::list(toBeCopied->faces);
    dupVert->normal = toBeCopied->normal;
    dupVert->surface = toBeCopied->surface;
    dupVert->currSession = toBeCopied->currSession;
    dupVert->copyOfVert = toBeCopied->copyOfVert;
    dupVert->vertPoint = toBeCopied->vertPoint;
    dupVert->normalInVert = toBeCopied->normalInVert;
    dupVert->normalOutVert = toBeCopied->normalOutVert;
    return dupVert;
}

Vert* createVertSameId(Vert* toBeCopied){
    double *x = (double*) malloc(sizeof(double));
    double *y = (double*) malloc(sizeof(double));
    double *z = (double*) malloc(sizeof(double));

    x = toBeCopied->x;
    y = toBeCopied->y;
    z = toBeCopied->z;
    
    Vert* copiedV = createVert(x, y, z, 1.0);

    /*copiedV->xStr = strcpy(toBeCopied->xStr);
    copiedV->yStr = strcpy(toBeCopied->yStr);
    copiedV->zStr = strcpy(toBeCopied->zStr);*/
    
    return copiedV;
}


void Vert::updateOutOffsetVertex(double offset){
    if (this->normalOutVert == NULL){
        double *x = (double*) malloc(sizeof(double));
        double *y = (double*) malloc(sizeof(double));
        double *z = (double*) malloc(sizeof(double));

        *x = this->xTransformed + this->normal[0] * (offset / 2);
        *y = this->yTransformed + this->normal[1] * (offset / 2);
        *z = this->zTransformed + this->normal[2] * (offset / 2);

        this->normalOutVert = createVert(x, y, z, 1.0);
    } else{
        *this->normalOutVert->x = this->xTransformed + this->normal[0] * (offset / 2);
        *this->normalOutVert->y = this->yTransformed + this->normal[1] * (offset / 2);
        *this->normalOutVert->z = this->zTransformed + this->normal[2] * (offset / 2);
        this->normalOutVert->setWorldPos(*this->normalOutVert->x, *this->normalOutVert->y, *this->normalOutVert->z);
    }

}

void Vert::updateInOffsetVertex(double offset){
    if (this->normalInVert == NULL){
        double *x = (double*) malloc(sizeof(double));
        double *y = (double*) malloc(sizeof(double));
        double *z = (double*) malloc(sizeof(double));

        *x = this->xTransformed - this->normal[0] * (offset / 2);
        *y = this->yTransformed - this->normal[1] * (offset / 2);
        *z = this->zTransformed - this->normal[2] * (offset / 2);

        this->normalInVert = createVert(x, y, z, 1.0);
    } else{
        *this->normalInVert->x = this->xTransformed - this->normal[0] * (offset / 2);
        *this->normalInVert->y = this->yTransformed - this->normal[1] * (offset / 2);
        *this->normalInVert->z = this->zTransformed - this->normal[2] * (offset / 2);

        this->normalInVert->setWorldPos(*this->normalInVert->x, *this->normalInVert->y, *this->normalInVert->z);
    }
}

bool EdgeNew::isBorder(){
    if (this->f0 == NULL || this->f1 == NULL)
        return true;
    else{
        return false;
    }
}

///Edge functions
///Create an edge by specifying two points and knot interval, will create the links for the edge
///Currently assume manifold, so an edge shouldn't need more than two links
EdgeNew* createEdge(Vert* v0, Vert* v1, double interval, bool connect)
{
    EdgeNew* e0 = new EdgeNew();
    
    e0->interval = interval;
    edgeLock.lock();
    int index = eIndex;
    eIndex++;
    edgeLock.unlock();

    e0->v0 = v0;
    e0->v1 = v1;

    e0->f0 = NULL;
    e0->f1 = NULL;

    e0->index = index;
    e0->setName(std::to_string(index));
    e0->faceCount = 0;
    e0->vertCount = 0;
    
    // TODO
    //std::cout << "SEARCHING FOR EDGE" << std::endl;
    if (connect){
        bool isAlreadyInListV0 = false;
        for (EdgeNew* cE : v0->edges){
            if ((e0->v0->index == cE->v0->index && e0->v1->index == cE->v1->index) || (e0->v0->index == cE->v1->index && e0->v1->index == cE->v0->index)){
                isAlreadyInListV0 = true;
            }
        }

        bool isAlreadyInListV1 = false;
        for (EdgeNew* cE : v1->edges){
            if ((e0->v0->index == cE->v0->index && e0->v1->index == cE->v1->index) || (e0->v0->index == cE->v1->index && e0->v1->index == cE->v0->index)){
                isAlreadyInListV1 = true;
            }
        }

        if (!isAlreadyInListV0){
            v0->edges.push_back(e0);
        }
        if (!isAlreadyInListV1){
            v1->edges.push_back(e0);
        }
    }

    return e0;
}

///Create edge without specifying knot interval, default to 1.0
EdgeNew* createEdge(Vert* v0, Vert* v1, bool connect)
{
    return createEdge(v0, v1, 1.0, connect);
}

///Lazy construct, create edge without prior verts
EdgeNew* createEdge(double x0, double y0, double z0, double x1, double y1, double z1, double interval)
{
    Vert* v0 = createVert(&x0, &y0, &z0); Vert* v1 = createVert(&x1, &y1, &z1);
    return createEdge(v0, v1, interval);
}

///Face functions
///Create face helper function
FaceNew* createFace()
{
    FaceNew* f0 = new FaceNew();
    f0->selected = false;
    std::list<EdgeNew*> edges; std::list<Vert*> verts;
    f0->edges = edges; f0->verts = verts;
    
    faceLock.lock();
    int index = fIndex;
    fIndex++;
    faceLock.unlock();
    
    f0->index = index;
    f0->setName(std::to_string(index));
    return f0;
}

EdgeNew* createDupEdge(EdgeNew* toBeCopied){
    EdgeNew* e0 = new EdgeNew();
    e0->interval = toBeCopied->interval;
    e0->v0 = toBeCopied->v0;
    e0->v1 = toBeCopied->v1;
    e0->faceCount = toBeCopied->faceCount;
    e0->vertCount = toBeCopied->vertCount;
    e0->f0 = toBeCopied->f0;
    e0->f1 = toBeCopied->f1;
    e0->index = toBeCopied->index;
    e0->surface = toBeCopied->surface;
    e0->edgePoint = toBeCopied->edgePoint;
    return e0;
}

FaceNew* createDupFace(FaceNew* toBeCopied){
    FaceNew* f0 = new FaceNew();
    for (EdgeNew* t : toBeCopied->edges){
        f0->edges.push_back(t);
    }
    for (Vert* t : toBeCopied->verts){
        f0->verts.push_back(t);
    }
    f0->index = toBeCopied->index;
    f0->surface = toBeCopied->surface;
    f0->selected = toBeCopied->selected;
    f0->facePoint = toBeCopied->facePoint;
    f0->mobius = toBeCopied->mobius;
    return f0;
}

FaceNew* createOffsetFace(std::list<Vert*> verts)
{
    FaceNew* f0 = createFace();

    for (Vert* currVert : verts){
        f0->verts.push_back(currVert);
    }

    return f0;
}

FaceNew* createFace(std::list<Vert*> vertices, std::list<EdgeNew*> *edges, Reader * currReader, bool connect){
    //std::cout << "FACE NAME" << std::endl;
    /*for (Vert* cV : vertices){
        std::cout << "VERTEX NAME" << std::endl;
        std::cout << cV->name << std::endl;
        std::cout << cV->index << std::endl;
    }*/

    EdgeNew * currentEdge;
    std::list<Vert*>::iterator it = vertices.begin();
    std::list<Vert*>::iterator it2 = vertices.begin();
    std::list<EdgeNew*> currentEdges;
    ++it2;
    //std::cout << "START CREATE FACE" << std::endl;
    while (it != vertices.end()){
        if (it2 != vertices.end()){
            /*std::cout << (*it)->index << std::endl;
            std::cout << (*it)->name << std::endl;
            std::cout << (*it2)->index << std::endl;
            std::cout << (*it2)->name << std::endl;
            std::cout << "MM" << std::endl;*/
            currentEdge = NULL;

            for (auto e0 : (*it)->edges){
                if ((e0->v0->index == (*it)->index && e0->v1->index == (*it2)->index) || (e0->v0->index == (*it2)->index && e0->v1->index == (*it)->index)){
                    currentEdge = e0;
                }
            }
            if (currentEdge == NULL){
                for (auto e0 : (*it2)->edges){
                    if ((e0->v0->index == (*it)->index && e0->v1->index == (*it2)->index) || (e0->v0->index == (*it2)->index && e0->v1->index == (*it)->index)){
                        currentEdge = e0;
                    }
                }
            }

            if (currentEdge == NULL && currReader != NULL){
                currentEdge = currReader->getEdge((*it)->index, (*it2)->index);
                if (currentEdge != NULL){
                    if (connect){
                        (*it)->edges.push_back(currentEdge);
                        (*it2)->edges.push_back(currentEdge);
                        //currentEdge->faceCount += 1;
                    }
                }
            }

            if (currentEdge == NULL){
                currentEdge = createEdge(*it, *it2, connect);
            }
            it2++;
        }
        else{
            currentEdge = NULL;

            for (auto e0 : vertices.back()->edges){
                if ((e0->v0->index == vertices.back()->index && e0->v1->index == vertices.front()->index) || (e0->v0->index == vertices.front()->index && e0->v1->index == vertices.back()->index)){
                    currentEdge = e0;
                }
            }
            if (currentEdge == NULL){
                for (auto e0 : vertices.front()->edges){
                    if ((e0->v0->index == vertices.back()->index && e0->v1->index == vertices.front()->index) || (e0->v0->index == vertices.front()->index && e0->v1->index == vertices.back()->index)){
                        currentEdge = e0;
                    }
                }
            }

            /*for( auto e0 : *edges ) {
                if ((e0->v0->index == vertices.back()->index && e0->v1->index == vertices.front()->index) || (e0->v0->index == vertices.front()->index && e0->v1->index == vertices.back()->index)){
                    currentEdge = e0;
                }
            }*/

            if (currentEdge == NULL && currReader != NULL){
                currentEdge = currReader->getEdge(vertices.back()->index, vertices.front()->index);
                if (currentEdge != NULL){
                    if (connect){
                        vertices.back()->edges.push_back(currentEdge);
                        vertices.front()->edges.push_back(currentEdge);
                        //currentEdge->faceCount += 1;
                    }
                }
            }

            if (currentEdge == NULL){
                //std::cout << "CREATE" << std::endl;
                currentEdge = createEdge(vertices.back(), vertices.front(), connect);
            }
        }
        it++;

        bool found = (std::find(edges->begin(), edges->end(), currentEdge) != edges->end());

        if (!found){
            edges->push_back(currentEdge);
        }

        currentEdges.push_back(currentEdge);
        currentEdge = NULL;
    }
    //std::cout << currentEdges.size() << std::endl;
    //std::cout << "END CREATE FACE" << std::endl;
    FaceNew* newFace;
    if (connect){
        //std::cout << "NEW" << std::endl;
        newFace = createFace(currentEdges, vertices);
    }
    else{
        //std::cout << "NOT" << std::endl;
        newFace = createFace();
        newFace->selected = false;
        newFace->verts = vertices;
        newFace->edges = currentEdges;
    }
    //TOFO
    //FaceNew* newFace = createFace(currentEdges, vertices);
    /*newFace->verts.clear();

    for (Vert* vert : vertices){
        newFace->verts.push_back(vert);
    }*/
    /*std::cout << "EDGES" << std::endl;
    for (EdgeNew* e : newFace->edges){
        std::cout << e->v0->index << std::endl;
        std::cout << e->v1->index << std::endl;
    }*/


    /*std::cout << "VERTS" << std::endl;
    for (Vert* e : newFace->verts){
        std::cout << e->index << std::endl;
        std::cout << e->name << std::endl;
        std::cout << "NUMBER OF EDGES" << std::endl;
        std::cout << e->edges.size() << std::endl;
    }*/

    return newFace;
}

///Create face given a vector of at least three edges, the edges must be adjacent and form a closed loop, otherwise fails
FaceNew* createFace(std::list<EdgeNew*> edges, std::list<Vert*> verts)
{

    /*std::cout << "HHHHHHHHHHH" << std::endl;
    for (Vert* v: verts){
        std::cout << v->name << std::endl;
    }
    std::cout << "NNNN" << std::endl;*/
    FaceNew* f0 = createFace();
    f0->selected = false;
    std::vector<Vert*> vIndex;

    //Check if more than three edges are given
    if(edges.size() < 3)
    {
        errorMessage("Fewer than 3 edges given", -1);
        return NULL;
    }

    std::list<Vert*>::iterator vertsIt = verts.begin();
    for( EdgeNew* edge : edges )
    {
        if (edge->f0 == NULL){
            edge->f0 = f0;
        }
        else{
            //std::cout << "HELLO" << std::endl;
            /*std::cout << "F1" << std::endl;
            std::cout << edge->faceCount << std::endl;
            std::cout << edge->v0->name << std::endl;
            std::cout << edge->v1->name << std::endl;
            if (edge->f0 != NULL){
                std::cout << edge->f0->name << std::endl;
            }
            if (edge->f1 != NULL){
                std::cout << edge->f1->name << std::endl;
            }*/
            edge->f1 = f0;
        }
        //std::cout << edge->f0 << std::endl;
        //std::cout << edge->f1 << std::endl;

        bool b0 = false, b1 = false;
        for( int i = 0; i < vIndex.size(); i++ )
        {
            b0 = b0 | (vIndex[i]->index == edge->v0->index);
            b1 = b1 | (vIndex[i]->index == edge->v1->index);
        }

        if ((*vertsIt)->index == edge->v0->index){
            if( !b0 ) {
                bool found = (std::find(f0->verts.begin(), f0->verts.end(), edge->v0) != f0->verts.end());
                if (!found){
                    f0->verts.push_back(edge->v0);
                    vIndex.push_back(edge->v0);
                }
            }
            if( !b1 ) {
                bool found = (std::find(f0->verts.begin(), f0->verts.end(), edge->v1) != f0->verts.end());
                if (!found){
                    f0->verts.push_back(edge->v1);
                    vIndex.push_back(edge->v1);
                }
            }
        } else{
            if( !b1 ) {
                bool found = (std::find(f0->verts.begin(), f0->verts.end(), edge->v1) != f0->verts.end());
                if (!found){
                    f0->verts.push_back(edge->v1);
                    vIndex.push_back(edge->v1);
                }
            }

            if( !b0 ) {
                bool found = (std::find(f0->verts.begin(), f0->verts.end(), edge->v0) != f0->verts.end());
                if (!found){
                    f0->verts.push_back(edge->v0);
                    vIndex.push_back(edge->v0);
                }
            }
        }
        vertsIt++;

        f0->edges.push_back(edge);

        //Check if an edge has more than two adjacent faces
        if( edge->faceCount == 0 )
        {
            edge->f0 = f0;
            edge->faceCount = 1;
        }
        else if (edge->faceCount == 1)
        {
            edge->f1 = f0;
            edge->faceCount = 2;
        }
        else
        {
            errorMessage("Invalid edges given for a face, edges can be adjacent to at most 2 faces.", -1);
            return NULL;
        }
        /*std::cout << "EDGE NUMBER" << std::endl;
        std::cout << edge->v0->name << std::endl;
        std::cout << edge->v1->name << std::endl;
        std::cout << edge->f0 << std::endl;
        std::cout << edge->f1 << std::endl;
        std::cout << edge->faceCount << std::endl;*/
    }

    //Check if edges given are adjacent
    if( vIndex.size() != edges.size() )
    {
        errorMessage("Edges given are not all adjacent", -1);
        return NULL;
    }
    //Add reference to the face for all the vertices in the face
    for( Vert* vert: vIndex )
        vert->faces.push_back(f0);

    /*for( EdgeNew* edge: f0->edges ){
        std::cout << "EDGE NUMBER" << std::endl;
        std::cout << edge->v0->name << std::endl;
        std::cout << edge->v1->name << std::endl;
        std::cout << edge->f0 << std::endl;
        std::cout << edge->f1 << std::endl;
        std::cout << edge->faceCount << std::endl;
    }*/

    return f0;
}

bool setName(Vert* v0, std::string n)
{
    return v0->setName(n);
}

bool setName(EdgeNew* e0, std::string n)
{
    return e0->setName(n);
}

bool setName(FaceNew* f0, std::string n)
{
    return f0->setName(n);
}


bool setSurface(FaceNew* f0, Surface* surface){
    f0->surface = surface;
    return true;
}

bool setSurface(Vert* v0, Surface* surface){
    v0->surface = surface;
    return true;
}

bool setSurface(EdgeNew* e0, Surface* surface){
    e0->surface = surface;
    return true;
}

bool setTmpSurface(FaceNew* f0){
    double *r = (double*) malloc(sizeof(double));
    double *g = (double*) malloc(sizeof(double));
    double *b = (double*) malloc(sizeof(double));

    *r = 1.0;
    *g = 1.0;
    *b = 0.0;
    Surface * tmpSurface = createSurface(r, g, b, "tmpSurface");
    f0->surface = tmpSurface;
    return true;
}

///Deletion functions
///When a vertex is deleted, the adjacent edges and faces are also deleted
bool deleteVert(Vert* vert)
{
    if (!vert)
        return false;
    for(EdgeNew* e : vert->edges)
    {
        deleteEdge(e);
    }
    for(FaceNew* f : vert->faces)
    {
        deleteFace(f);
    }
    vert->edges.clear(); vert->faces.clear();
    return vert->edges.empty() && vert->faces.empty();
}

///When an edge is deleted, the two end verts are deleted as are the two adjacent faces
bool deleteEdge(EdgeNew* edge)
{
    if(!edge)
        return false;
    if(edge->vertCount == 2)
    { deleteVert(edge->v0); deleteVert(edge->v1); edge->vertCount = 0; }
    else if (edge->vertCount == 1)
    { deleteVert(edge->v0); edge->vertCount = 0; }
    if(edge->faceCount == 2)
    { deleteFace(edge->f0); deleteFace(edge->f1); edge->faceCount = 0; }
    else if (edge->faceCount == 1)
    { deleteFace(edge->f0); edge->faceCount = 0; }
    return edge->vertCount == 0 && edge->faceCount == 0;
}

///When a face is deleted, the neighbouring edges and vertices are not
bool deleteFace(FaceNew* face)
{
    if(!face)
        return false;
    for(Vert* v0 : face->verts)
    {
        v0->faces.remove(face);
    }
    for(EdgeNew* e0 : face->edges)
    {
        if(e0->f0 == face)
        { e0->f0 = e0->f1; e0->faceCount = 1; }
        else if(e0->f1 == face)
        { e0->faceCount = 1; }
    }
    face->edges.clear(); face->verts.clear();

    return face->edges.empty() && face->verts.empty();
}


bool drawVert(Vert* v0, Surface * instSurface, Session* currSession){
    //std::cout << v0->index << std::endl;

    QColor color;
    if (instSurface != NULL){
        color = instSurface->color;
    } else if (v0->surface != NULL){
        color = v0->surface->getColor();
    } else {
        color = currSession->foreColor->getColor();
    }


    GLfloat fcolor[4] = {0,0,0,0};
    if (v0->selected){
        fcolor[0] = 255 - currSession->foreColor->getColor().red();
        fcolor[1] = 255 - currSession->foreColor->getColor().green();
        fcolor[2] = 255 - currSession->foreColor->getColor().blue();
        fcolor[3] = 0;
        glDepthRange(0.0, 0.999);
    } else {
        fcolor[0] = 1.0f * color.red() / 255;
        fcolor[1] = 1.0f * color.green() / 255;
        fcolor[2] = 1.0f * color.blue() / 255;
        fcolor[3] = 1.0f * color.alpha() /255;
    }

    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, fcolor);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, fcolor);

    glLoadName(v0->index);

    float x = v0->xTransformed;
    float y = v0->yTransformed;
    float z = v0->zTransformed;
    glBegin(GL_QUADS);
        glNormal3f(0, 0, 1);
        glVertex3f(x + 0.1 / 2, y + 0.1 / 2, z);
        glVertex3f(x - 0.1 / 2, y + 0.1 / 2, z);
        glVertex3f(x - 0.1 / 2, y - 0.1 / 2, z);
        glVertex3f(x + 0.1 / 2, y - 0.1 / 2, z);
    glEnd();
    glLoadName(v0->index);
    glBegin(GL_QUADS);
        glNormal3f(1, 0, 0);
        glVertex3f(x, y + 0.1 / 2, z + 0.1 / 2);
        glVertex3f(x, y - 0.1 / 2, z + 0.1 / 2);
        glVertex3f(x, y - 0.1 / 2, z - 0.1 / 2);
        glVertex3f(x, y + 0.1 / 2, z - 0.1 / 2);
    glEnd();
    glLoadName(v0->index);
    glBegin(GL_QUADS);
        glNormal3f(0, 1, 0);
        glVertex3f(x + 0.1 / 2, y, z - 0.1 / 2);
        glVertex3f(x + 0.1 / 2, y, z + 0.1 / 2);
        glVertex3f(x - 0.1 / 2, y, z + 0.1 / 2);
        glVertex3f(x - 0.1 / 2, y, z - 0.1 / 2);
    glEnd();

    if (v0->selected)
        glDepthRange(0.0, 1.0);
    return true;
}

bool drawEdge(EdgeNew* e0, Surface * instSurface, Session* currSession)
{
    QColor color;
    if (instSurface != NULL){
        color = instSurface->color;
    } else if (e0->surface != NULL){
        color = e0->surface->getColor();
    } else{
        color = currSession->foreColor->getColor();;
    }

    GLfloat fcolor[4] = {0,0,0,0};
    if (e0->selected){
        fcolor[0] = 255 - currSession->foreColor->getColor().red();
        fcolor[1] = 255 - currSession->foreColor->getColor().green();
        fcolor[2] = 255 - currSession->foreColor->getColor().blue();
        fcolor[3] = 0;
    } else {
        fcolor[0] = 1.0f * color.red() / 255;
        fcolor[1] = 1.0f * color.green() / 255;
        fcolor[2] = 1.0f * color.blue() / 255;
        fcolor[3] = 1.0f * color.alpha() /255;
    }
    //glLineWidth(2.5);

    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, fcolor);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, fcolor);
    glLoadName(e0->index);
    glBegin(GL_LINE_STRIP);
        glVertex3f(e0->v0->xTransformed, e0->v0->yTransformed, e0->v0->zTransformed);
        glVertex3f(e0->v1->xTransformed, e0->v1->yTransformed, e0->v1->zTransformed);
    glEnd();
    return true;
}

double getAngleFromVerts(std::vector<Vert*> vert1){
    std::vector<double> a;
    a.push_back((vert1[0]->xTransformed) - (vert1[1]->xTransformed));
    a.push_back((vert1[0]->yTransformed) - (vert1[1]->yTransformed));
    a.push_back((vert1[0]->zTransformed) - (vert1[1]->zTransformed));

    std::vector<double> b;
    b.push_back((vert1[2]->xTransformed) - (vert1[1]->xTransformed));
    b.push_back((vert1[2]->yTransformed) - (vert1[1]->yTransformed));
    b.push_back((vert1[2]->zTransformed) - (vert1[1]->zTransformed));

    double dotProduct = a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
    double magnitudeA = sqrt(pow(a[0], 2) + pow(a[1], 2) + pow(a[2], 2));
    double magnitudeB = sqrt(pow(b[0], 2) + pow(b[1], 2) + pow(b[2], 2));

    double cosAngle = dotProduct / (magnitudeA * magnitudeB);
    double angle = acos(cosAngle) * 180.0 / PI;;

    return angle;
}

std::vector<double> getNormalFromVerts(std::vector<Vert*> vert1){
    std::vector<double> a;
    a.push_back(((vert1[0]->xTransformed) - (vert1[1]->xTransformed)));
    a.push_back(((vert1[0]->yTransformed) - (vert1[1]->yTransformed)));
    a.push_back(((vert1[0]->zTransformed) - (vert1[1]->zTransformed)));

    std::vector<double> b;
    b.push_back(((vert1[2]->xTransformed) - (vert1[1]->xTransformed)));
    b.push_back(((vert1[2]->yTransformed) - (vert1[1]->yTransformed)));
    b.push_back(((vert1[2]->zTransformed) - (vert1[1]->zTransformed)));

    double xCross = (b[1]*a[2] - b[2]*a[1]);
    double yCross = (b[2]*a[0] - b[0]*a[2]);
    double zCross = (b[0]*a[1] - b[1]*a[0]);
    double norm = sqrt(pow(xCross, 2) + pow(yCross, 2) + pow(zCross, 2));

    std::vector<double> aCrossb;
    aCrossb.push_back(xCross / norm);
    aCrossb.push_back(yCross / norm);
    aCrossb.push_back(zCross / norm);

    return aCrossb;
}

std::vector<double> getNormalFromVertsForOffset(std::vector<Vert*> vert1, MeshNew* mesh){
    // Takes into account the mobius edges
    std::vector<double> a;
    std::vector<double> b;
    a.push_back((vert1[0]->xTransformed) - (vert1[1]->xTransformed));
    a.push_back((vert1[0]->yTransformed) - (vert1[1]->yTransformed));
    a.push_back((vert1[0]->zTransformed) - (vert1[1]->zTransformed));


    b.push_back((vert1[1]->xTransformed) - (vert1[2]->xTransformed));
    b.push_back((vert1[1]->yTransformed) - (vert1[2]->yTransformed));
    b.push_back((vert1[1]->zTransformed) - (vert1[2]->zTransformed));

    double xCross = (a[1]*b[2] - a[2]*b[1]);
    double yCross = (a[2]*b[0] - a[0]*b[2]);
    double zCross = (a[0]*b[1] - a[1]*b[0]);


    double norm = sqrt(pow(xCross, 2) + pow(yCross, 2) + pow(zCross, 2));

    std::vector<double> aCrossb;
    aCrossb.push_back(xCross / norm);
    aCrossb.push_back(yCross / norm);
    aCrossb.push_back(zCross / norm);

    return aCrossb;
}

std::vector<double> FaceNew::getNormal(){
    std::list<Vert*>::iterator it = this->verts.begin();

    std::vector<Vert*> vert1;
    vert1.push_back(*it);
    it++;
    vert1.push_back(*it);
    it++;
    vert1.push_back(*it);

    return getNormalFromVerts(vert1);
}




bool drawNormal(Vert* v0, Surface * instSurface){
    QColor color;
    if (instSurface != NULL){
        color = instSurface->color;
    } else if (v0->surface != NULL){
        color = v0->surface->getColor();
    } else {
        color = QColor(255, 0, 0);
    }

    GLfloat fcolor[4] = {0,0,0,0};
    fcolor[0] = 1.0f * color.red() / 255;
    fcolor[1] = 1.0f * color.green() / 255;
    fcolor[2] = 1.0f * color.blue() / 255;
    fcolor[3] = 1.0f * color.alpha() /255;

    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, fcolor);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, fcolor);

    glLoadName(v0->index);

    float radius = 0.15f;
    float height = 0.2f;

    float x0 = v0->xTransformed;
    float y0 = v0->yTransformed;
    float z0 = v0->zTransformed;

    float deltax = v0->normal[0] / 2.0;
    float deltay = v0->normal[1] / 2.0;
    float deltaz = v0->normal[2] / 2.0;

    float x1 = v0->xTransformed + deltax;
    float y1 = v0->yTransformed + deltay;
    float z1 = v0->zTransformed + deltaz;


    glLineWidth(2.5);
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex3f(x0, y0, z0);
    glVertex3f(x1, y1, z1);
    glEnd();


    /*glPushMatrix();
    glTranslatef(x1, y1, z1);

    if((deltax != 0.)||(deltay != 0.)) {
        glRotated(atan2(deltay, deltax) * 180 / PI, 0., 0., 1.);
        glRotated(atan2(sqrt(deltax * deltax + deltay * deltay),deltaz) * 180 / PI, 0., 1., 0.);
    } else if (deltaz < 0){
        glRotated(180, 1., 0., 0.);
    }

    GLUquadricObj *quadObj = gluNewQuadric();
    gluCylinder(quadObj, radius, 0, height, 10, 10);
    glPopMatrix();*/

    return true;
}

bool drawFace(FaceNew* f0, Surface * instSurface, Session* currSession)
{
    QColor color;
    if (f0->surface != NULL){
        color = f0->surface->getColor();
    } else if (instSurface != NULL){
        color = instSurface->getColor();
    } else{
        color = currSession->foreColor->getColor();
    }

    GLfloat fcolor[4] = {0,0,0,0};
    if (f0->selected){
        fcolor[0] = 0;
        fcolor[1] = 1;
        fcolor[2] = 1;
        fcolor[3] = 0;
    } else {
        fcolor[0] = 1.0f * color.red() / 255;
        fcolor[1] = 1.0f * color.green() / 255;
        fcolor[2] = 1.0f * color.blue() / 255;
        fcolor[3] = 1.0f * color.alpha() /255;
    }

    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, fcolor);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, fcolor);
    glLoadName(f0->index);

    std::vector<double> normalVector = f0->getNormal();

    glBegin(GL_POLYGON);
    glNormal3f(normalVector[0], normalVector[1], normalVector[2]);
    for(auto v0 : f0->verts) {
      glVertex3f(v0->xTransformed, v0->yTransformed, v0->zTransformed);
    }
    glEnd();

    return true;
}

std::tuple<int,int> getIndicesVertsFace(FaceNew* face, Vert* v0, Vert* v1){
    int indexV0 = 0;
    int indexV1 = 0;
    bool foundV0 = false;
    bool foundV1 = false;

    for(auto curVert = face->verts.begin(); curVert != face->verts.end() && !foundV0; ++curVert) {
        if (v0->index == (*curVert)->index){
            foundV0 = true;
        }
        else{
            indexV0++;
        }
    }

    // Check if in front
    // Get the second vertex.

    if (indexV0 + 1 != face->verts.size()){
        std::list<Vert*>::iterator it = face->verts.begin();
        std::advance(it, indexV0 + 1);

        if (v1->index == (*it)->index){
            indexV1 = indexV0 + 1;
            foundV1 = true;
        }
    }
    else{
        std::list<Vert*>::iterator it = face->verts.begin();
        //std::cout << "HELLLLO" << std::endl;
        //std::cout << v1->name << std::endl;
        //std::cout << (*it)->name << std::endl;
        if (v1->index == (*it)->index){
            indexV1 = 0;
            foundV1 = true;
        }
    }

    if (indexV0 != 0 && foundV1 == false){
        std::list<Vert*>::iterator it = face->verts.begin();
        std::advance(it, indexV0 - 1);

        if (v1->index == (*it)->index){
            indexV1 = indexV0 - 1;
            foundV1 = true;
        }
    }
    else if (indexV0 == 0 && foundV1 == false){
        std::list<Vert*>::iterator it = face->verts.end();
        --it;

        if (v1->index == (*it)->index){
            indexV1 = face->verts.size() - 1;
            foundV1 = true;
        }
    }

    return std::make_tuple(indexV0, indexV1);
}

bool EdgeNew::isMobiusEdge(){
    Vert* firstVert = this->v0;
    Vert* secondVert = this->v1;

    int indexF0V0 = 0;
    int indexF0V1 = 0;
    int indexF1V0 = 0;
    int indexF1V1 = 0;

    if (this->f0 != NULL && this->f1 != NULL){
        auto indicesVertF0 = getIndicesVertsFace(this->f0, this->v0, this->v1);
        indexF0V0 = std::get<0>(indicesVertF0);
        indexF0V1 = std::get<1>(indicesVertF0);

        auto indicesVertF1 = getIndicesVertsFace(this->f1, this->v0, this->v1);
        indexF1V0 = std::get<0>(indicesVertF1);
        indexF1V1 = std::get<1>(indicesVertF1);

        // Check if it is a mobius edge.
        if ((((indexF0V0 < indexF0V1) || (indexF0V0 == this->f0->verts.size() - 1 && indexF0V1 == 0)) && ((indexF1V0 > indexF1V1) && !(indexF1V0 == this->f1->verts.size() - 1 && indexF1V1 == 0)))
            || (((indexF1V0 < indexF1V1) || (indexF1V0 == this->f1->verts.size() - 1 && indexF1V1 == 0)) && ((indexF0V0 > indexF0V1) && !(indexF0V0 == this->f0->verts.size() - 1 && indexF0V1 == 0)))
            ){
            return false;
        }
        return true;
    }
    return false;
}

void EdgeNew::calculateEdgePoint(){
    double *xEdgePoint = (double*) malloc(sizeof(double));
    double *yEdgePoint = (double*) malloc(sizeof(double));
    double *zEdgePoint = (double*) malloc(sizeof(double));
    *xEdgePoint = 0;
    *yEdgePoint = 0;
    *zEdgePoint = 0;

    //Check if it is on a border.
    if (this->f1 != NULL){
        *xEdgePoint = (this->f0->facePoint->xTransformed + this->f1->facePoint->xTransformed + this->v0->xTransformed + this->v1->xTransformed) / 4.0;
        *yEdgePoint = (this->f0->facePoint->yTransformed + this->f1->facePoint->yTransformed + this->v0->yTransformed + this->v1->yTransformed) / 4.0;
        *zEdgePoint = (this->f0->facePoint->zTransformed + this->f1->facePoint->zTransformed + this->v0->zTransformed + this->v1->zTransformed) / 4.0;
    }
    else{
        *xEdgePoint = (this->v0->xTransformed + this->v1->xTransformed) / 2.0;
        *yEdgePoint = (this->v0->yTransformed + this->v1->yTransformed) / 2.0;
        *zEdgePoint = (this->v0->zTransformed + this->v1->zTransformed) / 2.0;
    }

    this->edgePoint = createVert (xEdgePoint, yEdgePoint, zEdgePoint);
}

void FaceNew::calculateFacePoint(){
    // Takes the average of all the point on the face.
    double *xFacePoint = (double*) malloc(sizeof(double));
    double *yFacePoint = (double*) malloc(sizeof(double));
    double *zFacePoint = (double*) malloc(sizeof(double));

    *xFacePoint = 0;
    *yFacePoint = 0;
    *zFacePoint = 0;

    for (Vert * currVert : this->verts){
        *xFacePoint += currVert->xTransformed;
        *yFacePoint += currVert->yTransformed;
        *zFacePoint += currVert->zTransformed;
    }

    *xFacePoint = *xFacePoint / this->verts.size();
    *yFacePoint = *yFacePoint / this->verts.size();
    *zFacePoint = *zFacePoint / this->verts.size();

    this->facePoint = createVert (xFacePoint, yFacePoint, zFacePoint);
}

void FaceNew::calculateWeightedFacePoint(){
    // Takes the average of all the point on the face.
    double *xFacePoint = (double*) malloc(sizeof(double));
    double *yFacePoint = (double*) malloc(sizeof(double));
    double *zFacePoint = (double*) malloc(sizeof(double));
    *xFacePoint = 0;
    *yFacePoint = 0;
    *zFacePoint = 0;
    double totalLength = 0.0;
    for (Vert * currVert : this->verts){
        // Need to weight vertex according to length edge.
        double length = 0.0;
        for (EdgeNew* e : this->edges){
            if (e->v0->index == currVert->index || e->v1->index == currVert->index){
                length += sqrt(pow(e->v1->xTransformed - e->v0->xTransformed, 2) + pow(e->v1->yTransformed - e->v0->yTransformed, 2) + pow(e->v1->zTransformed - e->v0->zTransformed, 2));
            }
        }
        *xFacePoint += currVert->xTransformed * length;
        *yFacePoint += currVert->yTransformed * length;
        *zFacePoint += currVert->zTransformed * length;
        totalLength += length;
    }

    *xFacePoint = *xFacePoint / (totalLength);
    *yFacePoint = *yFacePoint / (totalLength);
    *zFacePoint = *zFacePoint / (totalLength);

    this->facePoint = createVert (xFacePoint, yFacePoint, zFacePoint);
}

void Vert::initOctreeProxy()
{
    if (!octreeProxy)
        octreeProxy = new VertOctreeProxy(Session::getSingleton().getOctreeRoot(), this, xTransformed, yTransformed, zTransformed);
}

void Vert::destroyOctreeProxy()
{
    delete octreeProxy;
}

void Vert::updateOctreeProxy()
{
    if (octreeProxy)
    {
        //printf("Vert %s updated: %f, %f, %f\n", getFullName().c_str(), xTransformed, yTransformed, zTransformed);
        octreeProxy->updateWorldPosition(xTransformed, yTransformed, zTransformed);
    }
}

void Vert::calculateVertPoint(){
    double Rx = 0;
    double Ry = 0;
    double Rz = 0;

    double n;

    double Sx = xTransformed;
    double Sy = yTransformed;
    double Sz = zTransformed;

    double *xVertPoint = (double*) malloc(sizeof(double));
    double *yVertPoint = (double*) malloc(sizeof(double));
    double *zVertPoint = (double*) malloc(sizeof(double));
    if (faces.size() != edges.size()){
        n = 0;
        Rx = 0;
        Ry = 0;
        Rz = 0;
        for (EdgeNew* currEdge : edges){
            if (currEdge->f1 == NULL || currEdge->f0 == NULL){
                Rx += (currEdge->v0->xTransformed + currEdge->v1->xTransformed) / 2.0;
                Ry += (currEdge->v0->yTransformed + currEdge->v1->yTransformed) / 2.0;
                Rz += (currEdge->v0->zTransformed + currEdge->v1->zTransformed) / 2.0;

                n++;
            }
        }
        *xVertPoint = (Sx + Rx) / (n+1);
        *yVertPoint = (Sy + Ry) / (n+1);
        *zVertPoint = (Sz + Rz) / (n+1);
        /*std::cout << Sy << std::endl;
        std::cout << Ry << std::endl;
        std::cout << n << std::endl;
        std::cout << *yVertPoint << std::endl;*/
    }
    else{
        //(Q/n) + (2R/n) + (S(n-3)/n)

        // The valence of a point is simply the number of edges that connect to that point.
        n = faces.size();

        double Qx = 0;
        double Qy = 0;
        double Qz = 0;
        // Q is the average of the surrounding face points
        for (FaceNew* currFace : faces){
            Qx += currFace->facePoint->xTransformed;
            Qy += currFace->facePoint->yTransformed;
            Qz += currFace->facePoint->zTransformed;
        }

        Qx = Qx / faces.size();
        Qy = Qy / faces.size();
        Qz = Qz / faces.size();

        // R is the average of all surround edge midpoints

        for (EdgeNew* currEdge : edges){
            Rx += (currEdge->v0->xTransformed + currEdge->v1->xTransformed) / 2.0;
            Ry += (currEdge->v0->yTransformed + currEdge->v1->yTransformed) / 2.0;
            Rz += (currEdge->v0->zTransformed + currEdge->v1->zTransformed) / 2.0;
        }
        Rx = Rx / edges.size();
        Ry = Ry / edges.size();
        Rz = Rz / edges.size();

        *xVertPoint = (Qx + 2 * Rx + Sx * (n - 3)) / n;
        *yVertPoint = (Qy + 2 * Ry + Sy * (n - 3)) / n;
        *zVertPoint = (Qz + 2 * Rz + Sz * (n - 3)) / n;
    }

    //std::cout << "END VERT POINT" << std::endl;

    this->vertPoint = createVert (xVertPoint, yVertPoint, zVertPoint);
}

void Vert::update(){
    double *currentValSet = (double*) malloc(sizeof(double));
    parseGetBankVal(xStr.c_str(), this->currSession, currentValSet, 0);
    *x = *currentValSet;
    xTransformed = *currentValSet;
    parseGetBankVal(yStr.c_str(), this->currSession, currentValSet, 0);
    *y = *currentValSet;
    yTransformed = *currentValSet;
    parseGetBankVal(zStr.c_str(), this->currSession, currentValSet, 0);
    *z = *currentValSet;
    zTransformed = *currentValSet;
}

void Vert::setWorldPos(double x, double y, double z)
{
    xTransformed = x;
    yTransformed = y;
    zTransformed = z;
    updateOctreeProxy();
}

void Vert::applyTransformation(TransformationNew * t){
    if (dynamic_cast<Rotate*>(t)){
        Rotate* rotate = dynamic_cast<Rotate*>(t);

        double *xTmp = (double*) malloc(sizeof(double));
        double *yTmp = (double*) malloc(sizeof(double));
        double *zTmp = (double*) malloc(sizeof(double));

        // Rotation around an axis
        // http://ksuweb.kennesaw.edu/~plaval//math4490/rotgen.pdf
        double radAngle = *rotate->angle * (3.141592f/180.0f);
        double t = 1 - glm::cos(radAngle);
        double S = glm::sin(radAngle);
        double C = glm::cos(radAngle);

        double x1 = t * pow(*rotate->x, 2) + C;
        double x2 = t * *rotate->x * *rotate->y - S * *rotate->z;
        double x3 = t * *rotate->x * *rotate->z + S * *rotate->y;
        double y1 = t * *rotate->x * *rotate->y + S * *rotate->z;
        double y2 = t * pow(*rotate->y, 2) + C;
        double y3 = t * *rotate->y * *rotate->z - S * *rotate->x;
        double z1 = t * *rotate->x * *rotate->z - S * *rotate->y;
        double z2 = t * *rotate->y * *rotate->z + S * *rotate->x;
        double z3 = t * pow(*rotate->z, 2) + C;

        // Matrix multiplication
        // https://i.ytimg.com/vi/r-WlZLV0E0s/hqdefault.jpg
        double ax = this->xTransformed * x1 + this->yTransformed * x2 + this->zTransformed * x3;
        double ay = this->xTransformed * y1 + this->yTransformed * y2 + this->zTransformed * y3;
        double az = this->xTransformed * z1 + this->yTransformed * z2 + this->zTransformed * z3;

        this->setWorldPos(ax, ay, az);
    } else if (dynamic_cast<Scale*>(t)){
        Scale* scale = dynamic_cast<Scale*>(t);
        this->setWorldPos(this->xTransformed * *scale->x, this->yTransformed * *scale->y, this->zTransformed * *scale->z);
    } else if (dynamic_cast<Translate*>(t)){
        Translate* translate = dynamic_cast<Translate*>(t);
        this->setWorldPos(this->xTransformed + *translate->x, this->yTransformed + *translate->y, this->zTransformed + *translate->z);
    }
    updateOctreeProxy();
}

void Surface::update(){
    double *currentValSet = (double*) malloc(sizeof(double));
    parseGetBankVal(rStr.c_str(), this->currSession, currentValSet, 0);
    *r = *currentValSet;
    parseGetBankVal(gStr.c_str(), this->currSession, currentValSet, 0);
    *g = *currentValSet;
    parseGetBankVal(bStr.c_str(), this->currSession, currentValSet, 0);
    *b = *currentValSet;
}
