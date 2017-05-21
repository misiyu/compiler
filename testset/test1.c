void Test1_1(int p1,char p2,float p3)
{
    const int MAX=20,MIN=0;
    const char grade='A';
    const float PAI=3.14;
    int i;
    i=1+1.2;
    if(1<=1.0)
        if(0!=1)
            if(0==0)
                if(1>0)
                    if(1>=0)
                        i=1*1;
    printf(i);
}
void test2_1()
{
    printf(" test2_1");
}
float test6_1()
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

void test21_1()
{
    int i;
    i = 1;
    printf("test21_1");
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
        test2_1();
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
        test2_1();
}

void test22_1()
{
    int i;
    i=1;
    printf("test22_1");
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
        printf(test6_1());
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
    while(0);
    while(0){}
    i =1;
    while(i)
        return ;
}
void test23_1()
{
    int i,j;
    char enter;
    enter = 10;
    i =0;
    j =1;
    printf("test23_1");
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
                test2_1();
            case 5:
                {}
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
    char enter;
    enter = 10;
    printf("test1_1============= " );
    printf(enter );
    test1_1(1,'a',0.9);
    printf(enter );
    printf("test2_1============= " );
    printf(enter );
    printf(test6_1());
    printf(enter );
    printf("test3_1============= " );
    printf(enter );
    test21_1();
    printf(enter );
    printf("test4_1============= " );
    printf(enter);
    test22_1();
    printf(enter );
    printf("test5_1============= " );
    printf(enter);
    test23_1();
}
