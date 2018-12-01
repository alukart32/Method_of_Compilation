#pragma once

#include <vector>
#include "Cell.h"
#include "Rule.h"

#include "NonTerm.h"
#include "Term.h"

#include "First.h"
#include "Mask.h"
#include "Follow.h"

/*

Таблица LL для parser LL

Состоит из ячеек, содержащие индексы правил

строка  -  нетерминал правила ( E :: TE`,  E - нетерминал правила, а TE` - само правило )
столбец -  терминал ( <, >, =, :, ;, (, ), id, wh, done, str)

находим FIRST и FOLLOW для построения таблицы
*/
class Table_LL 
{
	// размер определим по кол-ву нетерминалов (правая часть правил) и терминалов
	int rows;
	int columns;

	int rules_size;
	int term_size;

	vector<Term>     terms;
	vector<NonTerm>  nonTerms;

	Cell **table;

	void allocTable(int r, int c) {
		// объявление двумерного динамического массива на 10 элементов:
		 table = new Cell*[r]; // две строки в массиве
		for (int index = 0; index < r; index++)
			table[index] = new Cell[c]; // и пять столбцов
	};

	void deleteTable() {
		for (int index = 0; index < rows; index++)
			delete[] table[index];

		delete table;
	};


	// передаём индексы нетерминала, терминала и правила, которое будет записываться в таблицу
	void fillTableAt(NonTerm nt, Term t, Rule rule) 
	{
		table[nt.getIndex()][t.getIndex()].setRule(rule.getRuleBody());
	};

public:
	Table_LL() {};
	
	Table_LL(int r, int c, int r_size, int t_size, vector<Term> new_term, vector<NonTerm> new_nterm):rows(r), columns(c), 
	rules_size(r_size), term_size(t_size),terms(new_term), nonTerms(new_nterm){};
	
	Cell getCellAt(NonTerm nt, Term t)
	{
		return table[nt.getIndex()][t.getIndex()];
	};

	int getRows()
	{
		return rows;
	};

	int getColumns()
	{
		return columns;
	};

	// findFirst, findFollow, setTable by those sets
	// передаём массив правил
	void setTable(vector<Rule> rules);
};


// передаём вектор правил
void Table_LL::setTable(vector<Rule> rules)
{



};

