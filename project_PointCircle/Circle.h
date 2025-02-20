//Circle.h
#ifndef CIRCLE_H
#define CIRCLE_H

#include "Point.h"

class Circle {
public:
    Point center;
    int radius;

    Circle(Point _center,int _radius);
    std::string relationToPoint(const Point& p) const;
};

#endif // CIRCLE_H