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
	stack <string> Stack;
	queue<string> token;

public:
	Parsing_LL() {
		token = queue<string>();
	};

	Parsing_LL(queue<string> str): token(str) {};

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