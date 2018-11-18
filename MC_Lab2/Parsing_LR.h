#pragma once

#include <stack>
#include <queue> 
#include <string>

using namespace std;

// одно из значений action(s, a) 
enum actionOp{SHIFT, REDUCE, ACCEPT, ERR};

class Parsing_LR {
	stack <int>Stack;
	queue<int> token;

public:
	Parsing_LR() {
		token = queue<int>();
	};;

	Parsing_LR(queue<int> str): token(str) {};

	// управляющая программа
	bool masterControlProgram() {
		// Установить ip на первый символ входной цепочки;
		int ip = 0;
		while (!token.empty())
		{
				// Пусть s – состояние на вершине магазина,
				// a – символ входной цепочки, на который указывает ip.

			// берём элемент на вершине Stack
			int s = Stack.top();
			// берём первый token в очереди
			int a = token.front();
			token.pop();

			if (action(s, a) == SHIFT)
			{
				Stack.push(a);
				Stack.push(s);// тут новое состояние
				ip++;
			}
			else if (action(s, a) == REDUCE)
			{
				//? наверно pop все token-ы образующие некоторое правило
				//  b - число пар
				for (i = 1; i<= b ; i++)
				{
					Stack.pop();
					Stack.pop();
				}
				// Пусть s’ – состояние на вершине магазина;
				Stack.push(A);
				Stack.push(Goto[s’, A]);
				//Вывод правила(A→β);
			}
			else if (action(s, a) == ACCEPT)
			{
				return true;
			}
			else
			{
				// некое восстановление после ошибки 
				error();
			}
		}
	};

	void error() {};

	int action(int s, int a) {
		// скорее всего возвращает тип операции
		actionOp operation;

		// необходимо опнять но основе top Stack и входного token a образуется ли свёрстка




		return operation;
	};

	void setToken(queue<int> str) {
		token = str;
	};;

	queue<int> getToken() {
		return token;
	};

	void printToken() {
		while (!token.empty())
		{
			string str = getToken(token.front());
			token.pop();
			cout << str << "  ";
		}
	};

	string getToken(int state) {
		switch (state)
		{
		case ID:
			return "ID";
			break;
		case DONE:
			return "DONE";
			break;
		case WHILE:
			return "WHILE";
			break;
		case END_WH:
			return "END_WH";
			break;
		case STR:
			return "STR";
			break;
		case COND:
			return "COND";
			break;
		case ASG:
			return "ASG";
			break;
		case ST_C:
			return "ST_C";
			break;
		case END_C:
			return "END_C";
			break;
		case END:
			return "END";
			break;

		}
	};

};