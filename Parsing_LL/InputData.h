#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

#include "Rule.h"
#include "NonTerm.h"
#include "Term.h"

#include <vector>

class InputData
{
	vector<Rule> rules;

	vector<NonTerm> nonTerms;
	vector<Term> terms;

	queue<string> lexData; // потом можно изменить на class Token

	// кол-во правил и терминалов
	int rules_size;
	int terms_size;

	bool  err_read_rules;
	bool err_set_terms;

	vector<Rule>    readRules();
	vector<NonTerm> setNonTerm(vector<Rule> rules);
	vector<Term>    setTerm();

public:
	void setData();
	void sendLexResult(queue<string>);

	vector<Rule>		   getRules() { return rules; }
	vector<Term>	       getTerm() { return terms; }
	vector <NonTerm>	   getNonTerm() { return nonTerms; }
	queue<string>		   getLexData() { return lexData; }
	int					   getRuleSize() { return rules_size; }
	int					   getTermSize() { return terms_size; }
};

// обработчик ввода данных rules и составление nTerm, Term
void InputData::setData()
{
	rules = readRules();
	// определение nonTerm
	if (!err_read_rules)
	{
		nonTerms = setNonTerm(rules);
		terms = setTerm();
	}

	if (err_set_terms)
		cout << "ERROR. Invalid input data!!!";
};

void InputData::sendLexResult(queue<string> q)
{
	lexData =  queue<string>(q);
};

vector<Rule> InputData::readRules()
{
	// открытие файла
	//cout << "Grammar File: ";
	//string fileName;
	//cin >> fileName;

	ifstream inFile("Grammar.txt");

	if (!inFile.is_open())
	{
		cout << "File not found";
		err_read_rules = true;
	}
	else {

		// определим число правил

		string str;
		rules_size = 0;

		while (!inFile.eof()) {
			getline(inFile, str);
			rules_size++;
		}

		inFile.close();

		vector<Rule> new_rules(rules_size);

		// запишим эти правила

		inFile.open("Grammar.txt");

		// индекс правила
		int i = 0;
		while (!inFile.eof()) {
			getline(inFile, str);

			new_rules[i].setRule(str);
			new_rules[i].setIndex(i);
			i++;
		}

		return new_rules;
	}
	vector<Rule> new_rules(rules_size);
	return  new_rules;
};

// считываем у каждлгл правила всё то, что до разделителя :: 
vector<NonTerm> InputData::setNonTerm(vector<Rule> rules)
{
	vector<NonTerm> tmpNonTerm(rules_size);
	string tmp;
	for (size_t i = 0; i < rules_size; i++)
	{
		// считываем
		tmp = "";
		int j = 0;
		while (rules[i].getRuleBody().at(j) != ':' && rules[i].getRuleBody().at(j) != ' ')
		{
			tmp += rules[i].getRuleBody().at(j);
			j++;
		}

		// записываем
		tmpNonTerm[i].setSymbol(tmp);
		tmpNonTerm[i].setIndex(i);
	}

	return tmpNonTerm;
};

// определим множество терминалов вручнкю - ! индекс это позиция столбца в таблице
vector<Term> InputData::setTerm()
{

	// открытие файла
	//cout << "Term File: ";
	//string fileName;
	//cin >> fileName;

	ifstream inFile("Term.txt");

	if (!inFile.is_open())
	{
		cout << "File not found";
		err_set_terms = true;
	}
	else {

		// определим число term

		string str;
		terms_size = 0;

		while (!inFile.eof()) {
			getline(inFile, str);
			terms_size++;
		}

		inFile.close();

		vector<Term> tmpTerm(terms_size);

		// запишим эти token

		inFile.open("Term.txt");

		// индекс token
		int i = 0;
		while (!inFile.eof()) {
			getline(inFile, str);

			tmpTerm[i].setSymbol(str);
			tmpTerm[i].setIndex(i);
			i++;
		}

		return tmpTerm;
	}
	vector<Term> tmpTerm(terms_size);
	return tmpTerm;
};
