const int icon1=+1,MAX=10;
const int icon2=-2,icon3=3;
const float fcon1=0.5,fcon2=1.,fcon3=+-3.4;
const char ccon1='A';
char gcvar1;
int givar1 , givar2;
float gfvar1 , gfvar2;
char enter;

int gis[10];
float gfs[10];
char gcs[10];

void test4()
{
    const int icon1=+2,MAX=9;
    printf(" ",icon1);
    printf(" ",MAX);
}

void test9()
{
    int n1,n2,n3;
    float f1,f2,f3;
    char c1,c2,c3;
    printf(enter);
    n1 = +0;
    printf(" 1:n1=",n1);
    n2 = -0;
    printf(" 2:n2=",n2);
    n3 = -3;
    printf(" 3:n3=",n3);
    n1 = +3;
    printf(" 4:n1=",n1);
    n1 = 1+2*3;
    printf(" 5:n1=",n1);
    n1 = 100*((2+3)*3);
    printf(" 6:n1=",n1);
    n1 = 2*((3+3)/3);
    printf(" 7:n1=",n1);
    f1 = ++1;
    printf(" 8:f1=",f1);
    f1 = --1;
    printf(" 9:f1=",f1);
    f1 = -f1*--0.5/ + - 0.5 * + -1;
    printf(" 10:f1=",f1);
    c1='b';
    n1 = c1+(-1);
    printf(" 11:n1=",n1);
    f1 = c1*0.5;
    printf(" 12:f1=",f1);
}

void test10()
{
    int i;
    i=0;
    givar1 = 2;
    givar2 = 3;
    gfvar1 = fcon1;
    gfvar2 = fcon2;
    gcvar1 = ccon1;
    while(i<MAX)
    {
        gis[i] = i+1;
        gfs[i] = i/10;
        gcs[i] = 'a'+i;
        i = i+1;
    }
}
void test11()
{
    int i;
    i=0;
    printf(enter);
    printf(" 1:givar1=",givar1);
    printf(" 2:givar2=",givar2);
    printf(" 3:gfvar1=",gfvar1);
    printf(" 4:gfvar2=",gfvar2);
    printf(" 5:gcvar1=",gcvar1);
    while(i<MAX)
    {
        printf(" ",gis[i]);
        printf(" ",gfs[i]);
        printf(" ",gcs[i]);
        i = i+1;
    }
}

int test12(int n)
{
    printf(n);
    return (n-1);
}


float test13(int n, float f, char ch)
{
    return (n+f+ch);
}
int test14(int n)
{
    return (n+2);
}
char test15()
{
    return ('a');
}

void Test1(int p1,char p2,float p3)
{
    const int MAX=20,MIN=0;
    const char grade='A';
    const float PAI=3.14;
    int i;
    i=1+1;
    if(1<=1)
        if(0!=1)
            if(0==0)
                if(1>0)
                    if(1>=0)
                        i=1*1;
    printf(i);
}

void TEst_2(int n)
{
    if(n>0)
    {
        printf(" ",n);
        test_2(n-1);
    }
    else
        return ;
}

char test3_1()
{
    return (65);
}

void test3()
{
    char chs[4];
    char ch;
    printf(enter);
    chs[0] = 'a';
    ch = 'b';
    printf(" ",-ch);
    printf(" ",ch);
    printf(" ",chs[0]+ch);
    printf(" ",'a');
    printf(" ",-'a');
    printf(" ",test3_1() );
}

float test6()
{
    int i;
    i = 0;
    while(i<1)
    {
        i = i+1;
        if(i == 1)
            switch(i)
            {
                case 1: 
                    if(i == 1)
                        while(i == 1)
                        {
                            return (1.0);
                        }
            }
    }
}

int test17()
{
    return (1);
}
int test19(int a,int b)
{
    return (a+b);
}

float test18()
{
    gfs[0]= 0.1;
    gfs[1]= 0.2;
    gfs[2] = 0.3;
    gfs[3] = gfs[test17()] + gfs[test17()*test19(1,1)];
    printf(gfs[3]);
    return (gfs[3]);
}

void test20()
{
    gis[0] = 1;
    gis[1] = 2;
    gis[2] = 3;
    gis[3] = 4;
    printf(gis[gis[gis[0]]]);
}

void test21()
{
    int i;
    i = 1;
    printf("test21");
    printf(enter);
    printf(" 1: ");
    if(1)
        while(i)
            i=0;
    printf(" 2: ");
    if(1)
    {

    }
    printf(" 3: ");
    if(1)
        test20();
    printf(" 4: ");
    if(1)
        i = 2;
    printf(" 5: ");
    if(1)
        scanf(i);
    printf(" 6: ");
    if(1)
        printf(i);
    printf(" 7: ");
    if(1)
        switch(i)
        {
            case 1: printf("111 ");
            case 2: printf("222 ");
        }
    printf(" 8: ");
    if(1);
    printf(" 9: ");
    if(0)
        ;
    else
        ;
    printf(" 10: ");
    if(0)
        return ;
    else
        test18();
}

void test22()
{
    int i;
    i=1;
    printf("test22");
    printf(enter);
    printf(" 1: ");
    while(i)
        if(i)
        {
            printf("111 ");
            i = 0;
        }
    i = 1;
    printf(" 2: ");
    while(i)
        while(i)
            i = 0;
    i = 1;
    printf(" 3: ");
    while(i)
    {
        i = 0;
    }
    i =1;
    printf(" 4: ");
    while(i)
    {
        printf(test18());
        i = 0;
    }
    i =1;
    printf(" 5: ");
    while(i)
        i = 0;
    i =1;
    printf(" 6: ");
    while(i)
        scanf(i);
    printf(" 7: ");
    while(i)
        printf("aaa ");
    printf(" 8: ");
    while(i) ;
    i =1;
    while(i)
        switch(i)
        {
            case 1: i=0;
            case 2: i=0;
        }
    i =1;
    while(i)
        return ;
}

void test23()
{
    int i,j;
    char enter;
    enter = 10;
    i =0;
    j =1;
    printf("test23");
    printf(enter);
    while(i < 12)
    {
        printf(enter );
        printf(" ",i);
        printf(" ");
        switch(i)
        {
            case 0:
                {

                }
            case 1:
                if(i>0)
                    printf(" aaa ");
            case 2:
                if(i >5 )
                    printf(" aaa ");
                else
                    printf(" bbb ");
            case 3:
                while(j)
                    j = 0;
            case 4:
                test17();
            case 5:
                test18();
            case 6:
                j = 1;
            case 7:
                scanf(j);
            case 8:
                printf(" 888 ");
            case 9: ;
            case 10:
                switch(i)
                {
                    case 10:
                        printf(" 101010 ");
                }
            case 11:
                return ;
        }
        i = i+1;
    }
}

void main()
{
    int n;
    n = 1;
    enter = 10;
    while(n)
    {
        scanf(n);
        switch(n)
        {
            case 1:
            {
                printf(" ===test9=== ");
                test9();
            }
            case 2:
            {
                test10();
                printf(" ===test11=== ");
                test11();
            }
            case 3:
            {
                printf(" ===test12=== ");
                test12(test12(test12(test12(test12(5)))));
            }
            case 4:
            {
                printf(" ===test14=== ");
                printf(test13(test14(1),0.5,test15())*test14(0));
            }
            case 5:
            {
                printf(" ===test1=== ");
                test1(1,'a',0.9);
            }
            case 6:
            {
                printf(" ===test_2=== ");
                printf(enter);
                test_2(5);
            }
            case 7:
            {
                printf(" ===test3=== ");
                test3();
            }
            case 8:
            {
                printf(" ===test6=== ");
                printf(test6());
            }
            case 9:
            {
                printf(" ===test4=== ");
                test4();
            }
            case 10:
            {
                printf(" ===test21=== ");
                test21();
            }
            case 11:
            {
                printf(" ===test22=== ");
                test22();
            }
            case 12:
            {
                printf(" ===test23=== ");
                test23();
            }
            case 13:
            {
                n = 0;
            }
        }
        
        
    }
}
