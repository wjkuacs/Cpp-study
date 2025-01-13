#include<bits/stdc++.h>
using namespace std;


// 成员属性设置为私有
//1、可以控制读写权限
//2、对于写可以检测数据的有效性

//人类
class Person
{
    public:
        //设置姓名
        void setName(string name)
        {
            m_Name = name;
        }
        //获取姓名
        string getName()
        {
            return m_Name;
        }

        //获取年龄
        int getAge()
        {
            return m_Age;
        }

        //设置偶像
        void setIdoi(string Idoi)
        {
            m_Idol = Idoi;
        }
    private:

        string m_Name;  //姓名  可读可写

        int m_Age = 18;  //年龄 只读

        string m_Idol;  //偶像 只写
};

int main()
{
    Person p;
    //姓名设置
    p.setName("张三");

    //姓名读取
    cout<<"姓名："<<p.getName()<<endl;

    //年龄读取（只能读取，不能获取）
    cout<<"年龄："<<p.getAge()<<endl;

    //偶像设置
    p.setIdoi("蔡徐坤");
    //cout<<"偶像："<<p.getIdol()<<endl;    只写状态，外界无法访问，但内部可以输入
    system("pause");
    return 0;
}