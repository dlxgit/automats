#pragma once
#include <boost/algorithm/algorithm.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/math/constants/constants.hpp>
#include <vector>
#include <string>
#include "GrammarParser.h"
#include <stack>
#include "FileReader.h"

//����� ����� � ����, �� ��������� ����� ���� ������

struct TableRunner
{
	TableRunner(const std::vector<Table> & tables, const std::vector<std::string> & tokens)
		: m_tables(tables)
		, m_tokens(tokens)
	{};


	std::vector<TableNode> getFirstNodes(std::vector<TableNode> & items, size_t iRule)
	{

		// 		std::string templ = m_tables[iRule].m_head.token;
		// 		for (auto el : items)
		// 		{
		// 			if (templ == el)
		// 			{
		// 				return std::vector<TableNode>();
		// 			}
		// 		}

		for (size_t i = 0; i < m_tables[iRule].m_nodes.size(); ++i)
		{
			if (isTerminal(m_tables[iRule].m_nodes[i][0].token))
			{
				items.push_back(m_tables[iRule].m_nodes[i][0]);
			}
			else
			{
				std::vector<TableNode> plus = getFirstNodes(items, getTableIndexByI1(m_tables[iRule].m_nodes[i][0].i1));
				for (auto el : plus)
				{
					bool has = false;
					for (auto el2 : items)
					{
						if (el.i1 == el2.i1)
						{
							has = true;
						}
					}
					if (!has)
					{
						items.push_back(el);
					}
				}
				//items.insert(items.end(), plus.begin(), plus.end());

			}

		}
		return items;
	}


	bool firstTermHaveOnlyEpsilon(size_t i, size_t j, size_t k, std::string token)
	{
		if (isTerminal(m_tables[i].m_nodes[j][k].token))
		{
			return token == m_tables[i].m_nodes[j][k].token;
		}
		else
		{
			for (size_t i = 0; i < m_tables[getTableIndexByI1(m_tables[i].m_nodes[j][k].i1)].m_nodes.size(); ++i)
			{
				//firstTermHaveOnlyEpsilon(getTableIndexByI1(m_tables[i].m_nodes[j][k].i1), );
			}

		}
	}

	//TODO: ������� ������� ������� ��� ������ ����������� �� ����� � ������� � �������� ����������, ��� ����� �� 


	std::vector<std::string> getFirstTerms(std::vector<std::string> & items, size_t iRule)
	{
		//TODO: for 6 rule does not return possible int (value>
		//if()
		
		std::string templ = m_tables[iRule].m_head.token;
		for (auto el : items)
		{
			if (templ == el)
			{
				return std::vector<std::string>();
			}
		}

		for (size_t i = 0; i < m_tables[iRule].m_nodes.size(); ++i)
		{
			if (m_tables[iRule].m_nodes[i][0].token == "<PAREN_EXPR>")
			{
				int abc = 3;
			}
			if (isTerminal(m_tables[iRule].m_nodes[i][0].token))
			{
				items.push_back(m_tables[iRule].m_nodes[i][0].token);
			}
			else
			{
				std::vector<std::string> plus = getFirstTerms(items, getTableIndexByI1(m_tables[iRule].m_nodes[i][0].i1));
				for (auto el : plus)
				{
					bool has = false;
					for (auto el2 : items)
					{
						if (el == el2)
						{
							has = true;
						}
					}
					if (!has)
					{
						items.push_back(el);
					}
				}
				//items.insert(items.end(), plus.begin(), plus.end());

			}

		}
		return items;
	}


	void DoPushStack(size_t i, size_t j, size_t k)
	{
		m_tables[i].m_nodes[j][k]
	}

	bool onlyInEpsilon(size_t iRule, std::string token)
	{
		if (iRule == 6 && token == "}")
		{
			int abc = 3;
		}

		if (token == "")
		{
			int abc = 3;
		}
		std::vector<std::string> vec = getFirstTerms(std::vector<std::string>(), iRule);
		
		for (size_t i = 0; i < vec.size(); ++i)
		{
			if (vec[i] == token)
			{

// 				for (size_t n = 0; n < m_tables[iRule].m_nodes.size(); ++n)
// 				{
// 					for (size_t z = 0; z < m_tables[iRule].m_nodes[n].size(); ++z)
// 					{
// 						if (m_tables[iRule].m_nodes[n][z].token == token)
// 						{
// // 							index = 0;
// // 							indexSubtable = n;
// // 							indexTable = iRule;
// 							return false;
// 						}
// 					}
// 				}
				auto res = getFirstNodes(std::vector<TableNode>(), iRule);
				for (auto x : res)
				{
					if (x.token == token)
					{
						 index = 0;
						 indexSubtable = 0;
						 for (size_t l = 0; l < m_tables.size(); ++l)
						 {
							 for (size_t ll = 0; ll < m_tables[l].m_nodes.size(); ++ll)
							 {
								 if (m_tables[l].m_nodes[ll][0].i2 == x.i2)
								 {
									 m_stack.push(m_tables[indexTable].m_nodes[indexSubtable][index + 1].i2);
									 index = 0;
									 indexSubtable = ll;
									 indexTable = l;
									 return false;
								 }
							 }
						 }
						 //indexTable = getTableIndexByI1(x.);
					}
				}

				return false;
			}
		}
		return true;
	}


	size_t getIndexOfTableId(size_t id)
	{
		for (size_t i = 0; i < m_tables.size(); ++i)
		{
			if (m_tables[i].m_head.i1 == id)
			{
				return i;
			}
		}
		return -1;
	}

	size_t chooseRightSubTable(size_t tableId, std::string token)
	{
		for (size_t i = 0; i < m_tables[getIndexOfTableId(tableId)].m_nodes.size(); ++i)
		{
			//if (tableId)
		}
	}

	bool isTerminal(std::string item)
	{
		return !(item[0] == '<' && item[item.size() - 1] == '>');
	}


	size_t getTableIndexByI1(size_t i1)
	{
		for (size_t i = 0; i < m_tables.size(); ++i)
		{
			if (m_tables[i].m_head.i1 == i1)
			{
				return i;
			}
		}
		std::cout << "LOGIC_ERR: i1 = " << i1 << std::endl;
		throw (std::logic_error("not found index"));
	}


	size_t getIndexOfNode(size_t indexTable, size_t indexSubtable, size_t indexNode)
	{
		for (size_t i = 0; i < m_tables[indexTable].m_nodes[indexSubtable].size(); ++i)
		{
			if (m_tables[indexTable].m_nodes[indexSubtable][i].i1 == i1)
			{
				return i;
			}
		}
		return std::string::npos;
	}

	TableNode getNextElement(size_t indexTable, size_t indexSubtable, size_t i1)
	{
		size_t idCurrent = getIndexOfNode(indexTable, indexSubtable, i1);
		if (m_tables[indexTable].m_nodes[indexSubtable].size() > idCurrent)
		{
			return m_tables[indexTable].m_nodes[indexSubtable][idCurrent];
		}
		//throw(std::invalid_argument(""))
	}

	bool hasNext(size_t indexTable, size_t indexSubtable, size_t indexNode)
	{

	}

	void pushNext(size_t indexTable, size_t indexSubtable, size_t indexNode)
	{
		size_t idCurrent = getIndexOfNode(indexTable, indexSubtable, i1);
		if (m_tables[indexTable].m_nodes[indexSubtable].size() > idCurrent)
		{
			m_stack.push(m_tables[indexTable].m_nodes[indexSubtable][idCurrent + 1].i2);
		}
	}

	void updateValuesFromStack()
	{
		size_t i2 = m_stack.top();
		for (size_t i = 0; i < m_tables.size(); ++i)
		{
			for (size_t k = 0; k < m_tables[i].m_nodes.size(); ++k)
			{
				for (size_t j = 0; j < m_tables[i].m_nodes[k].size(); ++j)
				{
					if (m_tables[i].m_nodes[k][j].i2 == i2)
					{
						index = j;
						indexSubtable = k;
						indexTable = i;
						return;
					}
				}
			}
		}
		throw(std::logic_error("logic_err"));
	}

	bool isEpsilon()
	{
		for (size_t i = 0; i < m_tables[indexTable].m_nodes.size(); ++i)
		{
			if (m_tables[indexTable].m_nodes[i][0].token == "E")
			{
				index = 1;
				indexSubtable = i;
				return true;
			}
		}
		return false;
	}

	size_t findI1OfTokenInTable(size_t tableId, std::string token)
	{
		std::vector<TableNode> vec;
		for (size_t i = 0; i < m_tables[tableId].m_nodes.size(); ++i)
		{
			for (size_t j = 0; j < m_tables[tableId].m_nodes[i].size(); ++j)
			{

			}
		}
	}

	void Run()
	{

		i1 = 0;
		size_t tokenID = 0;
		indexSubtable = 0;
		indexTable = 0;
		index = 0;

		while (index < m_tables[indexTable].m_nodes[indexSubtable].size() || !m_stack.empty())
		{
			
			//std::cout << "Entering: " << m_tables[indexTable].m_nodes[indexSubtable][index].token << std::endl;


			if (index >= m_tables[indexTable].m_nodes[indexSubtable].size())
			{
				//��� ������ �� ������� ��� ������� => ���� ���� �� ���� -> ������� ���� ������� � ������ continue
				if (!m_stack.empty())
				{
					updateValuesFromStack();
					m_stack.pop();
					continue;
				}
			}


			std::string token = m_tokens[tokenID];



			//�������� � ������ ���������� ���� �� ��������� ������� ���� ���������
			if (index == 0 && isTerminal(m_tables[indexTable].m_nodes[indexSubtable][0].token))
			{

				if (token != m_tables[indexTable].m_nodes[indexSubtable][0].token)
				{
					//�������� � ������ ����������(������ ������������ ���������)
					if (indexSubtable == m_tables[indexTable].m_nodes.size() - 1)
					{
						if (isEpsilon())
						{
							//indexSubtable++;
							continue;
						}
						else
						{
							//������ ��������� �� �����?? � ���������� ��� ������� ���� ������ ������������?
							//TODO:�������, ������� ������� ������
							throw(std::invalid_argument("�� ������� ��������� ������(���� ���������)."));
						}
					}
					indexSubtable++;
					continue;

				}			
			}
			else if (index == 0)
			{
				if (indexTable == 6 && token == "INT")
				{
					int abc = 3;
				}
				if (onlyInEpsilon(indexTable, token))
				{
					int abc = 3;
					updateValuesFromStack();
					m_stack.pop();
					continue;
				}
				else
				{
					int a = 3;
					//TODO:  �������� � ���, ��� ���� �� ������ �������, �� ����� ������� ������ ���������� � ����� � ���.

// 					m_stack.push(m_tables[indexTable].m_nodes[indexSubtable][index + 1].i2);
// 
// 					indexTable = getTableIndexByI1(m_tables[indexTable].m_nodes[indexSubtable][index].i1);
// 					index = 0;
// 					indexSubtable = 0;
					continue;
				}
			}


			//��������� ��� �������
			if (!isTerminal(m_tables[indexTable].m_nodes[indexSubtable][index].token))
			{
				//����������� ������
				if (m_tables[indexTable].m_nodes[indexSubtable].size() > index + 1)
				{
					m_stack.push(m_tables[indexTable].m_nodes[indexSubtable][index + 1].i2);

					indexTable = getTableIndexByI1(m_tables[indexTable].m_nodes[indexSubtable][index].i1);
					index = 0;
					indexSubtable = 0;

					continue;
				}
				else
				{
					//TODO: ��� ��������� ������ � �������, � ������? �� ������� � ����?
					indexTable = getTableIndexByI1(m_tables[indexTable].m_nodes[indexSubtable][index].i1);
					indexSubtable = 0;
					index = 0;
					continue;

				}

			}
			else
			{
				if (m_tables[indexTable].m_nodes[indexSubtable][index].token == token)
				{
					index++;
				}
				else
				{
					std::cout << "Error: exprected <" << m_tables[indexTable].m_nodes[indexSubtable][index].token << ">" << " but got <" << token << "> \n";
					throw(std::invalid_argument("Err"));
				}
			}

			++tokenID;
		}
	};

	size_t indexTable;
	size_t indexSubtable;
	size_t i1;
	size_t index;

	std::vector<Table> m_tables;
	std::vector<std::string> m_tokens;
	std::stack<size_t> m_stack;

};