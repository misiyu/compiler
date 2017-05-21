#include "FuncAnaly.h"

FuncAnaly::FuncAnaly(WordAnalyze *wordAnalyze,Symbol *word_sy,Table *tables,Symbol return_type,int dx,Errors *errors)\
		:ProdAnlzFather(wordAnalyze,word_sy,tables,errors)
{
	this->fun_return_type = return_type;
	this->dx=dx;
	this->hasReturn = false;
}

bool isStatement(Symbol word_sy)
{
	return (word_sy == if_sy || word_sy == while_sy || word_sy == lbrace || word_sy == scanf_sy || word_sy == printf_sy\
			||word_sy == return_sy || word_sy == semicolon || word_sy == ident || word_sy == switch_sy);
}

void FuncAnaly::complexStatement()
{
	if(WSY_V == const_sy)
    {
		while(WSY_V == const_sy)
			constDeclare();
    }
	if(DataTypeSet.isInSet(WSY_V))
    {
        varDeclare(&(this->dx));
    }
	if(WSY_V == rbrace)
		return;
    statementList();
}

void FuncAnaly::statementList()
{
	if(WSY_V == rbrace)
		return;
	do
	{
		statement();
		if(WSY_V == semicolon)
            readAWordSy();
	}while(isStatement(WSY_V));
}

void FuncAnaly::statement()
{
	if(WSY_V == if_sy)
    {
        readAWordSy();
        ifStatement();
    }
	else if(WSY_V == while_sy)
    {
        readAWordSy();
        whileStatement();
    }

	else if(WSY_V == lbrace)
	{
	    readAWordSy();
		statementList();
		if(WSY_V != rbrace)
			(this->errors)->addError(11);
		else
			readAWordSy();
		return ;
	}
	else if(WSY_V == scanf_sy)
    {
        readAWordSy();
        scanfStatement();
    }
	else if(WSY_V == printf_sy)
    {
        readAWordSy();
        printfStatement();
    }
	else if(WSY_V == return_sy)
    {
        readAWordSy();
        returnStament();
    }
	else if(WSY_V == switch_sy)
	{
		readAWordSy();
		switchStatement();
	}
	else if(WSY_V == semicolon)
	{

	}
	else if(WSY_V == ident )
	{
		Word idname;
		strcpy(idname,(this->wordAnalyze)->getWord());
		int idloc = 0;
		if(!(this->tables)->findIdname(idname,&idloc))
		{
			printf("%s ",idname);
			SymbolSet fixset;
			fixset += semicolon;
			(this->errors)->addError(&fixset,13);
			return ;
		}
		readAWordSy();
		if(WSY_V == lparent)
        {
            bool findIdResult = (this->tables)->findIdname0(idname,&idloc);
			if(findIdResult == false || (this->tables)->getTab(idloc).syType != func)
			{
				printf("%s ",idname);
				SymbolSet fixset;
				fixset += semicolon;
				(this->errors)->addError(&fixset,13);
				return ;
			}
            callFunStatement(idloc);
			if(WSY_V != semicolon)
				(this->errors)->addError(7);
        }
		else
		{
		    if(WSY_V == lbrack && (this->tables)->getTab(idloc).syType != arr)
            {
                bool findIdResult = (this->tables)->findIdname0(idname,&idloc);
                if(findIdResult == false || (this->tables)->getTab(idloc).syType != arr)
                {
                    printf("%s ",idname);
                    SymbolSet fixset;
                    fixset += semicolon;
                    (this->errors)->addError(&fixset,33);
                    return ;
                }
            }
			int adr = (this->tables)->getTab(idloc).addr.intconst;
			(this->tables)->emitxy(0,(this->tables)->getTab(idloc).lev,adr);
			becomesStatement(idloc);
		}
	}
	else
	{
		(this->errors)->addError(14);
	}
}

bool insertCase(CaseL caselabel[],int label,int *top,int curCT)
{
	for(int i=0;i<(*top);i++)
		if(caselabel[i].label == label)
		{
			return false;
		}
	caselabel[(*top)].label = label;
	caselabel[(*top)].lc = curCT;
	(*top)++;
	return true;
}

void FuncAnaly::switchStatement()
{
	CaseL caselabel[CASE_MAX_NUM];
	int exittab[CASE_MAX_NUM];
	int casenum = 0;
	int exittabNum = 0;
	if(WSY_V != lparent)
	{
		(this->errors)->addError(8);
	}
	readAWordSy();
	CreateExp;
	Symbol exDataType = expression.caculExpression();
    if(exDataType == float_sy)
        (this->errors)->addError(32);
	int mct1 = (this->tables)->getPlist_top();
	(this->tables)->emitxy(12,0,0);

	if(WSY_V != rparent)
	{
		(this->errors)->addError(9);
	}
	else
		readAWordSy();
	if(WSY_V != lbrace)
	{
		(this->errors)->addError(10);
	}
	else
		readAWordSy();
	int label;
	int curCT ;
	if(WSY_V != case_sy)
    {
        SymbolSet fixset;
        fixset += rbrace;
        (this->errors)->addError(&fixset,34);
        readAWordSy();
        return ;
    }
	while(WSY_V == case_sy)
	{
		readAWordSy();
		int mark = 1;
		if(WSY_V == myplus || WSY_V == myminus)
		{
			if(WSY_V == myminus)
				mark = -1;
			readAWordSy();
		}
		if(WSY_V == intcon)
			label = (this->wordAnalyze)->getIntconstv()*mark;
		else if(WSY_V == charcon)
		{
			if(mark == -1)
				this->errors->addError(5);
			label = (int)(this->wordAnalyze)->getCharconstv();
		}
		else
		{
			SymbolSet fixset(case_sy,rbrace);
			(this->errors)->addError(16);
			if(WSY_V == case_sy)
				continue;
			else if(WSY_V == rbrace) //=====================
				break;
		}
		curCT = (this->tables)->getPlist_top();
		if(insertCase(caselabel,label,&casenum,curCT)== false)
			(this->errors)->addError(15);
		readAWordSy();
		if(WSY_V != colon)
		{
			(this->errors)->addError(17);
		}
		readAWordSy();
		statement();
		exittab[exittabNum++] = (this->tables)->getPlist_top();
		(this->tables)->emitxy(10,0,0);
		if(WSY_V == semicolon)
            readAWordSy();
	}
	curCT = (this->tables)->getPlist_top();
	(this->tables)->updatePlist(mct1,-1,curCT);
	for(int i=0;i<casenum;i++)
	{
		(this->tables)->emitxy(13,0,caselabel[i].label);
		(this->tables)->emitxy(13,0,caselabel[i].lc);
	}
	curCT = (this->tables)->getPlist_top();
	for(int i=0;i<exittabNum;i++)
		(this->tables)->updatePlist(exittab[i],-1,curCT);
	if(WSY_V != rbrace)
	{
		//error
	}
	readAWordSy();
}

void FuncAnaly::callFunStatement(int idloc)
{
	(this->tables)->emitxy(18,0,idloc);
	if(WSY_V != lparent)
	{
		(this->errors)->addError(8);
	}
	else
		readAWordSy();
	int parNum = 0;
	if(WSY_V != rparent)
    {
        bool time = false;
        do{
            if(time == false)
                time = true;
            else
                readAWordSy();
			Symbol dataType1,dataType2;
			CreateExp;
            dataType1 = expression.caculExpression();
			parNum ++;
			dataType2 = (this->tables)->getTab(idloc+parNum).dataType;
			if(dataType1 != dataType2)
			{
				if((dataType1== int_sy || dataType1 ==char_sy) && dataType2 == float_sy)
				{
					(this->tables)->emitxy(26,0,0);
				}
				else if((dataType2== int_sy || dataType2 ==char_sy) && dataType1 == float_sy)
				{
					(this->errors)->addError(26);
					(this->errors)->addError(19);
					(this->tables)->emitxy(64,0,0);
					if(dataType2 ==char_sy)
                        (this->tables)->emitxy(69,0,0);
				}
				else if(dataType2 == char_sy && dataType1 == int_sy)
                    (this->tables)->emitxy(69,0,0);
			}
        }while(WSY_V == comma);
    }
	//btab[tab[i].ref].psize-1 );
	int mref = (this->tables)->getTab(idloc).mref;
	int y = (this->tables)->getBTab(mref).psize-1;
	if((this->tables)->getBTab(mref).lastParainTab - idloc != parNum)
	{
		SymbolSet fixset;
		fixset += semicolon;
		(this->errors)->addError(&fixset,25);
		return ;
	}
	(this->tables)->emitxy(19,0,y);
    if(WSY_V != rparent)
    {
		(this->errors)->addError(9);
    }
	else
		readAWordSy();
}
void FuncAnaly::becomesStatement(int idloc)
{
	SYMtype syType = (this->tables)->getTab(idloc).syType;
	if(syType!=var && syType!= arr)
	{
		SymbolSet fixset(lbrack,eql,semicolon);
		(this->errors)->addError(&fixset,30);
		if(WSY_V ==semicolon)
			return;
	}
	if(syType == arr && WSY_V != lbrack)
	{
		SymbolSet fixset(eql,semicolon);
		(this->errors)->addError(&fixset,31);
		if(WSY_V ==semicolon)
			return;
	}
	Symbol iddataType = (this->tables)->getTab(idloc).dataType;
    if(WSY_V == lbrack)
    {
        readAWordSy();
        CreateExp;
        Symbol dataType1 = expression.caculExpression();
        if(dataType1 == float_sy)
        {
            (this->errors)->addError(35);
            //(this->errors)->addError(19);
            (this->tables)->emitxy(64,0,0);
        }
		int a = (this->tables)->getTab(idloc).mref;
		(this->tables)->emitxy(20,0,a);
        if(WSY_V != rbrack)
			(this->errors)->addError(18);
		else
			readAWordSy();
    }
	if(WSY_V != becomes)
		(this->errors)->addError(4);
	else
		readAWordSy();
	Symbol expDateType;
	CreateExp;
	expDateType = expression.caculExpression();
	if(iddataType == float_sy && expDateType != float_sy)
		(this->tables)->emitxy(26,0,0);
	if((iddataType==int_sy || iddataType == char_sy) && expDateType==float_sy)
	{
		(this->errors)->addError(19);
		(this->tables)->emitxy(64,0,0);
		if(iddataType == char_sy)
            (this->tables)->emitxy(69,0,0);
	}
	if(iddataType == char_sy && expDateType == int_sy)
        (this->tables)->emitxy(69,0,0);
	(this->tables)->emitxy(38,0,0);
	if(WSY_V != semicolon)
		(this->errors)->addError(7);
	else
		readAWordSy();
}
void FuncAnaly::ifStatement()
{
	if(WSY_V != lparent)
		(this->errors)->addError(8);
	else
		readAWordSy();
	CreateExp;
	expression.conditionExpression();
	int mct1 = (this->tables)->getPlist_top();
	(this->tables)->emitxy(11,0,0);   //if stack top is false jump to y
	if(WSY_V != rparent)
		(this->errors)->addError(9);
	else
		readAWordSy();
	statement();
	if(WSY_V == semicolon)
		readAWordSy();
	if(WSY_V == else_sy)
    {
        readAWordSy();
		int mct2 = (this->tables)->getPlist_top();
		(this->tables)->emitxy(10,0,0);
		int curCT = (this->tables)->getPlist_top();
		(this->tables)->updatePlist(mct1,-1,curCT);
        statement();
		curCT = (this->tables)->getPlist_top();
		(this->tables)->updatePlist(mct2,-1,curCT);
    }
	else
	{
		int curCT = (this->tables)->getPlist_top();
		(this->tables)->updatePlist(mct1,-1,curCT);
	}
}
void FuncAnaly::whileStatement()
{
	if(WSY_V != lparent)
	{
		(this->errors)->addError(8);
	}
	int mct1 = (this->tables)->getPlist_top();
	readAWordSy();
	CreateExp;
	expression.conditionExpression();
	int mct2 = (this->tables)->getPlist_top();
	(this->tables)->emitxy(11,0,0);
	if(WSY_V != rparent)
	{
		(this->errors)->addError(9);
	}
	else
		readAWordSy();
	statement();
	(this->tables)->emitxy(10,0,mct1);
	int curCT = (this->tables)->getPlist_top();
	(this->tables)->updatePlist(mct2,-1,curCT);
}
int ord(Symbol dataType)
{
	if(dataType == int_sy)
		return 1;
	else if(dataType == float_sy)
		return 2;
	else if(dataType == char_sy)
		return 3;
	return 0;
}
void FuncAnaly::scanfStatement()
{
	if(WSY_V != lparent)
	{
		(this->errors)->addError(8);
	}
	do
	{
		readAWordSy();
		if(WSY_V != ident )
		{
			SymbolSet fixset(comma,rparent,semicolon);
			(this->errors)->addError(&fixset,3);
			if(WSY_V == comma)
				continue;
			else if(WSY_V == rparent)
				break;
			else if(WSY_V == semicolon)
				return;
		}
		int idloc = 0;
		(this->tables)->findIdname((this->wordAnalyze)->getWord(),&idloc);
		if((this->tables)->getTab(idloc).syType != var)
		{
			(this->errors)->addError(12);
			SymbolSet fixset(comma,rparent,semicolon);
			(this->errors)->addError(&fixset,3);
			if(WSY_V == comma)
				continue;
			else if(WSY_V == rparent)
				break;
			else if(WSY_V == semicolon)
				return;
		}
		readAWordSy();
		(this->tables)->emitxy(0,(this->tables)->getTab(idloc).lev,(this->tables)->getTab(idloc).addr.intconst);
		(this->tables)->emitxy(27,0,ord((this->tables)->getTab(idloc).dataType));
	}while(WSY_V == comma);
	if(WSY_V != rparent)
		(this->errors)->addError(9);
	else
		readAWordSy();
	if(WSY_V != semicolon)
		(this->errors)->addError(7);
}
void FuncAnaly::printfStatement()
{
	if(WSY_V != lparent)
		(this->errors)->addError(8);
	readAWordSy();
	if(WSY_V == rparent)
    {
        (this->errors)->addError(36);
    }
	if(WSY_V == stringcon)
	{
		(this->tables)->emitxy(24,0,(this->wordAnalyze)->getStrConLen());
		(this->tables)->emitxy(28,0,(this->wordAnalyze)->getIntconstv());
		readAWordSy();
		if(WSY_V == comma)
		{
		    readAWordSy();
			CreateExp;
			Symbol exDataType = expression.caculExpression();
			if(exDataType == float_sy)
				(this->tables)->emitxy(37,0,0);
			else
				(this->tables)->emitxy(29,0,ord(exDataType));
		}
	}
	if(WSY_V != rparent)
	{
	    Symbol exDataType;
		CreateExp;
		exDataType = expression.caculExpression();
		if(exDataType == float_sy)
			(this->tables)->emitxy(37,0,0);
		else
			(this->tables)->emitxy(29,0,ord(exDataType));
	}
	if(WSY_V != rparent)
	{
		(this->errors)->addError(9);
	}
	else
		readAWordSy();
	if(WSY_V != semicolon)
		(this->errors)->addError(7);
}
void FuncAnaly::returnStament()
{
	(this->tables)->emitxy(0,1,0);
	if(WSY_V == lparent || WSY_V != semicolon)
	{
	    if(this->fun_return_type == void_sy)
		{
			(this->errors)->addError(28);
		}
	    if(WSY_V != lparent)
        {
            (this->errors)->addError(8);
        }
		else
            readAWordSy();
		Symbol dataType1 = int_sy;
		if(WSY_V != rparent)
		{
			(this->hasReturn) = true;
			CreateExp;
			dataType1 = expression.caculExpression();
		}
		if(WSY_V != rparent)
		{
			(this->errors)->addError(9);
		}
		else
            readAWordSy();
		if(this->fun_return_type == float_sy && dataType1 != float_sy)
			(this->tables)->emitxy(26,0,0);
		else if((this->fun_return_type == int_sy ||this->fun_return_type == char_sy) && dataType1 == float_sy)
		{
			(this->errors)->addError(19);
			(this->tables)->emitxy(64,0,0);
			if(this->fun_return_type == char_sy)
                (this->tables)->emitxy(69,0,0);
		}
		else if(this->fun_return_type == char_sy && dataType1 == int_sy)
        {
            (this->tables)->emitxy(69,0,0);
        }
		(this->tables)->emitxy(38,0,0);
	}
	if(WSY_V != semicolon)
		(this->errors)->addError(7);
	(this->tables)->emitxy(33,0,0);
}

bool FuncAnaly::getHasReturn()
{
	return this->hasReturn;
}
