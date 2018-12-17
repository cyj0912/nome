#include "MacroExpander.h"
#include <boost/tokenizer.hpp>
#include <boost/regex.hpp>
#include <iostream>
#include <vector>
#include <map>

class CMacroDefinition
{
public:
	CMacroDefinition(const std::string& source)
	{
		typedef boost::tokenizer<boost::char_separator<char>> tokenizer;
		boost::char_separator<char> sep{ " ", "()" };
		tokenizer tok{ source, sep };
		int state = 0;
		for (auto iter = tok.begin(); iter != tok.end(); ++iter)
		{
			if (state == 0)
			{
				if (*iter != "MACRO")
					throw std::runtime_error("Macro format error, MACRO expected");
				state = 1;
			}
			else if (state == 1)
			{
				Name = *iter;
				state = 2;
			}
			else if (state == 2)
			{
				if (*iter != "(")
					throw std::runtime_error("Left paren expected");
				state = 3;
			}
			else if (state == 3)
			{
				if (*iter == ")")
				{
					Body = std::string(iter.base(), source.end());
					break;
				}
				else
					Params.push_back(*iter);
			}
		}

		auto endmacroOff = Body.find("ENDMACRO", 0);
		Body = Body.substr(0, endmacroOff);
	}

	std::string SubstWith(const std::string& expandSource)
	{
		std::vector<std::string> args;
		typedef boost::tokenizer<boost::char_separator<char>> tokenizer;
		boost::char_separator<char> sep{ " ", "()" };
		tokenizer tok{ expandSource, sep };
		auto iter = tok.begin(); //EXPAND
		++iter; //Name
		++iter; //(
		++iter; //  first arg
		while (*iter != ")" && iter != tok.end())
		{
			args.push_back(*iter);
			++iter;
		}

		if (args.size() != Params.size())
			throw std::runtime_error("Macro expansion parameter number mismatch");

		std::string result = Body;
		for (size_t i = 0; i < Params.size(); i++)
		{
			size_t pos;
			while ((pos = result.find(Params[i])) != std::string::npos)
			{
				result.replace(pos, Params[i].size(), args[i]);
			}
		}
		return result;
	}

	std::string Name;
private:
	std::string Body;
	std::vector<std::string> Params;
};

std::string CMacroExpander::ExpandAll(const std::string& input)
{
	std::map<std::string, CMacroDefinition> macroTable;

	boost::regex macroDefExpr{ "MACRO.*?ENDMACRO" };
	boost::smatch match;
	auto start = input.begin();
	auto end = input.end();
	boost::match_flag_type flags = boost::match_default;
	while (boost::regex_search(start, end, match, macroDefExpr, flags))
	{
		CMacroDefinition def{ std::string(match[0].first, match[0].second) };
		macroTable.insert({ def.Name, def });
		start = match[0].second;
		flags |= boost::match_prev_avail;
		flags |= boost::match_not_bob;
	}

	std::string result = input;
	boost::regex macroExpandExpr{ "EXPAND.*?ENDEXPAND" };
	start = result.begin();
	end = result.end();
	flags = boost::match_default;
	while (boost::regex_search(start, end, match, macroExpandExpr, flags))
	{
		typedef boost::tokenizer<boost::char_separator<char>> tokenizer;

		//Figure out which macro
		std::string expandSource = std::string(match[0].first, match[0].second);
		boost::char_separator<char> sep{ " ", "()" };
		tokenizer tok{ expandSource, sep };
		auto tkIter = tok.begin();
		++tkIter;
		std::string macroName = *tkIter;

		auto defIter = macroTable.find(macroName);
		if (defIter == macroTable.end())
			throw std::runtime_error("Unable to find macro");
		result = std::string(result.cbegin(), match[0].first) + defIter->second.SubstWith(expandSource) + std::string(match[0].second, result.cend());
		start = result.begin();
		end = result.end();
		//flags |= boost::match_prev_avail;
		//flags |= boost::match_not_bob;
	}

	return result;
}
