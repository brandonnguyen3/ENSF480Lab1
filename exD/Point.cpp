#include "point.h"

// Constructor
Point::Point(double a, double b){
    x = a;
    y = b;
}

// Getters and Setters
double Point::get_x() const{
    return x;
}

double Point::get_y() const{
    return y;
}

void Point::set_x(double a){
    x = a;
}

void Point::set_y(double b){
    y = b;
}

