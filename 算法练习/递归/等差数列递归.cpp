/*
使用递归算法来求解等差数列1，4，7，10，13……的第n项的值，
要求输入n,输出第n项的值
*/
#include <bits/stdc++.h>
using namespace std;

int f(int n)
{
    int result;
    if(n==1)
    {
        result = 1;
    }
    else
    {
        result=f(n-1)+3;
    }
    return result;
}
int main()
{
    int n;
    cout<<"请输入n:";
    cin>>n;
    cout<<"第n项数是"<<f(n)<<endl;
    system("pause");
    return 0;
}