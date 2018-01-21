%code requires{
#include <Lewis/Session.h>

}

%{
#include <FlexLexer.h>
#include <stdio.h>
#include <string.h>
#include <list>
#include <Lewis/Data.h>
#include <Lewis/MeshNew.h>
#include <Lewis/Session.h>
#include <Lewis/Reader.h>
#include <Lewis/TransformationNew.h>
#include <Lewis/PolylineNew.h>
#include <Lewis/CircleNew.h>
#include <Lewis/FunnelNew.h>
#include <Lewis/TunnelNew.h>
#include <Lewis/InstanceNew.h>
#include <Lewis/BSplineNew.h>
#include <Lewis/BezierCurveNew.h>

extern int nomlineno;
extern char* nomtext;
extern int nomcolumn;

int nomlex(void);
int nomerror(Session* currSession, const char *s) {
  printf("%s on line %d - %s\n", s, nomlineno, nomtext);
}

int nomwrap() {
    return 1;
}

map<string,QColor> surfaces2;
map<string,Vert*> vertices2;
std::vector<string> tempVariables2;
std::vector<string> tempFaceDelete2;
string currentSetName2;
std::list<SetNew *> currentSetList2;
map<string,std::vector<double>> currentBank2;
std::vector<string> currentInstanceList2;
std::list<InstanceNew *> currentGroup2;
std::list<FaceNew *> currentMeshFaces2;
std::list<Vert *> currentMeshVertices2;
std::list<EdgeNew *> currentMeshEdges2;
std::list<TransformationNew *> currentTransformations2;

%}

%parse-param { Session* currSession }

//%defines "compilerNome/parser.h"
//%output "compilerNome/parser.cpp"
//%define api.prefix {nom}

%token COLOR VARIABLE COMMENT NEWLINE SURFACE END_SURFACE MESH END_MESH FACE END_FACE BEG_POINT
END_POINT OBJECT END_OBJECT BANK END_BANK TUNNEL END_TUNNEL FUNNEL END_FUNNEL
POLYLINE END_POLYLINE INSTANCE END_INSTANCE CIRCLE END_CIRCLE BEG_DELETE END_DELETE
GROUP  END_GROUP TRANSLATE ROTATE MIRROR SET OPARENTHESES EPARENTHESES OBRACE
EXPR DOLLAR EBRACE PERIOD TOKHEAT STATE TOKTARGET TOKTEMPERATURE
SCALE SUBDIVISION END_SUBDIVISION SUBDIVISIONS TYPE OFFSET END_OFFSET MIN MAX STEP
BSPLINE END_BSPLINE CLOSED SLICES BEZIERCURVE END_BEZIERCURVE COS SIN TAN EXPONENT
MULTIPLY DIVIDE ADD SUBTRACT SLIDEREXPRESSION;

%error-verbose
%locations


%union
{
    double intNumber;
    double number;
    const char *string;
    bool boolean;
    struct {
        const char *string; // char *strVal;
        double number;   // int posVal;
    } numPos;
}

%token <string> BANK_EXPR
%token <string> NUMBER


%type <boolean> closedArgs
%type <number> num
%type <string> expr
%type <numPos> numberValue


%%

commands: /* empty */
	| commands command
	;


command:
    comment | mesh | surface | point | face | object | bank |
  tunnel | funnel | polyline | instance | delete | group | circle |
  subdivision | offset | bspline | beziercurve;

numberValue:
    NUMBER {
        $<string>$ = strdup($<string>1);
    } | SLIDEREXPRESSION
    {
        std::string exprStr = strdup($<string>1);
        exprStr.erase(0, 6);
        exprStr.erase(exprStr.size() - 1);
        $<string>$ = strdup(exprStr.c_str());
    }
    ;


num:
    NUMBER
    {
        $<number>$ = (double)atof($1);
    }
    ;

numPosTok:
    NUMBER
    {
        $<numPos>$.string = strdup($1);
        $<numPos>$.number = nomcolumn;
    }
    ;

comment:
    COMMENT
    {
    }
    ;


variables:
  |
    variables VARIABLE {
        tempVariables2.push_back($<string>2);
    }
	;

surfaceArgs:
    {$<string>$ = "";}
    | SURFACE VARIABLE {
        $<string>$ = $<string>2;
    }
	;

closedArgs:
    {$<boolean>$ = false;}
    | CLOSED {
        $<boolean>$ = true;
    }
	;

transformArgs:
    | transformArgs rotateArgs |  transformArgs translateArgs | transformArgs scaleArgs | transformArgs mirrorArgs
    ;

rotateArgs:
    ROTATE OPARENTHESES numberValue numberValue numberValue EPARENTHESES OPARENTHESES numberValue EPARENTHESES
    {
        double *x = (double*) malloc(sizeof(double));
        double *y = (double*) malloc(sizeof(double));
        double *z = (double*) malloc(sizeof(double));
        double *angle = (double*) malloc(sizeof(double));

        double *currentValSet = (double*) malloc(sizeof(double));
        parseGetBankVal($<string>3, currSession, currentValSet);
        *x = *currentValSet;
        parseGetBankVal($<string>4, currSession, currentValSet);
        *y = *currentValSet;
        parseGetBankVal($<string>5, currSession, currentValSet);
        *z = *currentValSet;
        parseGetBankVal($<string>8, currSession, currentValSet);
        *angle = *currentValSet;

        Rotate* currRotate = createRotate(x, y, z, angle);
        currRotate->xStr = strdup($<string>3);
        currRotate->yStr = strdup($<string>4);
        currRotate->zStr = strdup($<string>5);
        currRotate->angleStr = strdup($<string>8);

        currentTransformations2.push_back(currRotate);

    }
    ;

translateArgs:
    TRANSLATE OPARENTHESES numberValue numberValue numberValue EPARENTHESES
    {
        double *x = (double*) malloc(sizeof(double));
        double *y = (double*) malloc(sizeof(double));
        double *z = (double*) malloc(sizeof(double));

        double *currentValSet = (double*) malloc(sizeof(double));
        parseGetBankVal($<string>3, currSession, currentValSet);
        *x = *currentValSet;
        parseGetBankVal($<string>4, currSession, currentValSet);
        *y = *currentValSet;
        parseGetBankVal($<string>5, currSession, currentValSet);
        *z = *currentValSet;

        Translate* currTranslate = createTranslate(x, y, z);
        currTranslate->xStr = strdup($<string>3);
        currTranslate->yStr = strdup($<string>4);
        currTranslate->zStr = strdup($<string>5);

        currentTransformations2.push_back(currTranslate);
    }
    ;

scaleArgs:
    SCALE OPARENTHESES numberValue numberValue numberValue EPARENTHESES
    {
        double *x = (double*) malloc(sizeof(double));
        double *y = (double*) malloc(sizeof(double));
        double *z = (double*) malloc(sizeof(double));

        double *currentValSet = (double*) malloc(sizeof(double));
        parseGetBankVal($<string>3, currSession, currentValSet);
        *x = *currentValSet;
        parseGetBankVal($<string>4, currSession, currentValSet);
        *y = *currentValSet;
        parseGetBankVal($<string>5, currSession, currentValSet);
        *z = *currentValSet;

        Scale* currScale = createScale(x, y, z);
        currScale->xStr = strdup($<string>3);
        currScale->yStr = strdup($<string>4);
        currScale->zStr = strdup($<string>5);

        currentTransformations2.push_back(currScale);
    }
    ;

mirrorArgs:
    MIRROR OPARENTHESES numberValue numberValue numberValue numberValue EPARENTHESES
    {
        double *currentValSet = (double*) malloc(sizeof(double));
        parseGetBankVal($<string>3, currSession, currentValSet);
        double x = *currentValSet;
        parseGetBankVal($<string>4, currSession, currentValSet);
        double y = *currentValSet;
        parseGetBankVal($<string>5, currSession, currentValSet);
        double z = *currentValSet;
        parseGetBankVal($<string>6, currSession, currentValSet);
        double w = *currentValSet;

    }
    ;

faceArgs:
    | faceArgs faceMesh
	;

instanceArgs:
    | instanceArgs instanceGroup
	;

instanceGroup:
    INSTANCE VARIABLE VARIABLE surfaceArgs transformArgs END_INSTANCE
    {
        Reader* currReader = createReader(currSession);
        string instanceName = strdup($<string>2);
        string lookFor = strdup($<string>3);

        MeshNew * currentMesh = currReader->getMesh($<string>3);

        InstanceNew* newInstance;
        if (currentMesh != NULL) {
            newInstance = createInstance(currentMesh, currSession->verts, currReader, false);
            newInstance->setName(strdup($<string>2));
        }
        else{
            nomerror(currSession, "Incorrect vertex, face, or mesh name");
            YYABORT;
        }

        newInstance->transformations = currentTransformations2;
        currentTransformations2.clear();

        for (TransformationNew * t : newInstance->transformations){
            newInstance->applyTransformation(t);
        }

        string surfaceName = $<string>4;
        // Check if a surface has been applied.
        if (surfaceName.length() != 0){
            Surface * currentSurface = currReader->surf($<string>4);
            if (currentSurface != NULL) {
                setSurface(newInstance, currentSurface);
            }
            else{
                nomerror(currSession, "Incorrect surface name");
                YYABORT;
            }
        }

        currentGroup2.push_back(newInstance);
    }
    ;

faceDeleteArgs:
	| faceDeleteArgs faceDelete
	;

instanceOffseSubdivide:
    INSTANCE VARIABLE
    {
        string instanceName = strdup($<string>2);
    };

instanceOffseSubdivideArgs:
    | instanceOffseSubdivideArgs instanceOffseSubdivide
    ;

subdivision:
    SUBDIVISION VARIABLE instanceOffseSubdivideArgs TYPE VARIABLE SUBDIVISIONS numberValue END_SUBDIVISION
    {
        double *subdivision = (double*) malloc(sizeof(double));

        double *currentValSet = (double*) malloc(sizeof(double));
        parseGetBankVal($<string>7, currSession, currentValSet);
        *subdivision = *currentValSet;

        SubdivisionNew* currSubdivision = createSubdivision(strdup($<string>3), strdup($<string>5), subdivision);
        currSession->subdivisions.push_back(currSubdivision);
    };

offset:
    OFFSET VARIABLE MIN numberValue MAX numberValue STEP numberValue END_OFFSET
    {
        double *min = (double*) malloc(sizeof(double));
        double *max = (double*) malloc(sizeof(double));
        double *step = (double*) malloc(sizeof(double));

        double *currentValSet = (double*) malloc(sizeof(double));
        parseGetBankVal($<string>4, currSession, currentValSet);
        *min = *currentValSet;
        parseGetBankVal($<string>6, currSession, currentValSet);
        *max = *currentValSet;
        parseGetBankVal($<string>8, currSession, currentValSet);
        *step = *currentValSet;

        OffsetNew* currOffset = createOffset(strdup($<string>2), min, max, step);

        currSession->offsets.push_back(currOffset);
    };

mesh:
	MESH VARIABLE faceArgs END_MESH
    {

        MeshNew* currMesh = createMesh();

        for (std::list<FaceNew*>::iterator it=currentMeshFaces2.begin(); it != currentMeshFaces2.end(); ++it){
            currMesh->faces.push_back(*it);
        }

        for (std::list<Vert*>::iterator it=currentMeshVertices2.begin(); it != currentMeshVertices2.end(); ++it){
            currMesh->verts.push_back(*it);
        }

        for (std::list<EdgeNew*>::iterator it=currentMeshEdges2.begin(); it != currentMeshEdges2.end(); ++it){
            currMesh->edges.push_back(*it);
        }

        currMesh->setName(strdup($<string>2));
        currSession->meshes.push_back(currMesh);

        currentMeshFaces2.clear();
        currentMeshEdges2.clear();
        currentMeshVertices2.clear();
	}
	;

group:
	GROUP VARIABLE instanceArgs END_GROUP
    {
        GroupNew* currGroup = createGroup(currentGroup2);
        currGroup->setName(strdup($<string>2));
        currSession->groups.push_back(currGroup);
        currentGroup2.clear();
	}
	;

expr:
    OBRACE EXPR BANK_EXPR EBRACE
    {
        $<string>$ = $3;
    };

delete:
    BEG_DELETE faceDeleteArgs END_DELETE
    {
        Reader* currReader = createReader(currSession);

        for (std::string currFace : tempFaceDelete2){
            currReader->deleteFace(currReader->getFace(currFace));
        }

        tempFaceDelete2.clear();
	}
	;

set:
    SET VARIABLE numPosTok numberValue numberValue numberValue
    {
        string currentSetName = $<string>2;
        double currentSetValue = (double)atof($<numPos>3.string);
        double *currentValSet = (double*) malloc(sizeof(double));
        parseGetBankVal($<string>4, currSession, currentValSet);
        double currentSetStart = *currentValSet;
        parseGetBankVal($<string>5, currSession, currentValSet);
        double currentSetEnd = *currentValSet;
        parseGetBankVal($<string>6, currSession, currentValSet);
        double currentSetStepSize = *currentValSet;
        string currentSetValueString = $<numPos>3.string;


        int begPos = $<numPos>3.number-currentSetValueString.length();
        int lengthValChar = currentSetValueString.length();

        SetNew * currentSet = createSet(currentSetName, currentSetValue, currentSetStart, currentSetEnd, currentSetStepSize, begPos, lengthValChar);

        currentSetList2.push_back(currentSet);
	}
	;

setArgs:
    | setArgs set |  setArgs comment
	;

faceMesh:
    FACE VARIABLE parenthesisName surfaceArgs END_FACE
    {
        Reader* currReader = createReader(currSession);

        std::list<Vert*> verticesFace;

        for (std::vector<string>::iterator it = tempVariables2.begin() ; it != tempVariables2.end(); ++it){
            Vert * currentVertex = currReader->getVert(*it);

            if (currentVertex != NULL) {
                verticesFace.push_back(currentVertex);
                bool found = false;
                for (Vert* currentMeshVertex: currentMeshVertices2){
                    if (currentMeshVertex->index == currentVertex->index){
                        found = true;
                    }
                }
                if (found == false){
                    currentMeshVertices2.push_back(currentVertex);
                }

            }
            else{
                nomerror(currSession, "Incorrect vertex name");
                YYABORT;
            }
        }

        FaceNew * newFace = createFace(verticesFace, &currentMeshEdges2, currReader, false);
        setName(newFace, strdup($<string>2));

        string surfaceName = $<string>4;
        // Check if a surface has been applied.
        if (surfaceName.length() != 0){
            Surface * currentSurface = currReader->surf($<string>4);
            if (currentSurface != NULL) {
                setSurface(newFace, currentSurface);
            }
            else{
                nomerror(currSession, "Incorrect surface name");
                YYABORT;
            }
        }

        currentMeshFaces2.push_back(newFace);

        tempVariables2.clear();
    }
    ;

bank:
	BANK VARIABLE setArgs END_BANK
    {
        BankNew * currentBank2 = createBank();
        currentBank2->name = strdup($<string>2);
        currentBank2->sets = currentSetList2;
        currSession->banks.push_back(currentBank2);
        currentSetList2.clear();
	}
	;

circle:
    CIRCLE VARIABLE OPARENTHESES numberValue numberValue EPARENTHESES END_CIRCLE
    {
        string name = $<string>2;
        double *num = (double*) malloc(sizeof(double));
        double *rad = (double*) malloc(sizeof(double));

        double *currentValSet = (double*) malloc(sizeof(double));
        parseGetBankVal($<string>4, currSession, currentValSet);
        *num = *currentValSet;
        parseGetBankVal($<string>5, currSession, currentValSet);
        *rad = *currentValSet;

        CircleNew* currCircle = createCircle(num, rad);
        currCircle->setName(strdup($<string>2));
        currCircle->numStr = strdup($<string>4);
        currCircle->radStr = strdup($<string>5);
        currCircle->currSession = currSession;

        currSession->circles.push_back(currCircle);
    };

tunnel:
    TUNNEL VARIABLE OPARENTHESES numberValue numberValue numberValue numberValue EPARENTHESES
  END_TUNNEL
	{
        Reader* currReader = createReader(currSession);

        string name = $<string>2;
        double *n = (double*) malloc(sizeof(double));
        double *ro = (double*) malloc(sizeof(double));
        double *ratio = (double*) malloc(sizeof(double));
        double *h = (double*) malloc(sizeof(double));

        double *currentValSet = (double*) malloc(sizeof(double));
        parseGetBankVal($<string>4, currSession, currentValSet);
        *n = *currentValSet;
        parseGetBankVal($<string>5, currSession, currentValSet);
        *ro = *currentValSet;
        parseGetBankVal($<string>6, currSession, currentValSet);
        *ratio = *currentValSet;
        parseGetBankVal($<string>7, currSession, currentValSet);
        *h = *currentValSet;

        TunnelNew* currTunnel = createTunnel(n, ro, ratio, h, currReader);
        currTunnel->setName(strdup($<string>2));
        currTunnel->nStr = strdup($<string>4);
        currTunnel->roStr = strdup($<string>5);
        currTunnel->ratioStr = strdup($<string>6);
        currTunnel->hStr = strdup($<string>7);
        currTunnel->currSession = currSession;

        currSession->tunnels.push_back(currTunnel);
	}
	;

funnel:
    FUNNEL VARIABLE OPARENTHESES numberValue numberValue numberValue numberValue EPARENTHESES
  END_FUNNEL
	{
        Reader* currReader = createReader(currSession);

        string name = $<string>2;
        double *n = (double*) malloc(sizeof(double));
        double *ro = (double*) malloc(sizeof(double));
        double *ratio = (double*) malloc(sizeof(double));
        double *h = (double*) malloc(sizeof(double));

        double *currentValSet = (double*) malloc(sizeof(double));
        parseGetBankVal($<string>4, currSession, currentValSet);
        *n = *currentValSet;
        parseGetBankVal($<string>5, currSession, currentValSet);
        *ro = *currentValSet;
        parseGetBankVal($<string>6, currSession, currentValSet);
        *ratio = *currentValSet;
        parseGetBankVal($<string>7, currSession, currentValSet);
        *h = *currentValSet;

        FunnelNew* currFunnel = createFunnel(n, ro, ratio, h, currReader);
        currFunnel->setName(strdup($<string>2));

        currFunnel->nStr = strdup($<string>4);
        currFunnel->roStr = strdup($<string>5);
        currFunnel->ratioStr = strdup($<string>6);
        currFunnel->hStr = strdup($<string>7);
        currFunnel->currSession = currSession;

        currSession->funnels.push_back(currFunnel);
	}
	;

parenthesisName:
	OPARENTHESES variables EPARENTHESES
    {
	}
	;

face:
	FACE VARIABLE parenthesisName surfaceArgs END_FACE
    {
        Reader* currReader = createReader(currSession);

        std::list<Vert*> verticesFace;
        for (std::vector<string>::iterator it = tempVariables2.begin() ; it != tempVariables2.end(); ++it){
            Vert * currentVertex = currReader->vert(*it);
            if (currentVertex != NULL) {
                verticesFace.push_back(currentVertex);
            }
            else{
                nomerror(currSession, "Incorrect vertex name");
                YYABORT;
            }
        }

        FaceNew * newFace = createFace(verticesFace, &(currSession->edges), currReader, false);

        setName(newFace, strdup($<string>2));


        string surfaceName = $<string>4;
        // Check if a surface has been applied.
        if (surfaceName.length() != 0){
            Surface * currentSurface = currReader->surf($<string>4);
            if (currentSurface != NULL) {
                setSurface(newFace, currentSurface);
            }
            else{
                nomerror(currSession, "Incorrect surface name");
                YYABORT;
            }
        }

        currSession->faces.push_back(newFace);

        tempVariables2.clear();
	}
	;

faceDelete:
	FACE VARIABLE END_FACE
	{
        tempFaceDelete2.push_back($<string>2);
	}
	;

beziercurve:
  BEZIERCURVE VARIABLE parenthesisName SLICES numberValue surfaceArgs END_BEZIERCURVE{
    double *slices = (double*) malloc(sizeof(double));
    Reader* currReader = createReader(currSession);


    BezierCurveNew* currBezierCurve = createBezierCurveNew();
    currBezierCurve->setName(strdup($<string>2));
    double *currentValSet = (double*) malloc(sizeof(double));
    //parseGetBankVal($<string>5, currSession, currentValSet);
    //*slices = *currentValSet;
    *slices = 0;
    currBezierCurve->segments = slices;
    currBezierCurve->segmentsStr = strdup($<string>5);
    currBezierCurve->currSession = currSession;

    // Create list of vertices of face.
    for (std::vector<string>::iterator it = tempVariables2.begin() ; it != tempVariables2.end(); ++it){
        Vert * currentVertex = currReader->getVert(*it);
        if (currentVertex != NULL) {
            currBezierCurve->proxy.push_back(currentVertex);
        }
        else{
            nomerror(currSession, "Incorrect vertex name");
            YYABORT;
        }
    }

    currBezierCurve->updateBezierCurve();

    string surfaceName = $<string>6;
    // Check if a surface has been applied.
    if (surfaceName.length() != 0){
        Surface * currentSurface = currReader->surf($<string>6);
        if (currentSurface != NULL) {
            currBezierCurve->setSurface(currentSurface);
        }
        else{
            nomerror(currSession, "Incorrect surface name");
            YYABORT;
        }
    }

    currSession->bezierCurves.push_back(currBezierCurve);
    tempVariables2.clear();
};


bspline:
	BSPLINE VARIABLE parenthesisName closedArgs SLICES numberValue surfaceArgs END_BSPLINE{
    if ($<intNumber>1 != $<intNumber>8) {
        nomerror(currSession, "bspline and endbspline do not have the same number.");
        YYABORT;
    }

    Reader* currReader = createReader(currSession);

    BSplineNew* currBSpline = createBSplineNew();
    currBSpline->setName(strdup($<string>2));
    currBSpline->set_order($<intNumber>1);
    double *currentValSet = (double*) malloc(sizeof(double));
    parseGetBankVal($<string>6, currSession, currentValSet);
    currBSpline->segments = *currentValSet;
    currBSpline->currSession = currSession;

    currBSpline->segmentsStr = $<string>6;


    // Create list of vertices of face.
    for (std::vector<string>::iterator it = tempVariables2.begin() ; it != tempVariables2.end(); ++it){
        Vert * currentVertex = currReader->getVert(*it);
        if (currentVertex != NULL) {
            currBSpline->proxy.push_back(currentVertex);
        }
        else{
            nomerror(currSession, "Incorrect vertex name");
            YYABORT;
        }
    }

    currBSpline->isLoop = $<boolean>4;

    if (currBSpline->order > currBSpline->proxy.size()){
      std::string errorStr = "bspline order (";
      errorStr += currBSpline->order;
      errorStr += ") must be <= #controlpoints (";
      errorStr += currBSpline->proxy.size();
      errorStr += ").";
      nomerror(currSession, errorStr.c_str());
      YYABORT;
    }


    currBSpline->updateBSpline();

    string surfaceName = $<string>7;
    // Check if a surface has been applied.
    if (surfaceName.length() != 0){
        Surface * currentSurface = currReader->surf($<string>7);
        if (currentSurface != NULL) {
            currBSpline->setSurface(currentSurface);
        }
        else{
            nomerror(currSession, "Incorrect surface name");
            YYABORT;
        }
    }

    currSession->bsplines.push_back(currBSpline);

    tempVariables2.clear();
  };

polyline:
	POLYLINE VARIABLE parenthesisName surfaceArgs END_POLYLINE
	{
        Reader* currReader = createReader(currSession);

        // Create list of vertices of face.
        std::list<Vert*> verticesPolyline;
        for (std::vector<string>::iterator it = tempVariables2.begin() ; it != tempVariables2.end(); ++it){
            Vert * currentVertex = currReader->getVert(*it);
            if (currentVertex != NULL) {
                verticesPolyline.push_back(currentVertex);
            }
            else{
                nomerror(currSession, "Incorrect vertex name");
                YYABORT;
            }
        }

        PolylineNew* currPolyline = createPolylineNew(verticesPolyline);
        currPolyline->setName(strdup($<string>2));

        string surfaceName = $<string>4;
        // Check if a surface has been applied.
        if (surfaceName.length() != 0){
            Surface * currentSurface = currReader->surf($<string>4);
            if (currentSurface != NULL) {
                currPolyline->setSurface(currentSurface);
            }
            else{
                nomerror(currSession, "Incorrect surface name");
                YYABORT;
            }
        }
        currSession->polylines.push_back(currPolyline);
        tempVariables2.clear();
	}
	;

instance:
    INSTANCE VARIABLE VARIABLE surfaceArgs transformArgs END_INSTANCE
    {
        Reader* currReader = createReader(currSession);

        string instanceName = strdup($<string>2);
        string lookFor = strdup($<string>3);

        MeshNew * currentMesh = currReader->getMesh($<string>3);

        InstanceNew* newInstance = NULL;
        if (currentMesh != NULL) {
            newInstance = createInstance(currentMesh, currSession->verts, currReader, true);
        }
        else{
            GroupNew * currentGroup2 = currReader->getGroup($<string>3);
            if (currentGroup2 != NULL) {
                newInstance = createInstance(currentGroup2, currSession->verts, currReader);
            }
            else{
                nomerror(currSession, "Incorrect vertex, face, or mesh name");
                YYABORT;
            }
        }

        newInstance->setName(strdup($<string>2));
        newInstance->transformations = currentTransformations2;
        currentTransformations2.clear();

        for (TransformationNew * t : newInstance->transformations){
            newInstance->applyTransformation(t);
        }

        string surfaceName = $<string>4;
        // Check if a surface has been applied.
        if (surfaceName.length() != 0){
            Surface * currentSurface = currReader->surf($<string>4);
            if (currentSurface != NULL) {
                setSurface(newInstance, currentSurface);
            }
            else{
                nomerror(currSession, "Incorrect surface name");
                YYABORT;
            }
        }

        currSession->instances.push_back(newInstance);
	}
	;

object:
	OBJECT VARIABLE parenthesisName END_OBJECT
    {
	}
	;

surface:
    SURFACE VARIABLE COLOR OPARENTHESES numberValue numberValue numberValue EPARENTHESES END_SURFACE
    {
        double *r = (double*) malloc(sizeof(double));
        double *g = (double*) malloc(sizeof(double));
        double *b = (double*) malloc(sizeof(double));

        double *currentValSet = (double*) malloc(sizeof(double));
        parseGetBankVal($<string>5, currSession, currentValSet);
        *r = *currentValSet;
        parseGetBankVal($<string>6, currSession, currentValSet);
        *g = *currentValSet;
        parseGetBankVal($<string>7, currSession, currentValSet);
        *b = *currentValSet;

        Surface* currSurface = createSurface(r, g, b, strdup($<string>2));

        currSurface->rStr = strdup($<string>5);
        currSurface->gStr = strdup($<string>6);
        currSurface->bStr = strdup($<string>7);
        currSurface->currSession = currSession;

        currSession->surfaces.push_back(currSurface);
	}
	;

point:
    BEG_POINT VARIABLE OPARENTHESES numberValue numberValue numberValue EPARENTHESES END_POINT
    {
        double *x = (double*) malloc(sizeof(double));
        double *y = (double*) malloc(sizeof(double));
        double *z = (double*) malloc(sizeof(double));

        double *currentValSet = (double*) malloc(sizeof(double));
        parseGetBankVal($<string>4, currSession, currentValSet);
        *x =*currentValSet;
        parseGetBankVal($<string>5, currSession, currentValSet);
        *y =*currentValSet;
        parseGetBankVal($<string>6, currSession, currentValSet);
        *z =*currentValSet;

        Vert * newVertex = createVert (x, y, z);
        newVertex->setName(strdup($<string>2));

        newVertex->currSession = currSession;
        newVertex->xStr = strdup($<string>4);
        newVertex->yStr = strdup($<string>5);
        newVertex->zStr = strdup($<string>6);

        currSession->verts.push_back(newVertex);
	}
	;