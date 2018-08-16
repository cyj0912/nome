//Copyright Toby Chen

#pragma once

#include "Data.h"
#include "MeshNew.h"

#include <stdexcept>

//These initializers are for the parser to keep track of temporary variables
//  and to make creating new sweeps easier
struct SweepPathInitializer
{
	ISweepPath* Path;

	void Clear()
	{
		Path = nullptr;
	}
};

struct SweepCrosssectionInitializer
{
	ISweepPath* CrossSection;
};

struct SweepInitializer
{
	SweepPathInitializer PathInit;
	std::vector<SweepCrosssectionInitializer> CrossSectionInits;

	void Clear()
	{
		PathInit.Clear();
		CrossSectionInits.clear();
	}
};

//Defines a sweep
class Sweep : public MeshNew
{
public:
	explicit Sweep(Session* session, const SweepInitializer& initializer);

	bool CheckSemantics() const;

private:
	void CalculateMesh();

	//General data
	Session* ParentSession;
	Reader* Reader;

	///The path to sweep along
	ISweepPath* Path;

	ISweepPath* CrossSection;
};
