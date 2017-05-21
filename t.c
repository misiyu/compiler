const int PrimeNum = 11;
int prime[11] ;
void init()
{
    prime[0] = 2;
    prime[1] = 3;
    prime[2] = 5;
    prime[3] = 7;
    prime[4] = 11;
    prime[5] = 13;
    prime[6] = 17;
    prime[7] = 19;
    prime[8] = 23;
    prime[9] = 29;
    prime[10] = 31;
    prime[13] = 1;
}
int mod(int n,int p)
{
    while(n >= p)
        n = n-p;
    return (n);
}
int divisors(int n){
    int i, k , m;
    k = 1;
    i = 0;
    while(i<PrimeNum)
    {
        m = 0;
        while(mod(n,prime[i]) == 0)
        {
            n = n/prime[i];
            m = m+1;
        }
        if(m > 0)
            k = K*(M+1);
        i = i+1;
    }
    if(k == 1)
        return (0);
    return (k);
}
int getAntiprime(int n){
    int m, i, k, max , num , count;
    max  = 0;
    num = 0;
    i = 0;
    k =1;
    while(k*k <= n)
    {

        k =k* prime[i];
        i = i+1;
    }
    m = k;
    while(k <= n){
        count = divisors(k);
        if(count > max){
            max = count;
            num = k;
        }
        k =k + m;
    }
    return (num);
}

void main()
{
    int n;
    scanf(n);
    init();
    printf(" ", getAntiprime(n));
}

