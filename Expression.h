#ifndef EXPRESSION_H_INCLUDED
#define EXPRESSION_H_INCLUDED

#include "WordAnalyze.h"
#include "FuncAnaly.h"

class Expression
{
	private :
		WordAnalyze *wordAnalyze;
		Symbol *word_sy;
		Table *tables;
		Errors *errors;
	public :
		Expression(WordAnalyze *wordAnalyze, Symbol *word_sy,Table *tables,Errors *errors);
		Symbol caculExpression();
		void conditionExpression();
		Symbol item();
		Symbol factor();
		//void selector(int idloc);
};

#endif // EXPRESSION_H_INCLUDED
