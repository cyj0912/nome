#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <iostream>
#include <unordered_map>
#include <glm/glm.hpp>
#include "parameter.h"
#include <stack>
#include <vector>
#include <QColor>

class Transformation;
using namespace glm;

float evaluate_expression(string expr,
                          unordered_map<string, Parameter> *params);

float evaluate_mesh_expression(string expr,
                               unordered_map<string, Parameter> *params,
                               Mesh * mesh);

float evaluate_transformation_expression(string expr,
                               unordered_map<string, Parameter> *params,
                               Transformation * t);

float evaluate_vertex_expression(string expr,
                                 unordered_map<string, Parameter> *params,
                                 Vertex * t);

QColor evaluate_color_expression(string expr, int lineNumber);

float getParameterValue(string name,
                        unordered_map<string, Parameter> *params);

float getMeshParameterValue(string name,
                            unordered_map<string, Parameter> *params,
                            Mesh * mesh);

float getTransformationParameterValue(string name,
                                      unordered_map<string, Parameter> *params,
                                      Transformation *t);

float getVertexParameterValue(string name,
                              unordered_map<string, Parameter> *params,
                              Vertex * mesh);

bool isOperator(char token);

float getVal(float x, float y, char oper);

int getPriority(char oper);

vec3 getXYZ(string input);

float getOneValue(string input);

vec4 getXYZW(string input);

#endif // UTILS_H
