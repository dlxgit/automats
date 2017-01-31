#pragma once
#include <vector>
#include <iostream>
#include <boost/algorithm/algorithm.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>


/*
	в считывании правила добавить проверку чтобы слева мог быть только нетерминал (необяз)

	
*/



enum SymbolType
{
	TERMINAL,
	NONTERMINAL
};

struct GrammarSymbol
{
	GrammarSymbol() {};

	GrammarSymbol(SymbolType type, const std::string & val)
	{
		this->type = type;
		this->val = val;
	}

// 	bool Equals(const GrammarSymbol & symb) const
// 	{
// 		return this->type == symb.type && this->val == symb.val;
// 	}

	bool operator==(const GrammarSymbol & right) const
	{
		return this->type == right.type && this->val == right.val;
	}

	SymbolType type;
	std::string val;
};


struct GrammarRule
{
	enum State
	{
		LEFT_PART,

		ARROW,

		RIGHT_PART,
		RIGHT_TERMINAL,
		RIGHT_NONTERMINAL,

		ERR
	};

	GrammarRule(const std::string & strRule)
	{
// 		std::vector<std::string> ruleParts; //do part rule on two parts (left and right)
// 		GrammarParser::Split(ruleParts, strRule, "->");
// 		this->left = ruleParts[0];
// 
// 		std::vector<std::string> rightParts;
// 		GrammarParser::Split(rightParts, ruleParts[1], " ");


		/*
		for (const auto & el : rightParts)
		{
			if(el.)
		}*/

		State state = LEFT_PART;

		std::vector<GrammarSymbol> rightSymbols;

		std::string temp;

		for (size_t i = 0; i < strRule.length(); ++i)
		{			
			switch (state)
			{
			case LEFT_PART:
				if (i == 0)
				{
					if (strRule[0] != '<')
					{
						state = ERR;
						temp.clear();
					}
				}
				else
				{
					if (strRule[i] == '>')
					{
						if (temp.empty()) 
						{
							state = ERR;
						}
						else
						{
							state = ARROW;
							this->left = GrammarSymbol(NONTERMINAL, temp);
							temp.clear();
						}
					}
					else
					{
						temp += strRule[i];
					}

				}
				break;
			case ARROW:
				if (strRule[i] != ' ')
				{
					if (strRule.substr(i, 2) == "->")
					{
						state = RIGHT_PART;
						temp.clear();
						i += 1;
					}
					else
					{
						state = ERR;
						temp.clear();
					}
				}
				break;

			case RIGHT_PART:
				if (strRule[i] != ' ')
				{
					if (strRule[i] == '<')
					{
						if (strRule.length() >= i && strRule[i + 1] == ' ')
						{
							rightSymbols.push_back(GrammarSymbol(TERMINAL, "<"));
						}
						else if (strRule.length() >= i)
						{
							state = RIGHT_NONTERMINAL;
							temp.clear();
						}
					}
					else
					{
						state = RIGHT_TERMINAL;
						temp = strRule[i];
						if (i == strRule.length() - 1)
						{
							rightSymbols.push_back(GrammarSymbol(TERMINAL, temp));
							temp.clear();
							state = RIGHT_PART;
						}
					}
				}
	
				else
				{
// 					temp.clear();
// 					state = ERR;
				}

				break;

			case RIGHT_NONTERMINAL:
				if (strRule[i] == '>')
				{
					if (temp.length() == 0)
					{
						state = ERR;
						break;
					}
					else
					{
						state = RIGHT_PART;
						rightSymbols.push_back(GrammarSymbol(NONTERMINAL, temp));
						temp.clear();
					}
				}
				else
				{
					temp += strRule[i];
				}
				break;

			case RIGHT_TERMINAL:
				if (strRule[i] == ' ')
				{
					if (!temp.empty())
					{
						if (strRule.length() >= i + 1)
						{
							rightSymbols.push_back(GrammarSymbol(TERMINAL, temp));
							temp.clear();
							state = RIGHT_PART;
						}
					}
				}
				else
				{
					temp += strRule[i];
					if (i == strRule.length() - 1)
					{
						rightSymbols.push_back(GrammarSymbol(TERMINAL, temp));
						temp.clear();
						state = RIGHT_PART;
					}
				}
				break;

			}

		}

		if (state != RIGHT_PART)
		{
			throw("Error reading rule: " + strRule);
			//Error(цепочка закончилась, хотя автомат находился в состоянии ожидании символов)
		}
		this->right = rightSymbols;
	}

	

	/*
	GrammarRule(std::string left, std::vector<RuleSymbol> right)
	{
		this->left = left;
		this->right = right;
	}*/


	GrammarSymbol left; //left non-terminal
	std::vector<GrammarSymbol> right; //right terminals/nonterminals
};

typedef std::vector<GrammarRule> Grammar;



class GrammarParser 
{
public:
	GrammarParser(std::vector<std::vector<std::string>> grammar)
	{
		this->grammar = grammar;
	}
	
	static std::vector<GrammarRule> ParseGrammarFromStrings(const std::vector<std::string> & strRules)
	{
		std::vector<GrammarRule> result;

		for (auto & rule : strRules)
		{
			result.push_back(GrammarRule(rule));
// 			std::vector<std::string> ruleParts; //do part rule on two parts (left and right)
// 			Split(ruleParts, rule, "->");
// 			
// 			std::vector<std::string> rightParts;
// 			Split(rightParts, ruleParts[1], " ");
// 			result.push_back(GrammarRule(ruleParts[0], rightParts));
		}
		return result;
	}

	static void Split(std::vector<std::string> & out, const std::string & str, const std::string & delimeter)
	{
		std::vector<std::string> vecCopy = out;
		

		boost::split(vecCopy, str, boost::is_any_of(delimeter));
		EraseEmptyElements(vecCopy);
		out = vecCopy;
	}

	static void EraseEmptyElements(std::vector<std::string> & vec)
	{
		std::vector<std::string> result;
		for (auto el : vec)
		{
			if (el != "")
			{
				result.push_back(el);
			}
		}

		vec = result;
	}

	std::vector<std::vector<std::string>> grammar;	
};