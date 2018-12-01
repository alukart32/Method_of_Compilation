#pragma once
#include "Symbol.h"

class Term : public Symbol {
public:
	Term() {};

	Term(string new_terminal, int index) :Symbol(new_terminal, index) {};
};