#include<bits/stdc++.h>
using namespace std;


//1、求出立方体的面积（S）和体积（V）
//2、分别使用全局函数和成员函数判断两个立方体是否相等


class Cube
{
    public:
    //获取长宽高
    //设置长
    void setL(double l)
    {
        m_L = l;
    }
    //获取长
    double getL()
    {
        return m_L;
    }
    //设置宽
    void setW(double w)
    {
        m_W = w;
    }
    //获取宽
    double getW()
    {
        return m_W;
    }
    //设置高
    void setH(double h)
    {
        m_H = h;
    }
    //获取高
    double getH()
    {
        return m_H;
    }
    //获取立方体面积
    double calculateS()
    {
        S = 2 * (m_H * m_L + m_H * m_W + m_L * m_W);
        return S;
    }
    //获取立方体体积
    double calculateV()
    {
        V = m_L * m_W * m_H;
        return V ;
    }

    //利用成员函数来判断两个立方体是否相等
    bool isSameClass(Cube &cube)
    {
        if(cube.getL()==m_L &&cube.getW()==m_W &&cube.getH()==m_H)
    {
        return true;
    }
    else
    {
        return false;
    }
    }
    private:
        //设置Cube1的属性
        double m_L;     //长
        double m_W;     //宽
        double m_H;     //高
        double S;
        double V;
};

//利用全局函数来判断两个立方体是否相等
bool isSame(Cube &cube1,Cube &cube2)
{
    if(cube1.getL()==cube2.getL() &&cube1.getW()==cube2.getW() &&cube1.getH()==cube2.getH())
    {
        return true;
    }
    else
    {
        return false;
    }
}

int main()
{
    Cube cube1;
    cube1.setL(10);
    cube1.setW(10);
    cube1.setH(10);

    cout<<"cube1的面积为："<<cube1.calculateS()<<endl;
    cout<<"cube1的体积为："<<cube1.calculateV()<<endl;

    Cube cube2;
    cube2.setL(20);
    cube2.setW(30);
    cube2.setH(10);

    //利用全局函数判断
    bool ref =isSame(cube1,cube2);
    if(ref)
    {
        cout<<"全局函数判断：cube1 与 cube2 是一样的"<<endl;
    }
    else
    {
        cout<<"全局函数判断：cube1 与 cube2 是不一样的"<<endl;
    }

    //利用成员函数判断
    ref = cube1.isSameClass(cube2);
    if(ref)
    {
        cout<<"成员函数判断：cube1 与 cube2 是一样的"<<endl;
    }
    else
    {
        cout<<"成员函数判断：cube1 与 cube2 是不一样的"<<endl;
    }
    system("pause");
    return 0;
}