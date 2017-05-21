#include "Errors.h"

Errors::Errors(WordAnalyze *wordAnalyze,Symbol *word_sy)
{
	this->wordAnalyze = wordAnalyze;
	this->trueError = 0;
	this->warning = 0;
	this->word_sy = word_sy;
	strcpy(this->errorTab[0],"const,int,float,char or void is expected here\0");
	strcpy(this->errorTab[1],"int,float,char or void is expected here\0"      );
	strcpy(this->errorTab[2],"int,float,char is expected here\0");
	strcpy(this->errorTab[3],"a identify name is expected here\0");
	strcpy(this->errorTab[4],"a '=' is expected here\0");
	strcpy(this->errorTab[5],"'+' or '-' is not allowed in front of a char constant\0");
	strcpy(this->errorTab[6],"constant data type does not match with constant name\0");
	strcpy(this->errorTab[7],"a ; is expected here to end a statement\0");
	strcpy(this->errorTab[8],"a ( is expected here\0");
	strcpy(this->errorTab[9],"a ) is expected here\0");
	strcpy(this->errorTab[10],"a { is expected here\0");
	strcpy(this->errorTab[11],"a } is expected here\0");
	strcpy(this->errorTab[12],"it must be a variate here\0");
	strcpy(this->errorTab[13],"identity is not declared \0");
	strcpy(this->errorTab[14],"unknow symbol \0");
	strcpy(this->errorTab[15],"multiple same case lable \0");
	strcpy(this->errorTab[16],"it must be int constant or a char constant after case \0");
	strcpy(this->errorTab[17],"a : is expected here associate with case\0");
	strcpy(this->errorTab[18],"a ] is expexted here \0");
	strcpy(this->errorTab[19],"convert a float to int or char \0");
	strcpy(this->errorTab[20],"this symbol can not be a factor\0");
	strcpy(this->errorTab[21],"this is not an array\0");
	strcpy(this->errorTab[22],"main function is the end of program, context after it will be ignored\0");
	strcpy(this->errorTab[23],"there must be an unsigned int constant in the [] to declare an array\0");
	strcpy(this->errorTab[24],"multiple define a same name\0");
	strcpy(this->errorTab[25],"parameter qantity wrong\0");
	strcpy(this->errorTab[26],"parameters' date types do not match\0");
	strcpy(this->errorTab[27],"the return date type of main function should be void\0");
	strcpy(this->errorTab[28],"the void function should not have a return data\0");
	strcpy(this->errorTab[29],"no void function has not any return data yet\0");
	strcpy(this->errorTab[30],"a variate name or a array element is expected here\0");
	strcpy(this->errorTab[31],"a array name must be followed by a[]\0");
	strcpy(this->errorTab[32],"expression data type in switch should not be float\0");
    strcpy(this->errorTab[33],"array is not declared\0");
    strcpy(this->errorTab[34],"a case is expected here\0");
    strcpy(this->errorTab[35],"it must not be a float in [] \0");
    strcpy(this->errorTab[36],"empty printf() \0");
}

void Errors::addError(SymbolSet *fixset, int errorNO)
{
    printf("Error ");
	this->addError(errorNO);
	(this->wordAnalyze)->setErrorFlag();
	while(!fixset->isInSet(WSY_V))
		readAWordSy();
}

void Errors::addError(int errorNO)
{
	int lineNo = (this->wordAnalyze)->getLineCount();
	int chNO = (this->wordAnalyze)->getCharCount();
	(this->warning) ++;
	printf("Warning near line %d:%d : ",lineNo,chNO);
	printf(" %s\n",errorTab[errorNO]);
	if(this->warning >= 16)
		(this->wordAnalyze)->setErrorFlag();
}
