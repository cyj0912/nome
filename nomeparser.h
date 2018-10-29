#pragma once

#include <string>

class Session;

class NomeParser
{
public:
	static Session* makeWithNome(std::string input);
};
