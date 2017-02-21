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

//когда пушим в стек, мы автоматом пушим айди токена

struct StackItem
{
	size_t val;
	bool isLast;
};

struct TableRunner
{
	TableRunner(const std::vector<Table> & tables, const std::vector<std::string> & tokens)
		: m_tables(tables)
		, m_tokens(tokens)
	{
		m_direction = TableHelper::ParseTablesForFirst(m_tables);
	};

	std::vector<std::string> GetDirectionStack(std::string rule, std::string token)
	{
		std::vector<std::string> result;
		size_t tableId = getTableIndexByToken(rule);
		//m_tokens[tableId]
		for (size_t i = 0; i < m_direction[tableId].size(); ++i)
		{
			//мы нашли направляющее множество
			if (m_direction[tableId][i] == token || m_direction[tableId][i] == "E")
			{
				result = { m_tables[tableId].m_head.token};
				indexSubtable = i;
				return result;
			}
			else if (!isTerminal(m_direction[tableId][i]))
			{
				size_t findingTableId = getTableIndexByToken(m_direction[tableId][i]);

				result = { m_direction[tableId][i] };
				std::vector<std::string> newStack = GetDirectionStack(m_tables[findingTableId].m_head.token, token);

				if (newStack.empty())
				{
					continue;
				}

				for (auto el : m_tables[getTableIndexByToken(newStack[newStack.size() - 1])].m_nodes)
				{
					if (el[0].token == token)
					{
						result.insert(result.end(), newStack.begin(), newStack.end());
						if (result.size() > 1 && result[result.size() - 1] == result[result.size() - 2])
						{
							result.pop_back();
						}
						return result;
					}
				}
				return std::vector<std::string>();
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


	void DoPushStack(size_t i, size_t j, size_t k)
	{
		//m_tables[i].m_nodes[j][k]
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
// 									 std::cout << "Push: " << m_tables[indexTable].m_nodes[indexSubtable][index].token << std::endl;
// 									 push(m_tables[indexTable].m_nodes[indexSubtable][index + 1].i2);
// 									 index = 0;
// 									 indexSubtable = ll;
// 									 indexTable = l;

									 if (m_tables[indexTable].m_nodes[indexSubtable].size() > index + 1)
									 {
										 std::cout << "Push: " << m_tables[indexTable].m_nodes[indexSubtable][index].token << std::endl;
										 push(m_tables[indexTable].m_nodes[indexSubtable][index + 1].i2);
										 index = 0;
										 indexSubtable = 0;
										 indexTable = getTableIndexByI1(m_tables[indexTable].m_nodes[indexSubtable][index].i1);
									 }
									 else
									 {
										 std::cout << "Push: 0 " << m_tables[indexTable].m_nodes[indexSubtable][index].token << std::endl;
										 index = 0;
										 indexSubtable = 0;
										 indexTable = getTableIndexByI1(m_tables[indexTable].m_nodes[indexSubtable][index].i1);
										 push(m_tables[indexTable].m_nodes[indexSubtable][index].i2, true);
									 }
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
		size_t i2 = m_stack.top().val;
		if (m_stack.top().isLast)
		{
			return;
		}

		if (m_stack.top().isLast)
		{
			int abc = 3;
		}
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

	void pop()
	{
		//m_tables[getTableIndexByI1(m_stack.top())].m_head.token;
		if (m_stack.empty())
		{
			throw(std::exception("Success"));
		}
		if (m_stack.top().val == 13)
		{
			int abc = 3;
		}
		std::cout << "Pop:\t" << m_stack.top().val << " " << m_stack.top().isLast <<  std::endl;
		m_stack.pop();
		
	}

	void push(size_t val, bool isLast = false)
	{
		//std::cout << "Push:\t" << m_tables[getTableIndexByI1(m_stack.top().val)].m_head.token << std::endl;
		//std::cout << "Push: " << m_tables[getTableIndexByI1(m_stack.top().val)].m_head.token << " " << isLast << std::endl;
		std::cout << "push [isLast]: " << isLast << std::endl;
		m_stack.push({ val, isLast });
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
			if (tokenID == m_tokens.size())
			{
				throw(std::exception("Error: out of tokens"));
			}
			//std::cout << "Entering: " << m_tables[indexTable].m_nodes[indexSubtable][index].token << std::endl;


			if (index >= m_tables[indexTable].m_nodes[indexSubtable].size())
			{
				//это значит мы считали всю цепочку => если стек не пуст -> удаляем ласт элемент и делаем continue
				if (!m_stack.empty())
				{
					//std::cout << "Pop"
					

					updateValuesFromStack();
					pop();
					//index++;
				}
				else
				{
					updateValuesFromStack();
					pop();
				}
				//m_tokensStack.pop();
				continue;

			}

			std::string token = m_tokens[tokenID];
			if (tokenID == 4)
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
							if (m_stack.empty())
							{
								throw(std::invalid_argument("Error: terminal unmatched or stack is out."));
							}
							else
							{
								if (m_stack.top().val == 0)
								{
									//while (m_stack.top() == 0)
									{
										pop();
									}

									updateValuesFromStack();
								}
								else
								{
									updateValuesFromStack();
									m_stack.pop();
								}
							}
							//должны подняться по стеку?? и посмотреть для таблицы выше другую альтернативу?
							//TODO:функция, которая выводит ошибку
							//throw(std::invalid_argument("Не получен ожидаемый символ(напр множество)."));
						}
					}
					indexSubtable++;
					continue;

				}			
			}
			else if (index == 0)
			{
			
				if (onlyInEpsilon(indexTable, token))
				{
					if (token == ";")
					{
						int abc = 3;
					}
					int abc = 3;
					if (m_stack.top().val == 0)
					{

							pop();
						//pop();
						
						updateValuesFromStack();

						if (index == m_tables[indexTable].m_nodes[indexSubtable].size() - 1)
						{
							updateValuesFromStack();
							pop();
						}
					}
					else
					{
						updateValuesFromStack();
						pop();

					}
					continue;
				}
				else
				{
					int a = 3;
					//TODO:  проблема в том, что если не только эпсилон, то нужно выбрать нужную подтаблицу и зайти в нее.

// 					m_stack.push(m_tables[indexTable].m_nodes[indexSubtable][index + 1].i2);
// 
// 					indexTable = getTableIndexByI1(m_tables[indexTable].m_nodes[indexSubtable][index].i1);
// 					index = 0;
// 					indexSubtable = 0;
					continue;
				}
			}

			if (tokenID == 3)
			{
				int abc = 3;
			}


			//считываем тип символа
			if (!isTerminal(m_tables[indexTable].m_nodes[indexSubtable][index].token))
			{
				//непоследний символ
				if (m_tables[indexTable].m_nodes[indexSubtable].size() > index + 1)
				{
					//m_tokensStack.push(tokenID);

					std::cout << "Push: " << m_tables[indexTable].m_nodes[indexSubtable][index].token << std::endl;
					push(m_tables[indexTable].m_nodes[indexSubtable][index + 1].i2);

					indexTable = getTableIndexByI1(m_tables[indexTable].m_nodes[indexSubtable][index].i1);
					index = 0;
					indexSubtable = 0;

					continue;
				}
				else
				{
					std::cout << "Push: 0 " << m_tables[indexTable].m_nodes[indexSubtable][index].token << std::endl;
					push(m_tables[indexTable].m_nodes[indexSubtable][index + 1].i2, true);
					//TODO: это последний символ в таблице, а значит? не заносим в стек?
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
					if (token == ";")
					{
						int abc = 3;
					}
					std::cout << "READ_token: " << token << " in: " << m_tables[indexTable].m_head.token << std::endl;
					index++;
				}
				else
				{
					if (!m_stack.empty())
					{
						pop();
						//m_tokensStack.top();
						continue;
						
					}
					else
					{
						//std::cout << "Error: exprected <" << m_tables[indexTable].m_nodes[indexSubtable][index].token << ">" << " but got <" << token << "> \n";
#include <sstream>
						std::stringstream ss;
						ss << "Error: exprected <" << m_tables[indexTable].m_nodes[indexSubtable][index].token << ">" << " but got <" << token << "> \n";

						throw(std::exception(ss.str().c_str()));
					}
				}
			}

			++tokenID;
		}
		throw(std::exception("Success"));
	};

	size_t indexTable;
	size_t indexSubtable;
	size_t i1;
	size_t index;

	std::vector<Table> m_tables;
	std::vector<std::string> m_tokens;
	std::vector<std::vector<std::string>> m_direction;
	std::stack<size_t> m_tokensStack;
	std::stack<StackItem> m_stack;
	

};