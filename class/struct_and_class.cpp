//struct 和 class 的区别在于其默认的访问访问权限不同
//struct 默认权限是 public
//class 默认权限是 private

#include<bits/stdc++.h>
using namespace std;

class C1
{
    int m_A;        //默认权限为私有权限
};

struct C2
{
    int m_A;        //默认权限为公共权限
};

int main()
{
    //struct 和 class 的区别
    C1 c1;
    //c1.m_A = 100;     会报错，因此 class 的默认权限为私有
    C2 c2;
    c2.m_A = 100;       //不会报错，因此 struct 的默认权限为公有
    system("pause");
    return 0;
}
