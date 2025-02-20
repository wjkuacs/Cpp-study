//main.cpp
#include <iostream>
#include "Circle.h"
#include "Point.h"

int main(){
    Point center(0, 0);
    Circle c(center, 5);

    Point p1(2, 3);
    Point p2(-2, -3);
    Point p3(0, 5);

    std::cout << "Point p1 is " << c.relationToPoint(p1) << " the circle." << std::endl;
    std::cout << "Point p2 is " << c.relationToPoint(p2) << " the circle." << std::endl;
    std::cout << "Point p3 is " << c.relationToPoint(p3) << " the circle." << std::endl;

    return 0;
}