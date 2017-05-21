char enter;
int FIB(int x)
{
    if(x==1)
        return (1);
    if(x == 2)
        return (1);
    else
        return(fib(x-1)+fib(x-2));
}
void test5_1()
{
	int i;
    i = 1;
    while(i<=7)
    {
        printf(" ",fib(i));
        i = i+1;
    }
}
void test5_2()
{
	int a;
	char c;
	float f;
	scanf(a);
	printf(" ", a);
	scanf(a,c);
	printf(" ", a);
	printf(" ", c);
	scanf(a,c,f);
	printf(" ", a);
	printf(" ", c);
	printf(" ", f);
}

void test5_3()
{
	char chs[4];
	char ch;
	chs[0] = 'a';
	ch = 'b';
	printf(" ",-ch);
	printf(" ",ch);
	printf(" ",chs[0]+ch);
	printf(" ",'a');
	printf(" ",-'a');
}
void test5_4()
{
	char chs;
	char enter;
	enter = 10;
}
void test5_5()
{
	int n;
	char c;
	n = 32;
	while(n<=126)
	{
		c= n;
		printf( c);
		n = n+1;
	}
}
void main()
{
	enter = 10;
	test5_1();
	printf(enter );
	test5_3();
	printf(enter );
	test5_4();
	printf(enter );
	test5_5();
	printf(enter );
	scanf(enter);
	printf(" ", enter);
	test5_2();
}