#pragma once
#include <boost/algorithm/algorithm.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/math/constants/constants.hpp>
#include <vector>
#include <string>
#include "GrammarParser.h"
#include "LLBuilder.h"
#include <stack>


struct vec2
{
	vec2(int i1, int i2)
		:i1(i1), i2(i2)
	{};
	int i1;
	int i2;
};

struct LL1TableString
{
	LL1TableString(const std::vector<std::string> & input, bool shift, int transition, bool stack, bool error, bool end);

	int transition;
	bool error;
	bool shift;
	bool end;
	bool stack;
	std::vector<std::string> input;
};

typedef std::vector<LL1TableString> LL1Table;



struct TableRunner
{

	static void Run(std::vector<std::string> parts, std::vector<OldTable> tables)
	{
		//find first terminal

		std::vector<std::string>::iterator current = parts.begin();

		vec2 state = vec2(0, 0);

		//GrammarRule axiom = grammar[0];
		
// 		for (auto el : axiom.right)
// 		{
// 			std::vector<size_t> indexes = Table::GetFirstTerminalsFromRule(0, grammar);
// 		}
		
		
// 		for (auto el : grammar)
// 		{
// 			if (el.right[0].val == *current)
// 		}
	}


	static std::vector<std::string> Parse(const std::string & text)
	{
		std::vector<std::string> commandParts;
		boost::split(commandParts, text, boost::is_any_of(" "));
		return commandParts;
	}
	


	bool CheckInputSequence(const std::vector<std::string>& inputStr, const LL1Table & table, bool except = true);
	
	size_t GetCurrentTransition(const LL1TableString & row, size_t currentRowCount);
		
	std::stack<size_t> m_stack;
};