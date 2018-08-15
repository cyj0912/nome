//
//  BSplineNew.h
//

#ifndef BSplineNew_h
#define BSplineNew_h

#include <stdio.h>
#include <set>
#include "Data.h"
#include "MeshNew.h"

typedef class BSplineNew : public MeshNew, public ISweepPath
{
public:
    std::vector<Vert*> proxy;
    double segments;
    std::string segmentsStr;

    Session* currSession;
    //double prevSegment;
    int order;
    bool isLoop;

    bool setName(std::string n);

    void set_segments(double);
    void set_proxy(Vert*);
    void set_order(int);

    bool updateBSpline();

    //getters
    //double get_segments();
    //int get_order();

    //calculate
    float basis(int, int, float);
    void calculate(int, bool);

	std::vector<Matrix3x4> GetSweepFrames(const SweepPathParams& params) const override;

private:
	std::vector<Vector3> PointArray;
} BSplineNew;

///Instance functions
BSplineNew* createBSplineNew();
BSplineNew* createBSplineNew(BSplineNew*);

#endif /* BSplineNew_h */
