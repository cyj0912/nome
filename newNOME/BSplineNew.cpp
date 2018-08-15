//
//  BSplineNew.cpp
//  model
//
//  Created by L on 26/08/2017.
//  Copyright © 2017 L. All rights reserved.
//

#include "BSplineNew.h"
#include "Data.h"
#include <glm/glm.hpp>
#include "Session.h"

bool BSplineNew::updateBSpline()
{
    double *currentValSet = (double*) malloc(sizeof(double));
    parseGetBankVal(segmentsStr.c_str(), currSession, currentValSet, 0);

    if (*currentValSet != segments){
        segments = *currentValSet;
        verts.clear();
        edges.clear();
        calculate(order, true);

        std::list<Vert*>::iterator it = verts.begin();
        std::list<Vert*>::iterator it2 = verts.begin();
        EdgeNew *currentEdge;
        ++it2;
        while (it != verts.end()){
            if (it2 != verts.end()){
                currentEdge = createEdge(*it, *it2, false);
                edges.push_back(currentEdge);
                it2++;
            }
            else{
                if (isLoop){
                    currentEdge = createEdge(verts.back(), verts.front(), false);
                    edges.push_back(currentEdge);
                }
            }
            it++;

        }
        return 1;
    }
    else{
        calculate(order, false);
    }
    return 0;
}

void BSplineNew::set_proxy(Vert *v)
{
    proxy.push_back(v);
}


void BSplineNew::set_segments(double a)
{
    segments = a;
}

void BSplineNew::set_order(int a)
{
    order = a;
}


float BSplineNew::basis(int i, int k, float t)
{
    //calculate basis function, i = control point index, k = order, t = variable parameter
    if (k < 0)
    {
        return 0;
    }

    else if (k == 0)
    {
        int comp = (int) floor(t);

        if ((comp < i + 1) && (comp >= i))
        {
            return 1;
        }
        return 0;
    }

    else {
        float a = (t - i)/k;
        float b = (i + k + 1 - t)/k;

        a = a * basis(i, k-1, t);
        b = b * basis(i+1, k-1, t);

        return a + b;
    }

}

void BSplineNew::calculate (int order, bool createNewVertices)
{
    int numVertCreated = 0;
    int degree = order - 1;
    int originalSize = proxy.size();
    std::vector<Vert*> proxyLoop = proxy;
    int segmentLoop = (int)round(this->segments);

	PointArray.clear();


    if (isLoop == true){
        for (int i = 0; i < order-1; i++){
            proxyLoop.push_back(proxy.at(i));
        }
        //segmentLoop -= 1;
    }

    //calculate bspline for general order bspline, order>=2 is enforced
    if (order >= 2)
    {
        //clear all vertices just in case
        //verts.clear();


        float lim = degree + proxyLoop.size() - 2;

        float add = ((float) (proxyLoop.size() - degree))/(segmentLoop);


        int realLimit;
        if (isLoop == true){
            realLimit = segmentLoop-1;
        } else{
            realLimit = segmentLoop;
        }

        float upper;

        float t = degree + 1;

        //calculate bspline at each t
        for (int vertexNumber = 0; vertexNumber <= realLimit; vertexNumber++)//{
        {
            double *x = (double*) malloc(sizeof(double));
            double *y = (double*) malloc(sizeof(double));
            double *z = (double*) malloc(sizeof(double));

            *x = 0;
            *y = 0;
            *z = 0;

            for (int i = 1; i <= proxyLoop.size(); i++)
            {
                float temp = basis(i, degree, t);

                double* xProx = proxyLoop.at(i-1) -> x;
                double* yProx = proxyLoop.at(i-1) -> y;
                double* zProx = proxyLoop.at(i-1) -> z;

                *x = *x + (temp * *xProx);
                *y = *y + (temp * *yProx);
                *z = *z + (temp * *zProx);
            }

            if (createNewVertices){
                Vert* newBSplineVertex = createVert(x, y, z);
                //newBSplineVertex -> name = std::to_string(vertexNumber);
                //addVertex(newBSplineVertex);

                newBSplineVertex->setName("v" + std::to_string(vertexNumber));
                verts.push_back(newBSplineVertex);
            }
            else{
                std::list<Vert*>::iterator it = verts.begin();
                std::advance(it, numVertCreated);
                *((*it)->x) = *x;
                *((*it)->y) = *y;
                *((*it)->z) = *z;
            }
            numVertCreated += 1;

			//TODO: one day, the math library shall support double
			PointArray.emplace_back((float)*x, (float)*y, (float)*z);

            t = t + add;
        }
    }
}

std::vector<Matrix3x4> BSplineNew::GetSweepFrames(const SweepPathParams& params) const
{
	std::vector<Matrix3x4> result;
	for (const auto& point : PointArray)
	{
		Matrix3x4 frame{ 0,0,-1,0,
						 0,1,0,0,
						 1,0,0,0 };
		frame.SetTranslation(point);
		result.push_back(frame);
	}
	return result;
}

static int bIndex = 0;

///BSpline functions
BSplineNew* createBSplineNew()
{
    BSplineNew* b0 = new BSplineNew();
    //This behaviour depends on the parser
    b0->setName("bspline" + std::to_string(bIndex));
    bIndex++;
    //b0->prevSegment = -1;

    return b0;
}

bool BSplineNew::setName(std::string n)
{
    if(n.find(".") != std::string::npos && n.find(":") != std::string::npos)
        return false;
    name = n;
    bool error = updateNames();
    return error;
}
