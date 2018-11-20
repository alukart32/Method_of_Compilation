#pragma once

#include <stack>
#include <queue> 
#include <string>

using namespace std;

// одно из значений action(s, a) 
enum actionOp{SHIFT, REDUCE, ACCEPT};

class Parsing_LR {
	stack <string>STACK;
	// правила для управляющей таблицы
	vector<string> RULE_TBL;
	// полученные token-ы
	queue<string> token;

public:
	Parsing_LR() {
		token = queue<string>();
		STACK = stack<string>();
		RULE_TBL = vector<string>();
	};

	Parsing_LR(queue<string> str) : token(str) {};

	Parsing_LR(queue<string> str, vector<string> vect): token(str), RULE_TBL(vect) {};

	// управляющая программа
	bool masterControlProgram() {
		// Установить ip на первый символ входной цепочки;
		int ip = 0;
		while (!token.empty())
		{
				// Пусть s – состояние на вершине магазина,
				// a – символ входной цепочки, на который указывает ip.

			// берём элемент на вершине Stack
			string s = STACK.top();
			// берём первый token в очереди
			string a = token.front();
			token.pop();

			if (action(s, a) == SHIFT)
			{
				STACK.push(a);
				STACK.push(s);// тут новое состояние
				ip++;
			}
			else if (action(s, a) == REDUCE)
			{
				//? наверно pop все token-ы образующие некоторое правило
				//  b - число пар
				int b = 1; // для сборки проекта
				for (int i = 1; i<= b ; i++)
				{
					STACK.pop();
					STACK.pop();
				}
				// Пусть s’ – состояние на вершине магазина;
				//STACK.push(A);
				//STACK.push(Goto[s’, A]);
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

	int action(string s, string a) {
		// скорее всего возвращает тип операции
		actionOp operation;

		// необходимо опнять но основе top Stack и входного token a образуется ли свёрстка




		return operation;
	};

	void setToken(queue<string> str) {
		token = str;
	};;

	queue<string> getToken() {
		return token;
	};

	void printToken() {
		while (!token.empty())
		{
			string str = token.front();
			token.pop();
			cout << str << "  ";
		}
	};

	//string getToken(int state) {
	//	switch (state)
	//	{
	//	case ID:
	//		return "ID";
	//		break;
	//	case DONE:
	//		return "DONE";
	//		break;
	//	case WHILE:
	//		return "WHILE";
	//		break;
	//	case END_WH:
	//		return "END_WH";
	//		break;
	//	case STR:
	//		return "STR";
	//		break;
	//	case COND:
	//		return "COND";
	//		break;
	//	case ASG:
	//		return "ASG";
	//		break;
	//	case ST_C:
	//		return "ST_C";
	//		break;
	//	case END_C:
	//		return "END_C";
	//		break;
	//	case END:
	//		return "END";
	//		break;

	//	}
	//};
};