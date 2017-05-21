const int MAX = 10;
int gis[26];
int giv1,a[5];
int giv2,giv3;
float gfs[26],gfv1,gfv2,gfv3;
char gcv1,gcv2,gcs[26],gcv3;
char enter;

void init_3()
{
    int i;
    giv1 = 1;
    giv2 = 1;
    giv3 = 1;
    gfv1 = 1;
    gfv2 = 1;
    gfv3 = 1;
    gcv1 = 'a';
    gcv2 = 'b';
    gcv3 = 'c';
    i =0;
    while(i<26)
    {
        gis[i] = i+65;
        gfs[i] = 65.5+i;
        gcs[i] = 'A'+i;
        i = i+1;
    }
}

void test1_3()
{
    int gis[26];
    int giv1,a[5];
    int giv2,giv3;
    float gfs[26],gfv1,gfv2,gfv3;
    char gcv1,gcv2,gcs[26],gcv3;
    giv1 = -60;
    gcv1 = 'a';
    gfv1 = --97.55;
    gfs[5] = 97.55;
    gcs[5] = 'a';
    gis[5] = +60;

    giv2 = gcv1+gcs[5];
    printf(" ", giv2);
    gcv2 = giv2 / 2;
    printf(" ", gcv2);
    giv2 = gfs[5]+1;
    printf(" ", giv2);
    gfv2 = giv2;
    printf(" ", gfv2);
    gcv2 = gfs[5];
    printf(" ", gcv2);
    gfs[5] = gcv2;
    printf(" ", gfs[5]);
}

void test2_3()
{
    gcv3 = 321;
    giv3 = gcv3;
    printf(" ",giv3 );
    gcv3 = 321.99;
    gfv3 = gcv3;
    printf(" ",gfv3 );
    giv3 = 321.99;
    gfv3 = giv3;
    printf(" ", gfv3);
}

int test3_3()
{
    return (gis[0]); 
}
char test4_3()
{
    return (gcs[0]); 
}
float test5_3()
{
    return (gfs[0]); 
}
void test6_3()
{
    giv1 = test4_3()*gis[1]+gis[test4_3()/20];
    printf(" ", giv1);
    gcv1 = --7.8*--54;
    giv1 = gcv1;
    printf(" ", giv1);
    gfv1 = 'a'*6/0.3+5;
    printf(" ", gfv1);
    printf(" ", gcv1+0);
    printf(" ",giv1 );
    printf(" ",test5_3() );
    gfv1 = gfv1 + gcv1*giv1 /0.9 - (test5_3());
    printf(" ", gfv1);
}
void test17_3()
{
    int n;
    int c;
    int f;
    n = 2;
    c = 'a';
    f = 48.5;
    printf(" 1: ");
    if(f == c/n)
        printf(" f == c/n == 48.5" );
    printf(enter);
    printf(" 2: ");
    if(f == --6*--8+++0.7*10/14+'a'-'b'/2- ('a'/2+0.5))
        printf(" f == --6*--8+++0.7*10/14+'a'-'b'/2-('a'/2+0.5) == 48.5" );
    printf(enter);
    printf(" 3: ");
    n = f;
    if(n == ((-'a'+'b')*48 / 5 - 1) *--6)
        printf(" n == ((-'a'+'b')*48 / 5 - 1) * --6 == 48" );
    printf(enter);
    printf(" 4: ");
    n = f;
    if(2.25 ==  - -1.5* - -  1.5)
        printf(" 2.25 ==  - -1.5* - -  1.5" );
    printf(enter);
}
void main()
{
    enter = 10;
    init_3();
    test1_3();
    printf(enter );
    test2_3();
    printf(enter );
    test6_3();
    printf(enter );
    test17_3();
}
