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

	std::vector<Table> tables =
	{
		Table(
			{TableNode(
				GrammarSymbol(TERMINAL, "PROG"), 1, 2, GrammarSymbol(NONTERMINAL,"<PROG>"))
			},
			{
				{
					TableNode(GrammarSymbol(TERMINAL, "PROG"), 3, 2),
					TableNode(GrammarSymbol(TERMINAL, "id"), 4, 3),
					TableNode(GrammarSymbol(TERMINAL, "VAR"), 8, 4, GrammarSymbol(NONTERMINAL, "<VAR>")),
					TableNode(GrammarSymbol(TERMINAL, "begin"), 6, 5),
					TableNode(GrammarSymbol(TERMINAL, "st"), 19, 6, GrammarSymbol(NONTERMINAL, "<listst>")),
					TableNode(GrammarSymbol(TERMINAL, "END"), 0, 7) // 0 = 'NULL'
				}
			}),

		Table(
			{ TableNode(
				GrammarSymbol(TERMINAL, "VAR"), 8, 9, GrammarSymbol(NONTERMINAL,"<VAR>"))
			},
			{
				{
					TableNode(GrammarSymbol(TERMINAL, "VAR"), 10, 9),
					TableNode(GrammarSymbol(TERMINAL, "id"), 11, 10, GrammarSymbol(NONTERMINAL, "<idlist>"))

				}
			}),

		Table(
			{ TableNode(
				GrammarSymbol(TERMINAL, "id"), 11, 12, GrammarSymbol(NONTERMINAL,"<idlist>"))
			},
			{
				{
					TableNode(GrammarSymbol(TERMINAL, "id"), 13, 12),
					TableNode(GrammarSymbol(TERMINAL, ",begin"), 14, 13, GrammarSymbol(NONTERMINAL, "<A>"))

				}
			}),

		Table(
			{ TableNode(
				GrammarSymbol(TERMINAL, ","), 14, 16, GrammarSymbol(NONTERMINAL,"<A>")),
			TableNode(
				GrammarSymbol(TERMINAL, "begin"), 15, 18, GrammarSymbol(NONTERMINAL,"<A>"))
			},
			{
				{
					TableNode(GrammarSymbol(TERMINAL, ","), 17, 16),
					TableNode(GrammarSymbol(TERMINAL, "id"), 11, 17, GrammarSymbol(NONTERMINAL, "<idlist>"))

				},
				{

					TableNode(GrammarSymbol(TERMINAL, "begin"), 0, 18, GrammarSymbol(NONTERMINAL, "<E>"))

				}
			}),

		Table(
			{ TableNode(
				GrammarSymbol(TERMINAL, "st"), 19, 20, GrammarSymbol(NONTERMINAL,"<list>"))
			},
			{
				{
					TableNode(GrammarSymbol(TERMINAL, "st"), 21, 20),
					TableNode(GrammarSymbol(TERMINAL, "st, END"), 22, 21, GrammarSymbol(NONTERMINAL, "<B>"))

				}
			}),

		Table(
			{ TableNode(
				GrammarSymbol(TERMINAL, "st"), 22, 24, GrammarSymbol(NONTERMINAL,"<B>")),
			  TableNode(
				GrammarSymbol(TERMINAL, "END"), 23, 25, GrammarSymbol(NONTERMINAL,"<B>"))
			},
			{
				{
					TableNode(GrammarSymbol(TERMINAL, "st"), 19, 24, GrammarSymbol(NONTERMINAL, "<listst>"))
				},
				{
					TableNode(GrammarSymbol(TERMINAL, "END"), 0, 25, GrammarSymbol(NONTERMINAL, "<E>"))
				}
			})
	};

	return 0;
}