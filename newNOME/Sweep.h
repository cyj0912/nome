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
	bool Closed = false;
	bool MinTorsion = false;

	std::string AzimuthExpr;
	std::string TwistExpr;

	void Clear()
	{
		PathInit.Clear();
		CrossSectionInits.clear();
		Closed = false;
        MinTorsion = false;
		AzimuthExpr = std::string();
		TwistExpr = std::string();
	}
};

//Defines a sweep
class Sweep : public MeshNew
{
public:
	explicit Sweep(Session* session, const SweepInitializer& initializer);

	void Update();

	bool CheckSemantics() const;

private:
	void CalculateMesh();

	//General data
	Session* ParentSession;
	Reader* Reader;

	///The path to sweep along
	ISweepPath* Path;

	ISweepPath* CrossSection;

	bool bIsClosed = false;
	bool bMinTorsion = false;

	float Azimuth = 0.0f;
    std::string AzimuthExpr;
    float Twist = 0.0f;
    std::string TwistExpr;
};
