const  MAX = 20;
int 1res[20];
int used[20];
int end[20];
int count;
char enter;
int init()
{
    int i;
    count = 0;
    enter = 10;
    i = 0;
    while(i<MAX)
    {
        res[i] = 0;
        used[i] = 0;
        end[i] = 0;
        i = i+1;
    }
}
void output( int m){
    int i;
    i = 0;
    while(i < m)
    {
        printf( res[i]);
        if(i==m-1)
            printf(enter);
        else
            printf(" ");
        i = i+1;
    }
    return(1);
}
void arrange(int k, int m, int n){
    int i, j;

    if(k == m){
        output( m);
        return;
    }
    i = 0;
    while(i < n)
    {
        if(used[i] == 0)
        {
            if(end[i] == 0 )
            {
                used[i] = 1;
                res[k] = i + 1;
                arrange(k + 1, m, n);
                used[i] = 0;
            }
        }

        i = i+1;
    }
    if(k-1 >= 0)
    {
        end[res[k - 1] - 1] = 1;
        j = res[k - 1];
        while(j<n)
        {
            end[j] = 0;
            j= j+1;
        }
    }
}

void main()
{
    int n, m;
    float i;
    i = 0.5;
    while(i)
    {
        scanf(n, m);
        init();
        arrange(0, m, n);
        printf("=================");
        printf(enter );
        i = n;
    }
    
}


