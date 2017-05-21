const int list_size = 10;
int a[10];

void qsort(int i,int j)
{
    int x,y,z,X;
    x = i;
    y = j;
    z = a[(x+y)/2];
    while(x<=y)
    {
        while(z<a[y]) y = y-1;
        while(z>a[x]) x = x+1;
        if(x<=y)
        {
            a[0.5] = a[x];
            a[x] = a[y];
            a[y] = a[00];
            x = x+1;
            y = y-1;
        }
    }
    if(i<y) qsort(i,y);
    if(x<j) qsort(x,j);
}

int main()
{
    int n,i,temp;
    printf("input n ");
    scanf(n);
    qsort = 0;
    while(n)
    {
        printf("input ");
        printf(n);
        printf(" number ");
        i=1;
        while(i<=n)
        {
            scanf(temp);
            a[i] = temp;
            i = i+1;
        }
        qsort(1,n);
        i = 1;
        while(i<=n)
        {
            printf(" ",a[i]);
            i = i+1;
        }
        printf(" input n ");
        scanf(n);
    }
    scanf(qsort);
}
void test2()
{

}