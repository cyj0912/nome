//
//  Session.h
//

#ifndef Session_h
#define Session_h

#include <stdio.h>
#include <fstream>
#include "Data.h"
#include "Octree.h"
#include "OctreeProxy.h"

class MeshNew;
class InstanceNew;
class GroupNew;
class BankNew;
class PolylineNew;
class BSplineNew;
class BezierCurveNew;
class CircleNew;
class FunnelNew;
class TunnelNew;
class SubdivisionNew;
class OffsetNew;

class Session
{
public:
    std::list<Vert*> verts;
    std::list<EdgeNew*> edges;
    std::list<FaceNew*> faces;
    std::list<MeshNew*> meshes;
    std::list<Surface*> surfaces;
    std::list<GroupNew*> groups;
    std::list<InstanceNew*> instances;
    std::list<PolylineNew*> polylines;
    std::list<BSplineNew*> bsplines;
    std::list<BezierCurveNew*> bezierCurves;
    std::list<CircleNew*> circles;
    std::list<FunnelNew*> funnels;
    std::list<TunnelNew*> tunnels;
    std::list<BankNew*> banks;
    std::list<SubdivisionNew*> subdivisions;
    std::list<OffsetNew*> offsets;
    std::string name;
    std::string fileContent;
    std::vector<std::tuple<std::vector<Vert*>, std::vector<EdgeNew*>>> borders = std::vector<std::tuple<std::vector<Vert*>, std::vector<EdgeNew*>>>();
    std::tuple<std::vector<Vert*>, std::vector<EdgeNew*>> tmpBorder;
    bool isBorderSelected = false;

    int subdivisionType = 0;
    int offsetType = 0;

    bool recalculateOffset = true;
    bool recalculateSubdivision = true;
    bool recalculateSlider = true;

    int subdivisionLevel = 0;
    MeshNew* flattenMesh;
    std::vector<MeshNew*> flattenMeshList = std::vector<MeshNew*>();

    int tmpFaceIndex = 0;
    int tmpPolylineIndex = 0;

    std::list<EdgeNew*> selectedEdges;
    std::list<Vert*> selectedVerts;

    std::list<FaceNew*> selectedFaces;
    MeshNew* tmpMesh = nullptr;
    PolylineNew* tmpPolyline = nullptr;
    InstanceNew* tmpInstance = nullptr;

    bool normalVectShow = true;

    Surface* foreColor;
    Surface* backColor;
    Surface* outsideColor;
    Surface* insideColor;
    Surface* offsetColor;
    double epsilon = 0.1;
    std::string epsilonStr = "0.1";

	//We use multi-phased parsing to handle macros, phase0 is bank/set, phase1 is everything else
	int parsingPhase = 0;

    Session();
    ~Session();
	void reset();

    //Naming functions

    void mergeEdges(MeshNew* flattenMesh);

    bool setName(std::string n);
    std::string getName();
    bool updateNames();
    void groupFaces(std::string consolidateInstanceName, std::string consolidateMeshName);
    void addTmpFace();
    void deleteTmpFace();
    void addTmpPolyline();
    void selectVert(int hits, unsigned int *names, double posX, double posY, double posZ);
    void selectFace(int hits, unsigned int *names, double posX, double posY, double posZ);
    void selectEdge(int hits, unsigned int *names, double posX, double posY, double posZ);
    void selectBorder(int hits, unsigned int *names, double posX, double posY, double posZ);
	void updateFileContentSliders();
    void SaveSessionNom(std::string outputFile);
    void SaveSessionStl(std::string outputFile);
    void consolidateTmpMesh(std::string consolidateInstanceName, std::string consolidateMeshName);
    void clearSelection();
    void saveFileToStr(std::string fileName);
	void parseSavedStr();
    void deleteFace();
    void draw();
    void drawSubdivide(int subdivision, int previousSubdivisionLevel, double offset, bool calculateOffset, bool calculateSubdivide, bool calculateSlider);
    void createFlattenMesh(bool instance);
    std::vector<Vert*> findLoop(Vert* startVert, std::vector<Vert*> selectedVertsLoop);
    std::tuple<std::vector<Vert*>, std::vector<EdgeNew*>> findBorder(Vert* startVert);
    std::tuple<std::vector<Vert*>, std::vector<EdgeNew*>> findBorderRec(Vert* startVert, std::vector<Vert*> borderVerts, std::vector<EdgeNew*> seenEdges);
    void zipBorders();

    OctantNew* getOctreeRoot() const { return OctreeRoot; }

    static Session& getSingleton();

private:
    int accesses;

    OctantNew* OctreeRoot;
};

//Instantiation
void saveFaceSTL(FaceNew* currFace, std::ofstream& file);
void parseGetBankVal(const char* input, Session* sessionParse, double* output, int lineNumber);

#endif /* Session_h */
