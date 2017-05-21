#include "Global.h"

bool GlobalTool::isLegalSingal_ch(char ch)
{
	switch(ch)
	{
		case '+':
		case '-':
		case '*':
		case '/':
		case '(':
		case ')':
		case '[':
		case ']':
		case '{':
		case '}':
		case ',':
		case ';':
		case ':':
			return true;
		default:
			return false;
	}
}

SymbolSet::SymbolSet()
{
	this->len = 0;
}
SymbolSet::SymbolSet(Symbol sy0,Symbol sy1)
{
	this->symset[0] = sy0;
	this->symset[1] = sy1;
	this->len = 2;
}
SymbolSet::SymbolSet(Symbol sy0,Symbol sy1,Symbol sy2)
{
	this->symset[0] = sy0;
	this->symset[1] = sy1;
	this->symset[2] = sy2;
	this->len = 3;
}

SymbolSet SymbolSet::operator+=(Symbol sym)
{
	if(!this->isInSet(sym))
		(this->symset)[(this->len)++] = sym;
	return *this;
}

SymbolSet SymbolSet::operator+(Symbol sym)
{
	if(!this->isInSet(sym))
		(this->symset)[(this->len)++] = sym;
	return *this;
}

bool SymbolSet::isInSet(Symbol sym) const
{
	int i =0;
	for (i = 0; i < this->len; i++) {
		if(this->symset[i] == sym)
			return true;
	}
	return false;
}
