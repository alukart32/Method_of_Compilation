#include <iostream>
#include <string>

#include "Lex.h"

using namespace std;

int main() {
	/*
		1) ввод последовательности пользователя
			2) лексический анализатор -> token
			3) синтаксический анализатор получает token
			   запрос на след. token -> 2)

			входная строка закончилась или ( далее 2) )
			программа завершилась:
				1) синтаксический анализ завершён (accepted)
				2) синтаксический анализ завершён (error)
	*/

	Lex l = Lex();

	string s = string("d ; asd ;\"abc\"> while :=while=as;");

	l.readInput(s);
	l.lex();



	cout << endl;
	system("pause");
	return 0;
}