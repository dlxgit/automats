#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <iterator>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

namespace
{
	struct TableData
	{
		int index;
		std::string firstTerminal;
		bool isShift;
		int nextIndex;
		bool isStack;
		bool isError;
		bool isEnd;
	};

	std::vector<TableData> ParseFile(const std::string& filename)
	{
		std::vector<TableData> data;

		std::ifstream inFile(filename);
		for (std::string line; std::getline(inFile, line);)
		{
			std::vector<std::string> splStr;
			boost::split(splStr, line, boost::is_any_of("/"));

			data.push_back(TableData{
				boost::lexical_cast<int>(splStr[0]),
				splStr[1],
				boost::lexical_cast<bool>(splStr[2]),
				boost::lexical_cast<int>(splStr[3]),
				boost::lexical_cast<bool>(splStr[4]),
				boost::lexical_cast<bool>(splStr[5]),
				boost::lexical_cast<bool>(splStr[6])
			});
		}

		return data;
	}
}

struct TableNode
{
	TableNode() = default;

	TableNode(const std::string& inStr)
	{
		std::stringstream stream(inStr);
		std::vector<std::string> splittedString
		{
			std::istream_iterator<std::string>(stream),{}
		};

		token = splittedString[0];
		i1 = stoi(splittedString[1]);
		i2 = stoi(splittedString[2]);
	}

	std::string token;
	int i1;
	int i2;
};

struct Table
{
	TableNode m_head;
	std::vector<std::vector<TableNode>> m_nodes;
};

class FileReader
{
public:

	FileReader(const std::string& filename)
	{
		ParseFileForTables(filename);
		ParseTables();
	}

	void ParseFileForTables(const std::string& filename)
	{
		std::vector<std::string> table;
		std::ifstream inFile(filename);
		if (!inFile.is_open())
		{
			std::cout << "Couldn't open file" << std::endl;
		}

		bool isParsingTable = false;

		for (std::string line; std::getline(inFile, line);)
		{
			if (line == "}}")
			{
				if (isParsingTable)
				{
					isParsingTable = false;
					m_strTables.push_back(table);
				}
				else
				{
					isParsingTable = true;
					table.clear();
				}
			}
			else
			{
				if (isParsingTable)
				{
					table.push_back(line);
				}
			}
		}
	}

	void ParseTables()
	{
		for (const auto& tableStr : m_strTables)
		{
			Table table;
			std::vector<std::vector<TableNode>> tableNodes;

			table.m_head = tableStr[0];
			table.m_nodes = ParseTableForNodes({ tableStr.begin() + 2, tableStr.end() });
			m_tables.push_back(table);
		}
	}

	std::vector<std::vector<TableNode>> ParseTableForNodes(const std::vector<std::string>& nodes)
	{
		std::vector<std::vector<TableNode>> tableNodes;
		std::vector<TableNode> currNode;

		for (const auto& node : nodes)
		{
			if (node == "")
			{
				tableNodes.push_back(currNode);
				currNode.clear();
			}
			else
			{
				currNode.push_back(TableNode{ node });
			}
		}
		tableNodes.push_back(currNode);

		return tableNodes;
	}

private:
	std::vector<std::vector<std::string>> m_strTables;
	std::vector<Table> m_tables;
};