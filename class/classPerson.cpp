#include<bits/stdc++.h>
using namespace std;



class Person
{
    public:
    string m_Name;

    protected:
    string m_Car;

    private:
    int m_Password;

    public:
    void func()
    {
        m_Name = "张三";
        m_Car = "奔驰";
        m_Password = 123456; 
    }
};

int main()
{
    Person p1;
    p1.m_Name = "李四";
    //p1.m_Car = "宝马";        此为保护权限，类外无法访问
    //p1.m_Password = 123； 此为私有权限，类外无法访问
    system("pause");
    return 0;
}