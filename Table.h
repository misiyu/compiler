#ifndef TABLE_H_INCLUDED
#define TABLE_H_INCLUDED
#include "Global.h"
#include "stdlib.h"
class Table
{
	private :
		Tab tables[TAB_MAX_SIZE];
		BTab btables[BTAB_MAX_SIZE];
		ATab arrtables[ATAB_MAX_SIZE];
		float rtables[RTAB_MAX_SIZE];
		char stab[STab_MAX_SIZE ];
		Pcode plist[Pcode_MAX_SIZE];
		int display[3];

		int tab_top;
		int btab_top;
		int atab_top;
		int rtab_top;
		int plist_top;
		int level;
		int slen;

	public :
		Table();
		bool insertConstToTab(Word idname,Symbol dataType,ALLData value);
		bool insertVar(Word idname,Symbol dataType,int *dx,int varsize,SYMtype symtyp,bool isPara);
		bool insertFun(Word idname,Symbol retType);
		void insertStrconst(char str[]);
		int insertFloatCin(float fl);
		bool findIdname(Word idname,int *location);
		bool findIdname1(Word idname,int *loc);
		bool findIdname0(Word idname,int *loc);
		void emitxy(int fct,int x,int y);
		Tab getTab(int loc);
		BTab getBTab(int loc);
		int getPlist_top();
		void updatePlist(int lc,int x,int y);
		void storeStringCon(char str[]);
		int getSlen();
		int getTab_top();
		char getStabch(int loc);
		void showCode();
		Pcode getPlist(int pc);
		ATab getATab(int loc);
		float getFloatcon(int loc);
};

#endif // TABLE_H_INCLUDED
