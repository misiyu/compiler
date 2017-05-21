#ifndef FUNCANALY_H_INCLUDED
#define FUNCANALY_H_INCLUDED

#include "ProdAnlzFather.h"
#include "Expression.h"
typedef struct Struct7{
		int label;
		int lc;
	}CaseL;
class FuncAnaly : ProdAnlzFather
{
	private :
		Symbol fun_return_type;
		int dx;
		bool hasReturn;
	public :
		FuncAnaly(WordAnalyze *wordAnalyze,Symbol *word_sy,\
				Table *tables,Symbol return_type,int dx,Errors *errors);
		void complexStatement();
		void statementList();
		void ifStatement();
		void whileStatement();
		void caseStatement();
		void callFunStatement(int idloc);
		void becomesStatement(int idloc);
		void scanfStatement();
		void printfStatement();
		void returnStament();
		void statement();
		void switchStatement();

		bool getHasReturn();
};

#endif // FUNCANALY_H_INCLUDED
