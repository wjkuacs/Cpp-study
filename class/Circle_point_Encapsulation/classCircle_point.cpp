#include<bits/stdc++.h>
#include "point.h"
#include "circle.h"
using namespace std;

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