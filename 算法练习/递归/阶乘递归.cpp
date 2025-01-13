#include<bits/stdc++.h>
using namespace std;
//定义阶乘函数factorial(n)
int factorial(int n)
{
    int result;
    if(n==0)
    {
        result=1;
    }
    else
    {
        result=n*factorial(n-1);
    }
    return result;
}

int main()
{
    int n;
    cout<<"请输入所要求的阶乘的n:";
    cin>>n;
    cout<<"n的阶乘为"<<factorial(n)<<endl;
    system("pause");
    return 0;
}