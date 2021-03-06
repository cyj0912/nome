//
//  FunnelNew.h
//  model
//
//  Created by L on 26/08/2017.
//  Copyright © 2017 L. All rights reserved.
//

#ifndef FunnelNew_h
#define FunnelNew_h

#include <stdio.h>
#include <set>
#include "Data.h"
#include "MeshNew.h"
class Reader;

///Mesh class, formed by faces, primarily quad faces, valence four vertices
typedef class FunnelNew : public MeshNew
{
public:
    double *n;
    double *ro;
    double *ratio;
    double *h;

    std::string nStr;
    std::string roStr;
    std::string ratioStr;
    std::string hStr;

    Reader * reader;
    void createVertEdgeFunnel();
    int updateFunnel();
    bool setName(std::string n);
    Session* currSession;
} FunnelNew;

///Instance functions
FunnelNew* createFunnel(double *n, double *ro, double *ratio, double *h, Reader* reader);
FunnelNew* createFunnel(FunnelNew*);

#endif /* FunnelNew_h */
