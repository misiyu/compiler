#include "Table.h"

Table::Table()
{
	this->tab_top = -1;
	this->btab_top = 0;
	this->rtab_top = -1;
	this->atab_top = -1;
	this->plist_top = 0;
	this->level = 0;
	btables[0].psize = DomSize;
	btables[0].allSize = DomSize;
	btables[0].lastParainTab = -1;
	btables[0].lastSyinTab = -1;
	display[0] = 0;
	this->slen = 0;
	this->emitxy(18,0,0);
	this->emitxy(19,0,DomSize-1);
	this->emitxy(-1,-1,-1);
}


int Table::insertFloatCin(float fl)
{
	this->rtab_top ++;
	if(rtab_top >= RTAB_MAX_SIZE)
	{
		printf("rtables over flow~\n");
		exit(0);
	}
	this->rtables[this->rtab_top] = fl;
	return this->rtab_top;
}

void chIdnameToLow(Word idname)
{
    for(int i=0;i<word_max_len;i++)
        if(isalpha(idname[i]))
            idname[i] = tolower(idname[i]);
}

bool Table::insertConstToTab(Word idname,Symbol dataType,ALLData value)
{
    chIdnameToLow(idname);
	(this->tab_top) ++;
	if(this->tab_top >= TAB_MAX_SIZE)
	{
		printf("tables over flow\n");
		exit(0);
	}
	int tt = this->tab_top;
	strcpy((this->tables)[tt].name,idname);
	(this->tables)[tt].link = tt-1;
	(this->tables)[tt].syType = constant;
	(this->tables)[tt].dataType = dataType;
	(this->tables)[tt].mref = 0;
	(this->tables)[tt].lev = this->level;
	(this->tables)[tt].addr = value;
	(this->btables)[display[level]].lastSyinTab = tt;
	if(dataType == float_sy)
	{
		this->insertFloatCin(value.floatconst);
		(this->tables)[tt].addr.intconst = this->rtab_top;
	}
	return true;
}

bool Table::insertVar(Word idname,Symbol dataType,int *dx,int varsize,SYMtype symtyp,bool isPara)
{
    chIdnameToLow(idname);
	(this->tab_top) ++;
	if(this->tab_top >= TAB_MAX_SIZE)
    {
        printf("tables over flow\n");
        exit(0);
    }
	int tt = this->tab_top;
	int curblock = display[this->level];
	strcpy((this->tables)[tt].name,idname);
	(this->tables)[tt].link = tt-1;
	(this->tables)[tt].syType = symtyp;
	(this->tables)[tt].dataType = dataType;
	(this->tables)[tt].mref = 0;
	(this->tables)[tt].lev = this->level;
	(this->tables)[tt].addr.intconst = *dx;
	(*dx)+= varsize;
	if(*dx >= Stack_MAX_SIZE)
	{
		printf("running stack over flow\n");
		exit(0);
	}
	(this->btables)[curblock].lastSyinTab ++;
	(this->btables)[curblock].allSize += varsize;

	if(isPara)
    {
        (this->btables)[curblock].psize  ++;
        (this->btables)[curblock].lastParainTab ++;
    }
	if(symtyp == arr)
	{
		(this->atab_top)++;
		if(this->atab_top >= ATAB_MAX_SIZE)
		{
			printf("atables over flow\n");
			exit(0);
		}
		int aT = this->atab_top;
		(this->arrtables)[aT].elsize = 1;
		(this->arrtables)[aT].asize = varsize;
		(this->arrtables)[aT].high = varsize;
        (this->tables)[tt].mref = aT;
	}
	return true;
}

bool Table::insertFun(Word idname,Symbol retType)
{
    chIdnameToLow(idname);
    this->btab_top ++;
    int bt = this->btab_top;
    if(this->level == 0)  // if level is already 1 never change it
        this->level ++;
    this->display[level] = bt;
	this->tab_top ++;
	int tt = this->tab_top;
	display[this->level] = bt;
	strcpy((this->tables)[tt].name,idname);
	(this->tables)[tt].link = 0;
	(this->tables)[tt].syType = func;
	(this->tables)[tt].dataType = retType;
	(this->tables)[tt].mref = bt;
	(this->tables)[tt].lev = 0;
	(this->tables)[tt].addr.intconst = this->plist_top;   //entrance of pcode ============================
    (this->btables)[bt].psize = DomSize;
    (this->btables)[bt].allSize = DomSize;
    (this->btables)[bt].lastParainTab = tt;
    (this->btables)[bt].lastSyinTab = tt;
    (this->btables)[0].lastSyinTab = tt;
	return true;
}

void Table::insertStrconst(char str[])
{
	strcat((this->stab),str);
	this->slen = strlen(this->stab);
	if(this->slen >= STab_MAX_SIZE)
	{
		printf("stab over flow\n");
		exit(0);
	}
}

bool Table::findIdname(Word idname,int *location)
{
	if(this->findIdname1(idname,location))
        return true;
    else if(this->findIdname0(idname,location))
        return true;
    else
        return false;
}
bool Table::findIdname1(Word idname,int *loc)
{
    chIdnameToLow(idname);
	int i = (this->btables)[this->display[this->level]].lastSyinTab;
	for(;i>=0; i--)
    {
        if(strcmp((this->tables)[i].name,idname) == 0 && (this->tables)[i].lev == this->level)
        {
            *loc = i;
            return true;
        }
		if((this->tables)[i].link ==0 && this->level ==1)
            break;
    }
	return false;
}

bool Table::findIdname0(Word idname,int *loc)
{
    chIdnameToLow(idname);
    int i = (this->btables)[0].lastSyinTab;
    for(;i>=0;i--)
    {
        if(strcmp((this->tables)[i].name,idname) == 0 && (this->tables)[i].lev == 0 )
        {
            *loc = i;
            return true;
        }
    }
    return false;
}

void Table::emitxy(int fct,int x,int y)
{
	int plt = this->plist_top;
	(this->plist)[plt].f = fct;
	(this->plist)[plt].x = x;
	(this->plist)[plt].y = y;
	(this->plist_top) ++;
	if(this->plist_top >= Pcode_MAX_SIZE)
		printf("plist over flow\n");
}

Tab Table::getTab(int loc)
{
	return (this->tables)[loc];
}

int Table::getPlist_top()
{
	return this->plist_top;
}

void Table::updatePlist(int lc,int x,int y)
{
	if(x != -1)
		(this->plist)[lc].x = x;
	if(y != -1)
		(this->plist)[lc].y = y;
}

void Table::storeStringCon(char str[])
{
	strcpy((this->stab)+(this->slen),str);
}

int Table::getSlen()
{
	return this->slen;
}

void Table::showCode()
{
	FILE *fp = fopen("code","w");
	for(int i= 0;i < this->plist_top;i++)
	{
		fprintf(fp,"%d %d %d\n",this->plist[i].f,this->plist[i].x,this->plist[i].y);
	}
	fclose(fp);
	fp =NULL;
}

int Table::getTab_top()
{
	return this->tab_top;
}
BTab Table::getBTab(int loc)
{
	return (this->btables)[loc];
}

Pcode Table::getPlist(int pc)
{
	return (this->plist)[pc];
}

ATab Table::getATab(int loc)
{
	return (this->arrtables)[loc];
}

char Table::getStabch(int loc)
{
	return (this->stab)[loc];
}

float Table::getFloatcon(int loc)
{
	return (this->rtables)[loc];
}
