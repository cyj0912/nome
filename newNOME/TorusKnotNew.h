//
//  TorusKnotNew.h
//
#pragma once

#ifndef TorusKnotNew_h
#define TorusKnotNew_h

#include <stdio.h>
#include <set>
#include "Data.h"
#include "MeshNew.h"

///Mesh class, formed by faces, primarily quad faces, valence four vertices
typedef class TorusKnotNew : public MeshNew
{
public:
    double *num;
    double *rmaj;
    double *rmin;
    double *pass;
    double *turn;
    std::string numStr;
    std::string radStr;
    void createVertEdgeTorusKnot();
    int updateTorusKnot();
    bool setName(std::string n);
    Session * currSession;
} TorusKnotNew;

///Instance functions
TorusKnotNew* createTorusKnot(double *pass, double *turn, double *rmaj, double* rmin, double* num);
TorusKnotNew* createTorusKnot(TorusKnotNew*);

#endif /* TorusKnotNew.h */
