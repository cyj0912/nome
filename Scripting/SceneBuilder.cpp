#include "SceneBuilder.h"

#include "newNOME/Reader.h"
#include "newNOME/InstanceNew.h"

CSceneBuilder* CSceneBuilder::GetSingleton()
{
    static CSceneBuilder builder(nullptr);
    return &builder;
}

void CSceneBuilder::SimpleInstance(const std::string& instanceName, const std::string& generator, float posX, float posY, float posZ)
{
	Reader* currReader = createReader(currSession);

	MeshNew* currentMesh = currReader->getMesh(generator);

	InstanceNew* newInstance = NULL;
	bool onlyCreateNewVertices = false;
	if (currentMesh != NULL) {
		//if (currentTransformations2.size() > 0){
		onlyCreateNewVertices = true;
		//}
		newInstance = createInstance(currentMesh, currSession->verts, currReader, true, false, onlyCreateNewVertices, currSession, true);
		newInstance->currSession = currSession;
	}
	else {
		GroupNew * currentGroup2 = currReader->getGroup(generator);
		if (currentGroup2 != NULL) {
			newInstance = createInstance(currentGroup2, currSession->verts, currReader, currSession);
			newInstance->currSession = currSession;
		}
		else {
			throw "Can't find the target to instantiate";
		}
	}

	newInstance->setName(instanceName);

	//Handle transforms
	double* x = new double; *x = posX;
	double* y = new double; *y = posY;
	double* z = new double; *z = posZ;
	Translate* currTranslate = createTranslate(x, y, z);
	char buffer[256];
	snprintf(buffer, sizeof(buffer), "%f", posX);
	currTranslate->xStr = buffer;
	snprintf(buffer, sizeof(buffer), "%f", posY);
	currTranslate->yStr = buffer;
	snprintf(buffer, sizeof(buffer), "%f", posZ);
	currTranslate->zStr = buffer;
	for (TransformationNew * t : newInstance->transformations) {
		newInstance->applyTransformation(t);
	}

	currSession->instances.push_back(newInstance);
}
