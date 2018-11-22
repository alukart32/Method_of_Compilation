#pragma once

#include <stack>
#include <queue> 
#include <string>

using namespace std;

class Parsing_LL {
	stack <int>Stack;
	queue<int> token;

public:
	Parsing_LL() {
		token = queue<int>();
	};

	Parsing_LL(queue<int> str): token(str) {};

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

		}
	};

};