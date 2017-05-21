#ifndef PRODANLZFATHER_H_INCLUDED
#define PRODANLZFATHER_H_INCLUDED

#include "WordAnalyze.h"
#include "Errors.h"


class ProdAnlzFather
{
	private:

	public:
		int dx;
		Table *tables;
		Errors *errors;
		Symbol *word_sy;
		WordAnalyze *wordAnalyze;
		ProdAnlzFather(WordAnalyze *wordAnalyze, Symbol *word_sy,Table *tables, Errors *errors);
		void constDeclare();
		void varDeclare(int *dx);
};
#endif  //PRODANLZFATHER_H_INCLUDED
