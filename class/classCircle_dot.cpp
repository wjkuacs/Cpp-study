#include<bits/stdc++.h>
#include<gr.h>
using namespace std;
//圆周率
const double PI = 3.14;

//class 代表设计一个类，后面紧跟着的就是类的名称
//定义一个点类，一个圆类，并判断圆与点的位置关系

//点类
class Point 
{
    public:
        //设置X
            void setX(double x)
            {
                m_X = x;
            }
        //获取X
            double getX()
            {
                return m_X;
            }
            //设置Y
            void setY(double y)
            {
                m_Y = y;
            }
        //获取Y
            double getY()
            {
                return m_Y;
            }
    private:
        double m_X;

        double m_Y;
};

//圆类
class Circle
{
    public:
        //设置半径
        void setR(double r)
        {
            m_R = r;
        }
        //获取半径
        double getR()
        {
            return m_R;
        }
        //设置圆心
        void setCenter(Point center)
        {
            m_Center = center;
        }
        //获取圆心
        Point getCenter()
        {
            return m_Center;
        }
    private:
        double m_R;        //半径

        Point m_Center;     //圆心
};

//判断点和圆的关系
void isInCircle(Circle &circle,Point &p)
{
    //计算两点之间距离的平方
    double distance;
    distance = pow(circle.getCenter().getY() - p.getY(),2) + pow(circle.getCenter().getX() - p.getX(),2);
    //计算半径的平方
    double r_distance;
    r_distance = pow(circle.getR(),2);
    //判断关系
    if (r_distance == distance)
    {
        cout<<"点在圆上"<<endl;
    }
    else if (r_distance >distance)
    {
        cout<<"点在圆内"<<endl;
    }
    else
    {
        cout<<"点在圆外"<<endl;
    }
}


int main()
{
    //创建圆
        Circle circle;
        circle.setR(10);
        Point center;
        center.setX(10);
        center.setY(0);
        circle.setCenter(center);

    //创建点
        Point point;
        point.setX(10.0);
        point.setY(9);
    
    //判断关系
        isInCircle(circle,point);

    system("pause");
    return 0;
}