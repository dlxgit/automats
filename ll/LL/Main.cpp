#include "GrammarParser.h"
#include "LLBuilder.h"
#include "TableRunner.h"
#include <fstream>
#include "FileReader.h"


//TODO: при разборе в переходе Table() проверять, если индекс перехода в существующей таблице или вне ее (если нетерминал)


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
std::vector<OldTable> GetTheTables()
{
	std::vector<OldTable> res =
	{
		OldTable(
	{ OldTableNode(
		GrammarSymbol(TERMINAL, "PROG"), 1, 2, GrammarSymbol(NONTERMINAL,"<PROG>"))
	},
	{
		{
			OldTableNode(GrammarSymbol(TERMINAL, "PROG"), 3, 2),
			OldTableNode(GrammarSymbol(TERMINAL, "id"), 4, 3),
			OldTableNode(GrammarSymbol(TERMINAL, "VAR"), 8, 4, GrammarSymbol(NONTERMINAL, "<VAR>")),
			OldTableNode(GrammarSymbol(TERMINAL, "begin"), 6, 5),
			OldTableNode(GrammarSymbol(TERMINAL, "st"), 19, 6, GrammarSymbol(NONTERMINAL, "<listst>")),
			OldTableNode(GrammarSymbol(TERMINAL, "END"), 0, 7) // 0 = 'NULL'
		}
	}),

		OldTable(
	{ OldTableNode(
		GrammarSymbol(TERMINAL, "VAR"), 8, 9, GrammarSymbol(NONTERMINAL,"<VAR>"))
	},
	{
		{
			OldTableNode(GrammarSymbol(TERMINAL, "VAR"), 10, 9),
			OldTableNode(GrammarSymbol(TERMINAL, "id"), 11, 10, GrammarSymbol(NONTERMINAL, "<idlist>"))

		}
	}),

		OldTable(
	{ OldTableNode(
		GrammarSymbol(TERMINAL, "id"), 11, 12, GrammarSymbol(NONTERMINAL,"<idlist>"))
	},
	{
		{
			OldTableNode(GrammarSymbol(TERMINAL, "id"), 13, 12),
			OldTableNode(GrammarSymbol(TERMINAL, ",begin"), 14, 13, GrammarSymbol(NONTERMINAL, "<A>"))

		}
	}),

		OldTable(
	{ OldTableNode(
		GrammarSymbol(TERMINAL, ","), 14, 16, GrammarSymbol(NONTERMINAL,"<A>")),
			OldTableNode(
				GrammarSymbol(TERMINAL, "begin"), 15, 18, GrammarSymbol(NONTERMINAL,"<A>"))
	},
	{
		{
			OldTableNode(GrammarSymbol(TERMINAL, ","), 17, 16),
			OldTableNode(GrammarSymbol(TERMINAL, "id"), 11, 17, GrammarSymbol(NONTERMINAL, "<idlist>"))

		},
		{

			OldTableNode(GrammarSymbol(TERMINAL, "begin"), 0, 18, GrammarSymbol(NONTERMINAL, "<E>"))

		}
	}),

		OldTable(
	{ OldTableNode(
		GrammarSymbol(TERMINAL, "st"), 19, 20, GrammarSymbol(NONTERMINAL,"<list>"))
	},
	{
		{
			OldTableNode(GrammarSymbol(TERMINAL, "st"), 21, 20),
			OldTableNode(GrammarSymbol(TERMINAL, "st, END"), 22, 21, GrammarSymbol(NONTERMINAL, "<B>"))

		}
	}),

		OldTable(
	{ OldTableNode(
		GrammarSymbol(TERMINAL, "st"), 22, 24, GrammarSymbol(NONTERMINAL,"<B>")),
			OldTableNode(
				GrammarSymbol(TERMINAL, "END"), 23, 25, GrammarSymbol(NONTERMINAL,"<B>"))
	},
	{
		{
			OldTableNode(GrammarSymbol(TERMINAL, "st"), 19, 24, GrammarSymbol(NONTERMINAL, "<listst>"))
		},
		{
			OldTableNode(GrammarSymbol(TERMINAL, "END"), 0, 25, GrammarSymbol(NONTERMINAL, "<E>"))
		}
	})
	};
	return res;
}

void BeginProgram()
{
	std::ofstream lexerFile("D:/Automats/Tables/ll/LL/lexerProject/lexerOutput.txt");
 	lexerFile.clear();
 	lexerFile.flush();

	system("java -jar D:/Automats/Tables/ll/LL/lexerProject/out/artifacts/lexerProject_jar/lexerProject.jar D:/Automats/Tables/ll/LL/lexerProject/lexerInput.txt");
}

int main()
{
	BeginProgram();
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
	
	int ar[] = {3};
	//ar[-3];

	std::string text = "PROG Shik VAR a , b begin st END";

	std::vector<std::string> parts = TableRunner::Parse(text);
	//TableRunner::Run(parts, GetTheTables());
	//GetTheTables();
	TableRunner tableRunner;


	FileReader reader("D:/Automats/Tables/ll/LL/lexerProject/tables.txt");

	std::cout << "program has finished";
	system("pause");
	return 0;
}