// Copyright 2022 Suldin Vyacheslav

#include "Vector.h"
#include "Constants.h"
#include <iostream>
#include <math.h>

Vector::Vector() {}
Vector::Vector(double x, double y, double z) : x(x), y(y), z(z) {}
double x, y, z;
Vector Vector::operator+(Vector v) {
  return Vector(this->x + v.x, this->y + v.y, this->z + v.z);
}
Vector Vector::operator-(Vector v) { return *this + (-v); }
Vector Vector::operator*(double l) {
  return Vector(this->x * l, this->y * l, this->z * l);
}
Vector Vector::operator/(double l) { return *this * (1 / l); }
Vector &Vector::operator+=(Vector v) {
  x += v.x;
  y += v.y;
  z += v.z;
  return *this;
}
Vector &Vector::operator-() {
  x = -x;
  y = -y;
  z = -z;
  return *this;
}
Vector Vector::operator|(Vector v) {
  return Vector(this->y * v.z - this->z * v.y, this->z * v.x - this->x * v.z,
                this->x * v.y - this->y * v.x);
}
void Vector::print(char name[]) {
  std::cout << name << ": " << x << " " << y << " " << z << "\n";
}
Vector Vector::normalize() {
  double len = this->length();
  return Vector(this->x / len, this->y / len, this->z / len);
}
double Vector::length() {
  return sqrt(pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2));
}
Vector null() { return Vector(0, 0, 0); }
double distance(Vector v, Vector u) {
  return sqrt(pow((v.x - u.x), 2) + pow((v.y - u.y), 2) + pow((v.z - u.z), 2));
}
