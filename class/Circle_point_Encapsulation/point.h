#pragma once
#include<iostream>
using namespace std;

//点类
class Point 
{
    public:
        //设置X
            void setX(double x);
        //获取X
            double getX();
            //设置Y
            void setY(double y);
        //获取Y
            double getY();
    private:
        double m_X;

        double m_Y;
};