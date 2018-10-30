#pragma once

#include <string>

class Session;

class CSceneBuilder
{
public:
	CSceneBuilder(Session* sess) : currSession(sess) {}

	void SimpleInstance(const std::string& name, const std::string& generator, float posX, float posY, float posZ);

private:
	Session* currSession;
};
