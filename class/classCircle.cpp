#include<iostream>
using namespace std;


//设计一个圆类，求圆的周长
//圆求周长的公式：2*PI*r

//圆周率
const double PI = 3.14;

//class 代表设计一个类，后面紧跟着的就是类的名称
class Circle
{
    //访问权限
    //公共权限
    public:
    //属性
    //半径
    double m_r;
    //行为
    //获取圆的周长
    double calculateZC()
    {
        return 2*PI*m_r;
    }
};

int main()
{
    //通过圆类来创造一个具体的圆（对象）
    Circle cl;
    //给圆对象的属性进行赋值
    //实例化        （通过一个类创建一个对象的过程）
    cl.m_r = 10;
    cout<<"圆的周长为："<<cl.calculateZC()<<endl;
    system("pause");
    return 0;
}