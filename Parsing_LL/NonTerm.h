#pragma once

#include "Symbol.h"

class NonTerm : public Symbol {
public:
	NonTerm() {};

	NonTerm(string new_non_terminal, int index):Symbol(new_non_terminal, index) {};
};