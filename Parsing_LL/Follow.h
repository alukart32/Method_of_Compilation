#pragma once
#pragma once

#include <string>
using namespace std;

class FOLLOW {
	// сам first - разделитель '|'
	string body = "";
	// порядковый номер правила
	int rule_index = -1;
	// индекс того, где Follow(next) = Follow(curr)
	int referFollow = -1;
	// Follow(next) = First(curr)
	int referFirst = -1;
	// был ли сформирован
	bool created = false;

public:
	FOLLOW() {};

	FOLLOW(string new_body, int rule_index) :body(new_body), rule_index(rule_index) {};

	FOLLOW(string new_body, int rule_index, int new_reference) :body(new_body), rule_index(rule_index), referFollow(new_reference) {};

	void setBody(string new_body)
	{
		body += new_body;
	};

	void setRuleIndex(int i)
	{
		rule_index = i;
	};

	void setReferFollow(int rule_index_follow)
	{
		referFollow = rule_index_follow;
	};


	void setReferFirst(int rule_index_first)
	{
		referFirst = rule_index_first;
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

	int getReferFollow()
	{
		return referFollow;
	}

	int getReferFirst()
	{
		return referFirst;
	}

	bool isCreate() {
		return created;
	}
};