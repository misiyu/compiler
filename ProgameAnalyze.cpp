#include "ProgameAnalyze.h"

ProgameAnalyze::ProgameAnalyze(WordAnalyze *wordAnalyze, Symbol *word_sy,Table *tables,Errors *errors)\
            :ProdAnlzFather(wordAnalyze, word_sy,tables,errors)
{
}

void ProgameAnalyze::start()
{
	int order = 0;
	int dx = DomSize;
	readAWordSy();
	while(true)
    {
        if(WSY_V == const_sy && order == 0)
        {
            this->constDeclare();
        }
		else if(DataTypeSet.isInSet(WSY_V) && order <= 1)
		{
			order = 1;
			Word idname;
			do{
                Symbol dataType = WSY_V;
				readAWordSy();  //read idname
				if(WSY_V != ident)
				{
					SymbolSet fixset(semicolon,lparent,comma);
					(this->errors)->addError(&fixset,3);
					if(WSY_V == semicolon)
					{
						readAWordSy();
						continue;
					}
					else if (WSY_V == lparent) {

					}
					strcpy(idname,"\0");
				}
				else
					strcpy(idname,(this->wordAnalyze)->getWord());
				if(WSY_V != lparent)
					readAWordSy();
				if(WSY_V == lparent)
				{
					if(strcmp(idname,"main                \0") == 0)
					{
						(this->errors)->addError(27);
						(this->wordAnalyze)->setHasMainFlag();
					}
					funcDeclare(idname,dataType);
					order = 2;
					break;
				}
				else
					GlobalVarDeclare(dataType,idname,&dx);

			}while(DataTypeSet.isInSet(WSY_V));
		}
        else if(WSY_V == void_sy && order <=2)
		{
			Word idname;
			readAWordSy();
			if(WSY_V != ident)
			{
				SymbolSet fixset(lparent,lbrace);
				(this->errors)->addError(&fixset,3);
				if(WSY_V == lparent)
				{
					strcpy(idname,"errorsssssssssssssss\0");
					funcDeclare(idname,void_sy);
				}
				else if(WSY_V == lbrace)
				{

					readAWordSy();
					if(WSY_V != rbrace)
					{
						FuncAnaly funcAnaly(this->wordAnalyze,this->word_sy,this->tables,void_sy,dx,this->errors);
						funcAnaly.complexStatement();
					}
					if(WSY_V != rbrace)
					{
						(this->errors)->addError(11);
					}
					else
						readAWordSy();
					(this->tables)->emitxy(33,0,0);
				}
				order = 2;
				continue ;
			}
			strcpy(idname,(this->wordAnalyze)->getWord());
			if(strcmp(idname,"main                \0") == 0)
			{
				order = 3;
				(this->wordAnalyze)->setHasMainFlag();
			}
			else
				order = 2;
			readAWordSy();
			funcDeclare(idname,void_sy);
		}
		else if(DataTypeSet.isInSet(WSY_V))
        {
            order = 2;
            Symbol return_dtype = WSY_V;
			Word idname;
            readAWordSy();
			strcpy(idname,(this->wordAnalyze)->getWord());
			if(strcmp(idname,"main                \0") == 0)
			{
				(this->wordAnalyze)->setHasMainFlag();
				(this->errors)->addError(27);
			}
			readAWordSy();
			funcDeclare(idname,return_dtype);
        }
		else if(order >= 3)
		{
			(this->errors)->addError(22);
			(this->wordAnalyze)->tryToRun();
			readAWordSy();
		}
		else if(WSY_V == ident)
		{
			(this->errors)->addError(1);
			Symbol dataType = int_sy;
			Word idname;
			strcpy(idname,(this->wordAnalyze)->getWord());
			readAWordSy();
			if(WSY_V == lparent)
			{
				funcDeclare(idname,dataType);
				order = 2;
			}
			else
				GlobalVarDeclare(dataType,idname,&dx);
		}
		else
        {
			SymbolSet symset(int_sy,char_sy,float_sy);
			if(order == 0)
			{
				symset += const_sy;
				symset += void_sy;
				(this->errors)->addError(&symset,0);
			}
			else if(order == 1)
			{
				symset += void_sy;
				(this->errors)->addError(&symset,1);
			}
			else if(order == 2)
			{
				symset += void_sy;
				(this->errors)->addError(&symset,1);
			}
            //printf("something wrong \n");
            //break;
        }

	}
}

void ProgameAnalyze::GlobalVarDeclare(Symbol dataType,Word idname,int *dx)
{
    int temp;
	if((this->tables)->findIdname0(idname,&temp))
	{
		SymbolSet fixset(comma,semicolon);
		(this->errors)->addError(&fixset,24);
		if(WSY_V == semicolon)
		{
			readAWordSy();
			return;
		}
	}
	int varsize = 1;
	if(WSY_V == semicolon)
	{
        (this->tables)->insertVar(idname,dataType,dx,varsize,var,false); //dx is a pointer here which point to the dx delared in start
		readAWordSy();
		return;
	}
	else if(WSY_V == lbrack) //[
	{
		readAWordSy();
		if(WSY_V != intcon)
		{
			SymbolSet fixset(comma,semicolon,rbrack);
			(this->errors)->addError(&fixset,23);
			if(WSY_V == semicolon)
			{
				readAWordSy();
				return;
			}
			else if(WSY_V == rbrack)
				readAWordSy();
		}
		else{
			varsize = (this->wordAnalyze)->getIntconstv();
			readAWordSy();
			if(WSY_V != rbrack)
				(this->errors)->addError(18);
			else
				readAWordSy();
			(this->tables)->insertVar(idname,dataType,dx,varsize,arr,false); //the last false means this is not a parameter
		}
	}
	else
		(this->tables)->insertVar(idname,dataType,dx,varsize,var,false);
	while(WSY_V == comma)
	{
		readAWordSy();
		if(WSY_V != ident)
		{
			SymbolSet fixset(comma,semicolon);
			(this->errors)->addError(&fixset,3);
			if(WSY_V == comma)
				continue;
			else if (WSY_V == semicolon) {
				readAWordSy();
				return ;
			}
		}
		strcpy(idname,(this->wordAnalyze)->getWord());
		int temp;
		if((this->tables)->findIdname0(idname,&temp))
        {
            SymbolSet fixset(comma,semicolon);
            (this->errors)->addError(&fixset,24);
            if(WSY_V == semicolon)
            {
                readAWordSy();
                return;
            }
            else if(WSY_V == comma)
                continue;
        }
		readAWordSy();
		if(WSY_V == lbrack)
		{
			readAWordSy();
			if(WSY_V != intcon)
			{
				SymbolSet fixset(comma,semicolon);
				(this->errors)->addError(&fixset,23);
				if(WSY_V == semicolon)
				{
					readAWordSy();
					return;
				}
				else if(WSY_V == comma)
					continue;
			}
			else{
				varsize = (this->wordAnalyze)->getIntconstv();
				readAWordSy();
				if(WSY_V != rbrack)
					(this->errors)->addError(18);
				else
					readAWordSy();
				(this->tables)->insertVar(idname,dataType,dx,varsize,arr,false);
			}
		}
		else
			(this->tables)->insertVar(idname,dataType,dx,varsize,var,false);
	}
	if(WSY_V != semicolon)
		(this->errors)->addError(7);
	else
		readAWordSy();
}

void ProgameAnalyze::funcDeclare(Word idname,Symbol return_type)
{
    int temp;
	if((this->tables)->findIdname0(idname,&temp))
	{
		printf("error function name %s\n",idname);
		SymbolSet fixset;
		fixset += lparent;
		(this->errors)->addError(&fixset,24);
	}
	int dx=DomSize;
	(this->tables)->insertFun(idname,return_type);
	if(strcmp(idname,"main                \0") == 0)
	{
		int curTT = (this->tables)->getTab_top();
		(this->tables)->updatePlist(0,-1,curTT);
		(this->wordAnalyze)->setHasMainFlag();
	}
    if(WSY_V != lparent)
	{
		(this->errors)->addError(8);
	}
	else
		readAWordSy();
	funcPara(&dx);
	if(WSY_V != lbrace)
		(this->errors)->addError(10);
	else
		readAWordSy();
	if(WSY_V != rbrace)
	{
		FuncAnaly funcAnaly(this->wordAnalyze,this->word_sy,this->tables,return_type,dx,this->errors);
		funcAnaly.complexStatement();
		if(funcAnaly.getHasReturn() == false && return_type != void_sy)
			(this->errors)->addError(29);
	}
	if(WSY_V != rbrace)
	{
		(this->errors)->addError(11);
	}
	else
		readAWordSy();
	(this->tables)->emitxy(33,0,0);
}

void ProgameAnalyze::funcPara(int *dx)
{
	if(WSY_V == rparent)
	{
		readAWordSy();
		return ;
	}
	do{
        if(WSY_V == comma)
            readAWordSy();
		if(!DataTypeSet.isInSet(WSY_V))
		{
			SymbolSet fixset = DataTypeSet;
			fixset += rparent;
			fixset += lbrace;
			(this->errors)->addError(&fixset,2);
			if(WSY_V == rparent)
				break;
			else if(WSY_V == lbrace)
				return;
		}
		Symbol dataType = WSY_V;
		readAWordSy();
		if(WSY_V != ident)
		{
			SymbolSet fixset(rparent,lbrace,comma) ;
			(this->errors)->addError(&fixset,3);
			if(WSY_V == rparent)
				break;
			else if(WSY_V == lbrace)
				return;
			else if (WSY_V == comma)
				continue;
		}
		Word idname ;
		strcpy(idname,(this->wordAnalyze)->getWord());
		int temp;
		if((this->tables)->findIdname1(idname,&temp))
        {
            SymbolSet fixset(comma,rparent);
            this->errors->addError(&fixset,24);
            if(WSY_V == comma)
                continue;
            else
                return;
        }
		(this->tables)->insertVar((this->wordAnalyze)->getWord(),dataType,dx,1,var,true); //dx is declared in funcDeclare
		readAWordSy();
	}while(WSY_V == comma);
	if(WSY_V != rparent)
		(this->errors)->addError(9);
	else
		readAWordSy();
}
