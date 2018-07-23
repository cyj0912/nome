//
//  Instance.cpp
//  model
//
//  Created by L on 21/09/2017.
//  Copyright © 2017 L. All rights reserved.
//
#include <stdio.h>
#include <string.h>
#include <glm/glm.hpp>
#include "Data.h"
#include "InstanceNew.h"
#include "FunnelNew.h"
#include "TunnelNew.h"
#include "CircleNew.h"
#include "GroupNew.h"
#include "BezierCurveNew.h"
#include "BSplineNew.h"
#include "Reader.h"

class Reader;
bool setSurface(InstanceNew* i0, Surface* surface){
    i0->surface = surface;
    return true;
}


InstanceNew* createInstance(InstanceNew* i0)
{
    return new InstanceNew();
}

InstanceNew* createInstance(GroupNew* g0, std::list<Vert*> vertsDef, Reader* currReader, Session* currSession)
{
   InstanceNew* i0 = new InstanceNew();
   i0->group = g0;

   std::list<InstanceNew*> listInstances;
   for (InstanceNew* instanceNest : g0->instances){
       MeshNew* currentMesh = instanceNest->mesh;
       std::string currentName = instanceNest->name;
       std::list<TransformationNew*> currentTransformations = instanceNest->transformations;
        //std::cout << currentTransformations.size() << std::endl;
       if (currentMesh != NULL){
           InstanceNew* newInstance;
           newInstance = createInstance(currentMesh, vertsDef, currReader, true, false, true, currSession, true);
           //currentName = currentName.substr(currentName.find(":") + 1);
           newInstance->setName(currentName);

           /*for (Vert* newVertex: newInstance->verts){
               for (TransformationNew* t: currentTransformations){
                newVertex->transformations.push_back(t);
               }
           }*/

           newInstance->transformations = currentTransformations;
           newInstance->surface = instanceNest->surface;
           i0->listInstances.push_back(newInstance);
       } else if (instanceNest->group != NULL){
           InstanceNew* newInstance;
           newInstance = createInstance(instanceNest->group, vertsDef, currReader, currSession);
           //currentName = currentName.substr(currentName.find(":") + 1);
           newInstance->setName(currentName);
           newInstance->transformations = currentTransformations;
           newInstance->surface = instanceNest->surface;
           i0->listInstances.push_back(newInstance);
       }
   }

   return i0;
}

InstanceNew* createInstance(MeshNew* m0, std::list<Vert*> vertsDef, Reader* currReader, bool connect, bool doNotCreateVertices, bool onlyCreateNewVertices, Session* currSession, bool octree)
{
   InstanceNew* i0 = new InstanceNew();
   i0->mesh = m0;
   i0->verts = {};
   i0->currSession = currSession;

   //std::cout << m0->name << std::endl;
   //std::cout << m0->name << std::endl;
   // Copy all the vertices from the mesh to the instance.
   for (Vert* v0 : m0->verts){
       if (onlyCreateNewVertices == true){
           Vert* newVertex = createVert(v0);
           newVertex->name = v0->name;
           // MAYBE CHECK TRANSFORMATIONS.
           newVertex->transformations = currReader->getVertTransformations(v0->index);
           newVertex->copyOfVert = v0;
           setSurface(newVertex, m0->surface);
           i0->verts.push_back(newVertex);

           if (octree){
               newVertex->initOctreeProxy();
               newVertex->updateOctreeProxy();
           }
       }
       else if (((std::find(vertsDef.begin(), vertsDef.end(), v0) != vertsDef.end() || dynamic_cast<FunnelNew*>(m0) || dynamic_cast<TunnelNew*>(m0) || dynamic_cast<CircleNew*>(m0)  || dynamic_cast<BezierCurveNew*>(m0)  || dynamic_cast<BSplineNew*>(m0)) && doNotCreateVertices == false)){
           Vert* newVertex = createVert(v0);
           newVertex->name = v0->name;
           newVertex->copyOfVert = v0;
           setSurface(newVertex, m0->surface);
           i0->verts.push_back(newVertex);
           if (octree){
               newVertex->initOctreeProxy();
               newVertex->updateOctreeProxy();
           }
       }
       else{
           v0->copyOfVert = v0;
           i0->verts.push_back(v0);
       }
   }

   // Copy all the edges from the mesh to the instance.
   for (EdgeNew* e0 : m0->edges){
       //std::cout << "e0->v0->index" << std::endl;
       //std::cout << e0->v0->name << std::endl;
       //std::cout << e0->v1->name << std::endl;
       Vert* firstVert = NULL;
       Vert* secondVert = NULL;

       // Check if vertex is a vertex already in the scene.
       for (Vert* v0 : i0->verts){
           if(v0->index == e0->v0->index){
               firstVert = v0;
           }
       }

       // Otherwise it must be a vertex definition which has a unique name.
       if (!firstVert){
           for (Vert* v0 : i0->verts){
               if (v0->copyOfVert->index == e0->v0->index){
               //if(v0->name.compare(e0->v0->name) == 0){
                   //std::cout << "ALREADY" << std::endl;
                   firstVert = v0;
               }
           }
       }

       // Do the same thing for the second vertex.
       for (Vert* v1 : i0->verts){
           if(v1->index == e0->v1->index)
               secondVert = v1;
       }

       if (!secondVert){
           for (Vert* v1 : i0->verts){
               if (v1->copyOfVert->index == e0->v1->index){
               //if(v1->name.compare(e0->v1->name) == 0){
                   secondVert = v1;
               }
           }
       }

       // Check if the edge is already defined
       EdgeNew* newEdge = NULL;
       for( auto e0 : i0->edges ) {
           if ((e0->v0->index == firstVert->index && e0->v1->index == secondVert->index) || (e0->v0->index == secondVert->index && e0->v1->index == firstVert->index)){
               newEdge = e0;
           }
       }

       if (newEdge == NULL){
           newEdge = currReader->getEdge(firstVert->index, secondVert->index);
           //std::cout << "+++++" << std::endl;
           /*if (currReader->getVert(firstVert->index) != NULL){
               std::cout << currReader->getVertName(firstVert->index) << std::endl;
           }
           if (currReader->getVert(secondVert->index) != NULL){
               std::cout << currReader->getVertName(secondVert->index) << std::endl;
           }*/
           if (newEdge != NULL){
               setSurface(newEdge, m0->surface);
                i0->edges.push_back(newEdge);
           }
       }

       if (newEdge == NULL){
            newEdge = createEdge(firstVert, secondVert, connect);
            setSurface(newEdge, m0->surface);
            i0->edges.push_back(newEdge);
       }


   }

   for (FaceNew* f0 : m0->faces){
       std::list<EdgeNew*> edgesFace;
       std::list<Vert*> vertFace;
       for (Vert* vF : f0->verts){
           Vert* firstVert = NULL;
           for (Vert* v0 : i0->verts){
               if(v0->copyOfVert->index == vF->index)
                   firstVert = v0;
           }
           if (!firstVert){
               for (Vert* v0 : i0->verts){
                   if(v0->copyOfVert->index == (vF->index)){
                       firstVert = v0;
                   }
               }
           }
           //std::cout << firstVert->name << std::endl;
           vertFace.push_back(firstVert);
       }

       FaceNew* newFace = createFace(vertFace, &(i0->edges), currReader, connect);

       setName(newFace, f0->name);
       setSurface(newFace, f0->surface);

       i0->faces.push_back(newFace);
   }

   return i0;
}


bool InstanceNew::setName(std::string n)
{
    if(n.find(".") != std::string::npos && n.find(":") != std::string::npos)
        return false;
    name = n;
    return updateNames();
}

bool InstanceNew::updateNames()
{
    if (mesh != NULL){
        mesh->setPrefix(getFullName());
        return true;
    }
    return false;
}

bool InstanceNew::draw(Surface *s)
{
    Surface *toUse;
    if (surface == NULL){
        toUse = s;
    } else{
        toUse = surface;
    }
    for(auto v : verts) {
      drawVert(v, toUse, currSession);
    }
    for(auto e : edges) {
      drawEdge(e, toUse, currSession);
    }

    for(auto f : faces) {
      /*for(auto v : f->verts) {
          std::cout << v->name << std::endl;
      }*/
      drawFace(f, toUse, currSession);
    }

    for (auto i : listInstances) {
        i->draw(toUse);
    }

    return true;
}

void InstanceNew::flattenInstance(MeshNew* flattenedMesh)
{
    /*for(Vert* v : verts) {
      bool contains = false;
      for (Vert* vf : flattenedMesh->verts){
          if (v->index == vf->index){
              contains = true;
              break;
          }
      }
      if (!contains){
          flattenedMesh->verts.push_back(createDupVert(v));
      }
    }*/

    /*for(EdgeNew* e : edges) {
        bool contains = false;
        for (EdgeNew* ef : flattenedMesh->edges){
            if (e->index == ef->index){
                contains = true;
                break;
            }
        }
        if (!contains){
            if (e->f0 == NULL && e->f1 == NULL){
                for (Vert* v : flattenedMesh->verts){
                    if ((v->index == e->v0->index) || (v->index == e->v1->index)){
                        v->edges.remove(e);
                    }
                }
            } else{
                flattenedMesh->edges.push_back(createDupEdge(e));
            }

        }
    }*/

    for(FaceNew* f : faces) {
        for(Vert* v : f->verts) {
          bool contains = false;
          for (Vert* vf : flattenedMesh->verts){
              if (v->index == vf->index){
                  contains = true;
                  break;
              }
          }
          if (!contains){
              flattenedMesh->verts.push_back(createDupVert(v));
          }
        }

        for(EdgeNew* e : edges) {
            bool contains = false;
            for (EdgeNew* ef : flattenedMesh->edges){
                if (e->index == ef->index){
                    contains = true;
                    break;
                }
            }
            if (!contains){
                if (e->f0 == NULL && e->f1 == NULL){
                    for (Vert* v : flattenedMesh->verts){
                        if ((v->index == e->v0->index) || (v->index == e->v1->index)){
                            v->edges.remove(e);
                        }
                    }
                } else{
                    flattenedMesh->edges.push_back(createDupEdge(e));
                }
            }
        }

        bool contains = false;
        for (FaceNew* ff : flattenedMesh->faces){
            if (f->index == ff->index){
                contains = true;
                break;
            }
        }
        if (!contains){
            flattenedMesh->faces.push_back(createDupFace(f));
        }
    }
    list<EdgeNew*> newListEdges = list<EdgeNew*>();
    list<FaceNew*> newListFaces = list<FaceNew*>();
    for (Vert* v0 : flattenedMesh->verts){
        for (EdgeNew* oldEdge : v0->edges){
            for (EdgeNew* newEdge : flattenedMesh->edges){
                if (oldEdge->index == newEdge->index){
                    newListEdges.push_back(newEdge);
                    break;
                }
            }
        }

        for (FaceNew* oldFace : v0->faces){
            for (FaceNew* newFace : flattenedMesh->faces){
                if (oldFace->index == newFace->index){
                    newListFaces.push_back(newFace);
                    break;
                }
            }
        }
        v0->edges = newListEdges;
        v0->faces = newListFaces;

        newListEdges.clear();
        newListFaces.clear();
    }

    for (EdgeNew* e0 : flattenedMesh->edges){
        for (Vert* newVert : flattenedMesh->verts){
            if (e0->v0->index == newVert->index){
                e0->v0 = newVert;
                break;
            }
        }

        for (Vert* newVert : flattenedMesh->verts){
            if (e0->v1->index == newVert->index){
                e0->v1 = newVert;
                break;
            }
        }

        if (e0->f0 != NULL){
            for (FaceNew* newFace : flattenedMesh->faces){
                if (e0->f0->index == newFace->index){
                    e0->f0 = newFace;
                    break;
                }
            }
        }

        if (e0->f1 != NULL){
            for (FaceNew* newFace : flattenedMesh->faces){
                if (e0->f1->index == newFace->index){
                    e0->f1 = newFace;
                    break;
                }
            }
        }
    }

    list<EdgeNew*> newListEdgesF = list<EdgeNew*>();
    list<Vert*> newListVertsF = list<Vert*>();
    for (FaceNew* f0 : flattenedMesh->faces){
        for (EdgeNew* oldEdge : f0->edges){
            for (EdgeNew* newEdge : flattenedMesh->edges){
                if (oldEdge->index == newEdge->index){
                    newListEdgesF.push_back(newEdge);
                    break;
                }
            }
        }

        for (Vert* oldVert : f0->verts){
            for (Vert* newVert : flattenedMesh->verts){
                if (oldVert->index == newVert->index){
                    newListVertsF.push_back(newVert);
                    break;
                }
            }
        }
        f0->edges = newListEdgesF;
        f0->verts = newListVertsF;

        newListEdgesF.clear();
        newListVertsF.clear();
    }

    for (InstanceNew* i : listInstances) {
        i->flattenInstance(flattenedMesh);
    }


}

bool InstanceNew::drawFaces()
{
    for(auto f : faces) {
      drawFace(f, surface, currSession);
    }

    for (auto i : listInstances) {
        i->drawFaces();
    }

    return true;
}


Node* InstanceNew::vert(std::string name)
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

Node* InstanceNew::edge(std::string name)
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

Node* InstanceNew::face(std::string name)
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

Node* InstanceNew::vert(int i)
{
    for(Vert* v0 : verts)
    {
        if(v0->index == i)
            return v0;
    }
    return NULL;
}

Node* InstanceNew::edge(int i)
{
    for(EdgeNew* e0 : edges)
    {
        if(e0->index == i)
            return e0;
    }
    return NULL;
}

Node* InstanceNew::face(int i)
{
    for(FaceNew* f0 : faces)
    {
        if(f0->index == i)
            return f0;
    }
    return NULL;
}

void InstanceNew::updateVerts(){
    if (mesh != NULL){
        for (Vert* v0 : verts){
            /*double *x = (double*) malloc(sizeof(double));
            double *y = (double*) malloc(sizeof(double));
            double *z = (double*) malloc(sizeof(double));

            *x = *(v0->x);
            *y = *(v0->y);
            *z = *(v0->z);

            v0->xTransformed = x;
            v0->yTransformed = y;
            v0->zTransformed = z;*/

            v0->setWorldPos(*v0->x, *v0->y, *v0->z);
        }
    }
    else if (group != NULL){
        for (InstanceNew* i0 : listInstances){
            for (Vert* v0 : i0->verts){
                /*double *x = (double*) malloc(sizeof(double));
                double *y = (double*) malloc(sizeof(double));
                double *z = (double*) malloc(sizeof(double));

                *x = *(v0->x);
                *y = *(v0->y);
                *z = *(v0->z);

                v0->xTransformed = x;
                v0->yTransformed = y;
                v0->zTransformed = z;*/

                v0->setWorldPos(*v0->x, *v0->y, *v0->z);
            }
        }
    }
}

void InstanceNew::applyTransformationGroup(){
    if (group != NULL){
        for (InstanceNew* currInstance : listInstances){
            for (Vert* v : currInstance->verts){
                for (TransformationNew * t : v->transformations){
                    v->applyTransformation(t);
                }

            }
            for (TransformationNew * t : currInstance->transformations){
                currInstance->applyTransformation(t);
            }
        }
    }
}

void InstanceNew::applyTransformation(TransformationNew* t){

    if (mesh != NULL){
        if (dynamic_cast<Rotate*>(t)){
            Rotate* rotate = dynamic_cast<Rotate*>(t);
            for (Vert* v0 : verts){
                // https://en.wikipedia.org/wiki/Rotation_matrix#Non-standard_orientation_of_the_coordinate_system
                double x, y, z;

                double normalizeLength = sqrt(((*rotate->x) * (*rotate->x)) + ((*rotate->y) * (*rotate->y)) + ((*rotate->z) * (*rotate->z)));
                double normalizeX = (*rotate->x) / normalizeLength;
                double normalizeY = (*rotate->y) / normalizeLength;
                double normalizeZ = (*rotate->z) / normalizeLength;

                double radAngle = *rotate->angle * (3.141592f/180.0f);

                double x1 = glm::cos(radAngle) + (normalizeX * normalizeX) * (1 - glm::cos(radAngle));
                double x2 = normalizeX * normalizeY * (1 - glm::cos(radAngle)) - normalizeZ * glm::sin(radAngle);
                double x3 = normalizeX * normalizeZ * (1 - glm::cos(radAngle)) + normalizeY * glm::sin(radAngle);
                double y1 = normalizeY * normalizeX * (1 - glm::cos(radAngle)) + normalizeZ * glm::sin(radAngle);
                double y2 = glm::cos(radAngle) + normalizeY * normalizeY * (1 - glm::cos(radAngle));
                double y3 = normalizeY * normalizeZ * (1 - glm::cos(radAngle)) - normalizeX * glm::sin(radAngle);
                double z1 = normalizeZ * normalizeX * (1 - glm::cos(radAngle)) - normalizeY * glm::sin(radAngle);
                double z2 = normalizeZ * normalizeY * (1 - glm::cos(radAngle)) + normalizeX * glm::sin(radAngle);
                double z3 = glm::cos(radAngle) + normalizeZ * normalizeZ * (1 - glm::cos(radAngle));
                x = v0->xTransformed * x1 + v0->yTransformed * x2 + v0->zTransformed * x3;
                y = v0->xTransformed * y1 + v0->yTransformed * y2 + v0->zTransformed * y3;
                z = v0->xTransformed * z1 + v0->yTransformed * z2 + v0->zTransformed * z3;
                /*
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
                double ax = *v0->xTransformed * x1 + *v0->yTransformed * x2 + *v0->zTransformed * x3;
                double ay = *v0->xTransformed * y1 + *v0->yTransformed * y2 + *v0->zTransformed * y3;
                double az = *v0->xTransformed * z1 + *v0->yTransformed * z2 + *v0->zTransformed * z3;

                *x = ax;
                *y = ay;
                *z = az;*/

                /*v0->xTransformed = x;
                v0->yTransformed = y;
                v0->zTransformed = z;*/
                v0->setWorldPos(x, y, z);
            }
        }
        else if (dynamic_cast<Reverse*>(t)){
            if (transformationApplied == false){
                Reverse* scale = dynamic_cast<Reverse*>(t);

                for (FaceNew* f0 : faces){
                    f0->verts.reverse();
                    f0->edges.reverse();
                    EdgeNew* currEdge = f0->edges.front();
                    f0->edges.pop_front();
                    f0->edges.push_back(currEdge);
                }

            }
        }
        else if (dynamic_cast<Scale*>(t)){
            Scale* scale = dynamic_cast<Scale*>(t);
            for (Vert* v0 : verts){
                /*double *x = (double*) malloc(sizeof(double));
                double *y = (double*) malloc(sizeof(double));
                double *z = (double*) malloc(sizeof(double));

                *x = *v0->xTransformed * *scale->x;
                *y = *v0->yTransformed * *scale->y;
                *z = *v0->zTransformed * *scale->z;
                v0->xTransformed = x;
                v0->yTransformed = y;
                v0->zTransformed = z;*/

                double x = v0->xTransformed * *scale->x;
                double y = v0->yTransformed * *scale->y;
                double z = v0->zTransformed * *scale->z;
                v0->setWorldPos(x, y, z);
            }
        }
        else if (dynamic_cast<Translate*>(t)){

            Translate* translate = dynamic_cast<Translate*>(t);
            for (Vert* v0 : verts){
                /*double *x = (double*) malloc(sizeof(double));
                double *y = (double*) malloc(sizeof(double));
                double *z = (double*) malloc(sizeof(double));

                *x = *v0->xTransformed + *translate->x;
                *y = *v0->yTransformed + *translate->y;
                *z = *v0->zTransformed + *translate->z;
                v0->xTransformed = x;
                v0->yTransformed = y;
                v0->zTransformed = z;*/

                double x = v0->xTransformed + *translate->x;
                double y = v0->yTransformed + *translate->y;
                double z = v0->zTransformed + *translate->z;
                v0->setWorldPos(x, y, z);
            }
        }
    }
    else if (group != NULL){
        for (InstanceNew* i0 : listInstances){
            i0->applyTransformation(t);
        }
    }
    this->transformationApplied = true;
}

void InstanceNew::undoTransformation(TransformationNew* t){
    if (dynamic_cast<Rotate*>(t)){
        Rotate* rotate = dynamic_cast<Rotate*>(t);
        for (Vert* v0 : verts){
            double *x = (double*) malloc(sizeof(double));
            double *y = (double*) malloc(sizeof(double));
            double *z = (double*) malloc(sizeof(double));

            // Rotation around an axis
            // http://ksuweb.kennesaw.edu/~plaval//math4490/rotgen.pdf
            double radAngle = -*rotate->angle * (3.141592f/180.0f);
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
            double ax = *v0->x * x1 + *v0->y * x2 + *v0->z * x3;
            double ay = *v0->x * y1 + *v0->y * y2 + *v0->z * y3;
            double az = *v0->x * z1 + *v0->y * z2 + *v0->z * z3;

            *x = ax;
            *y = ay;
            *z = az;
            v0->x = x;
            v0->y = y;
            v0->z = z;
        }
    }
    else if (dynamic_cast<Scale*>(t)){
        Scale* scale = dynamic_cast<Scale*>(t);
        for (Vert* v0 : verts){
            double *x = (double*) malloc(sizeof(double));
            double *y = (double*) malloc(sizeof(double));
            double *z = (double*) malloc(sizeof(double));

            *x = *v0->x * (1.0 / *scale->x);
            *y = *v0->y * (1.0 / *scale->y);
            *z = *v0->z * (1.0 / *scale->z);
            v0->x = x;
            v0->y = y;
            v0->z = z;
        }
    }
    else if (dynamic_cast<Translate*>(t)){

        Translate* translate = dynamic_cast<Translate*>(t);
        for (Vert* v0 : verts){
            double *x = (double*) malloc(sizeof(double));
            double *y = (double*) malloc(sizeof(double));
            double *z = (double*) malloc(sizeof(double));

            *x = *v0->x - *translate->x;
            *y = *v0->y - *translate->y;
            *z = *v0->z - *translate->z;
            v0->x = x;
            v0->y = y;
            v0->z = z;

        }

    }
}

void InstanceNew::update(){
    Vert* lastVertSeen = NULL;
    for (Vert* vI : verts){
        for (Vert* vM : this->mesh->verts){
            if (vI->name == vM->name){
                lastVertSeen = vM;
                break;
            }
        }
        if (lastVertSeen != NULL){
            vI->x = lastVertSeen->x;
            vI->y = lastVertSeen->y;
            vI->z = lastVertSeen->z;
            lastVertSeen = NULL;
        }
    }

}

void InstanceNew::updateTransformations(){
    for (TransformationNew* t : this->transformations){
        if (dynamic_cast<Scale*>(t)){
            Scale* scale = dynamic_cast<Scale*>(t);

            double *xValSet = (double*) malloc(sizeof(double));
            parseGetBankVal(scale->xStr.c_str(), currSession, xValSet, 0);
            *(scale->x) = *xValSet;

            double *yValSet = (double*) malloc(sizeof(double));
            parseGetBankVal(scale->yStr.c_str(), currSession, yValSet, 0);
            *(scale->y) = *yValSet;

            double *zValSet = (double*) malloc(sizeof(double));
            parseGetBankVal(scale->zStr.c_str(), currSession, zValSet, 0);
            *(scale->z) = *zValSet;
        } else if (dynamic_cast<Translate*>(t)){
            Translate* translate = dynamic_cast<Translate*>(t);

            double *xValSet = (double*) malloc(sizeof(double));
            parseGetBankVal(translate->xStr.c_str(), currSession, xValSet, 0);
            *(translate->x) = *xValSet;

            double *yValSet = (double*) malloc(sizeof(double));
            parseGetBankVal(translate->yStr.c_str(), currSession, yValSet, 0);
            *(translate->y) = *yValSet;

            double *zValSet = (double*) malloc(sizeof(double));
            parseGetBankVal(translate->zStr.c_str(), currSession, zValSet, 0);
            *(translate->z) = *zValSet;

        } else if (dynamic_cast<Rotate*>(t)){
            Rotate* rotate = dynamic_cast<Rotate*>(t);

            double *xValSet = (double*) malloc(sizeof(double));
            parseGetBankVal(rotate->xStr.c_str(), currSession, xValSet, 0);
            *(rotate->x) = *xValSet;

            double *yValSet = (double*) malloc(sizeof(double));
            parseGetBankVal(rotate->yStr.c_str(), currSession, yValSet, 0);
            *(rotate->y) = *yValSet;

            double *zValSet = (double*) malloc(sizeof(double));
            parseGetBankVal(rotate->zStr.c_str(), currSession, zValSet, 0);
            *(rotate->z) = *zValSet;

            double *angleValSet = (double*) malloc(sizeof(double));
            parseGetBankVal(rotate->angleStr.c_str(), currSession, angleValSet, 0);
            *(rotate->angle) = *angleValSet;
        }
    }
}
