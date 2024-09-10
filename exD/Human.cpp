#include "Human.h"
#include <cstring>
#include <iostream>

// Constructor
Human::Human(const char* name, double x, double y){
    location.set_x(x);
    location.set_y(y);

    this->name = new char[strlen(name) + 1];
    strcpy(this->name, name);
}

// Destructor
Human::~Human(){
    delete[] name;
}

// Getters
const char* Human::get_name() const{
    return name;
}

Point Human::get_point() const{
    return location;
}

// Setter
void Human::set_name(const char* name) {
    // Need to delete the memory for the old name to prevent memory leak.
    delete[] this->name;

    this->name = new char[strlen(name) + 1];
    strcpy(this->name, name);
}

// Display
void Human::display() const{                      
    cout << "Human Name: " << name << "\nHuman Location: "
    << location.get_x() << " ,"
    << location.get_y() << ".\n" << endl;
}