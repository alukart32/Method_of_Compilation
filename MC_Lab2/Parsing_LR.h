#pragma once

#include <stack>
#include <string>

using namespace std;

class Parsing_LR {
	stack <string>Stack;
	string token;

public:
	Parsing_LR() {
		token = "";
	};

	Parsing_LR(string str): token(str) {};














	void setToken(string str) {
		token = str;
	};

	string getToken() {
		return token;
	}
};