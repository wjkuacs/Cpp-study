#include <bits/stdc++.h>
using namespace std;
int q(int n,int a,int b)
{
    int result;
    if(n==1)
    {
        result=a;
    }
    else
    {
        result=b*q(n-1,a,b);
    }
    return result;
}
int main()
{
    int n,a,b;
    cout<<"请输入等比数列的项数n:";
    cin>>n;
    cout<<"请输入等比数列的首项a:";
    cin>>a;
    cout<<"请输入等比数列的公比b:";
    cin>>b;
    cout<<"这个以"<<a<<"为首项，"<<"以"<<b<<"为公比的等差数列的第"<<n<<"项值为"<<q(n,a,b)<<endl;
    
    
    
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=i;j++)
        {
            
        }
    }
    
    
    
    
    
    system("pause");
    return 0;
}