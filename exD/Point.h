#ifndef POINT_H
#define POINT_H

class Point{
private:
    double x;
    double y;
public:
    Point(double a = 0, double b = 0);

    // Getters with const keyword to prevent changing values
    double get_x() const;
    double get_y() const;

    // Setters
    void set_x(double a);
    void set_y(double a);
};

#endif