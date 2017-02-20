#pragma once
#include <vector>
#include <iostream>
#include "GrammarParser.h"

/*
	на примере в лекции, 11 таблица, справа <A> с индексом 14, хотя таблиц <A> две (14,15)::? (или это одна), каким образом тогда выбирается индекс? по первому? или
*/


/*что если A -> B 
			B -> a | b

*/

struct TableNode
{
	TableNode(GrammarSymbol term, size_t i1, size_t i2, GrammarSymbol nonTerm = GrammarSymbol(TERMINAL, "\n"))
	{
		this->term = term;
		this->nonTerm = nonTerm;
		this->call_id = i1;
		this->rule_id = i2;
	}

	GrammarSymbol nonTerm;
	GrammarSymbol term;

	size_t call_id; //индекс вызванного правила, после считывания которого мы считываем эту запись
	size_t rule_id;
};

struct Table
{
	enum Type
	{
		LEFT,
		RIGHT
	};


	static std::vector<GrammarRule> GetAllRulesWith(const GrammarSymbol & symbol, const Grammar & grammar)
	{
		std::vector<GrammarRule> result;
		
		for (auto & rule : grammar)
		{
			if (rule.left == symbol)
			{
				result.push_back(rule);
			}
		}

		return result;
	}

	static size_t GetIndexOfTable(const std::vector<Table> & tables, const GrammarSymbol & symb)
	{
		for (size_t i = 0; i < tables.size(); ++i)
		{
			if(ta)
		}
	}
	
	static std::vector<GrammarSymbol> GetFirstTerminalsFromSymbol(const GrammarSymbol & symbol, const Grammar & grammar, )
	{
		std::vector<GrammarSymbol> result;
		std::vector<GrammarRule> rules;
		if (symbol.type == NONTERMINAL)
		{

			result.push_back(GetAllRulesWith(symbol, grammar));
		}
		else
		{
			
	}


	Table() {};

	Table(const Grammar & grammar, const GrammarRule & rule, size_t index, Type type = LEFT)
	{
		this->top = TableNode(rule.left, );
		
		std::vector<TableNode> bot;


		std::vector<GrammarRule> rulesWithNonTerm = GetAllRulesWith(rule.left, grammar);

		for (auto el : rule.right)
		{
			if (el.type == TERMINAL)
				nodes.push_back(TableNode())
		}
		}
	}
	
	TableNode top;
	std::vector<TableNode> bottom;
};

class LLBuilder
{

public:

	LLBuilder() {};

	LLBuilder(const Grammar & grammar)
	{
		
	};

// 	void BuildTable(const Grammar & grammar, std::vector<Table> & tables)
// 	{
// 
// 	}

	std::vector<Table> tables;
};