#pragma once

#include <string>
using namespace std;

/*

Родительский класс для нетерминалов и терминалов

*/

class Symbol {
	// сам токен
	string symbol;
	// порядковый номер
	int index;
public:
	Symbol() {};

	Symbol(string new_token, int i) : symbol(new_token), index(i) {};

	void setIndex(int i)
	{
		index = i;
	};

	int getIndex() {
		return index;
	}
	
	void setSymbol(string new_token) {
		symbol = new_token;
	};

	string getSymbol() {
		return symbol;
	}
};