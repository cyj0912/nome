#include "Sweep.h"
#include "Reader.h"

Sweep::Sweep(Session* session, const SweepInitializer& initializer)
{
	Path = initializer.PathInit.Path;

	if (initializer.CrossSectionInits.size() < 1)
		throw std::invalid_argument("Cannot create sweep: no crosssection defined.");

	CrossSection = initializer.CrossSectionInits[0].CrossSection;

	if (!CheckSemantics())
		throw std::invalid_argument("Cannot create sweep: some arguments are incorrect.");
	surface = nullptr;
	ParentSession = session;
	Reader = createReader(ParentSession);
	CalculateMesh();
}

bool Sweep::CheckSemantics() const
{
	if (!Path)
		return false;
	if (!CrossSection)
		return false;

	return true;
}

void Sweep::CalculateMesh()
{
	//Clear the previous mesh if there is
	for (auto* v : verts)
		delete v;
	verts.clear();
	for (auto* e : edges)
		delete e;
	edges.clear();
	for (auto* f : faces)
		delete f;
	faces.clear();

	//Query the frenet frames according to our needs
	SweepPathParams params;
	params.bMinimizeTorsion = false;
	params.bClosed = false;
	params.Symmetry = 1;
	params.Azimuth = 0.0f;
	params.Twist = 0.0f;
	const auto pathFrames = Path->GetSweepFrames(params);
	const auto csFrames = CrossSection->GetSweepFrames(params);
	const auto pathCount = pathFrames.size();
	const auto csCount = csFrames.size();
	const int numSlices = pathCount - 1;

	//First vector stores the rings, second stores the vertices
	std::vector<std::vector<Vert*>> vertCache;

	auto addVertex = [this](const Vector3& pos, const std::string& name)
	{
		double *x = (double*)malloc(sizeof(double));
		double *y = (double*)malloc(sizeof(double));
		double *z = (double*)malloc(sizeof(double));
		*x = pos.x_; *y = pos.y_; *z = pos.z_;
		Vert* newVert = createVert(x, y, z);
		newVert->setName(name);
		verts.push_back(newVert);
		return newVert;
	};

	//Fill in the first ring vertices
	{
		vertCache.emplace_back();
		Vector3 pt1 = pathFrames[0].Translation();
		Matrix3 m1 = pathFrames[0].ToMatrix3();
		for (int i = 0; i < csCount; i++)
		{
			Vector3 p1 = pt1 + m1 * csFrames[i].Translation();
			Vert* vert = addVertex(p1, "r0v" + std::to_string(i));
			vertCache[0].push_back(vert);
		}
	}

	//For every slice, we generate a seris of faces
	for (int slice = 0; slice < numSlices; slice++)
	{
		vertCache.emplace_back();
		Matrix3x4 m2 = pathFrames[slice + 1];

		//Calculate p1 p2 p3 p4 and form a face with them
		Vert* p1v = vertCache[slice][0]; //ring $slice vert 0
		Vert* p2v = addVertex(m2 * csFrames[0].Translation(), "r" + std::to_string(slice + 1) + "v0"); //ring $slice+1 vert 0
		vertCache[slice + 1].push_back(p2v);
		for (int csSlice = 1; csSlice < csCount; csSlice++)
		{
			Vert* p3v = vertCache[slice][csSlice]; //ring $slice vert csSlice
			Vert* p4v = addVertex(m2 * csFrames[csSlice].Translation(),
				"r" + std::to_string(slice + 1) + "v" + std::to_string(csSlice)); //ring $slice+1 vert csSlice
			vertCache[slice + 1].push_back(p4v);

			//p1---p2
			// |   |
			//p3---p4
			std::list<Vert*> verticesFace;
			verticesFace.push_back(p1v);
			verticesFace.push_back(p2v);
			verticesFace.push_back(p4v);
			verticesFace.push_back(p3v);
			FaceNew* newFace = createFace(verticesFace, &(edges), Reader, false);
			newFace->setName("r" + std::to_string(slice) + "f" + std::to_string(csSlice - 1));
			faces.push_back(newFace);

			p1v = p3v;
			p2v = p4v;
		}
	}
}
