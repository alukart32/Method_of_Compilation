#pragma once

#include <string>
using namespace std;

class Rule {
	// само правило
	string ruleBody;
	// есть ли символ перехода в никуда epsilon
	bool epsilon = false;
	// порядковый индекс правила 
	int index;

	void isEpsilonInRule() {
		int i = 0;
		bool flag = false;

		while (i < ruleBody.length() && !flag)
		{
			if (ruleBody[i] == 'e')
				flag = true;
			i++;
		}
	};

public:
	Rule() {};

	Rule(string new_rule): ruleBody(new_rule)
	{
		isEpsilonInRule();
	};
	
	Rule(string new_rule, int i): ruleBody(new_rule), index(i)
	{
		isEpsilonInRule();
	};

	void setRule(string tmp)
	{
		ruleBody = tmp;
	};

	void setIndex(int i) {
		index = i;
	};

	int getIndex()
	{
		return index;
	};

	string getRuleBody()
	{
		return ruleBody;
	};
	
};