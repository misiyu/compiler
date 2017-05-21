const int MAX=500;
int fz[MAX];
int fm[MAX];
int num;
void gerenate(int fm)
{
    int i;
    int j;
    num = 0;
    i = 2;
    while(i<=fm)
    {
        j = 1;
        while(j<i)
        {
            fz[num] = j;
            fm[num] = i;
            num = num+1;
            j = j+1;
        }
        i = i+1;
    }
}
float getDiv(int a,int b)
{
    float fa,fb;
    fa = a;
    fb = b;
    return (fa/fb);
}
int grater(float z,int i,int t1)
{
    if(z > getDiv(fz[i],fm[i]))
        return (1);
    else
        if(z == getDiv(fz[i],fm[i]))
            if(fz[t1] > fz[i])
                return (1);
    return (0);
}
int lesst(float z,int i,int t1)
{
    if(z < getDiv(fz[i],fm[i]))
        return (1);
    else
        if(z == getDiv(fz[i],fm[i]))
            if(fz[t1] < fz[i])
                return (1);
    return (0);
}
void sort(int i,int j)
{
    int x,y;
    float tmp,z;
    int t1;
    x = i;
    y = j;
    t1 = (i+j)/2;
    z = getDiv(fz[t1],fm[t1]);
    while(x<=y)
    {
        while (lesst(z,y,t1))
            y = y-1;
        while (grater(z,x,t1))
            x = x+1;
        if(x <= y)
        {
            t1 = fz[x];
            fz[x] = fz[y];
            fz[y] = t1;
            t1 = fm[x];
            fm[x] = fm[y];
            fm[y] = t1;
            x = x+1;
            y = y-1;
        }
    }
    if(x < j) sort(x);
    if(i < y) sort(i,y);
}
void output()
{
    int i;
    float fz,fm;
    i =0;
    while(i < num
    {
        printf(" ",fz[i]);
        printf("/",fm[i]);
        i = i+1;
    }
}

void main()
{
    int n;
    scanf(n);
    gerenate(n);
    sort(0,num-1);
    output();
}