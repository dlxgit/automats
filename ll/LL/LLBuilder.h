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
		//забыл зачем nonTerm = GrammarSymbol(TERMINAL, "\n"))  //вспомнил (для правых правил) - иногда просто терминал справа.
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
// 		LEFT,
// 		RIGHT
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
			//if(ta)
		}
	}
	
	//TODO: реализовать функцию возвращающую направляющее множество для нетерминала
	static std::vector<GrammarSymbol> GetFirstTerminalsFromRule(const GrammarRule & rule , const Grammar & grammar)
	{
		std::vector<GrammarSymbol> result;
		std::vector<GrammarRule> rules;
		if (rule.right[0].type == NONTERMINAL)
		{

			//.push_back(GetAllRulesWith(symbol, grammar));
		}
		else
		{

		}
	}


	Table() {};

	Table(const Grammar & grammar, const GrammarRule & rule, size_t index, Type type = LEFT)
	{

		
		//std::vector<TableNode> bot;
		std::vector<GrammarRule> rulesWithNonTerm = GetAllRulesWith(rule.left, grammar); //нашли правила с нетерминалом (пример - аксиома)

		//добавляем в левую часть каждый нетерминал найденного правила + направляющее множество
		for (auto el : rulesWithNonTerm)
		{
			left.push_back(TableNode(
				GetFirstTerminalsFromSymbol(el.right[0], grammar),
				//i1,
				//i2,
				el.left));
		}

		//для каждого элемента левой части (если несколько альтернатив правил) строим правую часть (цепочка нод с индексами для правой части правила)
		for (size_t i = 0; i < rulesWithNonTerm.size(); ++i)
		{
			right.push_back(std::vector<TableNode>());
			//fillRightPart (можно вынести в функцию!!)
			for (auto el2 : rulesWithNonTerm[i].right)
			{
				if (el2.type == TERMINAL)
				{
					right[i].push_back(TableNode(
						el2,
						//i1,
						//i2
						));
				}
				else
				{
					right[i].push_back(TableNode(
						GetFirstTerminalsFromRule(el2, grammar),
						//i1,
						//i2,
						el2));
				}
			}
		}
	}
	
	std::vector<TableNode> left;
	std::vector<std::vector<TableNode>> right;
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