#ifndef PROGAME_H_INCLUDED
#define PROGAME_H_INCLUDED

#include "ProdAnlzFather.h"
#include "FuncAnaly.h"

class ProgameAnalyze:ProdAnlzFather
{
	private:
	public:
		ProgameAnalyze(WordAnalyze *wordAnalyze, Symbol *word_sy,Table *tables,Errors *errors);
		void start();
		void funcDeclare(Word idname,Symbol return_type);
		void funcPara(int *dx);
		void GlobalVarDeclare(Symbol ident_type,Word idname,int *dx);
};

#endif // PROGAME_H_INCLUDED
