void main()
{
    int n;
    char c;
    float f;
    char enter;
    enter = 10;
    printf("test17_1===========");
    printf(enter);
    
    printf(" 1: ");
    if(7.6 > 7)
        printf(" 7.6 > 7 ");
    printf(enter);
    printf(" 2: ");
    if(111.3333 > 'a')
        printf(" 111.3333 > 'a' ");
    printf(enter);
    printf(" 3: ");
    if(97.00 == 'a')
        printf(" 97.00 = 'a' ");
    printf(enter);
    printf(" 4: ");
    n = 90;
    if(n == 90.000)
        printf("n=90 n == 90.000 ");
    printf(enter);
    printf(" 5: ");
    c = 'b';
    f = 98.000;
    if(f == c)
        printf("c = 'b' f = 98.000 c == f ");
    printf(enter);
    printf(" 6: ");
    n = 98;
    if(n == c)
        printf("c = 'b' n = 98 c == n ");
    printf(enter);
    printf(" 7: ");
    printf(enter);
    printf("test17_2===========");
    printf(enter);
    printf(" 1: ");
    if(11.5 >= 10)
        if(13.444 > 10)
            if(13.444 != 10)
                if(3.444 < 10)
                    if(3.444 <= 10)
                        printf("fconst cmp intconst");
    printf(enter);
    printf(" 2: ");
    n = 10;
    if(11.5 >= n)
        if(13.444 > n)
            if(13.444 != n)
                if(3.444 < n)
                    if(3.444 <= n)
                        printf("fconst cmp int var");
    printf(enter);
    printf(" 3: ");
    n = 10;
    f = 11.44;
    if(f >= n)
        if(f > n)
            if(f != n)
            {
                f = 3.44;
                if(f < n)
                    if(f <= n)
                        printf("float var cmp int var");
            }
    printf(enter);
    printf(" 4: ");
    f = 11.44;
    if(f >= 10)
        if(f > 10)
            if(f != 10)
                if(f < 100)
                    if(f <= 100)
                        printf("float var cmp intconst");
    printf(enter);
    printf(" 5: ");
    f = 97.44;
    if(f >= 'a')
        if(f > 'a')
            if(f != 'a')
                if(f < 'b')
                    if(f <= 'b')
                        printf("float var cmp charconst");
    printf(enter);
    printf(" 6: ");
    f = 97.44;
    if(97.44 >= 'a')
        if(97.44 > 'a')
            if(97.44 != 'a')
                if(97.44 < 'b')
                    if(97.44 <= 'b')
                        printf("float const cmp charconst");
    printf(enter);
    printf(" 7: ");
    f = 97.44;
    c = 'a';
    if(97.44 >= c)
        if(97.44 > c)
            if(97.44 != c)
            {
                c = 'b';
                if(97.44 < c)
                    if(97.44 <= c)
                        printf("float const cmp char var");
            }
    printf(enter);
    printf(" 7: ");
    f = 97.44;
    c = 'a';
    if(f >= c)
        if(f > c)
            if(f != c)
            {
                c = 'b';
                if(f < c)
                    if(f <= c)
                        printf("float var cmp char var");
            }
    printf(enter);

    ;;;;;;;
}