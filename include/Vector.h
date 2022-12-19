// Copyright 2022 Suldin Vyacheslav
#ifndef INCLUDE_VECTOR_H_
#define INCLUDE_VECTOR_H_

class Vector {
public:
  Vector();
  Vector(double x, double y, double z);
  double x, y, z;
  Vector operator+(Vector v);
  Vector operator-(Vector v);
  Vector operator*(double l) const;
  Vector operator|(Vector v);
  Vector operator/(double l);
  Vector &operator+=(Vector v);
  Vector &operator-();
  void print(char *name);
  Vector normalize();
  double length();
};

double distance(Vector v, Vector u);

Vector null();

#endif // INCLUDE_VECTOR_H_
