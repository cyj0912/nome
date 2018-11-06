#pragma once

#include <string>

class Session;

class CSceneBuilder
{
public:
	CSceneBuilder(Session* sess) : currSession(sess) {}

	static CSceneBuilder* GetSingleton();

	Session* GetSession() const
	{
		return currSession;
	}

	void SetSession(Session* s)
	{
		currSession = s;
	}

	void SimpleInstance(const std::string& name, const std::string& generator, float posX, float posY, float posZ);

private:
	Session* currSession;
};
