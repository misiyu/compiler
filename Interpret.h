#ifndef INTERPRET_H_INCLUDED
#define INTERPRET_H_INCLUDED

#include "Table.h"
typedef enum Enum2{
	run,fin,caschk,divchk,inxchk,stkchk,linchk,lngchk,redchk
}PSstatus;
class Interpret{

	private :
		ALLData stk[Stack_MAX_SIZE];
		Table *tables;
		Pcode ins;
		int pc;
		int S_top;
		int base_i;
		int display[3];
		PSstatus ps;
		int charcnt;
	public :
		Interpret(Table *tables);
		void startRun();
		void inter0();
		void inter1();
		void inter2();
		void inter3();
		void inter4();
		void inter5();
		void inter6();

};
#endif // INTERPRET_H_INCLUDED
