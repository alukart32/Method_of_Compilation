#pragma once

#include <string>
using namespace std;

class FIRST {
	// сам first - разделитель '|'
	string body = "";
	// порядковый номер правила
	int rule_index;
	// индекс самого левого символа ( E:: _T_ E`): T - самый левый символ
	int reference;
	// был ли сформирован
	bool created = false;

public:
	FIRST() {};

	FIRST(string new_body, int rule_index) :body(new_body), rule_index(rule_index) {};

	FIRST(string new_body, int rule_index, int new_reference) :body(new_body), rule_index(rule_index), reference(new_reference) {};

	void setBody(string new_body)
	{
		body += new_body;
	};

	void setRuleIndex(int i) 
	{
		rule_index = i;
	};

	void setReference(int rule_index) 
	{
		reference = rule_index;
	};

	void setCreated(bool flag)
	{
		created = flag;
	};

	string getBody() 
	{
		return body;
	}

	int getRuleIndex()
	{
		return rule_index;
	}

	int getReference() 
	{
		return reference;
	}

	bool isCreate() {
		return created;
	}

};

