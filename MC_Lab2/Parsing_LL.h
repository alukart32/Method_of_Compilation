#pragma once

#include <iostream>
#include <stack>
#include <queue> 
#include <string>

using namespace std;

/*
Пусть грамматика языка будет хранится как строка (необходимо при работе first и follow)

Тогда таблица Table переход будет иметь вид

номер нетерминала \ номер терминала
				   |номер правила

номер терминала и нетерминала будем заранее знать enum TERM{ID DN WH END_WH STR CND ASG ST_C END_C}
												  enum NON_TERM{S, T, T`, ...}

будем их хранить в vector<string> а когда они нужны будут то переводим в их код ! аккуратней с индексацией

в Stack будут string как терминалов, так и нетерминалов



*/
class Parsing_LL {
	vector<string> RULES;

	int *Grammar;

	vector<string> FIRST;
	vector<string> FOLLOW;
	vector<string> RULES;

	// терминальные символы
	vector<string> TERMINAL;

	// нетерминальные символы
	vector<string> NON_TERMINAL;
	string non_term = "E E` T T` F";
	vector<string> TERMINAL;
	string term = "id dn wh e_wh str cnd asg st_c e_c";

	stack <string> Stack;

	// продукции
	stack <int>productionNumbers;

	// номера правил
	int Table[2][4];

	queue<string> token;

public:
	Parsing_LL() {
		token = queue<string>();
		setTerminals(term);
		setNonTerminals(non_term);
	};

	Parsing_LL(queue<string> str) : token(str) {
		setTerminals(term);
		setNonTerminals(non_term);
	};

	void setToken(queue<string> str) {
		token = str;
	};

	void translate() {
		Stack.push("$");
		// добавим входной строке знак конца
		Stack.push("E");
		// верхний символ Stack 
		string top;
		// текущий символ в входной строке
		string current;

		// индекс текущего символа в входной строке
		int index = 0;
		do {
			top = Stack.top();
			// top - терминал? то есть из { ID, STR, COND, ASG, DONE, WHILE, END_WH, ST_C, END_C, SPACE, ERR};
			if (isTerminal(top)) {
				// top == current ?
				current = token.front();
				if (top.compare(current) == 0) {
					// удаление top из Stack
					Stack.pop();

					// удаление текущего символа, так как его мы уже прошли
					token.pop();
					current = token.front();
					continue;
				}
				else {
					error();
					break;
				}
			}
			else if () {
				// удаление top из Stack
				Stack.pop();

				// поместить продукцию Y1Y2...Yk в магазин 
				// вывести правило X-> Y1Y2...Yk
			}
			else {
				error();
				break;
			}


		} while (top.compare("$") != 0); // пока Stack не пуст

		if (current.compare("$") != 0)
			error();
	}

	void error() {
		cout << "ERROR. PIDOR";
	};

	void error(string msg) {
		cout << msg << endl;
	};

	// функции для построения таблицы
	/*
	Пример работы
	   0 E  -> TE`
	   1 E` -> +TE`|q
	   2 T  -> FT`
	   3 T` -> *FT`|q
	   4 F  ->(E) | id

	   5 First(E)  = { (, id}			  // смотрим на то что у нас стоит в самом левом положении - T => надо сначала найти First(T)
	   1 First(E`) = {+, q}			  // смотрим ... и видим что самый левая продукция будет + => заносим его, далее мы видим что для другой продукции
									  // (это где e одно) там самое левое это e => заносим и его
	   4 First(T) =  { (, id}           // смотрим на то что у нас стоит в самом левом положении - F => надо сначала найти First(F)
	   2 First(T`) = { *, q}
	   3 First(F) =  { (, id}

	   */
	   
	 /*
		
		1) смотрим правило:
			a) если первый ЛЕВЫЙ элемент это терминал типа > < = := ; то добавляем
			б) если есть переход в e то тоже добаляем (желательно в конец)
		2) если составное ( E -> T E`), то необходимо запомнить, что надо вернуться к E	потом
			в некую map
						нетерминал тек. \ самый левый элемент | что зависит
							  E  		|		   T		  |
							  T 		|		   F		  |       E


			а лучше будем хранить таблицу правил и отмечать которые прошли сразу


			будем идти вниз, занося в таблицы сложно составные продукции
		3) проходим по каждому правилу
			когда дойдем до конца будем реверсивно идти по таблице чтобы найти для них { }

		
	*/
	struct first_item{
		string first;
		int index;
	};

	struct h_first_map {
		string first;
		// что зависит
		int relt;
		// индекс того нетерминала, у которого самый левый элемент непростой
		int index;
	};

	void first() {
		// используем итератор для перебора
		vector <string>v = vector<string>(NON_TERMINAL);
		int rule_amont = RULES.size();

		//// массив полученных first
		first_item *arr_fist = new first_item[rule_amont];
		//int set_first = 0;

		

		// итератор для прохода по NON_TERMINAL
		std::vector<string>::iterator it = v.begin(); 
		// временный char

		char c;

		// массив пройденных нетерминалов (их индексы = индекс в массиве, значение true - пройден нетерминал с индексом i)
		bool *arr_of_checked_rules = new bool[rule_amont];
		
	
		
		string tmp_first;
		int i = 0;
		int amountOfComposNT = 0;
		// для начала определим FIRST для быстро определяемых
		while ( i < rule_amont && it != v.end()) {
			// пункт 1
			// смотрим левый элемент

			// всё что за ::
			c = getLeftSym(it);

			// если всё ок, то можно проверить и на наличие как q, id, dn, wh, e_wh, str, cnd, asg, st_c, e_c
			if (checkLeftFactor(c)) {
				tmp_first += c;
				if (checkEnd(it).compare("") != 0)
					tmp_first += checkEnd(it);

				arr_of_checked_rules[i] = true;
				arr_fist[i].first = tmp_first;
				tmp_first = "";

			}
			else {
				amountOfComposNT++;
			}
		}

		i = 0;
		int l = 0;
		vector <string>vt = vector<string>(NON_TERMINAL);
		h_first_map *arr_h_first = new h_first_map[amountOfComposNT];


		// определим FIRST для составных
		while (amountOfComposNT !=0 && it != vt.end()) {
			// пункт 2
			// для тех кто сотавной слева элемент имеет
			if (arr_of_checked_rules[i] == false) {
				l = getLeftNonTermPos(it);
				if (l != -1) {
					// запомним индекс того правила у которого самый левый нетерминал
					arr_h_first[i].index = i;
					// запомним индекс этого нетерминала
					arr_h_first[i].relt = l;
				}
			}
		}

	}

	int getLeftNonTermPos(vector<string>::iterator it) {
		// выделим нетерминал E` до ::  E::TR или E`::YU
		string tmp;
		if (it->at(3) != ':')
			tmp += it->at(3);
		else
			tmp += it->at(4);

		vector <string>v = vector<string>(RULES);
		vector<string>::iterator t = v.begin();

		for (int i = 0; t != v.end(); ++t) {
			if (t->compare(tmp) == 0) {
				return i;
			}
			i++;
		}

		return -1;
	}

	char getLeftSym(vector<string>::iterator it) {
		char c;

		// E::+FG или E`::YH может быть правило
		if (it->at(3) != ':')
			c = it->at(3);
		else
			c = it->at(4);
		return c;
	}

	bool checkLeftFactor(char c) {
		switch (c){
		case '<':
		case '>':
		// :=
		case ':':
		case '=':
		case ';':
		case '(':
			return true;
			break;
		}
		return false;
	}

	string checkEnd(vector<string>::iterator it) {
		int i = 1;
		while (i < it->length() && it->at(i) != '|') {
			i++;
		}
		// дошли до того, что после |
		// след. эл. за |
		i++;

		switch (it->at(i)) {
		case 'q':
			return "q";
			break;
		case 'i':
		case 'd':
		case 'e':
		case 'w':
		case 's':
		case 'c':
		case 'a':
			string tmp;
			tmp += it->at(i);
			while (i < it->length()) {
				tmp += it->at(i);
				i++;
			}

			return tmp;
			break;
		}
		return "";
	}
	/*
	Пример работы
	   E  -> TE`
	   E` -> +TE`|q
	   T  -> FT`
	   T` -> *FT`|q
	   F  ->(E) | id
	   Правила

	   1) Если A - это начальный символ вообще то помещаем $
	   2) Если продукция B есть  α A или  α A β , где β переходит в e, то FOLLOW(A) = FOLLOW(B)
	   3) Если продукция B есть  α A β, то FOLLOW(A) = FIRST(β)
	   1)  FOLLOW(E) = {$}            // так как он начальный символ
	   2)  FOLLOW(E`) = FOLLOW(E) | α A β |              =>  FOLLOW(T) = FIRST(E`)
								  | + T E`|
		  !!! FOLLOW(T) = {+}	и FIRST(E`) !

	   3)  FOLLOW(T) = {+}
							| α A  β |              =>  FOLLOW(T`) = FOLLOW(T)
							| F T`   |
	   4)  FOLLOW(T`) = FOLLOW(T)
							| α A  β |              =>  FOLLOW(F) = FIRST(T`)
							| * F  T |

		   FOLLOW(F) = {*}

	   5)   FOLLOW(F) = {*}
						| α A β |              =>  FOLLOW(E) = FIRST( ) ) = )
						| ( E ) |
			!!!FOLLOW(E) = {$, )} !
		далее расмотрим те продукции где происходит переход в e

	   6) E` -> +T
						| α A β |              =>  FOLLOW(T) = FOLLOW(E`)
						| + T   |

		  !!!FOLLOW(T`) = FOLLOW(T) и FOLLOW(E`) !
	   7) T` -> *F
						| α A β |              =>  FOLLOW(F) = FOLLOW(T`)
						| * F   |
		 !!! FOLLOW(F) = {*} и FOLLOW(T`) !
		  и тогда
		FOLLOW(E) = { $, ) }
		FOLLOW(E`) = FOLLOW(E) = { $, ) }
		FOLLOW(T) = {+}	и FIRST(E`) = { +,$,) }
		FOLLOW(T`) = FOLLOW(T) =   { +,$,) }
		FOLLOW(F) = {*} и FOLLOW(T`) = {+,$,), *}
	   */
	void follow(string alpha) {
		bool continue_wh = false;
		do {

			continue_wh = false;
			for (int i = 0; i < alpha.length(); i++)
			{
				for (int i = 0; i < ; i++)
				{

				}
			}

		} while (continue_wh);
	}


	// временные set функции до правильного определения множеств TERMINAL и NON_TERMINAL
	bool isNonTerminal(string top) {
		vector <string>v = vector<string>(NON_TERMINAL);
		// используем итератор для перебора
		for (std::vector<string>::iterator it = v.begin(); it != v.end(); ++it) {
			if (it->compare(top) == 0)
				return true;
		}
		return false;
	};

	bool isTerminal(string top) {
		vector <string>v = vector<string>(TERMINAL);
		// используем итератор для перебора
		for (std::vector<string>::iterator it = v.begin(); it != v.end(); ++it) {
			if (it->compare(top) == 0)
				return true;
		}
		return false;
	};

	void setTerminals(string terminals) {
		// необходимо задать терминальные символы: 
		// size - их кол-во
		// terminals - str с терминалами, разделённые пробелом!!!

		string tmp;
		for (int i = 0; i < terminals.length(); i++)
		{
			while (terminals[i] != ' ' && i < terminals.length()) {
				tmp += terminals[i];
				i++;
			}
			TERMINAL.push_back(tmp);
			tmp = "";
		}
	}

	void setNonTerminals(string non_terminals) {
		// необходимо задать нетерминальные символы: 
		// size - их кол-во
		// terminals - str с терминалами, разделённые пробелом!!!

		string tmp;
		for (int i = 0; i < non_terminals.length(); i++)
		{
			while (non_terminals[i] != ' ' && i < non_terminals.length()) {
				tmp += non_terminals[i];
				i++;
			}
			NON_TERMINAL.push_back(tmp);
			tmp = "";
		}
	}


	int getNonTerminal(string nts) {
		int i = -1;

		vector <string>v = vector<string>(NON_TERMINAL);
		// используем итератор для перебора
		for (std::vector<string>::iterator it = v.begin(); it != v.end(); ++it) {
			if (it->compare(nts) == 0) {
				i++;
				return i;
			}
			i++;
		}
		return i;
	}

	int getTerminal(string nts) {
		int i = -1;

		vector <string>v = vector<string>(TERMINAL);
		// используем итератор для перебора
		for (std::vector<string>::iterator it = v.begin(); it != v.end(); ++it) {
			if (it->compare(nts) == 0) {
				i++;
				return i;
			}
			i++;
		}
		return i;
	}

	queue<string> getToken() {
		return token;
	};

	void printToken() {
		while (!token.empty())
		{
			string str = token.front();
			token.pop();
			cout << str << "  ";
		}
	};
};
