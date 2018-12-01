#include <string>


using namespace std;

#include "InputData.h"
#include "DataForTable.h"
#include "Lex.h"
#include "Table.h"

/*

1) Прочесть правила
2) записать их в массив
3) записать терминалы
4) записать нетерминалы
5) определить FIRST
6) определить FOLLOW
7) создать таблицу
8) parsing
 

*/

int main()
{
	InputData inputData;
	inputData.setData();

	DataForTable data = DataForTable(inputData.getRuleSize(), inputData.getTermSize(), inputData.getTerm(), inputData.getNonTerm());
	data.setData(inputData.getRules());

	Table_LL table = Table_LL(inputData.getRuleSize(), inputData.getTermSize(), 
								inputData.getRuleSize(), inputData.getTermSize(),
									inputData.getTerm(), inputData.getNonTerm());

	table.setTable(inputData.getRules());

	Lex lexer;
	lexer.readInput("");

	system("pause");
};