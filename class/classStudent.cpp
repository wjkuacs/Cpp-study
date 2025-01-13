#include<iostream>
#include<string>
using namespace std;

//设计一个学生类，属性有姓名和学号

class Student
{
    public:
    //类中的属性和行为统一称为“成员”
    //属性 被称为  成员属性或成员变量
    //行为 被称为  成员函数或成员方法

    //属性
    string m_name;
    int m_Id;

    //行为
    
    void setName(string name)
    {
        m_name = name;
    }
    void setID(int Id)
    {
        m_Id = Id;
    }
    
    void showStudent()
    {
        cout<<"姓名："<<m_name<<"     学号："<<m_Id<<endl;
    };

    
};

int main()
{
    Student s1;
    //s1.name = "张三";
    s1.setName("张三");
    //s1.m_Id = 1;
    s1.setID(1);
    s1.showStudent();
    system("pause");
    return 0;
}