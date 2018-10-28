#ifndef NOMEPARSER_H
#define NOMEPARSER_H

#include <vector>
#include "nomeglwidget.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "newNOME/Session.h"

class NomeParser
{
public:
    NomeParser();
	Session* makeWithNome(std::string input);
};

#endif // MINISLFPARSER_H
