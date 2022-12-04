#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "Constants.h"
#include "Vector.h"

class Delta {
public:
  Delta(Vector prev, Vector cur);

  Vector prev;

  Vector cur;

  Vector delta();
};

class Molecule {
public:
  Molecule(Vector coor, Vector vel);

  void base();
  void semiStep();
  void verlet();

  void periodic();
  void collide(Molecule &with);

  Delta coordinates;
  Vector velocity;

  Delta force;

  double mass;

  double radius;
};
