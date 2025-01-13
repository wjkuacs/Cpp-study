#include <bits/stdc++.h>
using namespace std;

int rabbit(int n)
{
    int result;
    if(n==1||n==2)
    {
        result = 1;
    }
    else
    {
        result = rabbit(n-1)+rabbit(n-2);
    }
    return result;
}
int main()
{
    int n;
    cin>>n;
    cout<<rabbit(n)<<endl;
    system("pause");
    return 0;
}