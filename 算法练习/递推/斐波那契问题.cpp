#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin>>n;
    long long rabbit[100001];
    rabbit[1]=1;
    rabbit[2]=1;
    for(int i=3;i<=n;i++)
    {
        rabbit[i]=rabbit[i-1]+rabbit[i-2];
    }
    cout<<rabbit[n]<<endl;
    system("pause");
    return 0;
}