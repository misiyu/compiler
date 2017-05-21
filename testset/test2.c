const int icon1=+1,MAX=10;
const int icon2=-2,icon3=3;
const float fcon1=0.5,fcon2=1.,fcon3=+-3.4;
const char ccon1='A';
int test1()
{
    const int icon3 = 0;
    return (1);
}
int test2()
{
    const int icon3 = 0;
    int n;
    return (2.3);
}
int test3()
{
    int n;
    return ('A');
}
float test4()
{
    return (1);
}
float test5()
{
    return (2.3);
}
float test6()
{
    return ('A');
}
char test7()
{
    return (65);
}
char test8()
{
    return (65.7);
}
char test9()
{
    return ('A');
}
void test10(int a)
{
    printf("  test10 a =",a );
}
void test11(int a,int b)
{
    printf("  test11 a =",a );
    printf("  test11 b =",b );
    return ;
}
void test12(int a,char c,float f)
{
    printf("  test12 a =",a );
    printf("  test12 c =",c );
    printf("  test12 f =",f );
    return ;
}
void test13(){}
void test14(){;}
void test15()
{
    char enter;
    enter = 10;
    printf(" ",test1());
    printf(enter);
    printf(" ",test2());
    printf(enter);
    printf(" ",test3());
    printf(enter);
    printf(" ",test4());
    printf(enter);
    printf(" ",test5());
    printf(enter);
    printf(" ",test6());
    printf(enter);
    printf(" ",test7());
    printf(enter);
    printf(" ",test8());
    printf(enter);
    printf(" ",test9());
    printf(enter);
    test10(1);
    printf(enter);
    test11(1,2);
    printf(enter);
    test12(65,'A',65.77);
    printf(enter);
    test12(65.77,'A',65);
    printf(enter);
    test12('A',65,65.77);
    printf(enter);
    test12('A',65.77,65);
    printf(enter);
    test12(65,65.77,'A');
    printf(enter);
    test12(65.77,65,'A');
    printf(enter);
    test13();
    test14();
}
void main()
{
    test15();
}