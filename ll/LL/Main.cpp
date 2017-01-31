#define _SCL_SECURE_NO_WARNINGS
#include "GrammarParser.h"
#include "LLBuilder.h"


bool HasOrSymbol(const GrammarRule & rule)
{
	//std::any_of(rule.right.begin(), rule.right.end(), [])
	return true;
}


void DeleteOrRules(std::vector<GrammarRule> & grammar)
{
	for (auto & rule : grammar)
	{
		for (auto & rightSymbol : rule.right) //для каждого правого символа правила
		{
			//if(h)
		}
	}
};

/*
	TODO:
	генерация таблицы каждого правила(с индексами (слева и справа))
	
	бегунок
*/



int main()
{
	std::vector<std::string> rules =
	{
		"<PROG> -> PROG id <VAR> begin <IDLIST> END",
		"<VAR> -> VAR <idlist>",
		"<IDLIST> -> id <A>",
		"<A> -> , <IDLIST> | E",
		"<IDLIST> -> st <B>",
		"<B> -> <IDLIST> | E"
	};

	std::vector<GrammarRule> grammarRules = GrammarParser::ParseGrammarFromStrings(rules);

	GrammarSymbol symbol();

	return 0;
}