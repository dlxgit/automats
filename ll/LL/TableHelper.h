#pragma once

#include <string>
#include "CTableRunner.h"


struct TableHelper
{

	static std::vector<std::vector<std::string>> ParseTablesForFirst(const std::vector<Table> & tables)
	{
		//std::ofstream outputFile("direction.txt");
		std::ofstream outputFile("direction.txt");

		std::vector<std::vector<std::string>> directions;
		for (size_t i = 0; i < tables.size(); ++i)
		{
			directions.push_back(std::vector<std::string>());
			for (size_t j = 0; j < tables[i].m_nodes.size(); ++j)
			{
				directions[i].push_back(tables[i].m_nodes[j][0].token);
				outputFile << tables[i].m_nodes[j][0].token;
			}
			outputFile << std::endl;
		}
		return directions;		
	}
};