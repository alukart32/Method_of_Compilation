#include <string>
#include <queue> 

using namespace std;

/*
	Ѕудем рассматривать входной поток символов на соответсвие по типу:
		1) id
		2) while
		3) done
		4) "("
		5) ")"
		6) "< > ="
		7) num
		*) empty
*/

// класс token
enum { ID, STR, COND, ASG, DONE, WHILE, END_WH, ST_C, END_C, SPACE, ERR, $};

class Lex {
	// хранится ввод
	string buffer;
	// хранится набор token-ов
	queue<int> tmpTokens;

	// ошибка ввода
	bool error = false;
public:
	// конструктор
	Lex() {
		buffer = string("");
		tmpTokens = queue<int>();// <string>
	}

	void readInput(string input) {
		// копирование строки
		buffer = input;
	}

	// вызов синтаксического анализа
	void lex() {
		/*
			будем получать по одному token в зависимости от послед. символов ("while" -> WH token, "whilr" -> ID token)
		*/
		int i = 0, tmp_class = 0;
		error = false;
		while (i < buffer.length() && !error)
		{
			tmp_class = getTokenClass(buffer[i]);
			switch (tmp_class)
			{
			case SPACE:
				break;
			case ID:
				i = readID(i + 1);
				break;

			case STR:
				i = readSTR(i + 1);
				break;

			case ASG:
				i = readASG(i + 1);
				break;
			case COND:
				addToken(COND);
				break;
			case ST_C:
				addToken(ST_C);
				break;
			case END_C:
				addToken(END_C);
				break;
			case END_WH:
				addToken(END_WH);
				break;
			case ERR:
				error = true;
				break;
			}
			i++;
		}
		if (!error)
			addToken(END);
		else
			errMsg();
	}

	int getTokenClass(char c) {
		if (c == ' ')
			return SPACE;

		if (isalpha(c))
			return ID;

		//if (c >= '0' && c <= '9')
		//	return NUM;

		if (c == '>' || c == '<' || c == '=')
			return COND;

		if (c == '(')
			return ST_C;

		if (c == ')')
			return END_C;

		if (c == ';')
			return END_WH;

		if (c == ':')
			return ASG;

		if (c == '"')
			return STR;

		return ERR;
	}

	int readID(int i) {
		string tmp;
		tmp += buffer[i - 1];
		while ((isalpha(buffer[i]) || isalnum(buffer[i]) || buffer[i] == '_' || buffer[i] == '@') && i < buffer.length())
		{
			tmp += buffer[i];
			i++;
		}
		// проверка почему закончился цикл
		// если причина не в том что дошли до конца а в другом
		if (i != buffer.length() - 1) {
			if (buffer[i] != ' ' && buffer[i] != '<' && buffer[i] != '>' && buffer[i] != '=')
				error = true;
		}

		if (error)
			return i;

		if (tmp.compare("done") == 0)
			addToken(DONE);
		else
			if (tmp.compare("while") == 0)
				addToken(WHILE);
			else
				addToken(ID);

		return --i;
	}

	int readSTR(int i) {
		while (buffer[i] != '"' && i < buffer.length()) {
			i++;
		}
		if (i == buffer.length() - 1) {
			if (buffer[i] != '"')
				error = true;
		}

		if (error)
			return i;

		addToken(STR);
		return i;
	}

	int readASG(int i) {
		if (buffer[i] == '=')
			addToken(ASG);
		else
			error = true;

		return i;
	}

	void addToken(int state) {
		tmpTokens.push(state);
	}

	queue<int> sendToken() {
		return tmpTokens;
	}

	bool getErrFlag() {
		return error;
	}

	void errMsg() {
		cout << "ERR" << endl;
		cout << "Current defined tokens in lex: ";
		
		while (!tmpTokens.empty())
		{
			string str = getToken(tmpTokens.front());
			tmpTokens.pop();
			cout << str << "  ";
		}
	}

	string getToken(int state) {
		switch (state)
		{
		case ID:
			return "ID";
			break;
		case DONE:
			return "DONE";
			break;
		case WHILE:
			return "WHILE";
			break;
		case END_WH:
			return "END_WH";
			break;
		case STR:
			return "STR";
			break;
		case COND:
			return "COND";
			break;
		case ASG:
			return "ASG";
			break;
		case ST_C:
			return "ST_C";
			break;
		case END_C:
			return "END_C";
			break;
		case END:
			return "END";
			break;

		}
	}
};