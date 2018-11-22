﻿#include <iostream>
#include <string>

#include "Lex.h"
#include "Parsing_LL.h"

using namespace std;

int main() {
	/*
		1) ввод последовательности пользователя
			2) лексический анализатор -> token
			3) синтаксический анализатор получает набор token исходного ввода

			входная строка закончилась или ( далее 2) )
			программа завершилась:
				1) синтаксический анализ завершён (accepted)
				2) синтаксический анализ завершён (error)
	*/

	Lex l = Lex();
	string s = string("; as = :==>as<");//"d ; asd ;\"abc\"> while :=while=as;"

	l.readInput(s);
	l.lex();
	if (!l.getErrFlag())
	{
		Parsing_LL  parsing = Parsing_LL(l.sendToken());
		parsing.printToken();
	}

	

	cout << endl << endl;
	system("pause");
	return 0;
}