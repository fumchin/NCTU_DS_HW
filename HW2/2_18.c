#include <stdio.h>

int C(int n,int k)
{
    if(n==k || k==0)
    {
        return 1;
    }
    else if(n>k && k>0)
    {
        return C(n-1,k) +C(n-1,k-1);
    }
}

int main()
{
    printf("input n and k: ");
    int n,k;
    while(scanf("%d%d",&n,&k) != EOF)
    {
        printf("%d\n",C(n,k));
        printf("input n and k: ");
    }

    return 0;
}
