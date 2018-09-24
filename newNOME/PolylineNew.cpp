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

	//s stores all the positions
	std::vector<Vector3> s;
	for (auto* v : verts)
		s.push_back(v->getUntransformedPosition());

	//You can't really sweep correctly with size=1 or 2
	if (s.size() == 1)
	{
		result.push_back(Matrix3x4(s[0], Quaternion::IDENTITY, Vector3::ONE));
		return result;
	}
	else if (s.size() == 2)
	{
		result.push_back(Matrix3x4(s[0], Quaternion::IDENTITY, Vector3::ONE));
		result.push_back(Matrix3x4(s[1], Quaternion::IDENTITY, Vector3::ONE));
		return result;
	}

	//d stores all the derivatives (tangents)
	std::vector<Vector3> d;
	d.push_back((s[1] - s[0]).Normalized());
	for (int i = 1; i < s.size() - 1; i++)
	{
		auto delta = s[i + 1] - s[i - 1];
		d.push_back(delta.Normalized());
	}
	d.push_back((s[s.size() - 1] - s[s.size() - 2]).Normalized());

	Vector3 Y = -(d[1] - d[0]);
	Y.Normalize();
	for (int i = 0; i < s.size(); i++)
	{
		Matrix3x4 f;
		Vector3 X = Y.CrossProduct(d[i]).Normalized();
		Vector3 newY = d[i].CrossProduct(X).Normalized();
		Y = (Y + newY) / 2.0f;
		f.SetRotation(Matrix3(X, newY, d[i]));
		f.SetTranslation(s[i]);
		result.push_back(f);
	}
	return result;
}
