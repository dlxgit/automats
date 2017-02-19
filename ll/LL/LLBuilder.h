#pragma once
#include <vector>
#include <iostream>
#include "GrammarParser.h"

/*
	на примере в лекции, 11 таблица, справа <A> с индексом 14, хот€ таблиц <A> две (14,15)::? (или это одна), каким образом тогда выбираетс€ индекс? по первому? или
*/


/*что если A -> B 
			B -> a | b

*/

struct OldTableNode
{
	OldTableNode(GrammarSymbol term, size_t i1, size_t i2, GrammarSymbol nonTerm = GrammarSymbol(TERMINAL, "\n"))
	{
		//забыл зачем nonTerm = GrammarSymbol(TERMINAL, "\n"))  //вспомнил (дл€ правых правил) - иногда просто терминал справа.
		this->term = term;
		this->nonTerm = nonTerm;
		this->call_id = i1;
		this->rule_id = i2;
	}

	GrammarSymbol nonTerm;
	GrammarSymbol term;

	size_t call_id; //индекс вызванного правила, после считывани€ которого мы считываем эту запись
	size_t rule_id;
};

struct OldTable
{
	enum Type
	{
		LEFT,
		RIGHT
	};

	static size_t getRuleIndex(GrammarRule & rule, const std::vector<GrammarRule> & grammar)
	{
		for (std::vector<GrammarRule>::const_iterator it = grammar.cbegin(); it != grammar.cend(); ++it)
		{
			if (&*it == &rule)
			{
				return it - grammar.begin();
			}
		}
		return 0;
	}

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

	static size_t GetIndexOfTable(const std::vector<OldTable> & tables, const GrammarSymbol & symb)
	{
		for (size_t i = 0; i < tables.size(); ++i)
		{
			//if(ta)
		}
	}


	//TODO: реализовать функцию возвращающую (направл€ющее множество дл€ нетерминала) <- »Ќƒ≈ —џ Ё“»’ ѕ–ј¬»Ћ
	//вопрос: если в resultIndexes будут добавл€тьс€ одинаковые правила? повли€ет ли это на работу программы? если да то надо скорее всего удал€ть повторы(?)
	static std::vector<size_t> GetFirstTerminalsFromRule(size_t indexRule, const Grammar & grammar)
	{
		std::vector<GrammarSymbol> result;
		std::vector<GrammarRule> rules;

		std::vector<size_t> resultIndexes;

		//изначальный поиск правил с нужным символом(right[0])
		for (size_t i = 0; i < grammar.size(); ++i)
		{
			if (i != indexRule)
			{
				if (grammar[i].left == grammar[indexRule].right[0])
				{
					resultIndexes.push_back(i);
				}
			}
		}

		bool allTermsBeginWithTerm = false;
		while (!allTermsBeginWithTerm)
		{
			allTermsBeginWithTerm = true;
			for (size_t i = 0; i < resultIndexes.size(); ++i)
			{
				if (grammar[resultIndexes[i]].right[0].type == NONTERMINAL) //BEGINS WITH NONTERM
				{
					if (allTermsBeginWithTerm)
					{
						allTermsBeginWithTerm = false;

						resultIndexes.erase(resultIndexes.begin() + i);
						std::vector<GrammarRule> additionalRules = GetAllRulesWith(grammar[resultIndexes[i]].right[0], grammar);
						for (auto el : additionalRules)
						{
							resultIndexes.push_back(getRuleIndex(el, grammar));
						}
						break;
					}
				}
				else //BEGINS WITH TERM
				{
					//?do nothing?
				}

			}

		}
		return resultIndexes;
	}


	OldTable() {};

	OldTable(const std::vector<OldTableNode> & left, const std::vector<std::vector<OldTableNode>> & right):
		left(left), right(right)
	{
		
	}

	size_t GetFreeIndex()
	{
		
	}


	OldTable(const Grammar & grammar, const GrammarRule & rule, size_t index, Type type = LEFT)
	{

		int a = 3;

		//std::vector<TableNode> bot;
		std::vector<GrammarRule> rulesWithNonTerm = GetAllRulesWith(rule.left, grammar); //нашли правила с нетерминалом (пример - аксиома)

		//добавл€ем в левую часть каждый нетерминал найденного правила + направл€ющее множество
		for (auto el : rulesWithNonTerm)
		{
			//TODO
			/*
			left.push_back(TableNode(
				GetFirstTerminalsFromSymbol(el.right[0], grammar),
				//i1,
				//i2,
				el.left));
				*/
		}

		//дл€ каждого элемента левой части (тк может быть несколько альтернатив правил) строим правую часть (цепочка нод с индексами дл€ правой части правила)
		for (size_t i = 0; i < rulesWithNonTerm.size(); ++i)
		{
			//TODO: жалуетс€
			//right[i].push_back(std::vector<TableNode>());

			//fillRightPart (можно вынести в функцию!!)
			for (auto el2 : rulesWithNonTerm[i].right)
			{

				//TODO
/*
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
			*/

			}

		}
	}
	std::vector<OldTableNode> left;
	std::vector<std::vector<OldTableNode>> right;
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

	std::vector<OldTable> tables;
};



