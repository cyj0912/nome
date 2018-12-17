#pragma once

#include <string>

//An so infinitely ugly solution to the user-defined generator problem

class CMacroExpander
{
public:
    std::string ExpandAll(const std::string& input);
};
