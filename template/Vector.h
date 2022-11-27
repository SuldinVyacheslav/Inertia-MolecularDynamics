#include <iostream>

#pragma once

class Vector
{
public:
    Vector();
    Vector(double x, double y, double z);
    double x, y, z;
    Vector operator+(Vector v);
    Vector operator-(Vector v);
    Vector operator*(double l);
    Vector operator/(double l);
    Vector& operator+=(Vector v);
    Vector& operator-();
    void print();
    Vector normalize();
    double length();
};

double distance(Vector v, Vector u);