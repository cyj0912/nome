//
//  TorusKnotNew.cpp
//  model
//
//  Created by Henry on 11/04/2018
//  Copyright © 2018 Henry. All rights reserved.
//

#include "TorusKnotNew.h"
#include "Session.h"
#include <math.h>
#include <glm/glm.hpp>

static int cIndex = 0;

///Circle functions
TorusKnotNew* createTorusKnot(double *pass, double *turn, double *rmaj, double* rmin, double *num)
{
    TorusKnotNew* t0 = new TorusKnotNew();
    //This behaviour depends on the parser
    t0->setName("torusKnot" + std::to_string(cIndex));
    double *passPtr = (double*) malloc(sizeof(double));
    t0->pass = pass;
    t0->turn = turn;
    t0->rmaj = rmaj;
    t0->rmin = rmin;
    t0->num = num;

    t0->createVertEdgeTorusKnot();

    cIndex++;

    /*c0->createVertEdgeCircle();
    c0-> updateCircle();*/
    return t0;
}

bool TorusKnotNew::setName(std::string n)
{
    if(n.find(".") != std::string::npos && n.find(":") != std::string::npos)
        return false;
    name = n;
    bool error = updateNames();
    return error;
}

int TorusKnotNew::updateTorusKnot() {
    double *currentValPass = (double*) malloc(sizeof(double));
    parseGetBankVal(numStr.c_str(), this->currSession, currentValPass, 0);

    double *currentValTurn = (double*) malloc(sizeof(double));
    parseGetBankVal(radStr.c_str(), this->currSession, currentValTurn, 0);

    double *currentValRmaj = (double*) malloc(sizeof(double));
    parseGetBankVal(radStr.c_str(), this->currSession, currentValRmaj, 0);

    double *currentValRmin = (double*) malloc(sizeof(double));
    parseGetBankVal(radStr.c_str(), this->currSession, currentValRmin, 0);

    double *currentValNum = (double*) malloc(sizeof(double));
    parseGetBankVal(radStr.c_str(), this->currSession, currentValNum, 0);

    // Check if we need to create new vertices (if the number of vertices has changed).
    if (*num != *currentValNum){
        *num = *currentValNum;
        createVertEdgeTorusKnot();
        return 1;
    }
    else if (*pass != *currentValPass || *turn != *currentValTurn || *rmaj != *currentValRmaj || *rmin != *currentValRmin){
        *pass = *currentValPass;
        *turn = *currentValTurn;
        *rmaj = *currentValRmaj;
        *rmin = *currentValRmin;

        // Redraw in case the radius has changed.
        float i = 0;
        for (Vert* vert : verts) {
            float currAngle = 2.0 * i / *num * M_PI;
            double rad = *rmaj + *rmin * glm::cos(*pass * currAngle);

            *(vert->x) = rad * glm::cos(*turn * currAngle);
            *(vert->y) = rad * glm::sin(*turn * currAngle);
            *(vert->z) = -1.0 * *rmin * glm::sin(*pass * currAngle);
            i++;
        }
        return 0;
    }

}

void TorusKnotNew::createVertEdgeTorusKnot(){
    verts.clear();
    edges.clear();
    for(int i = 0; i < *num; i++)
    {   
        float currAngle = 2.0 * i / *num * M_PI;

        double *x = (double*) malloc(sizeof(double));
        double *y = (double*) malloc(sizeof(double));
        double *z = (double*) malloc(sizeof(double));

        double rad = *rmaj + *rmin * glm::cos(*pass * currAngle);

        *x = rad * glm::cos(*turn * currAngle);
        *y = rad * glm::sin(*turn * currAngle);
        *z = -1.0 * *rmin * glm::sin(*pass * currAngle);

        Vert * newVertex = createVert (x, y, z);
        newVertex->setName("v" + std::to_string(i));
        //newVertex->setName(name + "." +  std::to_string(i));
        verts.push_back(newVertex);
    }

    std::list<Vert*>::iterator it = verts.begin();
    std::list<Vert*>::iterator it2 = verts.begin();
    EdgeNew *currentEdge;
    ++it2;
    while (it != verts.end()){
        if (it2 != verts.end()){
            currentEdge = createEdge(*it, *it2, false);
            it2++;
        }
        else{
            currentEdge = createEdge(verts.back(), verts.front(), false);
        }
        it++;
        edges.push_back(currentEdge);
    }
}
