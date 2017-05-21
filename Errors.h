#ifndef ERRORS_H_INCLUDED
#define ERRORS_H_INCLUDED
#include "WordAnalyze.h"
class Errors{
	private :
		char errorTab[40][100];
		WordAnalyze *wordAnalyze;
		Symbol *word_sy;
		int trueError ;
		int warning ;
	public :
		Errors(WordAnalyze *wordAnalyze,Symbol *word_sy);
		void addError(SymbolSet *fixset, int errorNO);
		void addError(int errorNO);
};

#endif // ERRORS_H_INCLUDED
