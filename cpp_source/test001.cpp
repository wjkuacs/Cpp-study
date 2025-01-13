#include <bits/stdc++.h>
using namespace std;
//这是一个计算n！的和的程序，也是作为新的编辑器刚刚配置了C++环境之后的测试
//很久没有写C++代码了，还是有一些生疏。
int factorial(int n)
{
    int result = 1;
    if(n==0)
    {
        result =1;
    }
    else
    {
        for(int j=1;j<=n;j++)
        {
            result *=j; 
        }
    }
    return result;
}
int main()
{
    int i=0,sum=0,n;
    cout<<"请输入目标数字n：";
    cin>>n;
    for(i=0;i<=n;i++)
    {
        sum += factorial(i);
    }
    cout<<"n的阶乘之和为："<<sum<<endl;
    system("pause");
    return 0;
}