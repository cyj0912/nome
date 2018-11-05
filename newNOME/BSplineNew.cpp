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
		int comp = (int)floor(t);

		if ((comp < i + 1) && (comp >= i))
		{
			return 1;
		}
		return 0;
	}

	else {
		float a = (t - i) / k;
		float b = (i + k + 1 - t) / k;

		a = a * basis(i, k - 1, t);
		b = b * basis(i + 1, k - 1, t);

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

	//s stores all the positions
	std::vector<Vector3> s = PointArray;

	//You can't really sweep correctly with size=1 or 2
	if (s.size() == 1)
	{
		result.emplace_back(Matrix3x4(s[0], Quaternion(params.Azimuth, Vector3::UNIT_Z), Vector3::ONE));
		return result;
	}
	else if (s.size() == 2)
	{
		result.emplace_back(Matrix3x4(s[0], Quaternion(params.Azimuth, Vector3::UNIT_Z), Vector3::ONE));
		result.emplace_back(Matrix3x4(s[1], Quaternion(params.Azimuth + params.Twist, Vector3::UNIT_Z), Vector3::ONE));
		return result;
	}

	if (params.bClosed)
    {
	    //Prepend the point list with end and append with begin, begin + 1;
        s.insert(s.begin(), s[s.size() - 1]);
        s.push_back(s[1]);
        s.push_back(s[2]);
    }

    if (params.bMinimizeTorsion)
    {
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

            Quaternion rotAroundTgt(params.Azimuth + params.Twist * i, Vector3::UNIT_Z);
            Matrix3x4 localRot(Vector3::ZERO, rotAroundTgt, Vector3::ONE);

            result.push_back(f * localRot);
        }
    }
    else
    {
        //Intrinsic mode
        result.push_back(Matrix3x4::IDENTITY); //Placeholder for the first vert

        //Deal with all vertices except the two on the ends
        for (int i = 1; i < s.size() - 1; i++)
        {
            Vector3 vPrev = s[i - 1] - s[i];
            Vector3 vNext = s[i + 1] - s[i];
            vPrev.Normalize();
            vNext.Normalize();
            Vector3 normal = -(vPrev + vNext) / 2.0f;
            normal.Normalize();
            Vector3 biNormal = normal.CrossProduct(vNext).Normalized();
            Vector3 tangent = biNormal.CrossProduct(normal).Normalized();
            Matrix3x4 f;
            f.SetRotation(Matrix3(biNormal, normal, tangent));
            f.SetTranslation(s[i]);

            Quaternion rotAroundTgt(params.Azimuth + params.Twist * i, Vector3::UNIT_Z);
            Matrix3x4 localRot(Vector3::ZERO, rotAroundTgt, Vector3::ONE);

            result.push_back(f * localRot);
        }

        {
            //First vert
            Vector3 tangent = s[1] - s[0];
            tangent.Normalize();
            //Grab the binormal from the second vert
            Vector3 biNormal = result[1].Column(0);
            Vector3 normal = tangent.CrossProduct(biNormal).Normalized();
            Matrix3x4 f;
            f.SetRotation(Matrix3(biNormal, normal, tangent));
            f.SetTranslation(s[0]);

            Quaternion rotAroundTgt(params.Azimuth + params.Twist * 0, Vector3::UNIT_Z);
            Matrix3x4 localRot(Vector3::ZERO, rotAroundTgt, Vector3::ONE);

            result[0] = f * localRot;
        }

        {
            //Last vert
            Vector3 tangent = -(s[s.size() - 2] - s[s.size() - 1]);
            tangent.Normalize();
            //Grab the binormal from the second to last vert
            Vector3 biNormal = result[result.size() - 1].Column(0);
            Vector3 normal = tangent.CrossProduct(biNormal).Normalized();
            Matrix3x4 f;
            f.SetRotation(Matrix3(biNormal, normal, tangent));
            f.SetTranslation(s[s.size() - 1]);

            Quaternion rotAroundTgt(params.Azimuth + params.Twist * (s.size() - 1), Vector3::UNIT_Z);
            Matrix3x4 localRot(Vector3::ZERO, rotAroundTgt, Vector3::ONE);

            result.push_back(f * localRot);
        }
    }

	if (params.bClosed)
    {
	    result.pop_back();
	    result.erase(result.begin());
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
