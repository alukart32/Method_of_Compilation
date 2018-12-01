#pragma once

using namespace std;

#include <string>
#include "Rule.h"
#include "NonTerm.h"
#include "Term.h"
#include "First.h"
#include "Mask.h"
#include "Follow.h"

class DataForTable
{
	int rules_size;
	int term_size;

	vector<Term> terms;
	vector<NonTerm> nonTerms;

	// разделитель в множествах first и follow ' ' а то это геморойно поправлять строку при другом разделителе
	vector<FIRST> first_set;
	vector<FOLLOW> follow_set;

	// функции для составления таблицы
	vector<FIRST>  findFirst(vector<Rule> rules);
	vector<FOLLOW> findFollow(vector<Rule> rules);

	string getLeftSymbol(Rule rule, int &endOf);
	bool isTerm(string s);
	bool isNonTerm(string t);
	string getSomeMoreTerm(Rule rule, int startPos);

	Mask getMask(Rule p_rule);
	int getRuleAIndex(string rule, vector<Rule> set);
	bool checkForEpsilon(Rule rule);
	string formatString(string str);

public:

	DataForTable() {};

	DataForTable(int r_size, int t_size, vector<Term> new_term, vector<NonTerm> new_nterm) :rules_size(r_size), term_size(t_size),
		terms(new_term), nonTerms(new_nterm) {};

	void setData(vector<Rule> rules);

	vector<FIRST> getFirst()
	{
		return first_set;
	}

	vector<FOLLOW> getFollow()
	{
		return follow_set;
	}
};

// передаём массив правил, так удобней чем vector
void DataForTable::setData(vector<Rule> new_rules)
{
	// создадим множества  
	first_set = findFirst(new_rules);
	follow_set = findFollow(new_rules);

};

// нахождение множество FIRST
vector<FIRST> DataForTable::findFirst(vector<Rule> p_rules) {
	vector<FIRST> first(rules_size);

	// часть первая: проход по всем правилам, для которых можно установить FIRST

	string tmp;
	// временный буфер для first
	string buffer = "";

	for (size_t i = 0; i < rules_size; i++)
	{
		// проверим символ после ::
		// получим его

		// индекс, на который оканчивается самый левый элемент
		int endLeftSymbol = 0;
		tmp = getLeftSymbol(p_rules[i], endLeftSymbol);


		if (isTerm(tmp)) {
			buffer += tmp;
			// теперь ищем другие терминалы, если возвращаемая строка не "" то дабавляем её
			tmp = getSomeMoreTerm(p_rules[i], endLeftSymbol);
			if (tmp != "")
				buffer += " " + tmp;

			first[i].setBody(buffer);
			first[i].setRuleIndex(i);
			first[i].setCreated(true);
			buffer = "";
		}
	}

	// часть вторая: проход по оставшимся правилам

	// индекс для правил, которые будем искать для определения first i-ого правила
	int j = 0;
	// создан ли i first
	bool created = false;

	string tmp_i;
	string tmp_j;

	int i = rules_size - 1;
	for (; i > -1; i--)
	{
		// проверка на то, а был ли first для правила i создан
		// если false то смотрим вниз по правилам, находим соответствующее и записываем first 
		if (!first[i].isCreate())
		{
			tmp_i = getLeftSymbol(p_rules[i], j);// передача j неважно
			// проход вниз по правилам
			for (size_t j = i + 1; j < rules_size; j++)
			{
				tmp_j = nonTerms[j].getSymbol();
				// определяем j правило это правило, которое ищем
				if (tmp_i.compare(tmp_j) == 0)
				{

					first[i].setBody(first[j].getBody());
					first[i].setRuleIndex(i);
					first[i].setCreated(true);
					break;
				}
			}
		}
	}

	return first;
};

// нахождение множество FOLLOW
vector<FOLLOW> DataForTable::findFollow(vector<Rule> p_rules)
{
	// будем использовать маску на правило alpha A beta
	/*

		если первый символ A, то FOLLOW(A)+= $

	1) если beta == 0 или beta == ..., но вправиле eсть eps(переход в никуда), то FOLLOW(A)+=FOLLOW(B)
	2) если	beta == ... и eps == 0, то FOLLOW(A)+=FIRST(beta)

	*/

	vector<FOLLOW> tmp_arr_follow(rules_size);

	Mask mask;
	// для первого символа добавляем $
	tmp_arr_follow[0].setBody("$");
	tmp_arr_follow[0].setRuleIndex(0);

	// этап 1: проход по всем правилам без перехода по eps в правилах (E:: +TE`| eps то берём сначала E:: +TE` в рассмотрение )
	for (size_t i = 0; i < rules_size; i++)
	{
		mask = getMask(p_rules[i]);

		// определим дальнейшие действия

		// если beta = 0 , то FOLLOW(A) += FOLLOW(B), B - текущее правило
		if (mask.getBeta() == "")
		{
			// запишем FOLLOW(B) в FOLLOW(A)
			// получим индекс правила  и запишем зависимость
			tmp_arr_follow[getRuleAIndex(mask.getA(), p_rules)].setReferFollow(i);
			tmp_arr_follow[i].setRuleIndex(i);
		}
		else
		{
			// 	beta == ... , FOLLOW(A)+=FIRST(beta)
			//  если beta терминал то добавляем
			if (isTerm(mask.getBeta()))
				tmp_arr_follow[getRuleAIndex(mask.getA(), p_rules)].setBody(" " + mask.getBeta());
			else
				tmp_arr_follow[getRuleAIndex(mask.getA(), p_rules)].setReferFirst(i);

			tmp_arr_follow[i].setRuleIndex(i);
		}

	}
	
	// часть 2: у тех правил, имеющие eps определим и FOLLOW(A) += FOLLOW(B)
	for (size_t i = 0; i < rules_size; i++)
	{
			// проверим на наличие eps
			if (checkForEpsilon(p_rules[i]))
			{
				mask = getMask(p_rules[i]);
				// есть eps, то FOLLOW(A) += FOLLOW(B)
				//tmp_arr_follow[getRuleAIndex(mask.getA(), p_rules)].setReferFollow(tmp_arr_follow[i].getRuleIndex());
				tmp_arr_follow[getRuleAIndex(mask.getA(), p_rules)].setReferFollow(i);
			}
	}


	// часть 3: присвоение значений
	// временный буферы
	string tmp;
	string tmp_follow;
	string s = "eps";

	for (size_t i = 0; i < rules_size; i++)
	{
		// смотрим по индексам refFollow и refFirst и по ним присваиваем значение
		if (tmp_arr_follow[i].getReferFirst() != -1)
		{
			// eps здесь уже не должно быть
			tmp = first_set[tmp_arr_follow[i].getReferFirst()].getBody();
			string::size_type j = tmp.find(s);

			if (j != string::npos)
				tmp.erase(j, s.length());

			tmp_arr_follow[i].setBody(formatString(tmp + " "));
		}

		if (tmp_arr_follow[i].getReferFollow() != -1)
		{
			tmp = tmp_arr_follow[tmp_arr_follow[i].getReferFollow()].getBody();
			string::size_type j = tmp.find(s);

			if (j != string::npos)
				tmp.erase(j, s.length());

			tmp_arr_follow[i].setBody(formatString(tmp + " "));
		}
	}
	return tmp_arr_follow;
};

//------------------------------------------------------------------------------------------------------------------

// для FIRST

string DataForTable::getLeftSymbol(Rule rule, int &index)
{
	int i = 0;
	int delimiter_size = 0;

	while (delimiter_size != 2)
	{
		if (rule.getRuleBody().at(i) == ':')
			delimiter_size++;

		if (delimiter_size != 2)
			i++;
	}

	string tmp;

	i++;
	// дошли до символа, который за ::
	// после :: если будут пробелы
	while (rule.getRuleBody().at(i) == ' ')
		i++;

	if (rule.getRuleBody().at(i) >= 'A' && rule.getRuleBody().at(i) <= 'Z')
	{
		tmp += rule.getRuleBody().at(i);
		// посмотрим следующий символ ( для случаев E`)
		i++;
		while (rule.getRuleBody().at(i) != ' ')
			tmp += rule.getRuleBody().at(i);
	}
	else
	{
		// читаем терминал
		while ((rule.getRuleBody().at(i) < 'A' || rule.getRuleBody().at(i) > 'Z') && rule.getRuleBody().at(i) != ' ')
		{
			tmp += rule.getRuleBody().at(i);
			i++;
		}
	}
	index = i;
	return tmp;
};

// является ли t терминалом
bool DataForTable::isTerm(string t)
{
	bool flag = false;

	for (size_t i = 0; i < term_size; i++)
	{
		if (terms[i].getSymbol().compare(t) == 0)
		{
			flag = true;
			break;
		}
	}
	return flag;
};

// является ли t нетерминалом
bool DataForTable::isNonTerm(string t)
{
	bool flag = false;

	for (size_t i = 0; i < rules_size; i++)
	{
		if (nonTerms[i].getSymbol().compare(t) == 0)
		{
			flag = true;
			break;
		}
	}
	return flag;
};


// находим другие терминалы в правиле
string DataForTable::getSomeMoreTerm(Rule rule, int startPos)
{
	// startPos - индекс откуда будем производить поиск
	string str = rule.getRuleBody();
	string tmp = "";
	// isClosingParenthesis чтобы выйти из первой секции правила ( :: (E)| ... | ...), то есть чтобы не считали что-то из первой секции
	bool iscp = false;
	int i = startPos;
	char c = ' ';

	// пройдём до знака после первого |
	while (rule.getRuleBody().at(i) != '|')
	{
		i++;
		if (i == rule.getRuleBody().length())
			break;
	}
	// первый символ после |
	i++;
	while (i < str.length())
	{
		c = rule.getRuleBody().at(i);
		// проходим ' '
		if (c != ' ' && c != '|')
		{
			// когда встретели что-то отличное от нетерминала
			if (c <= 'A' || c >= 'Z')
			{
				// считаем его
				while (c != ' ')
				{
					tmp += c;
					i++;

					// если достигли ко
					if (i == str.length())
						break;
					else
						c = rule.getRuleBody().at(i);
				}
				// разделитель
				tmp += " ";
			}
			else
				i++;
		}
		else i++;
	}
	return tmp;
};

//------------------------------------------------------------------------------------------------------------------

// для FOLLOW

// по маске определим что возвращать 

/*

Возможная проблема при записи не через пробелы: E) будет как одно !!!

*/
Mask DataForTable::getMask(Rule rule)
{
	int i = 0;
	int delimiter_size = 0;
	while (delimiter_size != 2)
	{
		if (rule.getRuleBody().at(i) == ':')
			delimiter_size++;

		if (delimiter_size != 2)
			i++;
	}
	// дошли ло того что справа от :: TE`

	// маска
	Mask mask;
	string tmp;

	int j = 0;
	char c = ' ';

	while (rule.getRuleBody().at(i) != '|' && i < rule.getRuleBody().length())
	{
		c = rule.getRuleBody().at(i);
		// проходим ' ' ':'
		if (c != ' ' && c != ':')
		{
			// считываем 
			while (c != ' ' && c != ':' )
			{
				tmp += c;
				i++;

				// если достигли конца
				if (i == rule.getRuleBody().length())
					break;
				else
					c = rule.getRuleBody().at(i);
				// пытаемся понять что за след. символ
				if ((c >= 'A' && c <= 'Z'))
				{	
					// если текущий является терминалом (idT или >H)
					if (isTerm(tmp))
					{
						i--;
						break;
					}
					
				}
			}
			switch (j)
			{
			case 0:
				mask.setAlpha(tmp);
				tmp = "";
				j++;
				break;
			case 1:
				mask.setA(tmp);
				tmp = "";
				j++;
				break;
			case 2:
				mask.setBeta(tmp);
				tmp = "";
				j++;
				break;
			}
			i++;
			if (i > rule.getRuleBody().length())
				break;
		}
		else
		{
			i++;
			if (i > rule.getRuleBody().length())
				break;
		}
	}
	return mask;
};

// получаем индекс правила, соответствующий нетерминалу A
int DataForTable::getRuleAIndex(string A, vector<Rule> set_rules)
{
	// поиск по всем правилам
	int index = 0;

	int j = 0;
	string tmp;
	char c = ' ';

	for (size_t i = 0; i < rules_size; i++)
	{
		c = set_rules[i].getRuleBody().at(j);
		while (c != ':' && c != ' ')
		{
			if (c != ' ')
			{
				tmp += c;
				j++;

				c = set_rules[i].getRuleBody().at(j);
				if (c == ':' || c == ' ')
					break;
			}
			j++;
		}
		if (A.compare(tmp) == 0)
		{
			index = i;
			break;
		}
		j = 0;
		tmp = "";
	}
	return index;
};

// праверяем на наличие eps в правиле
bool DataForTable::checkForEpsilon(Rule rule)
{
	string tmp;

	tmp = rule.getRuleBody();
	size_t pos = tmp.find("eps");
	if (pos != string::npos)
		return true;
	else return false;
};

string DataForTable::formatString(string str)
{
	// a  ,      c -> a , c

	string tmp;
	char c = '1';
	int space_count = 0;

	for (size_t i = 0; i < str.length(); i++)
	{
		c = str.at(i);
		if (c == ' ')
		{
			space_count++;

			if (space_count <= 1)
				tmp += c;
			else
				space_count = 0;
		}
		else
		{
			space_count = 0;
			tmp += c;
		}
	}

	return tmp;
};