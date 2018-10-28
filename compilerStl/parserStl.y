%code requires{
#include <newNOME/Session.h>
}

%{
#include <cstdio>
#include <cstring>
#include <string>
#include <list>
#include <newNOME/Data.h>
#include <newNOME/MeshNew.h>
#include <newNOME/Session.h>
#include <newNOME/Reader.h>
#include <newNOME/TransformationNew.h>
#include <newNOME/PolylineNew.h>
#include <newNOME/CircleNew.h>
#include <newNOME/FunnelNew.h>
#include <newNOME/TunnelNew.h>
#include <newNOME/InstanceNew.h>
#include <newNOME/BankNew.h>
#include <newNOME/OffsetNew.h>

extern int stllineno;
extern char* stltext;

extern int stlcolumn;

int stllex(void);
void stlerror(Session* currSession, const char *s) {
  printf("%s on line %d - %s\n", s, stllineno, stltext);
}

int stlwrap() {
    return 1;
}

std::map<std::string,QColor> surfaces;
std::map<std::string,Vert*> vertices;
std::vector<std::string> tempVariables;
std::vector<std::string> tempFaceDelete;
std::string currentSetName;
std::list<SetNew *> currentSetList;
std::map<std::string,std::vector<double>> currentBank;
std::vector<std::string> currentInstanceList;
std::list<InstanceNew *> currentGroup;
std::list<FaceNew *> currentMeshFaces;
std::list<Vert *> currentMeshVertices;
std::list<EdgeNew *> currentMeshEdges;

std::list<Vert *> currentFaceVertices;
std::list<FaceNew *> currentSolidFace;

std::list<TransformationNew *> currentTransformations;

%}

%parse-param { Session* currSession }

%token OUTER SOLID FACET ENDFACET LOOP ENDLOOP VERTEX NORMAL ENDSOLID VARIABLE NUMBER
;

%error-verbose
%locations


%union
{
    double number;
    char *string;
    struct {
        char *string; // char *strVal;
        double number;   // int posVal;
    } numPos;
}

%token <string> BANK_EXPR
%token <string> NUMBER

%type <number> num
%type <string> expr

%%

commands: /* empty */
    | commands command
    ;


command:
    solid

    ;

solid:
    SOLID VARIABLE facetsArgs ENDSOLID VARIABLE
    {
        Reader* currReader = createReader(currSession);
        MeshNew* currMesh = createMesh();

        for (std::list<FaceNew*>::iterator it=currentSolidFace.begin(); it != currentSolidFace.end(); ++it){
            currMesh->faces.push_back(*it);
        }

        for (std::list<Vert*>::iterator it=currentMeshVertices.begin(); it != currentMeshVertices.end(); ++it){
            currMesh->verts.push_back(*it);
        }

        for (std::list<EdgeNew*>::iterator it=currentMeshEdges.begin(); it != currentMeshEdges.end(); ++it){
            currMesh->edges.push_back(*it);
        }

        currMesh->setName(strdup($<string>2));

        InstanceNew* newInstance = createInstance(currMesh, currSession->verts, currReader, true, false, false, currSession, true);

        newInstance->setName(strdup($<string>2));
        currSession->instances.push_back(newInstance);

        double *min = (double*) malloc(sizeof(double));
        double *max = (double*) malloc(sizeof(double));
        double *step = (double*) malloc(sizeof(double));

        *min = 0.0;
        *max = 0.5;
        *step = 0.01;

        OffsetNew* currOffset = createOffset("autoOffset", min, max, step);

        currSession->offsets.push_back(currOffset);

    };

vertex:
    VERTEX NUMBER NUMBER NUMBER
    {
        double *x = (double*) malloc(sizeof(double));
        double *y = (double*) malloc(sizeof(double));
        double *z = (double*) malloc(sizeof(double));

        *x = atof($<string>2);
        *y = atof($<string>3);
        *z = atof($<string>4);

        Vert * newVertex = NULL;
        for (Vert* currVert : currentMeshVertices){
            if ((abs(*currVert->x-*x) < 0.0000001) && (abs(*currVert->y-*y) < 0.0000001) && (abs(*currVert->z-*z) < 0.0000001)){
                newVertex = currVert;
                break;
            }
        }
        if (newVertex == NULL){
            newVertex = createVert (x, y, z);
            currentMeshVertices.push_back(newVertex);
        }

        currentFaceVertices.push_back(newVertex);
    };

vertexArgs:
    | vertexArgs vertex;

facetsArgs:
    | facetsArgs facets;

facets:
    FACET NORMAL NUMBER NUMBER NUMBER OUTER LOOP vertexArgs ENDLOOP ENDFACET
    {
        Reader* currReader = createReader(currSession);
        double *x = (double*) malloc(sizeof(double));
        double *y = (double*) malloc(sizeof(double));
        double *z = (double*) malloc(sizeof(double));

        *x = atof($<string>3);
        *y = atof($<string>4);
        *z = atof($<string>5);

        vector<Vert*> faceVert;
        for (Vert* vert : currentFaceVertices){
            faceVert.push_back(vert);
        }

        vector<double> normalCalc = getNormalFromVerts(faceVert);

        FaceNew * newFace = createFace(currentFaceVertices, &currentMeshEdges, currReader, false);

        currentSolidFace.push_back(newFace);
        currentFaceVertices.clear();
    };
