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

struct TableRunner
{
	TableRunner(const std::vector<Table> & tables, const std::vector<std::string> & tokens)
		: m_tables(tables)
		, m_tokens(tokens)
	{};


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

	void Run()
	{

		i1 = 0;
		size_t tokenID = 0;
		indexSubtable = 0;
		indexTable = 0;
		index = 0;

		while (index < m_tables[indexTable].m_nodes[indexSubtable].size() || !m_stack.empty())
		{
			if (index >= m_tables[indexTable].m_nodes[indexSubtable].size())
			{
				//это значит мы считали всю цепочку => если стек не пуст -> удаляем ласт элемент и делаем continue
				if (!m_stack.empty())
				{
					updateValuesFromStack();
					m_stack.pop();
					continue;
				}
			}


			std::string token = m_tokens[tokenID];
			if (token == "}")
			{
				int abc = 3;
			}
			if (tokenID == 6)
			{
				int abc = 3;
			}

			//переходу к другой подтаблице пока не достигнем нужного напр множества
			if (index == 0 && isTerminal(m_tables[indexTable].m_nodes[indexSubtable][0].token))
			{
				if (token != m_tables[indexTable].m_nodes[indexSubtable][0].token)
				{
					//переходу к другой подтаблице(другое направляющее множество)
					if (indexSubtable == m_tables[indexTable].m_nodes.size() - 1)
					{
						if (isEpsilon())
						{
							//indexSubtable++;
							continue;
						}
						else
						{
							//TODO:функция, которая выводит ошибку
							throw(std::invalid_argument("Не получен ожидаемый символ(напр множество)."));
						}
					}
					indexSubtable++;
					continue;

				}
				
			}


			//считываем тип символа
			if (!isTerminal(m_tables[indexTable].m_nodes[indexSubtable][index].token))
			{
				if (m_tables[indexTable].m_nodes[indexSubtable].size() >= index)
				{
					m_stack.push(m_tables[indexTable].m_nodes[indexSubtable][index + 1].i2);

					indexTable = getTableIndexByI1(m_tables[indexTable].m_nodes[indexSubtable][index].i1);
					index = 0;
					indexSubtable = 0;

					continue;
				}
				else
				{
					//TODO: это последний символ в таблице, а значит? не заносим в стек?
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