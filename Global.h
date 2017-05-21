#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED
#include "MyEnum.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>


#define WSY_V *(this->word_sy)
#define readAWordSy() (this->wordAnalyze)->getWordSymbol(this->word_sy)
#define CreateExp Expression expression(this->wordAnalyze,&(WSY_V),this->tables,this->errors)

const int Symbol_Quantity = 39;
const int DomSize = 5;  //domestic information scale size
const int word_max_len = 21;
const int key_list_size = 13;
const int line_max_len = 200;
const int CASE_MAX_NUM = 50;
const int Str_CON_MAX = 200;
const int TAB_MAX_SIZE = 500;  //=======================
const int BTAB_MAX_SIZE = 500;
const int ATAB_MAX_SIZE = 500;
const int RTAB_MAX_SIZE = 500;
const int Pcode_MAX_SIZE = 2000;
const int STab_MAX_SIZE = Str_CON_MAX*100;
const int Stack_MAX_SIZE = 20000;

typedef char Word[word_max_len];

typedef union Union{
	int intconst;
	char charconst;
	float floatconst;
	bool boolen;
}ALLData;

typedef struct Struct1{
	Word name;
	int link;
	SYMtype syType;
	Symbol dataType;
	int mref;
	short lev;
	ALLData addr;
}Tab;
typedef struct Struct2{
	int lastSyinTab;
	int lastParainTab;
	int psize;
	int allSize;
}BTab;
typedef struct Struct3{
	int high;
	short elsize;
	int asize;
}ATab;
typedef struct Struct4{

}Rconst;
typedef struct Struct5{
	int f;
	int x;
	int y;
}Pcode;

class GlobalTool{
    public:
    static bool isLegalSingal_ch(char ch);
};

class SymbolSet
{
	private:
		Symbol symset[Symbol_Quantity];
		int len;
	public :
		SymbolSet();
		SymbolSet(Symbol sy0,Symbol sy1);
		SymbolSet(Symbol sy0,Symbol sy1,Symbol sy2);
		SymbolSet operator += (Symbol sym);
		SymbolSet operator + (Symbol sym);
		bool isInSet(Symbol sym) const;
};

const SymbolSet DataTypeSet(int_sy,char_sy,float_sy);

#endif // GLOBAL_H_INCLUDED
