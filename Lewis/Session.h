//
//  Session.h
//  model
//
//  Created by L on 26/08/2017.
//  Copyright © 2017 L. All rights reserved.
//

#ifndef Session_h
#define Session_h

#include <stdio.h>
#include "Data.h"
#include "MeshNew.h"
#include "GroupNew.h"
#include "ObjectNew.h"
#include "BankNew.h"
#include "PolylineNew.h"

typedef struct Session
{
private:
    int accesses;

public:
    std::list<Vert*> verts;
    std::list<EdgeNew*> edges;
    std::list<FaceNew*> faces;
    std::list<MeshNew*> meshes;
    std::list<Surface*> surfaces;
    std::list<GroupNew*> groups;
    std::list<InstanceNew*> instances;
    std::list<PolylineNew*> polylines;
    std::list<BankNew*> banks;
    std::string name;

    //Naming functions
    bool setName(std::string n);
    std::string getName();
    bool updateNames();
    void selectVert(GLint hits, GLuint *names, GLdouble posX, GLdouble posY, GLdouble posZ);
    void selectFace(GLint hits, GLuint *names, GLdouble posX, GLdouble posY, GLdouble posZ);
    void selectEdge(GLint hits, GLuint *names, GLdouble posX, GLdouble posY, GLdouble posZ);

} Session;

//Instantiation
Session* createSession();
Session* createSession(Session*);


#endif /* Session_h */
