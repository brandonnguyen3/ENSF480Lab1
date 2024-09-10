#ifndef HUMAN_H
#define HUMAN_H
#include "Point.h"

class Human{
private:
    Point location;
    char* name;
public:
    Human(const char* name = "", double x = 0, double y = 0);

    // Destructor is needed to prevent memory leaks.
    ~Human();

    // Getters
    const char* get_name() const; // Adding const keyword at the start since it's a pointer.
    Point get_point() const;
    
    // Setter
    void set_name(const char* name);

    // Display
    void display() const;
};

#endif