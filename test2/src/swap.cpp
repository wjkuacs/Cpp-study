#include "swap.h"

void swap::run(){
    int temp = _a;
    _a = _b;
    _b = temp;
}

void swap::printInfo(){
    std::cout << "a: " << _a << std::endl; 
    std::cout <<" b: " << _b << std::endl;
}