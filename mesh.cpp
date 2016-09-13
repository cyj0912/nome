/**
 * @author Andy Wang, UC Berkeley.
 * Copyright 2016 reserve.
 * UC Berkeley, Slide_2016 project.
 * Advised by Prof. Sequin H. Carlos.
 */

#include "mesh.h"
#include "parameter.h"
#include "group.h"
#include <unordered_set>

Mesh::Mesh(int type)
{
    user_set_color = false;
    transformations_up.clear();
    parent = NULL;
    this -> type = type;
    in_editing_mode = false;
    if(type == 1 || type == 2)
    {
        n = 0;
        ro = 0.0f;
        ratio = 0.0f;
        h = 0.0f;
        n_expr = "";
        ro_expr = "";
        ratio_expr = "";
        h_expr = "";
    }
    isConsolidateMesh = false;
}

void Mesh::addVertex(Vertex * v)
{
    vertList.push_back(v);
}

Edge * Mesh::findEdge(Vertex * v1, Vertex * v2)
{
    unordered_map<Vertex*, vector<Edge*> >::iterator vIt;
    vector<Edge*>::iterator eIt;
    vIt = edgeTable.find(v2);
    if(vIt != edgeTable.end())
    {
        for(eIt = (vIt -> second).begin(); eIt < (vIt -> second).end(); eIt ++)
        {
            if((*eIt) -> vb == v1)
            {
                //cout<<"Find Edge from vertex "<<v2 -> ID<<" to vertex "<<v1 -> ID<<"."<<endl;
                return (*eIt);
            }
        }
    }
    vIt = edgeTable.find(v1);
    if(vIt != edgeTable.end()) {
        for(eIt = (vIt -> second).begin(); eIt < (vIt -> second).end(); eIt ++) {
            if((*eIt) -> vb == v2) {
                //cout<<"Find M Edge from vertex "<<v1 -> ID<<" to vertex "<<v2 -> ID<<"."<<endl;
                (*eIt) -> mobius = true;
                (*eIt) -> va -> onMobius = true;
                (*eIt) -> vb -> onMobius = true;
                return (*eIt);
            }
        }
    }
    return NULL;
}

Edge * Mesh::createEdge(Vertex * v1, Vertex * v2) {
    Edge * edge = findEdge(v1, v2);
    if(edge == NULL) {
        //cout<<"Creating new Edge from vertex "<<v1 -> ID<<" to vertex "<<v2 -> ID<<"."<<endl;
        edge = new Edge(v1, v2);
        if(v1 -> oneEdge == NULL) {
            v1 -> oneEdge = edge;
        }
        if(v2 -> oneEdge == NULL) {
            v2 -> oneEdge = edge;
        }
        unordered_map<Vertex*, vector<Edge*> >::iterator vIt;
        vIt = edgeTable.find(v1);
        if(vIt != edgeTable.end()) {
            (vIt -> second).push_back(edge);
        } else {
            vector<Edge*> currEdges;
            currEdges.push_back(edge);
            edgeTable[v1] = currEdges;
        }
    }
    //cout<<"The va of edge is "<<edge -> va -> ID<<" . The vb is "<< edge -> vb -> ID<<" ."<<endl;
    return edge;
}

void Mesh::addTriFace(Vertex * v1, Vertex * v2, Vertex * v3) {
    Face * newFace = new Face;
    Edge * e12 = createEdge(v1, v2);
    Edge * e23 = createEdge(v2, v3);
    Edge * e31 = createEdge(v3, v1);
    if(e12 -> fa == NULL) {
        e12 -> fa = newFace;
    } else if(e12 -> fb == NULL) {
        e12 -> fb = newFace;
    } else {
        cout<<"ERROR: Try to create a Non-Manifold at edge with vertex1 : "
        <<v1 -> ID<<" and vertex2 :"<<v2 -> ID<<endl;
        exit(0);
    }
    if(e23 -> fa == NULL) {
        e23 -> fa = newFace;
    } else if(e23 -> fb == NULL) {
        e23 -> fb = newFace;
    } else {
        cout<<"ERROR: Try to create a Non-Manifold at edge with vertex1 : "
        <<v2 -> ID<<" and vertex2 :"<<v3 -> ID<<endl;
        exit(0);
    }
    if(e31 -> fa == NULL) {
        e31 -> fa = newFace;
    } else if(e31 -> fb == NULL) {
        e31 -> fb = newFace;
    } else {
        cout<<"ERROR: Try to create a Non-Manifold at edge with vertex1 : "
        <<v3 -> ID<<" and vertex2 :"<<v1 -> ID<<endl;
        exit(0);
    }
    newFace -> oneEdge = e12;
    //cout<<"Testing: "<<newFace -> oneEdge -> va -> ID<<endl;
    e12 -> setNextEdge(v1, newFace, e31);
    e12 -> setNextEdge(v2, newFace, e23);
    e23 -> setNextEdge(v2, newFace, e12);
    e23 -> setNextEdge(v3, newFace, e31);
    e31 -> setNextEdge(v1, newFace, e12);
    e31 -> setNextEdge(v3, newFace, e23);
    newFace -> id = faceList.size();
    faceList.push_back(newFace);
}

void Mesh::addQuadFace(Vertex * v1, Vertex * v2, Vertex * v3, Vertex * v4) {
    Face * newFace = new Face;
    Edge * e12 = createEdge(v1, v2);
    Edge * e23 = createEdge(v2, v3);
    Edge * e34 = createEdge(v3, v4);
    Edge * e41 = createEdge(v4, v1);
    if(e12 -> fa == NULL) {
        e12 -> fa = newFace;
    } else if(e12 -> fb == NULL) {
        e12 -> fb = newFace;
    } else {
        cout<<"ERROR: Try to create a Non-Manifold at edge with vertex1 : "
        <<v1 -> ID<<" and vertex2 :"<<v2 -> ID<<endl;
        exit(0);
    }
    if(e23 -> fa == NULL) {
        e23 -> fa = newFace;
    } else if(e23 -> fb == NULL) {
        e23 -> fb = newFace;
    } else {
        cout<<"ERROR: Try to create a Non-Manifold at edge with vertex1 : "
        <<v2 -> ID<<" and vertex2 :"<<v3 -> ID<<endl;
        exit(0);
    }
    if(e34 -> fa == NULL) {
        e34 -> fa = newFace;
    } else if(e34 -> fb == NULL) {
        e34 -> fb = newFace;
    } else {
        cout<<"ERROR: Try to create a Non-Manifold at edge with vertex1 : "
        <<v3 -> ID<<" and vertex2 :"<<v4 -> ID<<endl;
        exit(0);
    }
    if(e41 -> fa == NULL) {
        e41 -> fa = newFace;
    } else if(e41 -> fb == NULL) {
        e41 -> fb = newFace;
    } else {
        cout<<"ERROR: Try to create a Non-Manifold at edge with vertex1 : "
        <<v4 -> ID<<" and vertex2 :"<<v1 -> ID<<endl;
        exit(0);
    }
    newFace -> oneEdge = e12;
    e12 -> setNextEdge(v1, newFace, e41);
    e12 -> setNextEdge(v2, newFace, e23);
    e23 -> setNextEdge(v2, newFace, e12);
    e23 -> setNextEdge(v3, newFace, e34);
    e34 -> setNextEdge(v3, newFace, e23);
    e34 -> setNextEdge(v4, newFace, e41);
    e41 -> setNextEdge(v4, newFace, e34);
    e41 -> setNextEdge(v1, newFace, e12);
    newFace -> id = faceList.size();
    faceList.push_back(newFace);
}

void Mesh::addPolygonFace(vector<Vertex*> vertices, bool reverseOrder) {
    if(vertices.size() < 3) {
        cout<<"A face have at least 3 vertices"<<endl;
        return;
    }
    Face * newFace = new Face;
    vector<Vertex*>::iterator vIt;
    vector<Edge*> edgesInFace;
    vector<Edge*>::iterator eIt;
    Edge * currEdge;
    if(!reverseOrder) {
        for(vIt = vertices.begin(); vIt < vertices.end(); vIt ++) {
            if(vIt != vertices.end() - 1) {
                currEdge = createEdge(*vIt, *(vIt + 1));
                edgesInFace.push_back(currEdge);
            } else {
                currEdge = createEdge(*vIt, *(vertices.begin()));
                edgesInFace.push_back(currEdge);
            }
            if(currEdge -> fa == NULL) {
                currEdge -> fa = newFace;
            } else if(currEdge -> fb == NULL) {
                currEdge -> fb = newFace;
            } else {
                cout<<"ERROR: Try to create a Non-Manifold at edge with vertex1 : "
                <<currEdge -> va -> ID<<" and vertex2 :"<<currEdge -> vb -> ID<<endl;
                exit(0);
            }
        }
    } else {
        for(vIt = vertices.end() - 1; vIt >= vertices.begin(); vIt --) {
            if(vIt != vertices.begin()) {
                currEdge = createEdge(*vIt, *(vIt - 1));
                edgesInFace.push_back(currEdge);
            } else {
                currEdge = createEdge(*vIt, *(vertices.end() - 1));
                edgesInFace.push_back(currEdge);
            }
            if(currEdge -> fa == NULL) {
                currEdge -> fa = newFace;
            } else if(currEdge -> fb == NULL) {
                currEdge -> fb = newFace;
            } else {
                cout<<"ERROR: Try to create a Non-Manifold at edge with vertex1 : "
                <<currEdge -> va -> ID<<" and vertex2 :"<<currEdge -> vb -> ID<<endl;
                exit(0);
            }
        }
    }
    newFace -> oneEdge = currEdge;
    for(eIt = edgesInFace.begin(); eIt < edgesInFace.end(); eIt ++) {
        Edge * currEdge = (*eIt);
        if(eIt == edgesInFace.begin()) {
            if(newFace == currEdge -> fa) {
                currEdge -> nextVbFa = *(eIt + 1);
                currEdge -> nextVaFa = *(edgesInFace.end() - 1);
            } else {
                if(currEdge -> mobius) {
                    currEdge -> nextVbFb = *(eIt + 1);
                    currEdge -> nextVaFb = *(edgesInFace.end() - 1);
                } else {
                    currEdge -> nextVaFb = *(eIt + 1);
                    currEdge -> nextVbFb = *(edgesInFace.end() - 1);
                }
            }
        } else if(eIt == (edgesInFace.end() - 1)) {
            if(newFace == currEdge -> fa) {
                currEdge -> nextVbFa = *(edgesInFace.begin());
                currEdge -> nextVaFa = *(eIt - 1);
            } else {
                if(currEdge -> mobius) {
                    currEdge -> nextVbFb = *(edgesInFace.begin());
                    currEdge -> nextVaFb = *(eIt - 1);
                } else {
                    currEdge -> nextVaFb = *(edgesInFace.begin());
                    currEdge -> nextVbFb = *(eIt - 1);
                }
            }
        } else {
            if(newFace == currEdge -> fa) {
                currEdge -> nextVbFa = *(eIt + 1);
                currEdge -> nextVaFa = *(eIt - 1);
            } else {
                if(currEdge -> mobius) {
                    currEdge -> nextVbFb = *(eIt + 1);
                    currEdge -> nextVaFb = *(eIt - 1);
                } else {
                    currEdge -> nextVaFb = *(eIt + 1);
                    currEdge -> nextVbFb = *(eIt - 1);
                }
            }
        }
    }
    newFace -> id = faceList.size();
    faceList.push_back(newFace);
}

// Build the next pointers for boundary edges in the mesh.
// @param mesh: refer to the mesh to build connection in.
// This one takes O(E) time.
void Mesh::buildBoundary() {
    unordered_map<Vertex*, vector<Edge*> >::iterator evIt;
    vector<Edge*> edgesAtThisPoint;
    vector<Edge*>::iterator eIt;
    for(evIt = edgeTable.begin(); evIt != edgeTable.end(); evIt++) {
        edgesAtThisPoint = evIt -> second;
        if(!edgesAtThisPoint.empty()) {
            for(eIt = edgesAtThisPoint.begin(); eIt < edgesAtThisPoint.end(); eIt++) {
                Edge * currEdge = (*eIt);
                if((currEdge -> nextEdge(currEdge -> va, currEdge -> fb)) == NULL) {
                    Edge * firstBoundaryEdge = currEdge;
                    Vertex * currVert = currEdge -> va;
                    Edge * nextBoundaryEdge;
                    //cout<<"first: "<<currEdge -> va -> ID<<" "<<currEdge -> vb -> ID<<endl;
                    do {
                        currEdge -> isSharp = true;
                        //cout<<"Now building boundary at vertex: "<<endl;
                        //cout<<currVert -> ID<<endl;
                        Face * currFace = currEdge -> fa;
                        nextBoundaryEdge = currEdge -> nextEdge(currVert, currFace);
                        while(nextBoundaryEdge -> fb != NULL) {
                            currFace = nextBoundaryEdge -> theOtherFace(currFace);
                            nextBoundaryEdge = nextBoundaryEdge -> nextEdge(currVert, currFace);
                        }
                        currEdge -> setNextEdge(currVert, NULL, nextBoundaryEdge);
                        nextBoundaryEdge -> setNextEdge(currVert, NULL, currEdge);
                        currEdge = nextBoundaryEdge;
                        currVert = currEdge -> theOtherVertex(currVert);
                    } while (currEdge != firstBoundaryEdge);
                }
            }
        }
    }
}

// @param p1, p2, p3 are positions of three vertices,
// with edge p1 -> p2 and edge p2 -> p3.
vec3 getNormal3Vertex(vec3 p1, vec3 p2, vec3 p3){
    return cross(p2 - p1, p3 - p2);
}

// Get the surface normal.
// @param currFace: pointer of the face.
void getFaceNormal(Face * currFace){
    //cout<<"New Face!"<<endl;
    Edge * firstEdge = currFace -> oneEdge;
    Edge * currEdge;
    Edge * nextEdge;
    currEdge = firstEdge;
    vec3 avgNorm = vec3(0, 0, 0);
    vec3 p1;
    vec3 p2;
    vec3 p3;
    do {
        //cout<<"New Edge!"<<endl;
        //cout<<"ID: "<<currEdge -> va -> ID<<endl;
        //cout<<"ID: "<<currEdge -> vb -> ID<<endl;
        if(currFace == currEdge -> fa) {
            nextEdge = currEdge -> nextVbFa;
            p1 = currEdge -> va -> position;
            p2 = currEdge -> vb -> position;
            p3 = nextEdge -> theOtherVertex(currEdge -> vb) -> position;
        } else if(currFace == currEdge -> fb) {
            if(currEdge -> mobius) {
                nextEdge = currEdge -> nextVbFb;
                p1 = currEdge -> va -> position;
                p2 = currEdge -> vb -> position;
                p3 = nextEdge -> theOtherVertex(currEdge -> vb) -> position;
            } else {
                nextEdge = currEdge -> nextVaFb;
                p1 = currEdge -> vb -> position;
                p2 = currEdge -> va -> position;
                p3 = nextEdge -> theOtherVertex(currEdge -> va) -> position;
            }
        }
        avgNorm += getNormal3Vertex(p1, p2, p3);
        currEdge = nextEdge;
    } while (currEdge != firstEdge);
    //cout<<"The new Face normal is: "<<result[0]<<" "<<result[1]<<" "<<result[2]<<endl;
    currFace -> normal = normalize(avgNorm);
}

// Get the vertex normal
// @param currVert: the target vertex.
void getVertexNormal(Vertex * currVert){
    Edge * firstEdge = currVert -> oneEdge;
    if(firstEdge == NULL) {
        cout<<"Lonely vertex without any adjacent edges"<<endl;
        return;
    }
    Edge * currEdge = firstEdge;
    Face * currFace = currEdge -> fa;
    vec3 avgNorm(0, 0, 0);
    int mobiusCounter = 0;
    do {
        if(mobiusCounter % 2 == 0) {
            avgNorm += currFace -> normal;
        } else {
            avgNorm -= currFace -> normal;
        }
        if(currEdge -> mobius) {
            mobiusCounter += 1;
        }
        currFace = currEdge -> theOtherFace(currFace);
        if(currFace == NULL) { //If the face is NULL, need to skip this face
            Edge * nextEdge = currEdge -> nextEdge(currVert, currFace);
            if(nextEdge -> va == currEdge -> va || nextEdge -> vb == currEdge -> vb) {
                mobiusCounter += 1;
            }
            currEdge = nextEdge;
            currFace = currEdge -> theOtherFace(currFace);
        }
        currEdge = currEdge -> nextEdge(currVert, currFace);
    } while ( currEdge != firstEdge);
    //if(currVert -> onMobius) {
    //cout<<"The value of avgNorm is :"<<avgNorm[0]<<" "<<avgNorm[1]<<" "<<avgNorm[2]<<endl;
    //cout<<"The position of this vertex is :"<<currVert -> position[0]<<" "<<currVert -> position[1]<<" "<<currVert -> position[2]<<endl;
    //}//cout<<"ID: "<<currVert -> ID <<" has "<<mobiusCounter<<" mConter"<<endl;
    currVert -> normal = normalize(avgNorm);
}

// Iterate over every vertex in the mesh and compute its normal
void Mesh::computeNormals(){
    vector<Vertex*>::iterator vIt;
    vector<Face*>::iterator fIt;
    //cout<<"faceTable size: "<<faceList.size()<<endl;
    for(fIt = faceList.begin(); fIt < faceList.end(); fIt++) {
        getFaceNormal(*fIt);
    }

    //cout<<"vertTable size: "<<vertList.size()<<endl;
    for(vIt = vertList.begin(); vIt != vertList.end(); vIt++) {
        //cout<<"Now calculating vertex with ID: "<< vIt -> first <<endl;
        getVertexNormal(*vIt);
    }

}

inline void drawIndependentVertex(float x, float y, float z){
    float sz = 0.1;
    glVertex3f(x, y, z);
}

void Mesh::drawMesh(int startIndex, bool smoothShading)
{
    /* The overall mesh color.*/
    GLfloat fcolor[] = {1.0f * color.red() / 255,
                        1.0f * color.green() / 255,
                        1.0f * color.blue() / 255,
                        1.0f * color.alpha() /255};
    /* The color for the selected face */
    GLfloat fscolor[] = {1.0f - 1.0f * color.red() / 255,
                         1.0f - 1.0f * color.green() / 255,
                         1.0f - 1.0f * color.blue() / 255,
                         1.0f - 1.0f * color.alpha() /255};
    /* The color for individual vertex */
    GLfloat vcolor[] = {0 / 255,
                         1.0f * color.green() / 255,
                         0 / 255,
                         1.0f - 1.0f * color.alpha() /255};
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, fcolor);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, fcolor);
    Face * tempFace;
    vector<Face*>::iterator fIt;
    unordered_set<Vertex*> visited;
    for(fIt = faceList.begin(); fIt < faceList.end(); fIt++)
    {
        tempFace = (*fIt);
        if(tempFace -> user_defined_color)
        {
            QColor user_color = tempFace -> color;
            if(tempFace -> selected)
            {

                /* The reverse of user defined face color, ussed for selection. */
                GLfloat uscolor[] = {1.0f - 1.0f * user_color.red() / 255,
                                     1.0f - 1.0f * user_color.green() / 255,
                                     1.0f - 1.0f * user_color.blue() / 255,
                                     1.0f - 1.0f * user_color.alpha() /255};
                glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, uscolor);
                glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, uscolor);
            }
            else
            {
                /* The user defined face color.*/
                GLfloat ucolor[] = {1.0f * user_color.red() / 255,
                                    1.0f * user_color.green() / 255,
                                    1.0f * user_color.blue() / 255,
                                    1.0f * user_color.alpha() /255};
                glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, ucolor);
                glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ucolor);
            }
        } else {
            if(tempFace -> selected)
            {
                glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, fscolor);
                glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, fscolor);
            }
        }
        vec3 fNormal = tempFace -> normal;
        Vertex * tempv;
        Edge * firstEdge = (*fIt) -> oneEdge;
        //cout<<"New Face: "<<endl;
        glLoadName(tempFace -> id + startIndex);
        glBegin(GL_POLYGON);
        Edge * currEdge = firstEdge;
        Edge * nextEdge;
        //tempv = currEdge -> va;
        //cout<<"Hmm?"<<endl;
        //cout<<"Hello! I am on the "<<fIt - faceList.begin()<<" face."<<endl;
        if(!smoothShading)
        {
            glNormal3f(fNormal[0], fNormal[1], fNormal[2]);
        }
        do
        {
            if(tempFace == currEdge -> fa)
            {
                tempv = currEdge -> vb;
                nextEdge = currEdge -> nextVbFa;
            }
            else
            {
                if(currEdge -> mobius)
                {
                    tempv = currEdge -> vb;
                    nextEdge = currEdge -> nextVbFb;
                }
                else
                {
                    tempv = currEdge -> va;
                    nextEdge = currEdge -> nextVaFb;
                }
            }
            if(smoothShading) {
                float normx;
                float normy;
                float normz;
                if(tempv -> onMobius)
                {
                    vec3 vNormal = tempv -> normal;
                    if(dot(vNormal, fNormal) >= 0)
                    {
                        normx = tempv -> normal[0];
                        normy = tempv -> normal[1];
                        normz = tempv -> normal[2];
                    }
                    else
                    {
                        normx = - tempv -> normal[0];
                        normy = - tempv -> normal[1];
                        normz = - tempv -> normal[2];
                    }
                }
                else
                {
                    normx = tempv -> normal[0];
                    normy = tempv -> normal[1];
                    normz = tempv -> normal[2];
                }
                glNormal3f(normx, normy, normz);
            }
            //cout<<"normx: "<<normx<<" normy: "<<normy<<" normz: "<<normz<<endl;
            float x = tempv -> position[0];
            float y = tempv -> position[1];
            float z = tempv -> position[2];
            //cout<<"x: "<<x<<" y: "<<y<<" z: "<<z<<endl;
            visited.insert(tempv);
            glVertex3f(x, y, z);
            currEdge = nextEdge;
            //cout<<"Current Vertex ID: "<<tempv -> ID<<endl;
        } while(currEdge != firstEdge);
        glEnd();
        if(tempFace -> selected || tempFace -> user_defined_color)
        {
            glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, fcolor);
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, fcolor);
        }
    }

    for(Vertex* v: this->vertList){
        if (visited.find(v) == visited.end()){
            glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, vcolor);
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, vcolor);
            glBegin(GL_POINTS);
            glNormal3f(v->position[0] * 100, v->position[1] * 100, v->position[2] * 100);
            drawIndependentVertex(v->position[0], v->position[1], v->position[2]);
            glEnd();
        }
    }
}

vector<Edge*> Mesh::boundaryEdgeList() {
    vector<Edge*> boundaryEdgeList;
    unordered_map<Vertex*, vector<Edge*> >::iterator vIt;
    //cout<<"Edge table size: "<<edgeTable.size()<<endl;
    for(vIt = edgeTable.begin(); vIt != edgeTable.end(); vIt++) {
        //cout<<vIt -> first -> ID<<endl;
        vector<Edge*> edges = vIt -> second;
        vector<Edge*>::iterator eIt;
        vector<Edge*> newEdges;
        for(eIt = edges.begin(); eIt < edges.end(); eIt ++) {
            if((*eIt) -> fb == NULL) {
                boundaryEdgeList.push_back(*eIt);
            }
        }
    }
    //cout<<"size: " << boundaryEdgeList.size()<<endl;
    return boundaryEdgeList;
}

void Mesh::drawVertices()
{
    vector<Vertex*>::iterator vIt;
    glPointSize(10);
    for(vIt = vertList.begin(); vIt < vertList.end(); vIt++) {
        if((*vIt) -> selected) {
            glBegin(GL_POINTS);
            vec3 position = (*vIt) -> position;
            glNormal3f(position[0] * 100, position[1] * 100, position[2] * 100);
            glVertex3f(position[0], position[1], position[2]);
            glEnd();
        }
    }
}

bool Mesh::isEmpty() {
    return vertList.size() == 0 && faceList.size() == 0;
}

void Mesh::clear()
{
    //for(Vertex*& v : vertList)
    //{
    //    delete v;
    //}
    //for(Face*& f : faceList)
    //{
    //    delete f;
    //}
    vertList.clear();
    faceList.clear();
    edgeTable.clear();
}

void Mesh::clearAndDelete()
{
    for(Vertex*& v : vertList)
    {
        delete v;
    }
    for(Face*& f : faceList)
    {
        delete f;
    }
    vertList.clear();
    faceList.clear();
    edgeTable.clear();
}

void Mesh::setColor(QColor color)
{
    this -> color = color;
}

void Mesh::setGlobalParameter(unordered_map<string, Parameter> *params)
{
    this -> params = params;
}

void Mesh::addTransformation(Transformation new_transform)
{
    transformations_up.push_back(new_transform);
}

void Mesh::setTransformation(vector<Transformation> new_transforms)
{
    transformations_up = new_transforms;
}

Mesh Mesh::makeCopy(string copy_mesh_name) {
    //cout<<"Creating a copy of the current map.\n";
    Mesh newMesh;
    if(copy_mesh_name == "")
    {
        newMesh.name = this->name;
    }
    else
    {
        newMesh.name = copy_mesh_name;
    }
    newMesh.clear();
    vector<Vertex*>::iterator vIt;
    for(vIt = vertList.begin();
        vIt < vertList.end(); vIt ++) {
        Vertex * vertCopy = new Vertex;
        vertCopy -> ID = (*vIt) -> ID;
        vertCopy -> name = (*vIt) -> name;
        vertCopy -> position = (*vIt) -> position;
        vertCopy -> isParametric = (*vIt) -> isParametric;
        if((*vIt) -> isParametric)
        {
            vertCopy -> x_expr = (*vIt) -> x_expr;
            vertCopy -> y_expr = (*vIt) -> y_expr;
            vertCopy -> z_expr = (*vIt) -> z_expr;
            vertCopy -> params = (*vIt) -> params;
            vertCopy -> influencingParams = (*vIt) -> influencingParams;
        }
        newMesh.addVertex(vertCopy);
    }
    vector<Face*>::iterator fIt;
    vector<Vertex*> vertices;
    for(fIt = faceList.begin();
     fIt < faceList.end(); fIt ++) {
        Face * tempFace = *fIt;
        Edge * firstEdge = tempFace -> oneEdge;
        Edge * currEdge = firstEdge;
        Edge * nextEdge;
        Vertex * tempv;
        vertices.clear();
        do {
            if(tempFace == currEdge -> fa) {
                tempv = currEdge -> vb;
                nextEdge = currEdge -> nextVbFa;
            } else {
                if(currEdge -> mobius) {
                    tempv = currEdge -> vb;
                    nextEdge = currEdge -> nextVbFb;
                } else {
                    tempv = currEdge -> va;
                    nextEdge = currEdge -> nextVaFb;
                }
            }
            vertices.push_back(newMesh.vertList[tempv -> ID]);
            currEdge = nextEdge;
        } while (currEdge != firstEdge);
        newMesh.addPolygonFace(vertices);
        newMesh.faceList[newMesh.faceList.size() - 1] -> user_defined_color
                = (*fIt) -> user_defined_color;
        newMesh.faceList[newMesh.faceList.size() - 1] -> color
                = (*fIt) -> color;
        newMesh.faceList[newMesh.faceList.size() - 1] -> name
                = (*fIt) -> name;
    }
    newMesh.buildBoundary();
    newMesh.computeNormals();
    newMesh.color = color;
    newMesh.params = params;
    newMesh.type = type;
    if(type == 1)
    {
        newMesh.n = n;
        newMesh.ro = ro;
        newMesh.ratio = ratio;
        newMesh.h = h;
        newMesh.n_expr = n_expr;
        newMesh.ro_expr = ro_expr;
        newMesh.ratio_expr = ratio_expr;
        newMesh.h_expr = h_expr;
        newMesh.influencingParams = influencingParams;
    }
    else if(type == 2)
    {
        newMesh.n = n;
        newMesh.ro = ro;
        newMesh.ratio = ratio;
        newMesh.h = h;
        newMesh.n_expr = n_expr;
        newMesh.ro_expr = ro_expr;
        newMesh.ratio_expr = ratio_expr;
        newMesh.h_expr = h_expr;
        newMesh.influencingParams = influencingParams;
    }
    return newMesh;
}

Mesh Mesh::makeCopyForTempMesh(string copy_mesh_name) {
    Mesh newMesh;
    if(copy_mesh_name == "")
    {
        newMesh.name = this->name;
    }
    else
    {
        newMesh.name = copy_mesh_name;
    }
    newMesh.clear();
    unordered_map<Vertex*, Vertex*> original_to_copy;
    unordered_map<Vertex*, Vertex*>::iterator o2cIt;
    vector<Face*>::iterator fIt;
    vector<Vertex*> vertices;
    for(fIt = faceList.begin();
     fIt < faceList.end(); fIt ++)
    {
        Face * tempFace = *fIt;
        Edge * firstEdge = tempFace -> oneEdge;
        Edge * currEdge = firstEdge;
        Edge * nextEdge;
        Vertex * tempv;
        vertices.clear();
        do
        {
            if(tempFace == currEdge -> fa)
            {
                tempv = currEdge -> vb;
                nextEdge = currEdge -> nextVbFa;
            }
            else
            {
                if(currEdge -> mobius)
                {
                    tempv = currEdge -> vb;
                    nextEdge = currEdge -> nextVbFb;
                }
                else
                {
                    tempv = currEdge -> va;
                    nextEdge = currEdge -> nextVaFb;
                }
            }
            o2cIt = original_to_copy.find(tempv);
            if(o2cIt == original_to_copy.end())
            {
                Vertex * vertCopy = new Vertex;
                vertCopy -> ID = tempv -> ID;
                vertCopy -> name = tempv  -> name;
                vertCopy -> position = tempv -> position;
                vertCopy -> source_vertex = tempv -> source_vertex;
                newMesh.addVertex(vertCopy);
                original_to_copy[tempv] = vertCopy;
                vertices.push_back(vertCopy);
            }
            else
            {
                vertices.push_back(o2cIt -> second);
            }
            currEdge = nextEdge;
        } while (currEdge != firstEdge);
        newMesh.addPolygonFace(vertices);
        newMesh.faceList[newMesh.faceList.size() - 1] -> user_defined_color
                = (*fIt) -> user_defined_color;
        if((*fIt) -> user_defined_color)
        {
            newMesh.faceList[newMesh.faceList.size() - 1] -> color
                    = (*fIt) -> color;
        }
        newMesh.faceList[newMesh.faceList.size() - 1] -> name
                = (*fIt) -> name;
    }
    newMesh.buildBoundary();
    newMesh.computeNormals();
    newMesh.color = QColor(255, 69, 0);
    newMesh.params = params;
    newMesh.type = type;
    return newMesh;
}

Mesh Mesh::makeCopyForTransform() {
    //cout<<"Creating a copy of the current map.\n";
    Mesh newMesh;
    newMesh.before_transform_mesh = this;
    newMesh.clear();
    newMesh.name = this -> name;
    vector<Vertex*>::iterator vIt;
    for(vIt = vertList.begin();
        vIt < vertList.end(); vIt ++) {
        Vertex * vertCopy = new Vertex;
        vertCopy -> ID = (*vIt) -> ID;
        vertCopy -> name = (*vIt) -> name;
        vertCopy -> position = (*vIt) -> position;
        vertCopy -> before_transform_vertex = (*vIt);
        newMesh.addVertex(vertCopy);
    }
    vector<Face*>::iterator fIt;
    vector<Vertex*> vertices;
    for(fIt = faceList.begin();
     fIt < faceList.end(); fIt ++) {
        Face * tempFace = *fIt;
        Edge * firstEdge = tempFace -> oneEdge;
        Edge * currEdge = firstEdge;
        Edge * nextEdge;
        Vertex * tempv;
        vertices.clear();
        do {
            if(tempFace == currEdge -> fa) {
                tempv = currEdge -> vb;
                nextEdge = currEdge -> nextVbFa;
            } else {
                if(currEdge -> mobius) {
                    tempv = currEdge -> vb;
                    nextEdge = currEdge -> nextVbFb;
                } else {
                    tempv = currEdge -> va;
                    nextEdge = currEdge -> nextVaFb;
                }
            }
            vertices.push_back(newMesh.vertList[tempv -> ID]);
            currEdge = nextEdge;
        } while (currEdge != firstEdge);
        newMesh.addPolygonFace(vertices);
        newMesh.faceList[newMesh.faceList.size() - 1] -> user_defined_color
                = (*fIt) -> user_defined_color;
        newMesh.faceList[newMesh.faceList.size() - 1] -> color
                = (*fIt) -> color;
        newMesh.faceList[newMesh.faceList.size() - 1] -> name
                = (*fIt) -> name;
    }
    newMesh.buildBoundary();
    newMesh.computeNormals();
    newMesh.color = color;
    newMesh.params = params;
    newMesh.type = type;
    if(type == 1)
    {
        newMesh.n = n;
        newMesh.ro = ro;
        newMesh.ratio = ratio;
        newMesh.h = h;
        newMesh.n_expr = n_expr;
        newMesh.ro_expr = ro_expr;
        newMesh.ratio_expr = ratio_expr;
        newMesh.h_expr = h_expr;
        newMesh.influencingParams = influencingParams;
    }
    else if(type == 2)
    {
        newMesh.n = n;
        newMesh.ro = ro;
        newMesh.ratio = ratio;
        newMesh.h = h;
        newMesh.n_expr = n_expr;
        newMesh.ro_expr = ro_expr;
        newMesh.ratio_expr = ratio_expr;
        newMesh.h_expr = h_expr;
        newMesh.influencingParams = influencingParams;
    }
    return newMesh;
}

void Mesh::updateCopyForTransform()
{
    transformations_up = before_transform_mesh -> transformations_up;
    for(Vertex*& v: vertList)
    {
        v -> position = v -> before_transform_vertex -> position;
    }
}

void Mesh::transform(Transformation* t)
{
    mat4 matrix = t -> getMatrix();
    vector<Vertex*>::iterator vIt;
    for(vIt = vertList.begin(); vIt < vertList.end(); vIt++)
    {
        (*vIt) -> position = vec3(matrix * vec4((*vIt) -> position, 1));
    }
}

void Mesh::transform(mat4 matrix)
{
    vector<Vertex*>::iterator vIt;
    for(vIt = vertList.begin(); vIt < vertList.end(); vIt++)
    {
        (*vIt) -> position = vec3(matrix * vec4((*vIt) -> position, 1));
    }
}

mat4 Mesh::transformToTop()
{
    mat4 result = mat4(1);
    for(Transformation& t: transformations_up)
    {
        result = t.getMatrix() * result;
    }
    Group *p = this -> parent;
    while(p != NULL)
    {
        for(Transformation& t : p -> transformations_up)
        {
            result = t.getMatrix() * result;
        }
        p = p -> parent;
    }
    return result;
}

void Mesh::setFunnelParameterValues(string input)
{
    string nextExpression = "";
    bool expressionMode = false;
    string number = "";
    int i = 0;
    for(char& c : input)
    {
        if(c == '{')
        {
            expressionMode = true;
        }
        else if(c == '}')
        {
            expressionMode = false;
            switch(i)
            {
            case 0:
                n_expr = nextExpression.substr(5);
                n = int(evaluate_mesh_expression(n_expr, params, this) + 0.5);
                break;
            case 1:
                ro_expr = nextExpression.substr(5);
                ro = evaluate_mesh_expression(ro_expr, params, this);
                break;
            case 2:
                ratio_expr = nextExpression.substr(5);
                ratio = evaluate_mesh_expression(ratio_expr, params, this);
                break;
            case 3:
                h_expr = nextExpression.substr(5);
                h = evaluate_mesh_expression(h_expr, params, this);
                break;
            }
            nextExpression = "";
            i++;
        }
        else if(expressionMode)
        {
            nextExpression.push_back(c);
        }
        else if(!expressionMode && ((c >= '0' &&  c <= '9') || c == '.' || c == '-' || c == '+'))
        {
            number.push_back(c);
        }
        else
        {
            if(number != "")
            {
                switch(i)
                {
                case 0:
                    n = stoi(number);
                    break;
                case 1:
                    ro = stof(number);
                    break;
                case 2:
                    ratio = stof(number);
                    break;
                case 3:
                    h = stof(number);
                    break;
                }
                number = "";
                i++;
            }
        }
    }
    if(number != "")
    {
        switch(i)
        {
        case 0:
            n = stoi(number);
            break;
        case 1:
            ro = stof(number);
            break;
        case 2:
            ratio = stof(number);
            break;
        case 3:
            h = stof(number);
            break;
        }
    }
}

void Mesh::setTunnelParameterValues(string input)
{
    string nextExpression = "";
    bool expressionMode = false;
    string number = "";
    int i = 0;
    for(char& c : input)
    {
        if(c == '{')
        {
            expressionMode = true;
        }
        else if(c == '}')
        {
            expressionMode = false;
            switch(i)
            {
            case 0:
                n_expr = nextExpression.substr(5);
                n = int(evaluate_mesh_expression(n_expr, params, this) + 0.5);
                break;
            case 1:
                ro_expr = nextExpression.substr(5);
                ro = evaluate_mesh_expression(ro_expr, params, this);
                break;
            case 2:
                ratio_expr = nextExpression.substr(5);
                ratio = evaluate_mesh_expression(ratio_expr, params, this);
                break;
            case 3:
                h_expr = nextExpression.substr(5);
                h = evaluate_mesh_expression(h_expr, params, this);
                break;
            }
            nextExpression = "";
            i++;
        }
        else if(expressionMode)
        {
            nextExpression.push_back(c);
        }
        else if(!expressionMode && ((c >= '0' &&  c <= '9') || c == '.' || c == '-' || c == '+'))
        {
            number.push_back(c);
        }
        else
        {
            if(number != "")
            {
                switch(i)
                {
                case 0:
                    n = stoi(number);
                    break;
                case 1:
                    ro = stof(number);
                    break;
                case 2:
                    ratio = stof(number);
                    break;
                case 3:
                    h = stof(number);
                    break;
                }
                number = "";
                i++;
            }
        }
    }
    if(number != "")
    {
        switch(i)
        {
        case 0:
            n = stoi(number);
            break;
        case 1:
            ro = stof(number);
            break;
        case 2:
            ratio = stof(number);
            break;
        case 3:
            h = stof(number);
            break;
        }
    }
}

void Mesh::updateFunnel()
{
    if(n_expr != "")
    {
        int new_n = evaluate_expression(n_expr, params);
        if(new_n != n)
        {
            if(in_editing_mode)
            {
                return;
            }
            n = new_n;
            updateFunnel_n();
        }
    }
    if(ro_expr != "")
    {
        float new_ro = evaluate_expression(ro_expr, params);
        if(new_ro != ro)
        {
            ro = new_ro;
            updateFunnel_ro_ratio_or_h();
        }
    }
    if(ratio_expr != "")
    {
        float new_ratio = evaluate_expression(ratio_expr, params);
        if(new_ratio != ratio)
        {
            ratio = new_ratio;
            updateFunnel_ro_ratio_or_h();
        }
    }
    if(h_expr != "")
    {
        float new_h = evaluate_expression(h_expr, params);
        if(new_h != h)
        {
            h = new_h;
            updateFunnel_ro_ratio_or_h();
        }
    }
}

void Mesh::updateTunnel()
{
    if(n_expr != "")
    {
        int new_n = evaluate_expression(n_expr, params);
        if(new_n != n)
        {
            if(in_editing_mode)
            {
                return;
            }
            n = new_n;
            updateTunnel_n();
        }
    }
    if(ro_expr != "")
    {
        float new_ro = evaluate_expression(ro_expr, params);
        if(new_ro != ro)
        {
            ro = new_ro;
            updateTunnel_ro_ratio_or_h();
        }
    }
    if(ratio_expr != "")
    {
        float new_ratio = evaluate_expression(ratio_expr, params);
        if(new_ratio != ratio)
        {
            ratio = new_ratio;
            updateTunnel_ro_ratio_or_h();
        }
    }
    if(h_expr != "")
    {
        float new_h = evaluate_expression(h_expr, params);
        if(new_h != h)
        {
            h = new_h;
            updateTunnel_ro_ratio_or_h();
        }
    }
}

void Mesh::updateFunnel_n()
{
    makeFunnel();
    computeNormals();
    //transform(transformToTop());
}

void Mesh::updateFunnel_ro_ratio_or_h()
{
    for(int i = 0; i < n; i++)
    {
        Vertex * newVertex = vertList[i];
        float currAngle = 2.0 * i / n * PI;
        newVertex -> position = vec3(ro * glm::cos(currAngle), ro * glm::sin(currAngle), 0);
    }
    float ri = ro * (1 + ratio);
    for(int i = 0; i < n; i++)
    {
        Vertex * newVertex = vertList[i + n];
        float currAngle = 2.0 * i / n * PI;
        newVertex -> position = vec3(ri * glm::cos(currAngle), ri * glm::sin(currAngle), h);
    }
    computeNormals();
    //transform(transformToTop());
}

void Mesh::makeFunnel()
{
    if(n < 3) {
        return;
    }
    vertList.clear();
    edgeTable.clear();
    faceList.clear();
    vector<Vertex*> baseCircle;
    vector<Vertex*> highCircle;
    for(int i = 0; i < n; i++)
    {
        Vertex * newVertex = new Vertex;
        newVertex->ID = i;
        newVertex->name = "bc" + to_string(i);
        float currAngle = 2.0 * i / n * PI;
        newVertex -> position = vec3(ro * glm::cos(currAngle),
                                     ro * glm::sin(currAngle), 0);
        baseCircle.push_back(newVertex);
        addVertex(newVertex);
    }
    float ri = ro * (1 + ratio);
    for(int i = 0; i < n; i++)
    {
        Vertex * newVertex = new Vertex;
        newVertex->ID = i + n;
        newVertex->name = "hc"+ to_string(i);
        float currAngle = 2.0 * i / n * PI;
        newVertex -> position = vec3(ri * glm::cos(currAngle),
                                     ri * glm::sin(currAngle), h);
        highCircle.push_back(newVertex);
        addVertex(newVertex);
    }
    for(int i = 0; i < n - 1 ; i++)
    {
        addQuadFace(baseCircle[i], baseCircle[i + 1], highCircle[i + 1], highCircle[i]);
    }
    addQuadFace(baseCircle[n - 1], baseCircle[0], highCircle[0], highCircle[n - 1]);
    buildBoundary();
}

void Mesh::makeTunnel()
{
    if(n < 3) {
        return;
    }
    vertList.clear();
    edgeTable.clear();
    faceList.clear();
    vector<Vertex*> baseCircle;
    vector<Vertex*> highCircle;
    vector<Vertex*> lowCircle;
    for(int i = 0; i < n; i++)
    {
        Vertex * newVertex = new Vertex;
        newVertex->ID = i;
        newVertex->name = "bc" + to_string(i);
        float currAngle = 2.0 * i / n * PI;
        newVertex -> position = vec3(ro * glm::cos(currAngle),
                                     ro * glm::sin(currAngle), 0);
        baseCircle.push_back(newVertex);
        addVertex(newVertex);
    }
    float ri = ro * (1 + ratio);
    for(int i = 0; i < n; i++)
    {
        Vertex * newVertex = new Vertex;
        newVertex->ID = i + n;
        newVertex->name = "hc" + to_string(i);
        float currAngle = 2.0 * i / n * PI;
        newVertex -> position = vec3(ri * glm::cos(currAngle),
                                     ri * glm::sin(currAngle), h);
        highCircle.push_back(newVertex);
        addVertex(newVertex);
    }
    for(int i = 0; i < n; i++)
    {
        Vertex * newVertex = new Vertex;
        newVertex->ID = i + 2 * n;
        newVertex->name = "lc" + to_string(i);
        float currAngle = 2.0 * i / n * PI;
        newVertex -> position = vec3(ri * glm::cos(currAngle),
                                     ri * glm::sin(currAngle), -h);
        lowCircle.push_back(newVertex);
        addVertex(newVertex);
    }
    for(int i = 0; i < n - 1 ; i++)
    {
        addQuadFace(baseCircle[i], baseCircle[i + 1], highCircle[i + 1], highCircle[i]);
        addQuadFace(lowCircle[i], lowCircle[i + 1], baseCircle[i + 1], baseCircle[i]);
    }
    addQuadFace(baseCircle[n - 1], baseCircle[0], highCircle[0], highCircle[n - 1]);
    addQuadFace(lowCircle[n - 1], lowCircle[0], baseCircle[0], baseCircle[n - 1]);
    buildBoundary();
}

void Mesh::updateTunnel_n()
{
    makeTunnel();
    computeNormals();
}

void Mesh::updateTunnel_ro_ratio_or_h()
{
    for(int i = 0; i < n; i++)
    {
        Vertex * newVertex = vertList[i];
        float currAngle = 2.0 * i / n * PI;
        newVertex -> position = vec3(ro * glm::cos(currAngle),
                                     ro * glm::sin(currAngle), 0);
    }
    float ri = ro * (1 + ratio);
    for(int i = 0; i < n; i++)
    {
        Vertex * newVertex = vertList[i + n];
        float currAngle = 2.0 * i / n * PI;
        newVertex -> position = vec3(ri * glm::cos(currAngle),
                                     ri * glm::sin(currAngle), h);
    }
    for(int i = 0; i < n; i++)
    {
        Vertex * newVertex = vertList[i + 2 * n];
        float currAngle = 2.0 * i / n * PI;
        newVertex -> position = vec3(ri * glm::cos(currAngle),
                                     ri * glm::sin(currAngle), -h);
    }
    computeNormals();
}

void Mesh::addParam(Parameter* param)
{
    influencingParams.push_back(param);
}

Vertex * Mesh::findVertexInThisMesh(string name)
{
    for(Vertex*& v: vertList)
    {
        if(v->name == name)
        {
            return v;
        }
    }
    return NULL;
}

bool Mesh::deleteFaceInThisMesh(string name)
{
    for(Face*& f: faceList)
    {
        cout<<f->name<<" ";
        if(f->name == name)
        {
            deleteFace(f);
            return true;
        }
    }
    return false;
}

void Mesh::deleteVertex(Vertex *v)
{
    bool foundThisVertex = false;
    int counter = 0;
    for(Vertex * nextVert : vertList)
    {
        if(foundThisVertex)
        {
            nextVert->ID -= 1;
        }
        else if(nextVert == v)
        {
            foundThisVertex = true;
        }
        else
        {
            counter++;
        }
    }
    if(foundThisVertex)
    {
        vertList.erase(vertList.begin()+counter);
    }
    delete v;
}

void Mesh::deleteFace(Face *face)
{
    bool foundThisFace = false;
    int counter = 0;
    for(Face * nextFace : faceList)
    {
        if(foundThisFace)
        {
            nextFace->id -= 1;
        } else if(nextFace == face)
        {
            foundThisFace = true;
        } else {
            counter++;
        }
    }
    if(foundThisFace)
    {
        faceList.erase(faceList.begin()+counter);
    }
    vector<Edge*> removeEdgeList;
    removeEdgeList.clear();
    Edge * firstEdge = face -> oneEdge;
    Edge * currEdge = firstEdge;
    Edge * nextEdge;
    do
    {
        if(face == currEdge -> fa)
        {
            nextEdge = currEdge -> nextVbFa;
            if(currEdge -> fb != NULL)
            {
                if(currEdge -> mobius)
                {
                    currEdge -> nextVaFa = currEdge -> nextVaFb;
                    currEdge -> nextVbFa = currEdge -> nextVbFb;
                    currEdge -> mobius = false;
                    //Maybe we need to remark the end vertex non-Mobius here.
                }
                else
                {
                    /*Switch the va and vb, also need to change in the edgetable. */
                    unordered_map<Vertex*, vector<Edge*> >::iterator vIt;
                    vector<Edge*>::iterator eIt;
                    vIt = edgeTable.find(currEdge -> va);
                    if(vIt != edgeTable.end())
                    {
                        for(eIt = (vIt -> second).begin(); eIt < (vIt -> second).end(); eIt++)
                        {
                            if((*eIt) == currEdge)
                            {
                                (vIt -> second).erase(eIt);
                                break;
                            }
                        }
                    }
                    else
                    {
                        cout<<"Error, there is a bug in the program!"<<endl;
                    }
                    vIt = edgeTable.find(currEdge -> vb);
                    if(vIt != edgeTable.end())
                    {
                        (vIt -> second).push_back(currEdge);
                    }
                    else
                    {
                        vector<Edge*> edges;
                        edges.push_back(currEdge);
                        edgeTable[currEdge -> vb] = edges;
                    }
                    Vertex * temp = currEdge -> va;
                    currEdge -> va = currEdge -> vb;
                    currEdge -> vb = temp;
                    currEdge -> nextVaFa = currEdge -> nextVbFb;
                    currEdge -> nextVbFa = currEdge -> nextVaFb;
                }
                currEdge -> fa = currEdge -> fb;
                currEdge -> nextVaFb = NULL;
                currEdge -> nextVbFb = NULL;
                currEdge -> fb = NULL;
            }
            else
            {
                currEdge -> nextVaFa = NULL;
                currEdge -> nextVbFa = NULL;
                currEdge -> fa = NULL;
                removeEdgeList.push_back(currEdge);
            }
        }
        else
        {
            if(currEdge -> mobius)
            {
                nextEdge = currEdge -> nextVbFb;
                currEdge -> mobius = false;
            } else
            {
                nextEdge = currEdge -> nextVaFb;
            }
            currEdge -> nextVaFb = NULL;
            currEdge -> nextVbFb = NULL;
            currEdge -> fb = NULL;
        }
        currEdge = nextEdge;
    } while(currEdge != firstEdge);
    for(Edge * edge : removeEdgeList)
    {
        deleteEdge(edge);
    }
    delete face;
    return;
}

void Mesh::deleteEdge(Edge * edge)
{
    unordered_map<Vertex*, vector<Edge*> >::iterator vIt;
    vector<Edge*>::iterator eIt;
    vIt = edgeTable.find(edge -> va);
    bool foundEdge = false;
    if(vIt != edgeTable.end())
    {
        for(eIt = (vIt -> second).begin(); eIt < (vIt -> second).end(); eIt++)
        {
            if((*eIt) == edge)
            {
                foundEdge = true;
                (vIt -> second).erase(eIt);
                break;
            }
        }
    }
    if(!foundEdge)
    {
        cout<<"Error: You can't delete this edge. Check the program!"<<endl;
    }
    else
    {
        /* Also need to settle edgeTable here. We also need to set the oneEdge pointer
         * for the affected vertex when edge is deleted. */
        if(edge -> va -> oneEdge == edge)
        {
            foundEdge = false;
            if((vIt -> second).size() > 0)
            {
                edge -> va -> oneEdge = *((vIt -> second).begin());
                foundEdge = true;
            }
            else
            {
                for(vIt = edgeTable.begin(); vIt != edgeTable.end(); vIt++)
                {
                    for(eIt = (vIt -> second).begin(); eIt < (vIt -> second).end(); eIt++)
                    {
                        if((*eIt) -> vb == edge -> va)
                        {
                            edge -> va -> oneEdge = (*eIt);
                            foundEdge = true;
                            break;
                        }
                    }
                }
            }
            if(!foundEdge)
            {
                cout<<"Warning: Your deletion has deleted a vertex."<<endl;
                edge -> va -> oneEdge = NULL;
                deleteVertex(edge -> va);
            }
        }
        if(edge -> vb -> oneEdge == edge)
        {
            foundEdge = false;
            vIt = edgeTable.find(edge -> vb);
            if(vIt != edgeTable.end() && (vIt -> second).size() > 0)
            {
                edge -> vb -> oneEdge = *((vIt -> second).begin());
                foundEdge = true;
            }
            else
            {
                for(vIt = edgeTable.begin(); vIt != edgeTable.end(); vIt++)
                {
                    for(eIt = (vIt -> second).begin(); eIt < (vIt -> second).end(); eIt++)
                    {
                        if((*eIt) -> vb == edge -> vb)
                        {
                            edge -> vb -> oneEdge = (*eIt);
                            foundEdge = true;
                            break;
                        }
                    }
                }
            }
            if(!foundEdge)
            {
                cout<<"Warning: Your deletion has deleted a vertex."<<endl;
                edge -> vb -> oneEdge = NULL;
                deleteVertex(edge -> vb);
            }
        }
    }

    /* Also need to remove the key in edgeTable if it does not exist anymore. */
    delete(edge);
    return;
}

void Mesh::updateVertListAfterDeletion()
{
    vertList.clear();
    bool foundVa;
    bool foundVb;
    unordered_map<Vertex*, vector<Edge*> >::iterator vIt;
    for(vIt = edgeTable.begin(); vIt != edgeTable.end(); vIt++)
    {
        for(Edge * edge : (vIt -> second))
        {
            foundVa = false;
            foundVb = false;
            for(Vertex* v : vertList)
            {
                if(v == edge -> va)
                {
                    foundVa = true;
                }
                if(v == edge -> vb)
                {
                    foundVb = true;
                }
                if(foundVa && foundVb)
                {
                    break;
                }
            }
            if(!foundVa)
            {
                vertList.push_back(edge -> va);
            }
            if(!foundVb)
            {
                vertList.push_back(edge -> vb);
            }
        }
    }
    return;
}

void Mesh::setBoundaryEdgeToNull(Vertex* v) {
    /* Traverse around v and find boundary edges.
     * Set the nextFb pointers to NULL for those edges. */
    vector<Edge*> edgeAtThisPoint;
    unordered_map<Vertex*, vector<Edge*> >::iterator vIt;
    vIt = edgeTable.find(v);
    if(vIt != edgeTable.end()) {
        edgeAtThisPoint = vIt -> second;
        for(Edge* e : edgeAtThisPoint) {
            e -> isSharp = false;
            if((e -> fb) == NULL) {
                e->nextVaFb = NULL;
                e->nextVbFb = NULL;
            }
        }
    } else {
        cout<<"Error: The Vertex doesn't belongs to this Mesh. Debug here."<<endl;
    }
}
