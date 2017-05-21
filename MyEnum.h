#ifndef MYENUM_H_INCLUDED
#define MYENUM_H_INCLUDED

enum Symbol{
	intcon,floatcon,charcon,stringcon,myplus,myminus,mymult,mydiv,
	eql,neq,grt,geq,lss,leq,lparent,rparent,lbrack,rbrack,
	comma,semicolon,colon,becomes,lbrace,rbrace,period,
	const_sy,ident,if_sy,else_sy,while_sy,switch_sy,case_sy,
	printf_sy,scanf_sy,void_sy,return_sy,int_sy,char_sy,
	float_sy
};

enum SYMtype{
	func,var,constant,arr
};
#endif // MYENUM_H_INCLUDED
