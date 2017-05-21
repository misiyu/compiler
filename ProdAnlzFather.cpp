#include "ProdAnlzFather.h"

ProdAnlzFather::ProdAnlzFather(WordAnalyze *wordAnalyze, Symbol *word_sy,Table *tables,Errors *errors)
{
	this->wordAnalyze = wordAnalyze;
	this->word_sy = word_sy;
	this->dx = DomSize;
	this->tables = tables;
	this->errors = errors;
}
void ProdAnlzFather::constDeclare()
{
	SymbolSet fixset(const_sy,semicolon,comma);
	while(WSY_V == const_sy)
	{
		readAWordSy(); //read int, char or float
		Symbol contyp;
		Word idname;
		ALLData value;
		if(!DataTypeSet.isInSet(WSY_V))
		{
			this->errors->addError(&fixset,2);
			if(WSY_V == const_sy)
				continue;
			else if(WSY_V == semicolon)
			{
				readAWordSy();
				return;
			}
		}
		contyp =  WSY_V;
		do{
			readAWordSy();  //read ident
			if(WSY_V != ident)
			{
				(this->errors)->addError(&fixset,3);
				if(WSY_V == const_sy)
					break;
				else if(WSY_V == semicolon)
				{
					readAWordSy();
					return;
				}
				else if(WSY_V == comma)
				{
					continue;
				}
			}
			strcpy(idname,(this->wordAnalyze)->getWord());
			int temp;
			if((this->tables)->findIdname1(idname,&temp))
			{
			    printf("%s ",idname);
				(this->errors)->addError(&fixset,24);
				if(WSY_V == const_sy)
					break;
				else if(WSY_V == semicolon)
				{
					readAWordSy();
					return;
				}
				else if(WSY_V == comma)
				{
					continue;
				}
			}
			readAWordSy();  //read =
			if(WSY_V != becomes)
				(this->errors)->addError(4);
			else
				readAWordSy();  //read the value of constant
			int mark = 1;
			if(WSY_V == myplus || WSY_V == myminus)
			{
				if(WSY_V == myminus)
					mark = -1;
				if(contyp == char_sy)
				{
					(this->errors)->addError(5);
					readAWordSy();
				}
				else if(contyp == int_sy)
				{
					readAWordSy();
				}
				else if(contyp == float_sy)
				{
					int marktemp = 1;
					readAWordSy();
					if(WSY_V == myplus || WSY_V == myminus)
					{
						if(WSY_V == myminus)
							marktemp = -1;
						readAWordSy();
					}
					mark *= marktemp;
				}
			}
			if((contyp == int_sy && WSY_V != intcon)\
					||(contyp == char_sy && WSY_V != charcon)\
					||(WSY_V != intcon && WSY_V!=charcon && WSY_V != floatcon))
			{
				fixset += comma;
				(this->errors)->addError(&fixset,6);
				if(WSY_V == comma)
					continue;
				else
					return;
			}
			if(contyp == int_sy )
				value.intconst = (this->wordAnalyze)->getIntconstv()*mark;
			else if(contyp == char_sy)
            {
                value.intconst = (this->wordAnalyze)->getCharconstv();
                value.charconst = (this->wordAnalyze)->getCharconstv();
            }
			else if(contyp == float_sy)
				value.floatconst = (this->wordAnalyze)->getFloatconstv()*mark;
			(this->tables)->insertConstToTab(idname,contyp,value);
			readAWordSy();
		}while(WSY_V == comma );
		if( WSY_V != semicolon )
		{
			(this->errors)->addError(7);
		}
		else
			readAWordSy();
	}
}

void ProdAnlzFather::varDeclare(int *dx)
{
	while(DataTypeSet.isInSet(WSY_V))
	{
		Symbol dataType = WSY_V;
		Word idname ;
		int varsize =1;
		do
		{
            readAWordSy();
			if(WSY_V != ident)
			{
				SymbolSet fixset(comma,semicolon);
				(this->errors)->addError(&fixset,3);
				if(WSY_V == semicolon)
					break;
				else if(WSY_V == comma)
					continue;
			}
			strcpy(idname,(this->wordAnalyze)->getWord());
			int temp;
			if((this->tables)->findIdname1(idname,&temp))
			{
				SymbolSet fixset(comma,semicolon);
				printf("%s ",idname);
				(this->errors)->addError(&fixset,24);
				if(WSY_V == semicolon)
					break;
				else if(WSY_V == comma)
					continue;
			}
			readAWordSy();
			if( WSY_V == lbrack )
			{
				readAWordSy();
				if(WSY_V != intcon)
				{
					SymbolSet fixset(comma,semicolon);
					(this->errors)->addError(&fixset,23);
					if(WSY_V == semicolon)
						break;
					else if(WSY_V == comma)
						continue;
				}
				else{
					readAWordSy();
					if(WSY_V != rbrack)
						(this->errors)->addError(18);
					else
						readAWordSy();
					varsize = (this->wordAnalyze)->getIntconstv();
					(this->tables)->insertVar(idname,dataType,dx,varsize,arr,false);
				}
			}
			else
				(this->tables)->insertVar(idname,dataType,dx,varsize,var,false);
		}while(WSY_V == comma);
		if(WSY_V != semicolon)
        {
            (this->errors)->addError(7);
        }
		else
			readAWordSy();
	}
}

