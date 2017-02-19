#pragma once
#include <vector>
#include <string>


struct TableNode
{
	std::string token;
	int i1;
	int i2;
};


class Table
{


	std::vector<TableNode> m_nodes;
};