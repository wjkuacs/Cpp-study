//Circle.cpp
#include "Circle.h"
#include <cmath>
#include <string>

Circle::Circle(Point _center,int _radius) : center(_center),radius(_radius) {}

std::string Circle::relationToPoint(const Point& p) const{
    int dx = p.x - center.x;
    int dy = p.y - center.y;
    int distanceSquared = dx*dx + dy*dy;
    int radiusSquared = radius*radius;

    if (distanceSquared < radiusSquared){
        return "inside";
    }
    else if (distanceSquared == radiusSquared){
        return "on the boundary";
    }
    else {
        return "outside";
    }
}