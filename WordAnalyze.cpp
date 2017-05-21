#include "WordAnalyze.h"

WordAnalyze::WordAnalyze(Table *tables)
{
	strcpy(this->key[0]  , "case                \0");
	strcpy(this->key[1]  , "const               \0");
	strcpy(this->key[2]  , "else                \0");
	strcpy(this->key[3]  , "if                  \0");
	strcpy(this->key[4]  , "printf              \0");
	strcpy(this->key[5]  , "return              \0");
	strcpy(this->key[6]  , "scanf               \0");
	strcpy(this->key[7]  , "switch              \0");
	strcpy(this->key[8]  , "int                 \0");
	strcpy(this->key[9]  , "char                \0");
	strcpy(this->key[10] , "float               \0");
	strcpy(this->key[11] , "void                \0");
	strcpy(this->key[12] , "while               \0");

	this->key_sy[0 ] = case_sy;
	this->key_sy[1 ] = const_sy;
	this->key_sy[2 ] = else_sy;
	this->key_sy[3 ] = if_sy;
	this->key_sy[4 ] = printf_sy;
	this->key_sy[5 ] = return_sy;
	this->key_sy[6 ] = scanf_sy;
	this->key_sy[7 ] = switch_sy;
	this->key_sy[8 ] = int_sy;
	this->key_sy[9 ] = char_sy;
	this->key_sy[10] = float_sy;
	this->key_sy[11] = void_sy;
	this->key_sy[12] = while_sy;


	strcpy(this->SyStr[0] ,"intcon\0");
	strcpy(this->SyStr[1] ,"floatcon\0");
	strcpy(this->SyStr[2] ,"charcon\0");
	strcpy(this->SyStr[3] ,"stringcon\0");
	strcpy(this->SyStr[4] ,"myplus\0");
	strcpy(this->SyStr[5] ,"myminus\0");
	strcpy(this->SyStr[6] ,"mymult\0");
	strcpy(this->SyStr[7] ,"mydiv\0");
	strcpy(this->SyStr[8] ,"eql\0");
	strcpy(this->SyStr[9] ,"neq\0");
	strcpy(this->SyStr[10],"grt\0");
	strcpy(this->SyStr[11],"geq\0");
	strcpy(this->SyStr[12],"lss\0");
	strcpy(this->SyStr[13],"leq\0");
	strcpy(this->SyStr[14],"lparent\0");
	strcpy(this->SyStr[15],"rparent\0");
	strcpy(this->SyStr[16],"lbrack\0");
	strcpy(this->SyStr[17],"rbrack\0");
	strcpy(this->SyStr[18],"comma\0");
	strcpy(this->SyStr[19],"semicolon\0");
	strcpy(this->SyStr[20],"colon\0");
	strcpy(this->SyStr[21],"becomes\0");
	strcpy(this->SyStr[22],"lbrace\0");
	strcpy(this->SyStr[23],"rbrace\0");
	strcpy(this->SyStr[24],"period\0");
	strcpy(this->SyStr[25],"const_sy\0");
	strcpy(this->SyStr[26],"ident\0");
	strcpy(this->SyStr[27],"if_sy\0");
	strcpy(this->SyStr[28],"else_sy\0");
	strcpy(this->SyStr[29],"while_sy\0");
	strcpy(this->SyStr[30],"switch_sy\0");
	strcpy(this->SyStr[31],"case_sy\0");
	strcpy(this->SyStr[32],"printf_sy\0");
	strcpy(this->SyStr[33],"scanf_sy\0");
	strcpy(this->SyStr[34],"void_sy\0");
	strcpy(this->SyStr[35],"return_sy\0");
	strcpy(this->SyStr[36],"int_sy\0");
	strcpy(this->SyStr[37],"char_sy\0");
	strcpy(this->SyStr[38],"float_sy\0");

	this->tables = tables;
	this->errorFlag = false;
	this->hasMainFlag = false;

	while(true)
	{
		printf("input your file's name:\n");
		scanf("%s",this->input_file_name);
		this->input_file = fopen(input_file_name,"r");
		if(this->input_file == NULL)
			printf("file named %s is not exist!\n",input_file_name);
		else
			break;
	}
	this->char_count = 0;
	this->line_len = 0;
	this->line_count = 0;
	this->CIGWS = ' ';
}

int WordAnalyze::getIntconstv()
{
	return this->intconstv;
}
char WordAnalyze::getCharconstv()
{
	return this->charconstv;
}
float WordAnalyze::getFloatconstv()
{
	return this->floatconstv;
}
char *WordAnalyze::getStringconstp()
{
	return this->stringconstv;
}
char *WordAnalyze::getWord()
{
	return this->word;
}

int WordAnalyze::getLine()
{
	if(fgets((this->line),line_max_len,(this->input_file)) == NULL)
		return EOF;
	this->line_len = strlen(this->line);
	this->line_count ++;
	return 0;
}

bool isStringchar(char ch)
{
	return (ch-' ' == 0 || ch-' ' == 1 || (ch-' '>=3 && ch-' '<=94));
}
void chs3(int ch)
{
    printf("\n\n==================\n");
    printf("run end\n");
    exit(0);
}
Symbol getSingleChSy(char ch)
{
	switch(ch)
	{
		case '+':
			return myplus;
			break;
		case '-':
			return myminus;
			break;
		case '*':
			return mymult;
			break;
		case '/':
			return mydiv;
			break;
		case '(':
			return lparent;
			break;
		case ')':
			return rparent;
			break;
		case '[':
			return lbrack;
			break;
		case ']':
			return rbrack;
			break;
		case '{':
			return lbrace;
			break;
		case '}':
			return rbrace;
			break;
		case ',':
			return comma;
			break;
		case ';':
			return semicolon;
			break;
		case ':':
			return colon;
			break;
	}
    return colon;
}
int WordAnalyze::getWordSymbol(Symbol *sy)
{
	while(true)
	{
	    if(CIGWS == '}')
            CIGWS = getNextCh();

		while(isspace(CIGWS)){
			CIGWS = getNextCh();
		}

		if(isalpha(CIGWS) || CIGWS == '_')
		{
			int i=0;
			strcpy((this->word),"                    \0");
			for (i = 0;isalnum(CIGWS) || CIGWS=='_'; i++) {
				if(i<word_max_len-1)
				{
//				    if(isalpha(CIGWS))
//                        this->word[i] = tolower(CIGWS);
//                    else
                    this->word[i] = CIGWS;
				}
                CIGWS = getNextCh();
			}
			for (i = 0; i < key_list_size; i++) {
				if(strcmp(key[i],(this->word)) == 0)
					break;
			}
			if(i < key_list_size)
            {
                *sy = key_sy[i];
            }
			else
            {
                *sy = ident;
            }
			break;
		}
		else if(isdigit(CIGWS))
		{
			int marknumstart = this->char_count -1;
			char startChar = CIGWS;
			*sy = intcon;
			int num_len = 1;
			CIGWS = getNextCh();
			if(CIGWS == '0' && startChar == '0')
			{
				printf("Warning line %d:%d : " ,this->line_count,this->char_count);
				printf("too many useless zero in front of a number\n");
			}
			while(isdigit(CIGWS))
			{
				num_len ++;
				CIGWS = getNextCh();
			}
			if(CIGWS=='.')
			{
				*sy = floatcon;
				do{
					CIGWS = getNextCh();
				}while(isdigit(CIGWS));
			}
			if(*sy == intcon)
			{
				long temp;
				sscanf((this->line)+marknumstart,"%ld",&temp);
				if(temp > INT_MAX || num_len > 10)
					printf("Warning line %d:%d : the int contant is too long\n",this->line_count,this->char_count);
			}
			//read as a float no matter it is a int or a float;
			sscanf((this->line)+marknumstart,"%f",&(this->floatconstv));
			sscanf((this->line)+marknumstart,"%d",&(this->intconstv));
			//this->intconstv = (int)this->floatconstv;
			break;
		}
		else if(CIGWS == '"')
		{
			int strl = 0;
			*sy = stringcon;
            CIGWS = getNextCh();
			(this->stringconstv)[strl++] = CIGWS;
			while(CIGWS != '"' && CIGWS != '\n' &&isStringchar(CIGWS))
			{
				CIGWS = getNextCh();
				if(strl < Str_CON_MAX)
					(this->stringconstv)[strl++] = CIGWS;
			}
			if(strl >= Str_CON_MAX)
			{
				printf("Warning near line %d:%d : the string contant is too long,its length must be less than %d .\n",this->line_count,this->char_count,Str_CON_MAX);
			}
			(this->stringconstv)[strl-1] = '\0';
			this->strConLen = strl-1;
			(this->intconstv) = (this->tables)->getSlen();   //get the beginning index of string
			(this->tables)->insertStrconst(this->stringconstv);  //then add new string to stab

			if(CIGWS != '"' && CIGWS != '\n')
			{
				printf("Error near line %d:%d : " ,this->line_count,this->char_count);
				printf("%c is not a legal character in string\n",CIGWS);
				this->errorFlag = true;
				while(CIGWS != '"' && CIGWS != '\n')
					CIGWS = getNextCh();
			}
            CIGWS = getNextCh();
			break;
		}
		else if(CIGWS=='\'')
		{
			*sy = charcon;
			CIGWS = getNextCh();
			this->charconstv = CIGWS;
			CIGWS = getNextCh();
			if(CIGWS == '\'')
			{
				CIGWS = getNextCh();
			}
			else
			{
				printf("Warning: near line %d:%d :",this->line_count,this->char_count);
				printf(" a ' is expected here\n");
			}
			break;
		}
		else if(CIGWS == '=')
		{
			CIGWS = getNextCh();
			if(CIGWS=='=')
			{
				*sy = eql;
				CIGWS = getNextCh();
			}
			else
            {
                *sy = becomes;
            }
			break;
		}
		else if(CIGWS == '<')
		{
			CIGWS = getNextCh();
			if(CIGWS=='=')
			{
				*sy = leq;
				CIGWS = getNextCh();
			}
			else
            {
                *sy = lss;
            }
			break;
		}
		else if(CIGWS == '>')
		{
			CIGWS = getNextCh();
			if(CIGWS=='=')
			{
				*sy = geq;
				CIGWS = getNextCh();
			}
			else
            {
                *sy = grt;
            }
			break;
		}
		else if(CIGWS == '!')
		{
			CIGWS = getNextCh();
			if(CIGWS=='=')
			{
				*sy = neq;
				CIGWS = getNextCh();
			}
			else
            {
				printf("Error : near line %d:%d :",this->line_count,this->char_count);
				printf("wrong character with only a ! \n");
				this->errorFlag = true;
            }
			break;
		}
		else if(GlobalTool::isLegalSingal_ch(CIGWS))
		{
			*sy = getSingleChSy(CIGWS);
            if(CIGWS != '}')
                CIGWS = getNextCh();
			break;
		}
		else if(CIGWS == EOF)
        {
            //exit(0);
			return EOF;
        }
		else
		{
			printf("Error : near line %d:%d :",this->line_count,this->char_count);
			printf("illegal character %c \n",CIGWS);
			this->errorFlag = true;
		    CIGWS = getNextCh();
			continue;
		}
	}

	return 0;
}

void WordAnalyze::tryToRun()
{

	(this->tables)->emitxy(33,0,0);
	if(this->hasMainFlag == false)
	{
		printf("Error there is not main function in the programe\n");
		this->errorFlag = true;
	}
	printf("compile program end\n");
	printf("=========================\n\n");
	fclose(this->input_file);
	this->input_file = NULL;
	if(this->errorFlag == false)
	{
	    //chs3(1);
		Interpret interpret(this->tables);
		interpret.startRun();
	}
	else{
		printf("there are some error in the program so can not run it \n");
	}
	exit(0);
}
void chLine(char line[],int start,int *lineLen)
{
    if((line[start]=='{' || line[start]==';') && line[start+1]=='}')
    {
        int len = *lineLen;
        for(int i=len;i>start+1;i--)
            line[i]=line[i-1];
        line[start+1]=' ';
        line[len+1] = '\0';
        *lineLen = strlen(line);
    }
    else if(line[start] == '*'||line[start] == '/' )
    {
        int i;
        for(i=start+1;line[i]==' '&&i<*lineLen;i++);
        if(line[i] == '+' || line[i] == '-')
        {
            int mark1 = start+1;
            int mark2 = 0;

            int len = *lineLen;
            for(;i<len;i++)
                if(line[i]!='+' && line[i]!='-' && line[i]!=' ')
                    break;
            if(isalnum(line[i]))
            {
                for( ; i<len;i++)
                    if( (!isalnum(line[i])))
                        break;
                if(line[i] == '.')
                {
                    for(i++;i<len;i++)
                        if( (!isalnum(line[i])))
                            break;
                }
                mark2 = i;
                for(i=len+1;i>=mark2+2;i--)
                    line[i] = line[i-2];
                line[i] = ')';
                i--;
                for(;i>=mark1+1;i--)
                    line[i]=line[i-1];
                line[i]='(';
            }
            line[len+2] = '\0';
            *lineLen = strlen(line);
        }
    }
}
char WordAnalyze::getNextCh()
{
	if(this->char_count == line_len)
	{
		if(getLine() == EOF)
		{
			tryToRun();
			return EOF;
		}
		this->char_count = 0;
	}
    chLine(this->line,this->char_count,&(this->line_len));
	char ret = line[this->char_count];
	this->char_count ++;
	return ret;
}

int WordAnalyze::getStrConLen()
{
	return this->strConLen;
}

int WordAnalyze::getLineCount()
{
	return this->line_count;
}
int WordAnalyze::getCharCount()
{
	return this->char_count;
}
void WordAnalyze::setErrorFlag()
{
	this->errorFlag = true;
}
void WordAnalyze::setHasMainFlag()
{
	this->hasMainFlag = true;
}
