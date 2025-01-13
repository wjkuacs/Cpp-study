#include <bits/stdc++.h>
using namespace std;

double rabbit1(int n)
{
    double result1;
    if(n==1||n==2)
    {
        result1=1;
    }
    else
    {
        result1 =rabbit1(n-1)+rabbit1(n-2);
    }
    return result1;
}

double rabbit2(int n)
{
    double result2;
    if(n==1)
    {
        result2=1;
    }
    else if(n==2)
    {
        result2=2;
    }
    else
    {
        result2 = rabbit2(n-1)+rabbit2(n-2);
    }
    return result2;
}

int main()
{
    int n,i=1;
    double sum=0;
    cin>>n;
    for(i=1;i<=n;i++)
    {
        sum+=rabbit1(i)/rabbit2(i);
    }
    cout<<sum<<endl;
    system("pause");
    return 0;
}