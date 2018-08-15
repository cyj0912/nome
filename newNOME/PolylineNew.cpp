//
//  Mesh.cpp
//  model
//
//  Created by L on 26/08/2017.
//  Copyright © 2017 L. All rights reserved.
//

#include "PolylineNew.h"

static int pIndex = 0;

///Polyline functions
PolylineNew* createPolylineNew(std::list<Vert*> verticesPolyline)
{
    PolylineNew* p0 = new PolylineNew();
    //This behaviour depends on the parser
    p0->setName("polyline" + std::to_string(pIndex));
    p0->verts = verticesPolyline;

    EdgeNew * currentEdge;
    std::list<Vert*>::iterator it = verticesPolyline.begin();
    std::list<Vert*>::iterator it2 = verticesPolyline.begin();
    std::list<EdgeNew*> currentEdges;
    ++it2;
    while (it != verticesPolyline.end()){
        if (it2 != verticesPolyline.end()){
            currentEdge = createEdge(*it, *it2, false);
            it2++;
            p0->edges.push_back(currentEdge);
        }
        it++;

    }

    pIndex++;

    return p0;
}

PolylineNew* createPolylineNew(std::list<Vert*> verticesPolyline, std::list<EdgeNew*> *edgeList)
{
    PolylineNew* p0 = new PolylineNew();
    //This behaviour depends on the parser
    p0->setName("polyline" + std::to_string(pIndex));
    p0->verts = verticesPolyline;

    EdgeNew * currentEdge;
    std::list<Vert*>::iterator it = verticesPolyline.begin();
    std::list<Vert*>::iterator it2 = verticesPolyline.begin();
    std::list<EdgeNew*> currentEdges;
    ++it2;
    while (it != verticesPolyline.end()){
        if (it2 != verticesPolyline.end()){
            currentEdge = NULL;
            for (EdgeNew* e0 : *edgeList){
                if ((e0->v0->index == (*it)->index && e0->v1->index == (*it2)->index) || (e0->v0->index == (*it2)->index && e0->v1->index == (*it)->index)){
                    currentEdge = e0;
                    break;
                }
            }
            if (currentEdge == NULL){
                currentEdge = createEdge(*it, *it2, false);
                edgeList->push_back(currentEdge);
            }
            it2++;
            p0->edges.push_back(currentEdge);
        }
        it++;

    }

    pIndex++;

    return p0;
}

bool PolylineNew::setName(std::string n)
{
    if(n.find(".") != std::string::npos && n.find(":") != std::string::npos)
        return false;
    name = n;
    bool error = updateNames();
    return error;
}

std::vector<Matrix3x4> PolylineNew::GetSweepFrames(const SweepPathParams& params) const
{
	std::vector<Matrix3x4> result;
	for (auto* v : verts)
	{
		Vector3 pos = v->getUntransformedPosition();
		Matrix3x4 frame = Matrix3x4::IDENTITY;
		frame.SetTranslation(pos);
		result.push_back(frame);
	}
	return result;
}
