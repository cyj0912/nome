//
//  PolylineNew.h
//

#ifndef PolylineNew_h
#define PolylineNew_h

#include <stdio.h>
#include <set>
#include "Data.h"
#include "MeshNew.h"

///Mesh class, formed by faces, primarily quad faces, valence four vertices
typedef class PolylineNew : public MeshNew, public ISweepPath
{
public:
    bool setName(std::string n);

	//Inherited via ISweepPath
	std::vector<Matrix3x4> GetSweepFrames(const SweepPathParams& params) const override;
} PolylineNew;

///Instance functions
PolylineNew* createPolylineNew(std::list<Vert*> verticesPolyline);
PolylineNew* createPolylineNew(std::list<Vert*> verticesPolyline, std::list<EdgeNew*> *edgeList);
PolylineNew* createPolylineNew(PolylineNew*);

#endif /* PolylineNew_h */
