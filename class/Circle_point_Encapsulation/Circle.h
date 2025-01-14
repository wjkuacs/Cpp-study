#pragma once
#include<iostream>
#include "point.h"
using namespace std;

//圆类
class Circle
{
    public:
        //设置半径
        void setR(double r);
        //获取半径
        double getR();
        //设置圆心
        void setCenter(Point center);
        //获取圆心
        Point getCenter();
    private:
        double m_R;        //半径

        Point m_Center;     //圆心
};
