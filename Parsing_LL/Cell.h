#pragma once

/*

Ячейка таблицы

*/
class Cell {
	// индекс того правила, которое будет в ячейке
	string rule_index;
public:
	Cell() {};

	Cell(string rule) : rule_index(rule) {};

	void setRule(string rule)
	{
		rule_index = rule;
	};
	string getRule()
	{
		return rule_index;
	};

};
