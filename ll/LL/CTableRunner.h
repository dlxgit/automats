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
#include "TableHelper.h"
#include <sstream>

//когда пушим в стек, мы автоматом пушим айди токена

struct StackItem
{
	size_t val;
	bool isLast;
};

struct DirectionItem
{
	std::string item;
	size_t subIndex;
};

typedef std::vector<DirectionItem> DirectionStack;

struct TableRunner
{
	TableRunner(const std::vector<Table> & tables, const std::vector<std::string> & tokens)
		: m_tables(tables)
		, m_tokens(tokens)
	{
		m_direction = TableHelper::ParseTablesForFirst(m_tables);
	};

	DirectionStack GetDirectionStack(const std::string & rule, const std::string & token)
	{
		DirectionStack result;
		size_t tableId = getTableIndexByToken(rule);
		//m_tokens[tableId]
		for (size_t i = 0; i < m_direction[tableId].size(); ++i)
		{
			//мы нашли направляющее множество
			if (m_direction[tableId][i] == token || m_direction[tableId][i] == "E")
			{
				result = { { m_tables[tableId].m_head.token, i } };
				//indexSubtable = i;
				return result;
			}
			else if (!isTerminal(m_direction[tableId][i]))
			{
				size_t findingTableId = getTableIndexByToken(m_direction[tableId][i]);

				result = { {m_direction[tableId][i], i} };
				DirectionStack newStack = GetDirectionStack(m_tables[findingTableId].m_head.token, token);

				if (newStack.empty())
				{
					continue;
				}

				for (auto el : m_tables[getTableIndexByToken(newStack[newStack.size() - 1].item)].m_nodes)
				{
					if (el[0].token == token)
					{
						result.insert(result.end(), newStack.begin(), newStack.end());
						if (result.size() > 1 && result[result.size() - 1].item == result[result.size() - 2].item)
						{
							result.pop_back();
						}
						return result;
					}
				}
				return DirectionStack();
			}
		}	
	}

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

	//TODO: добавит функцию которая при ошибке поднимается по стеку и заходит в соседние подтаблицы, где такие же 


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

	size_t getTableIndexByToken(const std::string & token)
	{
		for (size_t i = 0; i < m_tables.size(); ++i)
		{
			if (m_tables[i].m_head.token == token)
			{
				return i;
			}
		}
		//std::cout << "LOGIC_ERR: i1 = " << i1 << std::endl;
		throw (std::logic_error("not found table"));
	}



	size_t getIndexOfNode(size_t indexTable, size_t indexSubtable, size_t indexNode)
	{
		for (size_t i = 0; i < m_tables[indexTable].m_nodes[indexSubtable].size(); ++i)
		{
			//if (m_tables[indexTable].m_nodes[indexSubtable][i].i1 == i1)
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

// 	void pushNext(size_t indexTable, size_t indexSubtable, size_t indexNode)
// 	{
// 		size_t idCurrent = getIndexOfNode(indexTable, indexSubtable, i1);
// 		if (m_tables[indexTable].m_nodes[indexSubtable].size() > idCurrent)
// 		{
// 			push(m_tables[indexTable].m_nodes[indexSubtable][idCurrent + 1].i2);
// 		}
// 	}

	void updateValuesFromStack()
	{
		for (size_t i = 0; i < m_tables.size(); ++i)
		{
			for (size_t k = 0; k < m_tables[i].m_nodes.size(); ++k)
			{
				for (size_t j = 0; j < m_tables[i].m_nodes[k].size(); ++j)
				{
					if (m_tables[i].m_nodes[k][j].i2 == m_stack.top())
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

	void pop()
	{
		//m_tables[getTableIndexByI1(m_stack.top())].m_head.token;
		if (m_stack.empty())
		{
			throw(std::exception("Success"));
		}
		if (m_stack.top() == 13)
		{
			int abc = 3;
		}
		std::cout << "Pop:\t" << m_stack.top() << " " <<  std::endl;
		m_stack.pop();	
	}

	void push(size_t val)
	{
		//std::cout << "Push:\t" << m_tables[getTableIndexByI1(m_stack.top().val)].m_head.token << std::endl;
		//std::cout << "Push: " << m_tables[getTableIndexByI1(m_stack.top().val)].m_head.token << " " << isLast << std::endl;
		m_stack.push(val);
	}

	size_t findI2ByToken(size_t indexTable, std::string token)
	{
		for (auto el : m_tables[indexTable].m_nodes)
		{
			for (auto el2 : el)
			{
				if (el2.token == token)
				{
					return el2.i2;
				}
			}
		}
		throw (std::exception("Logic_err: not found in findI2ByToken."));
	}

	bool pushDirection(DirectionStack stack)
	{
		m_tables[indexTable].m_nodes[indexSubtable][index];

		size_t startStackSize = m_stack.size();

		for (size_t i = 0; i < stack.size(); ++i)
		{
			if (m_tables[indexTable].m_nodes[indexSubtable][0].token == stack[i].item)
			{
				//заход в следующую подтаблицу
				if (m_tables[indexTable].m_nodes[indexSubtable].size() > 1)
				{
					if (i == 0)
					{
						indexTable = getTableIndexByToken(stack[i].item);
						indexSubtable = stack[i].subIndex;
						continue;
					}
					std::cout << "Push from pushDirection(): " << stack[i].item << std::endl;
					push(m_tables[indexTable].m_nodes[indexSubtable][1].i2);
				}
				
				indexTable = getTableIndexByToken(stack[i].item);
				indexSubtable = stack[i].subIndex;
				continue;
			}
		}

		if (m_stack.size() == startStackSize)
		{
			indexTable = getTableIndexByToken(stack.back().item);
			indexSubtable = stack.back().subIndex;
			index = 0;
		}
		else
		{
			indexTable = getTableIndexByToken(stack.back().item);
			indexSubtable = stack.back().subIndex;
			index = 0;
		}
		return true;
	}

	void Run()
	{
		size_t tokenID = 0;
		indexSubtable = 0;
		indexTable = 0;
		index = 0;

		while (index < m_tables[indexTable].m_nodes[indexSubtable].size() || !m_stack.empty())
		{
			if (tokenID == m_tokens.size())
			{
				throw(std::exception("Error: out of tokens"));
			}

			if (index >= m_tables[indexTable].m_nodes[indexSubtable].size())
			{
				//это значит мы считали всю цепочку => если стек не пуст -> удаляем ласт элемент и делаем continue
				if (!m_stack.empty())
				{
					updateValuesFromStack();
					pop();
				}
				//?
				continue;
			}

			std::string token = m_tokens[tokenID];

			//если мы вначале и ищем направляющее множество
			if (index == 0)
			{
				auto st = GetDirectionStack(m_tables[indexTable].m_head.token, token);
				if (st.empty())
				{
					//ошибка
					std::stringstream ss;
					ss << "Error: exprected <" << m_tables[indexTable].m_nodes[indexSubtable][index].token << ">" << " but got <" << token << "> \n";
					throw(std::exception(ss.str().c_str()));
				}
				if (m_tables[indexTable].m_head.token == st.back().item)
				{
					//то из текущего правила выводится сам терминал (без стеков)
					int abc = 3;
					indexSubtable = st.back().subIndex;
				}
				else
				{
					//заполнить стек
					pushDirection(st);
// 					size_t tempI = findI2ByToken(indexTable, m_tables[indexTable].m_nodes[indexSubtable][0].token);
// 					if (m_tables[indexTable].m_nodes[indexSubtable].size() > 1)
// 					{
// 						push(m_tables[indexTable].m_nodes[indexSubtable][1].i2);
// 					}
// 					for (auto el : st)
// 					{
// 						//tempI
// 						//push();
// 					}
					continue;
				}
				
			}
			//если мы не в начале и это нетерминал
			else if (!isTerminal(m_tables[indexTable].m_nodes[indexSubtable][index].token))
			{
				std::cout << "Push: " << m_tables[indexTable].m_nodes[indexSubtable][index].token << std::endl;
				push(m_tables[indexTable].m_nodes[indexSubtable][index + 1].i2);

				indexTable = getTableIndexByI1(m_tables[indexTable].m_nodes[indexSubtable][index].i1);
				index = 0;
				indexSubtable = 0;

				continue;

			}

			if (m_tables[indexTable].m_nodes[indexSubtable][index].token == "E")
			{
				std::cout << "READ_EPSILON in: " << m_tables[indexTable].m_head.token << std::endl;
				index++;
			}
			else if (m_tables[indexTable].m_nodes[indexSubtable][index].token == token)
			{
				std::cout << "READ_token: " << token << " in: " << m_tables[indexTable].m_head.token << std::endl;
				index++;
				++tokenID;
			}
			else
			{
				std::stringstream ss;
				ss << "Error: exprected <" << m_tables[indexTable].m_nodes[indexSubtable][index].token << ">" << " but got <" << token << "> \n";

				throw(std::exception(ss.str().c_str()));
			}

		}
		throw(std::exception("Success"));
	};

	size_t indexTable;
	size_t indexSubtable;
	size_t index;

	std::vector<Table> m_tables;
	std::vector<std::string> m_tokens;
	std::vector<std::vector<std::string>> m_direction;
	std::stack<size_t> m_stack;
	

};