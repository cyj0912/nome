//
//  Reader.cpp
//

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

///Reader instantiation with various fields
//Instatiate reader with no treenode
Reader* createReader(Session* currSession)
{
    Reader* r0 = new Reader();
    r0->session = currSession;
    r0->assigned = false;
    return r0;
}

//Instantiate reader with treenode
Reader* createReader(Session* currSession, Node* node)
{
    Reader* r0 = new Reader();
    r0->session = currSession;
    r0->node = node;
    r0->assigned = true;
    return r0;
}

//Clone reader object
Reader* createReader(Reader r1)
{
    Reader* r0 = new Reader();
    r0->node = r1.node;
    r0->session = r1.session;
    r0->assigned = r1.assigned;
    return r0;
}



///Reader tree traversal
//Link a reader to a node
bool Reader::link(Node* n0)
{
    if(n0 == NULL)
        return false;
    node = n0;
    return true;
}

//Link a reader given string of the node
bool Reader::link(std::string s)
{
    Node* node = NULL;
    if(s[0] == 'm')
    {
        for(MeshNew* m0 : session->meshes)
        {
            if(m0->getName().compare(s) == 0)
                node = m0;
        }
    }
    else if(s[0] == 'i')
    {
        for(InstanceNew* i0 : session->instances)
        {
            if(i0->getName().compare(s) == 0)
                node = i0;
        }
    }
    return link(node);
}

//Search tree for given string
bool Reader::search(std::string s, int mode)
{
    //Loop through string to find
    std::string delimiter = ".";
    size_t pos = 0;
    std::string token;
    bool found = false;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        if(token[0] == 'i' && mode == 1)
        {
            found = true;
            link(token);
        }
        else if (token[0] == 'm')
        {
            found = true;
            link(token);
        }
        s.erase(0, pos + delimiter.length());
    }

    return found;
}



///For the parser?
Surface* Reader::surf(std::string n)
{
    for(Surface* s : session->surfaces)
        {
            if(!n.compare(s->name))
                return s;
        }
        return NULL;
}

bool Reader::isUnique(std::string name)
{
    for(Vert* i0 : session->verts)
    {
        if(!name.compare(i0->name))
            return false;
    }

    for(FaceNew* i0 : session->faces)
    {
        if(!name.compare(i0->name))
            return false;
    }

    for(MeshNew* i0 : session->meshes)
    {
        if(!name.compare(i0->name))
            return false;
    }

    for(Surface* i0 : session->surfaces)
    {
        if(!name.compare(i0->name))
            return false;
    }

    for(GroupNew* i0 : session->groups)
    {
        if(!name.compare(i0->name))
            return false;
    }

    for(InstanceNew* i0 : session->instances)
    {
        if(!name.compare(i0->name))
            return false;
    }

    for(PolylineNew* i0 : session->polylines)
    {
        if(!name.compare(i0->name))
            return false;
    }

    for(BSplineNew* i0 : session->bsplines)
    {
        if(!name.compare(i0->name))
            return false;
    }

    for(BezierCurveNew* i0 : session->bezierCurves)
    {
        if(!name.compare(i0->name))
            return false;
    }

    for(CircleNew* i0 : session->circles)
    {
        if(!name.compare(i0->name))
            return false;
    }

    for(FunnelNew* i0 : session->funnels)
    {
        if(!name.compare(i0->name))
            return false;
    }

    for(TunnelNew* i0 : session->tunnels)
    {
        if(!name.compare(i0->name))
            return false;
    }

    for(BankNew* i0 : session->banks)
    {
        if(!name.compare(i0->name))
            return false;
    }

    return true;
}



///Low level reader functions
Vert* Reader::vert(std::string n)
{
    return (Vert*) node->vert(n);
}

Vert* Reader::vert(VertI i)
{
    return (Vert*) node->vert(i);
}

EdgeNew* Reader::edge(std::string n)
{
    return (EdgeNew*) node->edge(n);
}

EdgeNew* Reader::edge(EdgeI i)
{
    return (EdgeNew*) node->edge(i);
}

FaceNew* Reader::face(std::string n)
{
    return (FaceNew*) node->edge(n);
}

FaceNew* Reader::face(FaceI i)
{
    return (FaceNew*) node->edge(i);
}

//For the parser?
MeshNew* Reader::mesh(std::string name){
    for(MeshNew* m : session->meshes)
    {
        if(!name.compare(m->getName()))
            return m;
    }
    for(MeshNew* m : session->polylines)
    {
        if(!name.compare(m->getName()))
            return m;
    }
    for(BSplineNew* m : session->bsplines)
    {
        if(!name.compare(m->getName()))
            return m;
    }
    for(BezierCurveNew* m : session->bezierCurves)
    {
        if(!name.compare(m->getName()))
            return m;
    }
    for(MeshNew* c : session->circles)
    {
        if(!name.compare(c->getName()))
            return c;
    }
    for(FunnelNew* f : session->funnels)
    {
        if(!name.compare(f->getName()))
            return f;
    }
    for(TunnelNew* t : session->tunnels)
    {
        if(!name.compare(t->getName()))
            return t;
    }

    return NULL;
}

///Reader convenience functions - these are the ones that should actually be called outside of this class
MeshNew* Reader::getMesh(std::string name)
{
    for (MeshNew* m0 : session->meshes){
        std::string currentName = name;
        if(m0->name.compare(currentName) == 0)
            return m0;
    }

    for (CircleNew* c0 : session->circles){
        std::string currentName = name;
        if(c0->name.compare(currentName) == 0)
            return c0;
    }

    for (TunnelNew* m0 : session->tunnels){
        //std::cout << m0->name << std::endl;
        std::string currentName = name;
        if(m0->name.compare(currentName) == 0)
            return m0;
    }

    for (FunnelNew* m0 : session->funnels){
        //std::cout << m0->name << std::endl;
        std::string currentName = name;
        if(m0->name.compare(currentName) == 0)
            return m0;
    }

    for (PolylineNew* m0 : session->polylines){
        std::string currentName = name;
        if(m0->name.compare(currentName) == 0)
            return m0;
    }

    for (BSplineNew* m0 : session->bsplines){
        std::string currentName = name;
        if(m0->name.compare(currentName) == 0)
            return m0;
    }

    for (BezierCurveNew* m0 : session->bezierCurves){
        std::string currentName = name;
        if(m0->name.compare(currentName) == 0)
            return m0;
    }


    /*if(search(name, 0))
        return (MeshNew*) node;*/
    return NULL;
}

GroupNew* Reader::getGroup(std::string name)
{
    for (GroupNew* g0 : session->groups){
        std::string currentName = name;
        if(g0->name.compare(currentName) == 0)
            return g0;
    }

    return NULL;
}

InstanceNew* Reader::getInstance(std::string name)
{
    if(node->getFullName().compare(name) == 0)
        return (InstanceNew*) node;
    if(search(name, 1))
        return (InstanceNew*) node;
    return NULL;
}



Vert* Reader::getVert(std::string name)
{

    // Check for definitions first
    for (Vert* v0 : session->verts){
        if(v0->name.compare(name) == 0)
            return v0;
    }


    for (InstanceNew* i0 : session->instances){
        string currentName = i0->getFullName();
        string argName;
        string argAfterName;
        if (name[0] == '.'){
            argName = name.substr(0,  name.substr(1).find(".") + 1);
            argAfterName = name.substr(name.substr(1).find(".") + 2);
        } else{
            argName = name.substr(0, name.find("."));
            argAfterName = name.substr(name.find(".") + 1);
        }

        if (currentName.compare(argName) == 0){
            string faceName = argAfterName.substr(0, argAfterName.find("."));
            for (FaceNew* f0 : i0->faces){
                if (f0->name.compare(faceName) == 0){
                    string vertName = argAfterName.substr(argAfterName.find(".") + 1);
                    for (Vert* v0 : f0->verts){
                        if (v0->name.compare(vertName) == 0){
                            return v0;
                        }
                    }
                }
            }
//std::cout << "---" << std::endl;
            for (Vert* v0 : i0->verts){
                //std::cout << faceName << std::endl;
                if (v0->name.compare(faceName) == 0){
                    return v0;
                }
            }

            for (InstanceNew* i1 : i0->listInstances){
                string currentNameInstance = i1->getFullName();
                if (currentNameInstance.compare(faceName) == 0){
                    string afterfaceNameInstance = argAfterName.substr(argAfterName.find(".") + 1);
                    string faceNameInstance = afterfaceNameInstance.substr(0, afterfaceNameInstance.find("."));

                    for (FaceNew* f0 : i1->faces){
                        //std::cout << "faceNameInstance" << std::endl;
                        if (f0->name.compare(faceNameInstance) == 0){
                            string vertName = afterfaceNameInstance.substr(afterfaceNameInstance.find(".") + 1);
                            for (Vert* v0 : f0->verts){
                                if (v0->name.compare(vertName) == 0){
                                    return v0;
                                }
                            }
                        }
                    }

                    for (Vert* v0 : i1->verts){
                        if (v0->name.compare(faceNameInstance) == 0){
                            return v0;
                        }
                    }
                }
            }
        }
    }
    return NULL;
}

std::list<TransformationNew*> Reader::getVertTransformations(int id){
    std::list<TransformationNew*> transformations;
    for (InstanceNew* i0 : session->instances){
        for (FaceNew* f0 : i0->faces){
            for (Vert* v0 : f0->verts){
                if (v0->index == id){
                    //std::cout << "TEST" << std::endl;
                    transformations.insert(transformations.end(), v0->transformations.begin(), v0->transformations.end());
                    //std::cout << transformations.size() << std::endl;
                    transformations.insert(transformations.end(), i0->transformations.begin(), i0->transformations.end());
                    //std::cout << transformations.size() << std::endl;
                    return transformations;
                }
            }
        }
        for (Vert* v0 : i0->verts){
            if (v0->index == id){
                transformations.insert(transformations.end(), v0->transformations.begin(), v0->transformations.end());
                transformations.insert(transformations.end(), i0->transformations.begin(), i0->transformations.end());
                return transformations;
            }
        }

        // Checking for groups
        for (InstanceNew* instanceElem : i0->listInstances){
            for (FaceNew* f0 : instanceElem->faces){
                for (Vert* v0 : f0->verts){
                    if (v0->index == id){
                        transformations.insert(transformations.end(), v0->transformations.begin(), v0->transformations.end());
                        transformations.insert(transformations.end(), i0->transformations.begin(), i0->transformations.end());
                        transformations.insert(transformations.end(), instanceElem->transformations.begin(), instanceElem->transformations.end());
                        return transformations;
                    }
                }
            }
            for (Vert* v0 : i0->verts){
                if (v0->index == id){
                    transformations.insert(transformations.end(), v0->transformations.begin(), v0->transformations.end());
                    transformations.insert(transformations.end(), i0->transformations.begin(), i0->transformations.end());
                    transformations.insert(transformations.end(), instanceElem->transformations.begin(), instanceElem->transformations.end());
                    return transformations;
                }
            }
        }
    }
    return transformations;
}


std::string Reader::getVertName(int id)
{
    // Check for definitions first
    for (Vert* v0 : session->verts){
        if(v0->index == id)
            return v0->name;
    }

    for (InstanceNew* i0 : session->instances){
        for (FaceNew* f0 : i0->faces){
            for (Vert* v0 : f0->verts){
                if (v0->index == id){
                    return i0->getFullName() + "." + f0->name + "." + v0->name;
                }
            }
        }
        for (Vert* v0 : i0->verts){
            if (v0->index == id){
                return i0->getFullName() + "." + v0->name;
            }
        }


        // Checking for groups
        for (InstanceNew* instanceElem : i0->listInstances){
            for (FaceNew* f0 : instanceElem->faces){
                for (Vert* v0 : f0->verts){
                    if (v0->index == id){
                        return i0->getFullName() + "." + instanceElem->name + "." + f0->name + "." + v0->name;
                    }
                }
            }
            for (Vert* v0 : instanceElem->verts){
                if (v0->index == id){
                    return i0->getFullName() + "." + instanceElem->name + "." + v0->name;
                }
            }
        }
    }
    return NULL;
}

std::string Reader::getFaceName(int id)
{
    // Check for definitions first
    for (FaceNew* f0 : session->faces){
        if(f0->index == id){
            return f0->name;
        }
    }

    for (InstanceNew* i0 : session->instances){
        for (FaceNew* f0 : i0->faces){
            if (f0->index == id){
                return i0->name + "." + f0->name;
            }
        }

        for (InstanceNew* instanceElem : i0->listInstances){
            for (FaceNew* f0 : instanceElem->faces){
                if (f0->index == id){
                    return i0->name + "." + instanceElem->name + "." + f0->name;
                }
            }
        }
    }
    return NULL;
}

Vert* Reader::getVert(int id)
{
    // Check for definitions first
    for (Vert* v0 : session->verts){
        if(v0->index == id)
            return v0;
    }

    for (InstanceNew* i0 : session->instances){
        for (Vert* v0 : i0->verts){
            if (v0->index == id){
                return v0;
            }
        }

        for (FaceNew* f0 : i0->faces){
            for (Vert* v0 : f0->verts){
                if (v0->index == id){
                    return v0;
                }
            }
        }

        // Check for groups
        for (InstanceNew* iListElem : i0->listInstances){
            for (Vert* v0 : iListElem->verts){
                if (v0->index == id){
                    return v0;
                }
            }

            for (FaceNew* f0 : iListElem->faces){
                for (Vert* v0 : f0->verts){
                    if (v0->index == id){
                        return v0;
                    }
                }
            }
        }

    }
    return NULL;
}

FaceNew* Reader::getFace(int id){
    for (FaceNew* f0 : session->faces){
        if(f0->index == id)
            return f0;
    }

    for (InstanceNew* i0 : session->instances){
        for (FaceNew* f0 : i0->faces){
            if(f0->index == id)
                return f0;
        }

        for (InstanceNew* iListElem : i0->listInstances){
            for (FaceNew* f0 : iListElem->faces){
                if(f0->index == id)
                    return f0;
            }
        }
    }



    return NULL;
}

EdgeNew* Reader::getEdge(std::string name)
{
    if(node->getFullName().find(name) != std::string::npos)
        return (EdgeNew*) node->edge(name);
    if(!search(name, 0))
        return NULL;
    return (EdgeNew*) node->edge(name);
}

FaceNew* Reader::getFace(std::string name)
{
    for (FaceNew* f0 : session->faces){
        if(f0->name.compare(name) == 0)
            return f0;
    }

    for (InstanceNew* i0 : session->instances){

        string currentName = i0->getFullName();
        string argName = name.substr(0, name.find("."));
        string argAfterName = name.substr(name.find(".") + 1);

        if (currentName.compare(argName) == 0){
            string faceName = argAfterName.substr(0, argAfterName.find("."));
            for (FaceNew* f0 : i0->faces){
                if (f0->name.compare(faceName) == 0){
                    return f0;
                }
            }
        }
    }
    return NULL;
    /*if(node->getFullName().find(name) != std::string::npos)
        return (FaceNew*) node->face(name);
    if(!search(name, 0))
        return NULL;
    return (FaceNew*) node->face(name);*/
}

bool Reader::deleteFace(FaceNew * searchFace){
    for (InstanceNew* i0 : session->instances){
        i0->faces.remove(searchFace);
    }
    for (EdgeNew* e : searchFace->edges){
        if (e->f0 == searchFace){
            e->f0 = NULL;
            e->f0 = e->f1;
            e->f1 = NULL;
        } else if (e->f1 == searchFace){
            e->f1 = NULL;
        }
    }
    for (Vert* v : searchFace->verts){
        v->faces.remove(searchFace);
    }
    return false;
}

EdgeNew* Reader::getEdge(int id1, int id2){
    for (InstanceNew* i0 : session->instances){
        for (EdgeNew* e0 : i0->edges){
            if ((e0->v0->index == id1 && e0->v1->index == id2) || (e0->v0->index == id2 && e0->v1->index == id1)){
                return e0;
            }
        }

        for (FaceNew* f0 : i0->faces){
            for (EdgeNew* e0 : f0->edges){
                if ((e0->v0->index == id1 && e0->v1->index == id2) || (e0->v0->index == id2 && e0->v1->index == id1)){
                    return e0;
                }
            }
        }

        // Check for groups
        for (InstanceNew* iListElem : i0->listInstances){
            for (EdgeNew* e0 : iListElem->edges){
                if ((e0->v0->index == id1 && e0->v1->index == id2) || (e0->v0->index == id2 && e0->v1->index == id1)){
                    return e0;
                }


                /*if (e0->v0->index == id1 || e0->v1->index == id1){
                    std::cout << "HHHH" << std::endl;
                }*/
            }

            for (FaceNew* f0 : iListElem->faces){
                for (EdgeNew* e0 : f0->edges){
                    if ((e0->v0->index == id1 && e0->v1->index == id2) || (e0->v0->index == id2 && e0->v1->index == id1)){
                        return e0;
                    }
                }
            }
        }
    }

    return NULL;
}


