#include <iostream>
#include "ProgameAnalyze.h"

using namespace std;

int main()
{
	Symbol word_sy;
	Table tables;
	WordAnalyze wordAnalyze(&tables);
	Errors errors(&wordAnalyze,&word_sy);
	ProgameAnalyze progameAnalyze(&wordAnalyze, &word_sy,&tables,&errors);
	progameAnalyze.start();
    return 0;
}
