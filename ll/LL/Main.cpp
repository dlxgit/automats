#include "GrammarParser.h"
#include "LLBuilder.h"
#include "TableRunner.h"
#include <fstream>
#include "FileReader.h"


//TODO: ��� ������� � �������� Table() ���������, ���� ������ �������� � ������������ ������� ��� ��� �� (���� ����������)


bool HasOrSymbol(const GrammarRule & rule)
{
	//std::any_of(rule.right.begin(), rule.right.end(), [])
	return true;
}


void DeleteOrRules(std::vector<GrammarRule> & grammar)
{
	for (auto & rule : grammar)
	{
		for (auto & rightSymbol : rule.right) //��� ������� ������� ������� �������
		{
			//if(h)
		}
	}
};

/*
	TODO:
	��������� ������� ������� �������(� ��������� (����� � ������))
	
	�������
*/

void BeginProgram(const std::string & fileName)
{
	std::ofstream lexerFile("D:/Automats/Tables/ll/LL/lexerProject/lexerOutput.txt");
 	lexerFile.clear();
 	lexerFile.flush();

	std::string cmd = std::string("java -jar D:/Automats/Tables/ll/LL/lexerProject/out/artifacts/lexerProject_jar/lexerProject.jar D:/Automats/Tables/ll/LL/lexerProject/") + fileName;
	system(cmd.c_str());
}

int main()
{
	BeginProgram("lexerInput1.txt");
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

	//std::vector<std::string> parts = TableRunner::Parse(text);
	//TableRunner::Run(parts, GetTheTables());
	//GetTheTables();

	TableRunner tableRunner(FileReader("D:/Automats/Tables/ll/LL/lexerProject/tables.txt").GetTables(), FileReader::ReadTokens());
	tableRunner.Run();


	std::cout << "program has finished";
	system("pause");
	return 0;
}