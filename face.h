/**
 * @author Andy Wang, UC Berkeley.
 * Copyright 2016 reserve.
 * UC Berkeley, NOME project.
 * Advised by Prof. Sequin H. Carlos.
 */

#ifndef __FACE_H__
#define __FACE_H__

#include <glm/glm.hpp>
#include <vector>
#include "edge.h"
#include "vertex.h"
#include "mesh.h"
#include <QColor>
using namespace glm;
using namespace std;

/**
 * @brief The Face class. The face class build for winged-
 * edge data structure. A face is constructed by a seqence of
 * vertices/edges.
 */
class Face
{
public:
    Face();
    Face(std::vector<Vertex> vertices);
    /* The face normal.*/
    vec3 normal;
    /* Pointer to one edge in this face.*/
    Edge *oneEdge;
    /* Pointer to the face point in subdivision. */
    Vertex *facePoint;
    /* Indicator of whether this face is selected.*/
    bool selected;
    /* FaceID, is the index from the global face list.*/
    int id;
    /* The name of this face.*/
    string name;
    /* The color of this face. */
    QColor color;
    std::vector<Vertex> vertices;
    /* Indicate if this face has user defined color. */
    bool user_defined_color;
};

#endif // __FACE_H__
