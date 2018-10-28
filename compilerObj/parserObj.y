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

extern int objlineno;
extern char* objtext;

extern int objcolumn;

int objlex(void);
void objerror(Session* currSession, const char *s) {
  printf("%s on line %d - %s\n", s, objlineno, objtext);
}

int objwrap() {
    return 1;
}

std::map<std::string, QColor> surfaces3;
std::map<std::string, Vert*> vertices3;
std::vector<std::string> tempVariables3;
std::vector<std::string> tempFaceDelete3;
std::string currentSetName3;
std::list<SetNew *> currentSetList3;
std::map<std::string, std::vector<double>> currentBank3;
std::vector<std::string> currentInstanceList3;
std::list<InstanceNew *> currentGroup3;
std::list<FaceNew *> currentMeshFaces3;
std::list<Vert *> currentMeshVertices3;
std::list<EdgeNew *> currentMeshEdges3;

std::list<Vert *> currentFaceVertices3;
std::list<FaceNew *> currentSolidFace3;

std::list<TransformationNew *> currentTransformations3;

double *getBankValue3(std::string str, Session* currSession){
    unsigned first = str.find("$") + 1;
    unsigned last = str.find(".");
    std::string strNew = str.substr (first,last-first);

    for(auto b : currSession->banks) {
        if (b->name == strNew){
            for(auto s : b->sets) {
                if (s->name == str.substr(last + 1)){
                    return &s->value;
                }
            }
        }
    }
    return NULL;
}



%}

%parse-param { Session* currSession }

%token COMMENT NUMBER V VT VN VP F L O G S SLASH MTLLIB USEMTL VARIABLE
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
%start start
%type <number> num
%type <string> expr

%%

commands: /* empty */
    | commands command
    ;


command:
    v | comment | v | f | vt | vn | vp | l | mtllib | usemtl | g | gEmpty | s

    ;

vArgs:
  |
    vArgs NUMBER {
      std::list<Vert*>::iterator it = currentMeshVertices3.begin();
      std::advance(it, atof($<string>2)-1);
      currentFaceVertices3.push_back((*it));
      currentMeshVertices3.push_back((*it));
    }

	;

comment:
  COMMENT {

  };

vw:
  |
    NUMBER {
    }
  ;

variableOptional:
  |
    VARIABLE {
    }
  ;

f:
   F vArgs {
       //std::cout << currentFaceVertices3.size() << std::endl;
       if (currentFaceVertices3.size() > 2){
           Reader* currReader = createReader(currSession);
           FaceNew * newFace = createFace(currentFaceVertices3, &currentMeshEdges3, currReader, false);

           currentSolidFace3.push_back(newFace);
       }
       currentFaceVertices3.clear();

   };

l:
  L vArgs {

  };

v:
    V NUMBER NUMBER NUMBER vw
    {
      double *x = (double*) malloc(sizeof(double));
      double *y = (double*) malloc(sizeof(double));
      double *z = (double*) malloc(sizeof(double));

      *x = atof($<string>2);
      *y = atof($<string>3);
      *z = atof($<string>4);

      Vert * newVertex = NULL;
      for (Vert* currVert : currentMeshVertices3){
          if ((abs(*currVert->x-*x) < 0.0000001) && (abs(*currVert->y-*y) < 0.0000001) && (abs(*currVert->z-*z) < 0.0000001)){
              newVertex = currVert;
              break;
          }
      }
      if (newVertex == NULL){
          newVertex = createVert (x, y, z);
          currentMeshVertices3.push_back(newVertex);
      }
    };

vt:
    V NUMBER NUMBER vw
    {
    };

vn:
    V NUMBER NUMBER NUMBER
    {
    };

vp:
    V NUMBER NUMBER NUMBER
    {
    };

usemtl:
    USEMTL VARIABLE
    {
    };

mtllib:
    MTLLIB VARIABLE
    {
    };


g:
    G VARIABLE
    {
    };

gEmpty:
    G
    {
    };

s:
    S NUMBER |S VARIABLE
    {

    };

start:
    commands
    {
        if (yychar == YYEOF) {
            /* Code to execute at the end of the parse */
            Reader* currReader = createReader(currSession);
            MeshNew* currMesh = createMesh();

            for (std::list<FaceNew*>::iterator it=currentSolidFace3.begin(); it != currentSolidFace3.end(); ++it){
                currMesh->faces.push_back(*it);
            }

            for (std::list<Vert*>::iterator it=currentMeshVertices3.begin(); it != currentMeshVertices3.end(); ++it){
                currMesh->verts.push_back(*it);
            }

            for (std::list<EdgeNew*>::iterator it=currentMeshEdges3.begin(); it != currentMeshEdges3.end(); ++it){
                currMesh->edges.push_back(*it);
            }

            currMesh->setName("mainMesh");

            InstanceNew* newInstance = createInstance(currMesh, currSession->verts, currReader, true, false, false, currSession, true);

            newInstance->setName("mainMesh");
            currSession->instances.push_back(newInstance);

            double *min = (double*) malloc(sizeof(double));
            double *max = (double*) malloc(sizeof(double));
            double *step = (double*) malloc(sizeof(double));

            *min = 0.0;
            *max = 0.5;
            *step = 0.01;

            OffsetNew* currOffset = createOffset("autoOffset", min, max, step);

            currSession->offsets.push_back(currOffset);
        }
    }
