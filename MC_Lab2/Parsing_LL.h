#pragma once

#include <stack>
#include <queue> 
#include <string>

using namespace std;

class Parsing_LL {
	vector<string> RULES;
	vector<string> SELECT;
	vector<string> FIRST;
	vector<string> FOLLOW;

	// терминальные символы
	vector<string> TERMINAL;

	string TERM = "ID DONE WHILE END_WH STR COND ASG ST_C END_C";

	// нетерминальные символы
	vector<string> NON_TERMINAL;
	
	stack <string> Stack;

	int M[6][9];

	queue<string> token;

public:
	Parsing_LL() {
		token = queue<string>();
		setTerminals(TERM);
	};

	Parsing_LL(queue<string> str): token(str) {
		setTerminals(TERM);
	};

	void setToken(queue<string> str) {
		token = str;
	};

	void translate() {
		Stack.push("$");
		// добавим входной строке знак конца
		token.push("S");
		// верхний символ Stack 
		string X;
		// текущий символ в Stack
		string a;
		do {
			X = Stack.top();

			// X - терминал? то есть из { ID, STR, COND, ASG, DONE, WHILE, END_WH, ST_C, END_C, SPACE, ERR};
			if (isTerminal(X)) {
				// X == a ?
				a = token.front();
				if (X.compare(a) == 0) {
					// удаление X из Stack
					Stack.pop();

					// удаление текущего символа, так как его мы уже прошли
					token.pop();
					a = token.front();
				}
				else {
					error();
					break;
				}
			}
			else if(M[getNonTerminal(X)][getTerminal(X)]){

			} 
			else { 
				error();
				break;
			}


		} while (X.compare("&") != 0); // пока Stack не пуст

		if (a.compare("&") != 0)
			error();
	}

	void error() {

		
	};

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

	int getNonTerminal(string nts) {
		int i = -1;

		vector <string>v = vector<string>(NON_TERMINAL);
		// используем итератор для перебора
		for (std::vector<string>::iterator it = v.begin(); it != v.end(); ++it) {
			if (it->compare(nts) == 0) {
				i++;
				return i;
			}
			i++;
		}
		return i;
	}

	int getTerminal(string nts) {
		int i = -1;

		vector <string>v = vector<string>(TERMINAL);
		// используем итератор для перебора
		for (std::vector<string>::iterator it = v.begin(); it != v.end(); ++it) {
			if (it->compare(nts) == 0) {
				i++;
				return i;
			}
			i++;
		}
		return i;
	}

	bool isNonTerminal(string X) {
		return true;
	};

	bool isTerminal(string X) {
		vector <string>v = vector<string>(TERMINAL);
		// используем итератор для перебора
		for (std::vector<string>::iterator it = v.begin(); it != v.end(); ++it) {
			if(it->compare(X) == 0);
				return true;
		}
		return false;
	};

	void setTerminals(string terminals) {
		// необходимо задать терминальные символы: 
		// size - их кол-во
		// terminals - str с терминалами, разделённые пробелом!!!
		
		string tmp;
		for (int i = 0; i < terminals.length(); i++)
		{
			while (terminals[i] != ' ' && i < terminals.length()) {
				tmp += terminals[i];
				i++;
			}
			TERMINAL.push_back(tmp);
			tmp = "";
		}		
	}

	void setNonTerminals() {

	}
};