#ifndef WORDANALYZE_H_INCLUDED
#define WORDANALYZE_H_INCLUDED
#include <stdio.h>
#include "Global.h"
#include "Interpret.h"

class WordAnalyze
{
	private:
		bool errorFlag;
		bool hasMainFlag;
		char input_file_name[40];
		Word key[key_list_size];
		char SyStr[39][20];
		Symbol key_sy[key_list_size];
		int char_count;
		int line_count;
		FILE *input_file;
		char CIGWS;				//char in global WordAnalyze
		char line[line_max_len];
		int line_len;
		Word word;

		int intconstv;
		float floatconstv;
		char charconstv;
		char stringconstv[Str_CON_MAX];
		Table *tables;
		int strConLen;

		char getNextCh();
	public:
		WordAnalyze(Table *tables);
		int getLine();
		int getWordSymbol( Symbol *sy);
		int getIntconstv();
		float getFloatconstv();
		char getCharconstv();
		char *getStringconstp();
		char *getWord();
		int getStrConLen();
		int getLineCount();
		int getCharCount();
		void setErrorFlag();
		void tryToRun();
		void setHasMainFlag();
};

#endif // WORDANALYZE_H_INCLUDED
