//
//  Reader.h
//

#ifndef Reader_h
#define Reader_h

#include <stdio.h>
#include <iostream>
#include <vector>
#include "Data.h"
#include "MeshNew.h"
#include "Session.h"

/// Reader class for accessing data from hierarchical tree
/// Mode = 0 : Transformations off, Mode = 1 : Transformations on
/// (This just means search at the mesh/instance level respectively)

using namespace std;

typedef class Reader
{
private:
    int accesses;
    void access();
    
public:
    Session* session;
    Node* node;
    bool assigned;

    //Link to node functions
    bool link(Node*);
    bool link(std::string);

    //Search tree hierarchy
    bool search(std::string, int);

    //For the parser?
    MeshNew* mesh(std::string);

    //Get low lying data of node
    Surface* surf(std::string);
    Vert* vert(VertI);
    EdgeNew* edge(EdgeI);
    FaceNew* face(FaceI);
    Vert* vert(std::string);
    EdgeNew* edge(std::string);
    FaceNew* face(std::string);

    //Convenience functions
    MeshNew* getMesh(std::string);
    InstanceNew* getInstance(std::string);
    Vert* getVert(std::string);
    Vert* getVert(int);
    EdgeNew* getEdge(std::string);
    FaceNew* getFace(std::string);
    FaceNew* getFace(int);
    bool deleteFace(FaceNew *);
    std::string getVertName(int id);

} Reader;

///Instantiation
Reader* createReader(Session*);
Reader* createReader(Session*, Node*);
Reader* createReader(Reader);


#endif /* Reader_h */
