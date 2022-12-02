#include <iostream>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#include "Vector.h"
#include "Constants.h"


class Delta
{
public:
    Delta(Vector prev, Vector cur);

    Vector prev;

    Vector cur;

    Vector delta();
};

class Molecule
{
public:
    Molecule(Vector coor, Vector vel);

    void base();
    void semiStep();
    void verlet();

    void periodic();
    void collide(Molecule &with);
    
    Delta coordinates;

    Delta force;

    Vector velocity;

    double mass = ARGON_MASS;

    double radius = ARGON_RADIUS;
};

