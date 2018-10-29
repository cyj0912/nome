#include "nomeparser.h"
#include "nomeFlexBison.cpp"
#include "stlFlexBison.cpp"
#include "objFlexBison.cpp"

Session* NomeParser::makeWithNome(std::string input)
{
    if(input.substr(input.find_last_of(".") + 1) == "stl") {
        StlCompiler* stlCompilerSession = new StlCompiler (input);
        return stlCompilerSession->getSession();
    } else if (input.substr(input.find_last_of(".") + 1) == "nom"){
        NOMECompiler* nomeCompilerSession = new NOMECompiler (input);
        return nomeCompilerSession->getSession();
    } else if (input.substr(input.find_last_of(".") + 1) == "obj"){
        ObjCompiler* objCompilerSession = new ObjCompiler (input);
        return objCompilerSession->getSession();
    }
	return nullptr;
}
