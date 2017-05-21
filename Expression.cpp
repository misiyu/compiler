#include "Expression.h"

Expression::Expression(WordAnalyze *wordAnalyze, Symbol *word_sy,Table *tables,Errors *errors)
{
	this->wordAnalyze= wordAnalyze;
	this->word_sy= word_sy;
	this->tables = tables;
	this->errors = errors;
}

bool isCompareSy(Symbol word_sy)
{
	return (word_sy == eql || word_sy == neq || word_sy == grt \
			|| word_sy == geq || word_sy == lss || word_sy == leq);
}
void Expression::conditionExpression()
{
	Symbol retDType1 = char_sy;
	Symbol retDType2 = char_sy;
	retDType1 = caculExpression();
	if(isCompareSy(WSY_V))
    {
		Symbol temp = WSY_V;
        readAWordSy();
        retDType2 = caculExpression();
		if(retDType1 == void_sy || retDType2 == void_sy)
		{
			(this->tables)->emitxy(24,0,0);
			return ;
		}
		else if(retDType1 == float_sy || retDType2 == float_sy)
		{
			if(retDType1 != float_sy)
				(this->tables)->emitxy(26,0,1);
			if(retDType2 != float_sy)
				(this->tables)->emitxy(26,0,0);
			retDType1 = retDType2 = float_sy;
		}
        if(retDType1 == float_sy)
		{
			if(temp == eql)
				(this->tables)->emitxy(39,0,0);
			else if(temp == neq)
				(this->tables)->emitxy(40,0,0);
			else if(temp == lss)
				(this->tables)->emitxy(41,0,0);
			else if(temp == leq)
				(this->tables)->emitxy(42,0,0);
			else if(temp == grt)
				(this->tables)->emitxy(43,0,0);
			else if(temp == geq)
				(this->tables)->emitxy(44,0,0);
		}
		else
		{
			if(temp == eql)
				(this->tables)->emitxy(45,0,0);
			else if(temp == neq)
				(this->tables)->emitxy(46,0,0);
			else if(temp == lss)
				(this->tables)->emitxy(47,0,0);
			else if(temp == leq)
				(this->tables)->emitxy(48,0,0);
			else if(temp == grt)
				(this->tables)->emitxy(49,0,0);
			else if(temp == geq)
				(this->tables)->emitxy(50,0,0);
		}
    }
    else{
        if(retDType1 == float_sy)
            (this->tables)->emitxy(65,0,0);
        else if(retDType1 == int_sy)
            (this->tables)->emitxy(66,0,0);
        else if(retDType1 == char_sy)
            (this->tables)->emitxy(67,0,0);
    }
}

Symbol combineOp(Symbol op1,Symbol op2)
{
	if((op1 == myminus && op2==myminus) || (op1 == myplus && op2==myplus))
		return myplus;
	else
		return myminus;
}
void chResultDataT(Symbol *resultdt,Symbol dataType1)
{
    if(dataType1 == float_sy)
        *resultdt = float_sy;
    else if(dataType1 == int_sy && (*resultdt) == char_sy)
        *resultdt = int_sy;
}
Symbol Expression::caculExpression()
{
	Symbol resultdt = char_sy;
	Symbol op;
	Symbol dataType1 = char_sy;
	Symbol dataType2 = char_sy;
	(this->tables)->emitxy(24,0,0);
	int itemCount = 0;
	do
	{
	    op = myplus;
		if(WSY_V == myplus || WSY_V == myminus)
        {
            op = combineOp(op,WSY_V);
            if(resultdt == char_sy)
                resultdt = int_sy;
        }
	    while(WSY_V == myplus || WSY_V == myminus)
		{
            readAWordSy();
			if(WSY_V == myplus || WSY_V == myminus)
			{
				op = combineOp(op,WSY_V);
			}
		}
		dataType1 = item();
		itemCount ++;
		if(dataType1 == float_sy || dataType2 == float_sy)
		{
			resultdt = float_sy;
			if(dataType1 != float_sy)
				(this->tables)->emitxy(26,0,0);
			if(itemCount >= 2)
			{
				if(dataType2 != float_sy)
					(this->tables)->emitxy(26,0,1);
			}

			dataType1 = dataType2 = float_sy;
			if(op == myplus)
				(this->tables)->emitxy(54,0,0);
			else if(op == myminus)
				(this->tables)->emitxy(55,0,0);
		}
		else if(dataType1 == void_sy)
		{
			return void_sy;
		}
		else
		{
			if(op == myplus)
				(this->tables)->emitxy(52,0,0);
			else if(op == myminus)
				(this->tables)->emitxy(53,0,0);
		}
		dataType2 = dataType1;
		chResultDataT(&resultdt,dataType1);
	}while(WSY_V == myplus || WSY_V == myminus);
	return resultdt;
}

Symbol Expression::item()
{
	int opCount=0;
	Symbol resultdt = char_sy;
	Symbol op ;
	Symbol dataType1 ;
	Symbol dataType2 ;
	do
	{
	    if(WSY_V == mymult || WSY_V == mydiv)
		{
		    op = WSY_V;
            readAWordSy();
		}
		dataType1 = factor();
		if(dataType1 == void_sy)
			return void_sy;
		opCount++;
		if(opCount>=2)
		{
			if(dataType1 == float_sy || dataType2 == float_sy)
			{
				resultdt = float_sy;
				if(dataType1 != float_sy)
					(this->tables)->emitxy(26,0,0);
				if(dataType2 != float_sy)
					(this->tables)->emitxy(26,0,1);
				if(op == mydiv)
					(this->tables)->emitxy(61,0,0);
				else if(op == mymult)
					(this->tables)->emitxy(60,0,0);
				dataType1 = dataType2 = float_sy;
			}
			else
			{
				if(op == mydiv)
					(this->tables)->emitxy(58,0,0);
				else if(op == mymult)
					(this->tables)->emitxy(57,0,0);
			}
		}
		dataType2 = dataType1;
		chResultDataT(&resultdt,dataType1);
	}while(WSY_V == mymult || WSY_V == mydiv);
	return resultdt;
}
bool isConst(Symbol word_sy)
{
	return (word_sy == intcon || word_sy == floatcon || word_sy == charcon);
}
Symbol Expression::factor()
{
	Symbol resultdt = char_sy;
	if(WSY_V == lparent)
	{
		readAWordSy();
		resultdt  = caculExpression();
		if(WSY_V != rparent)
		{
			(this->errors)->addError(9);
		}
		else
			readAWordSy();
	}
	else if(WSY_V == ident)
	{
		Word idname;
		strcpy(idname,(this->wordAnalyze)->getWord());
		int loc = 0;
		if(!(this->tables)->findIdname(idname,&loc))
		{
			printf("%s ",idname);
			SymbolSet fixset(semicolon,lbrace);
			(this->errors)->addError(&fixset,13);
			return void_sy;
		}
		readAWordSy();
		if((this->tables)->getTab(loc).syType == arr && WSY_V != lbrack)
		{
			SymbolSet fixset(semicolon,lbrace);
			(this->errors)->addError(&fixset,31);
			return void_sy;
		}
		if(WSY_V == lparent)
		{
		    bool findIdResult = (this->tables)->findIdname0(idname,&loc);
			if(findIdResult==false || (this->tables)->getTab(loc).syType != func)
			{
				printf("%s ",idname);
				SymbolSet fixset;
				fixset += semicolon;
				(this->errors)->addError(&fixset,13);
				return void_sy;
			}
			Symbol idDataTyp = (this->tables)->getTab(loc).dataType;
            chResultDataT(&resultdt,idDataTyp);
			FuncAnaly funcAnaly(this->wordAnalyze,this->word_sy,this->tables,idDataTyp,0,this->errors);
			funcAnaly.callFunStatement(loc);
		}
		else if(WSY_V == lbrack)
        {
            if((this->tables)->getTab(loc).syType != arr)
            {
                bool findIdResult = (this->tables)->findIdname0(idname,&loc);
                if(findIdResult==false || (this->tables)->getTab(loc).syType != arr)
                {
                    printf("%s ",idname);
                    SymbolSet fixset;
                    fixset += semicolon;
                    (this->errors)->addError(&fixset,33);
                    return void_sy;
                }
            }
            Symbol idDataTyp = (this->tables)->getTab(loc).dataType;
            chResultDataT(&resultdt,idDataTyp);
			(this->tables)->emitxy(0,(this->tables)->getTab(loc).lev,(this->tables)->getTab(loc).addr.intconst);
            readAWordSy();
            Symbol dataType3 = caculExpression();
            if(dataType3 == float_sy)
            {
                (this->errors)->addError(35);
                //(this->errors)->addError(19);
                (this->tables)->emitxy(64,0,0);
            }
			int a = ((this->tables)->getTab(loc)).mref;
			(this->tables)->emitxy(20,0,a);
			(this->tables)->emitxy(34,0,0);
            if(WSY_V != rbrack)
            {
				(this->errors)->addError(18);
            }
			else
				readAWordSy();
        }
		else
		{
		    Symbol idDataTyp = (this->tables)->getTab(loc).dataType;
            chResultDataT(&resultdt,idDataTyp);
			int adr = ( (this->tables)->getTab(loc) ).addr.intconst;
			Tab sy_item = (this->tables)->getTab(loc);
			if(sy_item.syType == constant && sy_item.dataType == float_sy)
                (this->tables)->emitxy(25,(this->tables)->getTab(loc).lev,adr);
			else if(sy_item.syType == constant)
            {
                (this->tables)->emitxy(24,0,adr);
            }
            else
                (this->tables)->emitxy(1,(this->tables)->getTab(loc).lev,adr);
		}
	}
	else if(isConst(WSY_V))
	{
		if(WSY_V == floatcon)
		{
			resultdt = float_sy;
			float value = (this->wordAnalyze)->getFloatconstv();
			(this->tables)->emitxy(25,0,(this->tables)->insertFloatCin(value));
		}
		else if(WSY_V == intcon)
		{
			(this->tables)->emitxy(24,0,(this->wordAnalyze)->getIntconstv());
			if(resultdt == char_sy)
                resultdt = int_sy;
		}
		else if(WSY_V == charcon)
			(this->tables)->emitxy(24,0,(this->wordAnalyze)->getCharconstv());
		readAWordSy();
	}
    else
    {
		SymbolSet fixset;
		fixset += semicolon;
		(this->errors)->addError(&fixset,20);
    }
	return resultdt;
}
