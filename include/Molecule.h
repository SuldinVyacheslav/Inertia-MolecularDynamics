// Copyright 2022 Suldin Vyacheslav

#ifndef INCLUDE_MOLECULE_H_
#define INCLUDE_MOLECULE_H_

#include <math.h>

#include <iostream>

#include "Constants.h"
#include "Vector.h"

class Delta {
 public:
  Delta();
  Delta(Vector prev, Vector cur);
  Vector prev;
  Vector cur;
  Vector delta();
};

class Molecule {
 public:
  Molecule(Vector coor, Vector vel);
  void base();
  void semi_step();
  void verlet();
  void periodic();
  void set_iner(const Vector &inertia_force);
  Delta coordinates;
  Vector velocity;
  Delta force;
  Delta iner_force;
  double mass;
  double radius;
};

#endif  // INCLUDE_MOLECULE_H_
