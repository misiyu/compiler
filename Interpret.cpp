#include "Interpret.h"

Interpret::Interpret(Table *tables){
	this->tables = tables;
	(this->tables)->showCode();
	this->pc = 0;
	this->base_i = 0;
	this->S_top = (this->tables)->getBTab(0).allSize+5;

	(this->charcnt) =0;

	(this->stk)[0].intconst = 0;  //return result
	(this->stk)[1].intconst = 0;  //RA return address
	(this->stk)[2].intconst = 0;  //SL static link all point to stk[0]
	(this->stk)[3].intconst = 0;  //DL dynamic Link point to previous' static link
	(this->stk)[4].intconst = 0;  //funcion name index in table
	(this->display)[0]=0;
	(this->display)[1]=0;
}

void Interpret::inter0()
{
	switch((this->ins).f)
	{
		case 0:             //取地址语句
			S_top += 1;
			stk[S_top].intconst = display[ins.x]+ins.y;
			break;
		case 1:             //取值语句
			S_top += 1;
			stk[S_top] = stk[display[ins.x]+ins.y];
			break;
		case 2:             //间接装入
			S_top += 1;
			stk[S_top] = stk[stk[display[ins.x]+ins.y].intconst];
			break;
		case 8:
			S_top += 1;
			break;
		case 9:         //栈顶元素加y
			stk[S_top].intconst = stk[S_top].intconst+ins.y;
			break;
		case 3:         //更新display
			int h1 = ins.y;
			int h2 = ins.x;
			int h3 = base_i;
			while(h1 != h2)
			{
				display[h1] = h3;
				h1 --;
				h3 = stk[h3+2].intconst;
			}
			break;
	}
}
void Interpret::inter1()
{
	int h1,h2,h3,h4;
	switch(ins.f)
	{
		case 10:        //无条件跳转
			pc = ins.y;
			break;
		case 11:        //栈顶为假时跳转
			if(!stk[S_top].boolen)
				pc = ins.y;
			break;
		case 12:        //转到y查case表
			h1 = stk[S_top].intconst;
			S_top --;
			h2 = ins.y;
			h3 = 0;
			while(h3 == 0)
			{
				if((this->tables)->getPlist(h2).y == h1)
				{
					h3 = 1;
					pc = (this->tables)->getPlist(h2+1).y;
				}
				else h2 += 2;
				if((this->tables)->getPlist(h2).f != 13)
				{
					pc = h2;
					break;
				}
			}
			break;
		case 14:  // for forstatement
			break;
		case 15:
			break;
		case 16:
			break;
		case 17:
			break;
		case 18:        //标记栈，函数调用时使用
			h2 = (this->tables)->getTab(ins.y).mref;
			h1 = (this->tables)->getBTab(h2).allSize;
			if(S_top+h1 > Stack_MAX_SIZE)
				ps = stkchk;
			else
			{
				S_top += 5;
				stk[S_top-1].intconst = h1-1;
				stk[S_top].intconst = ins.y;
			}
			break;
		case 19:        //调用函数
			h1 = S_top -ins.y;    //ins.y is btab[tab[i].ref].psize-1
			h2 = stk[h1+4].intconst;    //function location in tables
			h3 = (this->tables)->getTab(h2).lev;    //function level
			display[h3+1] = h1;         //store function base address in display
			h4 = stk[h1+3].intconst+h1;
			stk[h1+1].intconst = pc;      //RA
			stk[h1+2].intconst = display[h3];  //SL
			stk[h1+3].intconst = base_i;   //DL
			for(h3 = S_top+1;h3<h4;h3++)
			{
				stk[h3].intconst = 0;
			}
			base_i = h1;
			S_top = h4;
			pc = (this->tables)->getTab(h2).addr.intconst;

			break;
	}
}
void Interpret::inter2()
{
	int h1,h2,h3;
	switch(ins.f)
	{
		case 20:            //取下标变量地址
			h1 = ins.y;  //{ h1 points to atab  }
			h2 = (this->tables)->getATab(h1).high;
			h3 = stk[S_top].intconst;
			if ( h3 < 0)
				ps = inxchk;
			else if ( h3 >= h2 )
					ps = inxchk;
			else
				S_top --;
			//s[t].i := s[t].i+(h3-h2)
			stk[S_top].intconst = stk[S_top].intconst +h3;
			break;
		case 21:            //
			h1 = ins.y;
			h2 = (this->tables)->getATab(h1).high;
			h3 = stk[S_top].intconst;
			if(h3 < 0)
				ps = inxchk;
			else if (h3 >= h2) {
				ps = inxchk;
			}
			else
			{
				S_top--;
				stk[S_top].intconst = stk[S_top].intconst +h3*\
										(this->tables)->getATab(h1).elsize;
			}
			break;
		case 22:
			h1 = stk[S_top].intconst;
			S_top--;
			h2 = ins.y +S_top;
			if(h2 > Stack_MAX_SIZE)
				ps = stkchk;
			else
			{
				while(S_top < h2)
				{
					S_top++;
					stk[S_top] = stk[h1];
					h1++;
				}
			}
			break;
		case 23:
			break;
		case 24:            //装入字面常量
			S_top ++;
			if(S_top > Stack_MAX_SIZE)
				ps = stkchk;
			else
                stk[S_top].charconst = ins.y;
				stk[S_top].intconst = ins.y;
			break;
		case 25:            //装入实数
			S_top ++;
			if(S_top > Stack_MAX_SIZE)
				ps = stkchk;
			else
				stk[S_top].floatconst = (this->tables)->getFloatcon(ins.y);
			break;
		case 26:        //整型转浮点型
			h1 = S_top - ins.y;
			stk[h1].floatconst = stk[h1].intconst;
			break;
		case 27:        //读
			if (ins.y == 1)
            {
                int temp;
                scanf("%d",&temp);
                stk[stk[S_top].intconst].charconst = temp;
                stk[stk[S_top].intconst].intconst = temp;
            }
			else if (ins.y == 2) {
				scanf("%f",&(stk[stk[S_top].intconst].floatconst));
			}else if (ins.y ==3) {
			    char temp;
			    while(true)
			    {
			        scanf("%c",&temp);
			        if(isalnum(temp) || temp=='_' || temp=='+' || temp=='-' || temp=='*' || temp == '/')
                    {
                        stk[stk[S_top].intconst].intconst = temp;
                        stk[stk[S_top].intconst].charconst = temp;
                        break;
                    }
			    }
//				scanf("%c",&(stk[stk[S_top].intconst].charconst));
//				printf("temp = %c\n",stk[stk[S_top].intconst].charconst);

			}
			break;
		case 28:        //写字符串
			h1 = stk[S_top].intconst;
			h2 = ins.y;
			S_top -- ;
			charcnt += h1;
			//if(charcnt > (this->tables)->getSlen())
				//ps = lngchk;
			for(int i=h2;i<h1+h2;i++)
				printf("%c",(this->tables)->getStabch(i));
			break;
		case 29:        //写变量
			if(ins.y == 1)
				printf("%d",stk[S_top].intconst);
			else if (ins.y == 2) {
				printf("%f",stk[S_top].floatconst);
			}else if (ins.y == 3) {
				printf("%c",stk[S_top].charconst);
				//printf("%c",stk[S_top].charconst & 0x7f);
			}
			break;
	}
}
void Interpret::inter3()
{
	switch(ins.f)
	{
		case 30:
			break;
		case 31:
			ps = fin;
			break;
		case 32:
			S_top = base_i -1 ;
			pc = stk[base_i+1].intconst;
			base_i = stk[base_i+3].intconst;
			break;
		case 33:        //退出函数
			S_top = base_i;
			pc = stk[base_i+1].intconst;
			base_i = stk[base_i+3].intconst;
			display[1] = base_i;
			break;
		case 34:        //以栈顶为地址取值
			stk[S_top] = stk[stk[S_top].intconst];
			break;
		case 35:        //逻辑非
			stk[S_top].boolen = !(stk[S_top].boolen);
			break;
		case 36:        //整型求负
			stk[S_top].intconst = -(stk[S_top].intconst);
			break;
		case 37:        //写实数
			printf("%f",stk[S_top].floatconst);
			break;
		case 38:        //栈顶内容存入次栈顶地址
			stk[stk[S_top-1].intconst] = stk[S_top];
			break;
		case 39:        //浮点型等于
			S_top --;
			stk[S_top].boolen = (stk[S_top].floatconst == stk[S_top+1].floatconst);
			break;
	}
}
void Interpret::inter4()
{
	S_top --;
	switch(ins.f)
	{
		case 40:        //浮点型不等于
			stk[S_top].boolen = (stk[S_top].floatconst != stk[S_top+1].floatconst);
			break;
		case 41:        //浮点型小于
			stk[S_top].boolen = (stk[S_top].floatconst <  stk[S_top+1].floatconst);
			break;
		case 42:        //浮点型小于等于
			stk[S_top].boolen = (stk[S_top].floatconst <= stk[S_top+1].floatconst);
			break;
		case 43:        //浮点型大于
			stk[S_top].boolen = (stk[S_top].floatconst >  stk[S_top+1].floatconst);
			break;
		case 44:        //浮点型大于等于
			stk[S_top].boolen = (stk[S_top].floatconst >= stk[S_top+1].floatconst);
			break;
		case 45:        //整型等于
			stk[S_top].boolen = (stk[S_top].intconst == stk[S_top+1].intconst);
			break;
		case 46:        //整型不等于
			stk[S_top].boolen = (stk[S_top].intconst != stk[S_top+1].intconst);
			break;
		case 47:        //整型小于
			stk[S_top].boolen = (stk[S_top].intconst <  stk[S_top+1].intconst);
			break;
		case 48:        //整型小于等于
			stk[S_top].boolen = (stk[S_top].intconst <= stk[S_top+1].intconst);
			break;
		case 49:        //整型大于
			stk[S_top].boolen = (stk[S_top].intconst >  stk[S_top+1].intconst);
			break;
	}
}
void Interpret::inter5()
{
	S_top --;
	switch(ins.f)
	{
		case 50:        //整型大于等于
			stk[S_top].boolen = (stk[S_top].intconst >= stk[S_top+1].intconst);
			break;
		case 51:
			stk[S_top].boolen = (stk[S_top].boolen || stk[S_top+1].boolen);
			break;
		case 52:        //整型加
			stk[S_top].intconst = (stk[S_top].intconst + stk[S_top+1].intconst);
			break;
		case 53:        //整型减
			stk[S_top].intconst = (stk[S_top].intconst - stk[S_top+1].intconst);
			break;
		case 54:        //实型加
			stk[S_top].floatconst = (stk[S_top].floatconst + stk[S_top+1].floatconst);
			break;
		case 55:        //实型减
			stk[S_top].floatconst = (stk[S_top].floatconst - stk[S_top+1].floatconst);
			break;
		case 56:
			stk[S_top].boolen = (stk[S_top].boolen && stk[S_top+1].boolen);
			break;
		case 57:        //整型乘
			stk[S_top].intconst  = (stk[S_top].intconst * stk[S_top+1].intconst);
			break;
		case 58:        //整型除
			if(stk[S_top+1].intconst == 0)
				ps = divchk;
			else
				stk[S_top].intconst = (stk[S_top].intconst / stk[S_top+1].intconst);
			break;
		case 59:
			if(stk[S_top+1].intconst == 0)
				ps = divchk;
			else
				stk[S_top].intconst = (stk[S_top].intconst % stk[S_top+1].intconst);
			break;
	}
}
void Interpret::inter6()
{
	switch(ins.f)
	{
		case 60:    //实型乘
			S_top --;
			stk[S_top].floatconst = stk[S_top].floatconst * stk[S_top+1].floatconst;
			break;
		case 61:    //实型除
			S_top --;
			if(stk[S_top+1].floatconst == 0)
				ps = divchk;
			else
				stk[S_top].floatconst = stk[S_top].floatconst / stk[S_top+1].floatconst;
			break;
		case 62:

			break;
		case 63:
			break;
		case 64:        //实数转整数
		    stk[S_top].charconst = (char)stk[S_top].floatconst;
			stk[S_top].intconst = (int)stk[S_top].floatconst;
			break;
        case 65:        //实数转bool
			stk[S_top].boolen = stk[S_top].floatconst !=0 ;
			break;
        case 66:        //整数转bool
			stk[S_top].boolen = stk[S_top].intconst !=0 ;
			break;
        case 67:        //字符转bool
			stk[S_top].boolen = stk[S_top].charconst != 0;
			break;
        case 68:
			stk[S_top].floatconst = -stk[S_top].floatconst;
			break;
        case 69:        //整型转字符
            stk[S_top].charconst  = stk[S_top].intconst;
            stk[S_top].intconst = stk[S_top].intconst & 0xff;
            break;
	}
}

void Interpret::startRun()
{
	FILE *fp = fopen("pcRoad","w");
	fprintf(fp,"pc\n");
	fclose(fp);
	(this->ins) = (this->tables)->getPlist(this->pc);
	this->pc ++;
	ps = run;
	do
	{
		int temp  = (this->ins).f/10;
		switch(temp)
		{
			case 0: inter0();
					break;
			case 1: inter1();
					break;
			case 2: inter2();
					break;
			case 3: inter3();
					break;
			case 4: inter4();
					break;
			case 5: inter5();
					break;
			case 6: inter6();
					break;
		}
		(this->ins) = (this->tables)->getPlist(this->pc);
		fp = fopen("pcRoad","a");
		fprintf(fp,"%d\n",pc+1);
		fclose(fp);
        this->pc ++;
        if(pc >(this->tables)->getPlist_top())
            break;
        if(ins.f <0 || ins.f > 70)
            break;
        if(S_top > Stack_MAX_SIZE-30)
            ps = stkchk;
	}while(ps == run);
	if(ps == stkchk)
	{
		printf("\nRUN ERROR:running stack over flow!\n");
	}
	else if(ps == inxchk)
	{
		printf("\nRUN ERROR:array's index out of range!\n");
	}
	else if(ps == divchk)
	{
		printf("\nRUN ERROR:a zero may be devide!\n");
	}
	else
	{
		printf("\n\n==================\n");
		printf("run end\n");
	}
}
